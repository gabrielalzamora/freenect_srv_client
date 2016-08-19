

#include "mainwindow.h"
#include "ui_mainwindow.h"

#define W 640
#define H 480
#define SRVKPORT 10003
#define DEPTHPORT 10004
#define VIDEOPORT 10005
#define THREEPORT 10006
#define TWOPORT 10007
#define BARRIDOPORT 10008
#define ACCELPORT 10009

/*!
 * \class MainWindow
 *
 */

/*!
 * \brief constructor
 *
 * MainWindow constructor starts sockets and graphics
 * objects to show data on gui and inherit ui class
 * ( in mainwindow.ui ) that contain buttons, menus,
 *  text edit... to interact.
 * ui->tab_2 is programmed in Data class
 * \param parent
 * not used
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connectedServer = 0;
    connectedVideo = 0;
    skt_srvK = new QTcpSocket(this);
    connectedServer = 0;

    skt_video = new QTcpSocket(this);
    connectedVideo = 0;
    sizeVideo = 0;
    sceneVideo = new QGraphicsScene(this);
    ui->gvVideo->setScene(sceneVideo);

    skt_depth = new QTcpSocket(this);
    connectedDepth = 0;
    sizeDepth = 0;
    sceneDepth = new QGraphicsScene(this);
    ui->gvDepth->setScene(sceneDepth);
    //3D
    //2D
    skt_barrido = new QTcpSocket(this);
    connectedBarrido = 0;
    sizeBarrido = 0;
    sceneBarrido = new QGraphicsScene(this);
    ui->gvBarrido->setScene(sceneBarrido);
    barridoBuf.resize(360);
    ellipseVector.reserve(360);
    ellipseVector.resize(0);
    ellipse = NULL;

    connect(ui->lineEdit,SIGNAL(editingFinished()),this,SLOT(setHost()));
//    setHost();///----------------------------DEBUG

    connect(ui->pbGo,SIGNAL(released()),this,SLOT(initConnection()));
    connect(ui->pbStop,SIGNAL(released()),this,SLOT(closeConnection()));

    connect(ui->tab_2,SIGNAL(dataChanged()),this,SLOT(dataChanged()));
    connect(ui->tab_2,SIGNAL(ledOptionChanged()),this,SLOT(dataChanged()));

    connect(ui->pbVideo,SIGNAL(released()),this,SLOT(initVideo()));
    connect(skt_video,SIGNAL(readyRead()),this,SLOT(readDataVideo()));
    connect(ui->pbDepth,SIGNAL(released()),this,SLOT(initDepth()));
    connect(skt_depth,SIGNAL(readyRead()),this,SLOT(readDataDepth()));
    //3D
    //2D
    connect(ui->pbBarrido,SIGNAL(released()),this,SLOT(initBarrido()));
    connect(skt_barrido,SIGNAL(readyRead()),this,SLOT(readDataBarrido()));

    barridoAxes();
}
/*!
 * \brief destructor
 * to free memory and close properly
 */
MainWindow::~MainWindow()
{
    delete ui;
    delete skt_srvK;
    delete skt_video;
    delete skt_depth;
    //...
}

/*!
 * \brief auxiliary function to read host written by user in GUI QLineEdit
 */
void MainWindow::setHost()
{
//    ui->lineEdit->setText("192.168.1.34");///-----------------DEBUG
//    ui->lineEdit->setText("192.168.0.157");///-----------------DEBUG
//    ui->lineEdit->setText("127.0.0.1");///-----------------DEBUG
    hostAddr = QHostAddress(ui->lineEdit->text());
    ui->textBrowser->setText("connect to server ip:");
    ui->textBrowser->append(ui->lineEdit->text());
    ui->pbGo->setEnabled(true);
}

/*!
 * \brief send new srvKinect to server
 */
