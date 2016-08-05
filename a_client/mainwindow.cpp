

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
 * \brief MainWindow::MainWindow constructor
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
    ui->gviewVideo->setScene(sceneVideo);
    itemVideo = NULL;

    skt_depth = new QTcpSocket(this);
    connectedDepth = 0;
    sizeDepth = 0;
    sceneDepth = new QGraphicsScene(this);
    ui->gviewDepth->setScene(sceneDepth);
    itemDepth = NULL;
    //depthImg = QImage(W,H,QImage::Format_RGB16);

    connect(ui->lineEdit,SIGNAL(editingFinished()),this,SLOT(setHost()));
//    setHost();///----------------------------DEBUG

    connect(ui->pbGo,SIGNAL(released()),this,SLOT(initConnection()));
    connect(ui->pbStop,SIGNAL(released()),this,SLOT(closeConnection()));
//    connect(ui->tab_2,SIGNAL(srvKChanged(srvKinect)),this,SLOT(sendNewSrvK(srvKinect)));
    connect(ui->tab_2,SIGNAL(dataChanged()),this,SLOT(dataChanged()));
    connect(ui->tab_2,SIGNAL(ledOptionChanged()),this,SLOT(dataChanged()));
    connect(ui->pbVideo,SIGNAL(released()),this,SLOT(initVideo()));
    connect(skt_video,SIGNAL(readyRead()),this,SLOT(readDataVideo()));
    connect(skt_depth,SIGNAL(readyRead()),this,SLOT(readDataDepth()));
}
/*!
 * \brief MainWindow::~MainWindow destructor
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
 * \brief MainWindow::setHost
 * auxiliary function to set server host
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
 * \brief MainWindow::dataChanged
 */
void MainWindow::dataChanged()
{
    qDebug("MainClient::dataChanged");

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
    qDebug("  init tamaño enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG
}

/*!
 * \brief MainWindow::initConnection
 * connect to server and srvKinect update comm
 */
void MainWindow::initConnection()
{
    qDebug("MainClient::initConnection");
    QString msg;
    msg = "Unable to connect to server\ncheck server ip\n%s";


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
    qDebug("  client connected = %d",connectedServer);
}

/*!
 * \brief MainWindow::closeConnection
 * disconnect from server all sockets & close
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
 * \brief MainWindow::initVideo
 * start video connection to server
 * clicked twice stops video
 */
void MainWindow::initVideo()
{
    qDebug("MainClient::initVideo");
    if( connectedVideo ){//second click disconnects
        finalizeVideo();
        ui->textBrowser->append("- video cerrado ");
    }else{
        skt_video->connectToHost(hostAddr,VIDEOPORT);
        if( !skt_video->waitForConnected(3000) ){
            ui->textBrowser->setText(skt_video->errorString());
            qDebug("  client VIDEO connected = %d",connectedVideo);
            return;
        }
        connect(skt_video,SIGNAL(readyRead()),this,SLOT(readDataVideo()));
        connectedVideo = 1;
        ui->textBrowser->append("- video connected");
        qDebug("  client VIDEO connected = %d",connectedVideo);
    }
    //---------------------------request 1st image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_video->write(buff);
    qDebug("  init tamaño enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG
}
/*!
 * \brief MainWindow::finalizeVideo
 * stop video connection to server
 */
void MainWindow::finalizeVideo()
{
    qDebug("MainClient::finalizeVideo");
    //---------------------------request STOP server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(0);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));

    qDebug("  tamaño antes enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG

    skt_video->write(buff);//enviamos
    //---------------------------sended image to client
    skt_video->disconnectFromHost();
    connectedVideo = 0;
}
/*!
 * \brief MainWindow::readDataVideo
 * read video data and show on gui
 */
void MainWindow::readDataVideo()
{
    qDebug("MainClient::readDataVideo");

    QDataStream ioStream(skt_video);
    ioStream.setVersion(QDataStream::Qt_5_0);

    if(sizeVideo == 0){
        if(skt_video->bytesAvailable() < (int)sizeof(quint64))
            return;//wait till sizeVideo completed-----or-------return
        ioStream >> sizeVideo;
        qDebug() << "  valor de size: " << sizeVideo << "\n";
    }
    if(skt_video->bytesAvailable() < (sizeVideo-sizeof(quint64)))
        return;//wait till all image data received

    QImage image;
    ioStream >> image;
    //ioStream >> imgVideo;

    //-----------------------------------show image

    sceneVideo->addPixmap(QPixmap::fromImage(image).scaled(320,240,Qt::KeepAspectRatio));
    ui->gviewVideo->show();


    //---------------------------request next image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//escribimos tamaño buf al principio
    skt_video->write(buff);//enviamos

    qDebug("  read tamaño enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG

    sizeVideo = 0;//to allow get next img sizeVideo
}

/*!
 * \brief MainWindow::initDepth
 * start depth connection to server
 * clicked twice stops depth
 */
void MainWindow::initDepth()
{
    qDebug("MainClient::initDepth");
    if( connectedDepth ){//second click disconnects
        finalizeVideo();
        ui->textBrowser->append("- depth cerrado ");
    }else{
        skt_depth->connectToHost(hostAddr,DEPTHPORT);
        if( !skt_depth->waitForConnected(3000) ){
            ui->textBrowser->setText(skt_depth->errorString());
            qDebug("  client VIDEO connected = %d",connectedVideo);
            return;
        }
        connect(skt_depth,SIGNAL(readyRead()),this,SLOT(readDataVideo()));
        connectedDepth = 1;
        ui->textBrowser->append("- depth connected");
        qDebug("  client DEPTH connected = %d",connectedDepth);
    }
    //---------------------------request 1st image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));
    skt_depth->write(buff);
    qDebug("  init depth tamaño enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG
}
/*!
 * \brief MainWindow::finalizeDepth
 * stop depth connection to server
 */
void MainWindow::finalizeDepth()
{
    qDebug("MainClient::finalizeDepth");
    //---------------------------request STOP server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(0);
    out.device()->seek(0);
    out << quint64(buff.size() - sizeof(quint64));

    qDebug("  tamaño antes enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG

    skt_depth->write(buff);//enviamos
    //---------------------------sended image to client
    skt_depth->disconnectFromHost();
    connectedDepth = 0;
}
/*!
 * \brief MainWindow::readDataDepth
 * read depth data and show on gui
 */
void MainWindow::readDataDepth()
{
    qDebug("MainClient::readDataDepth");

    QDataStream ioStream(skt_depth);
    ioStream.setVersion(QDataStream::Qt_5_0);

    if(sizeDepth == 0){
        if(skt_depth->bytesAvailable() < (int)sizeof(quint64))
            return;//wait till sizeDepth completed-----or-------return
        ioStream >> sizeDepth;
        qDebug() << "  valor de size: " << sizeDepth << "\n";
    }
    if(skt_depth->bytesAvailable() < (sizeDepth-sizeof(quint64)))
        return;//wait till all image data received

    QImage image;
    ioStream >> image;

    sceneVideo->addPixmap(QPixmap::fromImage(image).scaled(320,240,Qt::KeepAspectRatio));
    ui->gviewVideo->show();

    //---------------------------request next image to server
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << quint8(1);
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//escribimos tamaño buf al principio
    skt_depth->write(buff);//enviamos

    qDebug("  read tamaño enviado: %u", (buff.size()-sizeof(quint64)));//DEBUG

    sizeDepth = 0;//to allow get next img sizeDepth
}