void MainWindow::dataChanged()
{
    //qDebug("MainClient::dataChanged");
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out << ui->tab_2->m_srvK.m_fAngulo;
    out << ui->tab_2->m_srvK.m_iAnguloKinect;
    out << ui->tab_2->m_srvK.m_fAltura;
    out << ui->tab_2->m_srvK.m_fYMin;
    out << ui->tab_2->m_srvK.m_fYMax;
    out << ui->tab_2->m_srvK.m_fZMax;
    out << ui->tab_2->m_srvK.m_ulRefresco3D;
    out << ui->tab_2->m_srvK.m_usModulo3D;
    out << ui->tab_2->m_srvK.m_bEnvio3D;
    out << ui->tab_2->m_srvK.m_bEnvio2D;
    out << ui->tab_2->m_srvK.m_bEnvioBarrido;
    out << ui->tab_2->m_srvK.m_bCompress3D;
    out << ui->tab_2->m_srvK.m_iBarridoEcu;
    out << ui->tab_2->m_srvK.m_iBarridoYMin;
    out << ui->tab_2->m_srvK.m_iBarridoYMax;
    out << ui->tab_2->m_srvK.m_ulRefrescoDepth;
    out << ui->tab_2->m_srvK.m_bEnvioDepth;
    out << ui->tab_2->m_srvK.m_bCompressDepth;
    out << ui->tab_2->m_srvK.m_ulRefrescoColor;
    out << ui->tab_2->m_srvK.m_bEnvioColor;
    out << ui->tab_2->m_srvK.m_bCompressColor;
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_srvK->write(buff);
    //qDebug("  init tamaño enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG
}

/*!
 * \brief connect to server and srvKinect update comm
 */
void MainWindow::initConnection()
{
    //qDebug("MainClient::initConnection");
    QString msg;
    msg = "Unable to connect to server\ncheck server ip\n";

    skt_srvK->connectToHost(hostAddr,SRVKPORT);
    if( !skt_srvK->waitForConnected(3000) ){
        msg.append(skt_srvK->errorString());
        ui->textBrowser->setText(msg);
        qDebug("  client NOT connected connectedServer = %d",connectedServer);
        return;
    }
    ui->pbStop->setEnabled(true);//let's activate stop button
    ui->pbGo->setEnabled(false);
    connectedServer = 1;
    ui->textBrowser->append("  client connected to server");
    dataChanged();
}
/*!
 * \brief disconnect from server all sockets & close
 */
void MainWindow::closeConnection()
{
    qDebug("MainClient::closeConnection");
    skt_srvK->disconnectFromHost();
    connectedServer = 0;
    if(connectedVideo){///---------recuerda desconectar lo demás cuando esté-------DEBUG
        finalizeVideo();
    }
    if(connectedDepth){
        finalizeDepth();
    }
    //...

    ui->pbGo->setEnabled(true);
    ui->pbStop->setEnabled(false);
    //close();
}

void MainWindow::socketErrorVideo()
{

}

/*!
 * \brief start/stop video connection to server
 *
 * clicked twice stops video
 */
void MainWindow::initVideo()
{
    qDebug("MainClient::initVideo");
    qDebug("  connectedVideo = %i",connectedVideo);
    if( connectedVideo ){//second click disconnects
        finalizeVideo();
        ui->textBrowser->append("- video closed ");
        return;
    }else{
        skt_video->connectToHost(hostAddr,VIDEOPORT);
        if( !skt_video->waitForConnected(3000) ){
            ui->textBrowser->setText(skt_video->errorString());
            qDebug("  client VIDEO NOT connected = %d",connectedVideo);
            return;
        }
        //connect(skt_video,SIGNAL(readyRead()),this,SLOT(readDataVideo()));
        connectedVideo = 1;
        ui->textBrowser->append("- video connected");
        qDebug("  connectedVideo = %i",connectedVideo);
    }
    //---------------------------request 1st image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_video->write(buff);
    qDebug() << buff;
}
/*!
 * \brief stop video connection to server
 */
void MainWindow::finalizeVideo()
{
    qDebug("MainClient::finalizeVideo");
    qDebug("  connectedVideo = %i",connectedVideo);
    connectedVideo = 0;
    //---------------------------request STOP server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(0);//tell 0 to server = stop
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    //qDebug("  tamaño video antes enviado: %lu", (buff.size()-sizeof(quint64)));//DEBUG
    skt_video->write(buff);//send 0 to server

    skt_video->disconnectFromHost();
    //connectedVideo = 0;
    qDebug("  connectedVideo = %i",connectedVideo);
    qDebug() << buff;
}
/*!
 * \brief read video data and show on gui
 */
void MainWindow::readDataVideo()
{
    //qDebug("MainClient::readDataVideo");
    QDataStream ioStream(skt_video);
    ioStream.setVersion(QDataStream::Qt_5_0);

    if(sizeVideo == 0){
        if(skt_video->bytesAvailable() < (int)sizeof(quint64))
            return;//wait till sizeVideo completed-----or-------return
        ioStream >> sizeVideo;
    }
    if(skt_video->bytesAvailable() < (sizeVideo-sizeof(quint64)))
        return;//wait till all image data received

    QImage image;
    ioStream >> image;

    //-----------------------------------show image
    sceneVideo->addPixmap(QPixmap::fromImage(image).scaled(320,240,Qt::KeepAspectRatio));
    ui->gvVideo->show();

    //---------------------------request next image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//escribimos tamaño buf al principio
    skt_video->write(buff);//enviamos

    sizeVideo = 0;//to allow get next img sizeVideo
}

/*!
 * \brief start/stop depth connection to server
 *
 * clicked twice stops depth
 */
void MainWindow::initDepth()
{
    qDebug("MainClient::initDepth");
    if( connectedDepth ){//second click disconnects
        finalizeDepth();
        ui->textBrowser->append("- depth closed ");
        return;
    }else{
        skt_depth->connectToHost(hostAddr,DEPTHPORT);
        if( !skt_depth->waitForConnected(3000) ){
            ui->textBrowser->setText(skt_depth->errorString());
            qDebug("  client DEPTH NOT connected = %d",connectedDepth);
            return;
        }
        //connect(skt_depth,SIGNAL(readyRead()),this,SLOT(readDataDepth()));
        connectedDepth = 1;
        ui->textBrowser->append("- depth connected");
    }
    //---------------------------request 1st image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_depth->write(buff);
    qDebug("  tamaño depth antes enviado: %lu", (buff.size()-sizeof(quint64)));//DEBUG
}
/*!
 * \brief stop depth connection to server
 */
void MainWindow::finalizeDepth()
{
    qDebug("MainClient::finalizeDepth");
    //---------------------------request STOP server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(0);//tell 0 to server = stop
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_depth->write(buff);//send 0 to server
    //qDebug("  tamaño depth antes enviado: %lu", (buff.size()-sizeof(quint64)));//DEBUG

    skt_depth->disconnectFromHost();
    connectedDepth = 0;
}
/*!
 * \brief read depth data and show on gui
 */
void MainWindow::readDataDepth()
{
   // qDebug("MainClient::readDataDepth");
    QDataStream ioStream(skt_depth);
    ioStream.setVersion(QDataStream::Qt_5_0);

    if(sizeDepth == 0){
        if(skt_depth->bytesAvailable() < (int)sizeof(quint64))
            return;//wait till sizeDepth completed-----or-------return
        ioStream >> sizeDepth;
    }
    if(skt_depth->bytesAvailable() < (sizeDepth-sizeof(quint64)))
        return;//wait till all image data received

    QImage image;
    ioStream >> image;

    //-----------------------------------show depth
    sceneDepth->addPixmap(QPixmap::fromImage(image).scaled(320,240,Qt::KeepAspectRatio));
    ui->gvDepth->show();

    //---------------------------request next image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//escribimos tamaño buf al principio
    skt_depth->write(buff);//enviamos

    sizeDepth = 0;//to allow get next img sizeDepth
}

/*!
 * \brief MainWindow::barreInit
 * draw axes on sceneBarre to show on gvBarrido.
 */
void MainWindow::barridoAxes()
{
    ui->gvBarrido->setBackgroundBrush(QColor(200,240,240,255));//light blue
    sceneBarrido->setBackgroundBrush(QColor(200,240,240,255));
    QPen ejesPen = QPen(QColor(255,0,0,255));//red color
    ejesPen.setWidth(2);
    QLine ejex = QLine(5,230,315,230);
    QLine ejey = QLine(160,230,160,5);
    //falta pintar escala cada ~500mm
    sceneBarrido->addLine(ejex,ejesPen);
    sceneBarrido->addLine(ejey,ejesPen);
}
/*!
 * \brief start/stop barrido connection to server
 *
 * clicked twice stops barrido
 */
void MainWindow::initBarrido()
{
    qDebug("MainClient::initBarrido");
    if( connectedBarrido ){//second click disconnects
        finalizeBarrido();
        ui->textBrowser->append("- barrido closed ");
        return;
    }else{
        skt_barrido->connectToHost(hostAddr,BARRIDOPORT);
        if( !skt_barrido->waitForConnected(3000) ){
            ui->textBrowser->setText(skt_barrido->errorString());
            qDebug("  client DEPTH NOT connected = %d",connectedDepth);
            return;
        }
        //connect(skt_barrido,SIGNAL(readyRead()),this,SLOT(readDataBarrido()));
        connectedBarrido = 1;
        ui->textBrowser->append("- barrido connected");
    }
    //---------------------------request 1st data batch to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_barrido->write(buff);
    qDebug("  tamaño antes enviado: %lu", (buff.size()-sizeof(quint64)));//DEBUG
}
/*!
 * \brief stop barrido connection to server
 */
void MainWindow::finalizeBarrido()
{
    qDebug("MainClient::finalizeBarrido");
    //---------------------------tell STOP to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(0);//tell server 0, stop
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    qDebug("  tamaño antes enviado: %lu", (buff.size()-sizeof(quint64)));///---DEBUG
    skt_barrido->write(buff);//send 0 to server
    //qDebug("  tamaño barrido antes enviado: %lu", (buff.size()-sizeof(quint64)));//DEBUG
    skt_barrido->disconnectFromHost();
    connectedBarrido = 0;
}
/*!
 * \brief read barrido data and show on gui
 */
void MainWindow::readDataBarrido()
{
    qDebug("MainClient::readDataBarrido");
    QDataStream in(skt_barrido);
    in.setVersion(QDataStream::Qt_5_0);///---------DEBUG

    if(sizeBarrido == 0){
        if(skt_barrido->bytesAvailable() < (int)sizeof(quint64))
            return;//wait till sizeBarrido completed-----or-------return
        in >> sizeBarrido;
        qDebug("  barrido recibe tamaño %llu",sizeBarrido);
    }
    if(skt_barrido->bytesAvailable() < (sizeBarrido-sizeof(quint64)))
        return;//wait till all data received

//-----------------------------------------------------read & paint barrido
    int x, y, aux(0);
    uint32_t auxBarrido;
    if( ellipseVector.size() != 0 ){//remove previous data
        for(int i=0;i<ellipseVector.size();i++){
            sceneBarrido->removeItem(ellipseVector[i]);
            delete ellipseVector[i];
        }
        ellipseVector.resize(0);
    }
    for(int i=0;i<360;i++){
        in >> auxBarrido;//read incomming data
        barridoBuf[i] = auxBarrido;//store in barrido vector
        qDebug("  compara read %lu con vector %u", auxBarrido, barridoBuf[i]);
        if(barridoBuf[i] == 0) continue;//no data info no plot
        y = (H/2)-((H/2)*barridoBuf[i]/ui->tab_2->m_srvK.m_fZMax);//divide barridoBuf[i] by max distance to fit in screen
        x = (W/2)*(360-i)/360;//make it fit in window W*H
        ellipseVector.push_back(new QGraphicsEllipseItem(x,y,1.0,1.0));
        sceneBarrido->addItem(ellipseVector[aux]);
        aux++;
    }
    ui->gvBarrido->show();
//-------------------------------------------------------paint barrido
    //---------------------------request next image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//escribimos tamaño buf al principio
    skt_barrido->write(buff);//enviamos
    qDebug("  barrido envia tamaño %lu",(buff.size() - sizeof(quint64)));

    sizeBarrido = 0;//to allow get next img sizeDepth
}
