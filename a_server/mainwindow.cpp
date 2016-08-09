/*
 * Copyright (c) 2016  Gabriel Alzamora
 * Copyright (c) 2015 The Qt Company Ltd
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */

#include <QNetworkInterface>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apikinect.h"

#define SRVKPORT 10003

/*!
 * \class MainWindow
 * \brief holds all server functionality.
 *
 * Through members that are type Apikinect, AttendClient,
 * Ui_MainWindow (ui), Data (ui->tab_2),FrameGL (ui->glWidget),
 * QTcpServer and Freenect::Freenect manage kinect and client
 * relations.
 * Apikinect allow to handle and comunicate with kinect.
 * Ui_MainWindow (ui) is the graphic interface.
 * Data (ui->tab_2) holds configuration to handle data.
 * FrameGL (ui->glWidget) all related to 3D view.
 * QTcpServer is the server who listen to incoming clients.
 * Freenect::Freenect will hold usb context on kinect communication.
 * Apikinect hold single kinect (device) comunication.
 * AttendClient is generated to attend single client communication.
 */

/*!
 * \brief MainWindow::MainWindow
 * \param parent
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numDevices = freenect.deviceCount();

    init();
    startServer();
    setServerIp();
    putKcombo();
    barridoInit();//paint axes on barrido view

    connect(ui->tab_2,SIGNAL(dataChanged()),this,SLOT(updateKinect()));
    connect(ui->tab_2,SIGNAL(ledOptionChanged()),this,SLOT(updateKinect()));
}
/*!
 * \brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    if(currentDeviceIndex !=-1){
        stoploop();
        stopK(currentDeviceIndex);
    }
    delete sceneVideo;
    delete sceneDepth;
    delete sceneBarre;
    if( imgVideo != NULL ) delete imgVideo;
    if( imgDepth != NULL ) delete imgDepth;
    if( imgBarre != NULL ) delete imgBarre;
    delete ui;
}
/*!
 * \brief MainWindow::videoDataReady
 * draw video image (on ui->gvVideo sceneVideo using data from buf vector)
 * \param buf
 */
void MainWindow::videoDataReady()
{
    if( imgVideo != NULL ) delete imgVideo;
    imgVideo = new QImage(videoBuf.data(),640,480,QImage::Format_RGB888);
    sceneVideo->addPixmap(QPixmap::fromImage(*imgVideo).scaled(320,240,Qt::KeepAspectRatio));
    ui->gvVideo->show();
}
/*!
 * \brief MainWindow::depthDataReady
 * draw depth image (on ui->gvDepth sceneDepth using data from buf vector).
 * \param buf
 */
void MainWindow::depthDataReady()
{
    if( imgDepth != NULL ) delete imgDepth;
    imgDepth = new QImage(640,480,QImage::Format_RGB32);
    unsigned char r,g,b, distaChar;
    for(int x = 0; x < 640; x++){
        for(int y = 0; y < 480; y++){
            int value = depthBuf[(x+y*640)];//value is distance in mm
            distaChar = value/39;//to transform distance to 8bit grey
            r=g=b=distaChar;
            imgDepth->setPixel(x,y,qRgb(r,g,b));// data to fit in 8 bits
        }
    }
    sceneDepth->addPixmap(QPixmap::fromImage(*imgDepth).scaled(320,240,Qt::KeepAspectRatio));
    ui->gvDepth->show();
}
/*!
 * \brief MainWindow::barreDataReady
 * draw barrido (barre) (on ui->gvBarre sceneBarre using
 */
void MainWindow::barridoDataReady()
{
    int x,y;
    int aux(0);
    if( ellipseVector.size() != 0 ){
        for(int i=0;i<ellipseVector.size();i++){
            sceneBarre->removeItem(ellipseVector[i]);
            delete ellipseVector[i];
        }
        ellipseVector.resize(0);
    }
    for(int i=0;i<360;i++){
        if(barridoBuf[i] == 0) continue;//no data info no plot
        y = 235-(235*barridoBuf[i]/ui->tab_2->m_srvK.m_fZMax);//divide barridoBuf[i] by max mesured distance to fit in screen
        x = 320*(360-i)/360;
        ellipseVector.push_back(new QGraphicsEllipseItem(x,y,1.0,1.0));
        sceneBarre->addItem(ellipseVector[aux]);
        aux++;
    }
    ui->gvBarre->show();
}
/*!
 * \brief MainWindow::barreInit
 * draw axes on sceneBarre to show on gvBarre.
 */
void MainWindow::barridoInit()
{
    ui->gvBarre->setBackgroundBrush(QColor(200,240,240,255));//light blue
    sceneBarre->setBackgroundBrush(QColor(200,240,240,255));
    QPen ejesPen = QPen(QColor(255,0,0,255));//red color
    ejesPen.setWidth(2);
    QLine ejex = QLine(5,230,315,230);
    QLine ejey = QLine(160,230,160,5);
    //pinta escala cada ~500mm
    sceneBarre->addLine(ejex,ejesPen);
    sceneBarre->addLine(ejey,ejesPen);
}
/*!
 * \brief MainWindow::updateKinect
 * set current led option and kinect angle on active kinect.
 */
void MainWindow::updateKinect()
{
    if( device != NULL ){
        device->setLed(freenect_led_options(ui->tab_2->ledOption));
        device->setTiltDegrees(double(ui->tab_2->m_srvK.m_iAnguloKinect));
    }
}
/*!
 * \brief MainWindow::updateSrvKinect
 * set srvKinect data sended by client
 * \param sk
 * [in] client current srvKinect
 */
void MainWindow::updateSrvKinect(srvKinect newSrvK)
{
//    qDebug("MainServer::updateKinect");
    ui->tab_2->m_srvK.m_fAngulo = newSrvK.m_fAngulo;
    ui->tab_2->setLimitsLineEAngulo(newSrvK.m_fAngulo);
    ui->tab_2->m_srvK.m_iAnguloKinect = newSrvK.m_iAnguloKinect;
    ui->tab_2->setLimitsLineEAngK(newSrvK.m_iAnguloKinect);
    ui->tab_2->m_srvK.m_fAltura = newSrvK.m_fAltura;
    ui->tab_2->setLimitsLineEAltura(newSrvK.m_fAltura);
    ui->tab_2->m_srvK.m_fYMin = newSrvK.m_fYMin;
    ui->tab_2->setLimitsLineEYmin(newSrvK.m_fYMin);
    ui->tab_2->m_srvK.m_fYMax = newSrvK.m_fYMax;
    ui->tab_2->setLimitsLineEYmax(newSrvK.m_fYMax);
    ui->tab_2->m_srvK.m_fZMax = newSrvK.m_fZMax;
    ui->tab_2->setLimitsLineEZmax(newSrvK.m_fZMax);

    ui->tab_2->m_srvK.m_ulRefresco3D = newSrvK.m_ulRefresco3D;
    ui->tab_2->setPointsSlider(newSrvK.m_ulRefresco3D);
    ui->tab_2->m_srvK.m_usModulo3D = newSrvK.m_usModulo3D;
    ui->tab_2->setPointsSliderM(newSrvK.m_usModulo3D);

    ui->tab_2->m_srvK.m_bEnvio3D = newSrvK.m_bEnvio3D;
    ui->tab_2->setPointsCBenvio3D(newSrvK.m_bEnvio3D);
    ui->tab_2->m_srvK.m_bEnvio2D = newSrvK.m_bEnvio2D;
    ui->tab_2->setPointsCBenvio2(newSrvK.m_bEnvio2D);
    ui->tab_2->m_srvK.m_bEnvioBarrido = newSrvK.m_bEnvioBarrido;
    ui->tab_2->setPointsCBenvioB(newSrvK.m_bEnvioBarrido);
    ui->tab_2->m_srvK.m_bCompress3D = newSrvK.m_bCompress3D;
    ui->tab_2->setPointsCBcomprimido(newSrvK.m_bCompress3D);
    ui->tab_2->m_srvK.m_iBarridoEcu = newSrvK.m_iBarridoEcu;
    ui->tab_2->setPointsLineEEcu(newSrvK.m_iBarridoEcu);
    ui->tab_2->m_srvK.m_iBarridoYMin = newSrvK.m_iBarridoYMin;
    ui->tab_2->setPointsLineEYmin(newSrvK.m_iBarridoYMin);
    ui->tab_2->m_srvK.m_iBarridoYMax = newSrvK.m_iBarridoYMax;
    ui->tab_2->setPointsLineEYmax(newSrvK.m_iBarridoYMax);

    ui->tab_2->m_srvK.m_ulRefrescoDepth = newSrvK.m_ulRefrescoDepth;
    ui->tab_2->setDepthSlider(newSrvK.m_ulRefrescoDepth);
    ui->tab_2->m_srvK.m_bEnvioDepth = newSrvK.m_bEnvioDepth;
    ui->tab_2->setDepthCBenvio(newSrvK.m_bEnvioDepth);
    ui->tab_2->m_srvK.m_bCompressDepth = newSrvK.m_bCompressDepth;
    ui->tab_2->setDepthCBcomprimido(newSrvK.m_bCompressDepth);
    ui->tab_2->m_srvK.m_ulRefrescoColor = newSrvK.m_ulRefrescoColor;
    ui->tab_2->setVideoSlider(newSrvK.m_ulRefrescoColor);
    ui->tab_2->m_srvK.m_bEnvioColor = newSrvK.m_bEnvioColor;
    ui->tab_2->setVideoCBenvio(newSrvK.m_bEnvioColor);
    ui->tab_2->m_srvK.m_bCompressColor = newSrvK.m_bCompressColor;
    ui->tab_2->setVideoCBcomprimido(newSrvK.m_bCompressColor);

    emit updateKinect();
}

/*!
 * \brief MainWindow::init
 * convenience function to initiate members
 */
void MainWindow::init()
{
    //apikinect
    device = NULL;
    currentDeviceIndex = -1;
    flag = false;
    videoBuf.resize(640*480*3);
    depthBuf.resize(640*480);
    p3Buf.reserve(300000);//max number of points
    p3Buf.resize(0);//initially we have none
    p2Buf.reserve(300000);
    p2Buf.resize(0);
    barridoBuf.resize(360);
    accel.resize(3);
    ptrToBuffers.ptrVideoBuf = &videoBuf;
    ptrToBuffers.ptrDepthBuf = &depthBuf;
    ptrToBuffers.ptrP3Buf = &p3Buf;
    ptrToBuffers.ptrP2Buf = &p2Buf;
    ptrToBuffers.ptrBarridoBuf = &barridoBuf;
    ptrToBuffers.ptrAccel = &accel;
    ellipseVector.reserve(360);
    ellipseVector.resize(0);
    sceneVideo = new QGraphicsScene;
    sceneDepth = new QGraphicsScene;
    sceneBarre = new QGraphicsScene;
    imgVideo = NULL;
    imgDepth = NULL;
    imgBarre = NULL;
    ui->gvVideo->setScene(sceneVideo);
    ui->gvDepth->setScene(sceneDepth);
    ui->gvBarre->setScene(sceneBarre);
    timeVector.resize(6);
    //server
    mainServer = new QTcpServer(this);
}
/*!
 * \brief MainWindow::setServerIp
 * write my server ip on gui label
 */
void MainWindow::setServerIp()
{
    QString ip;
    QList<QHostAddress> ipList = QNetworkInterface::allAddresses();
    // use first non-localhost IPv4 address
    for (int i = 0; i < ipList.size(); ++i) {
        if( (ipList.at(i) != QHostAddress::LocalHost) && ipList.at(i).toIPv4Address() ) {
            ip = ipList.at(i).toString();
            break;
        }
    }
    // if none, then use localhost
    if (ip.isEmpty()) ip = QHostAddress(QHostAddress::LocalHost).toString();
    ui->label_ip->setText(ip);
}
/*!
 * \brief MainWindow::putKcombo
 * fill combo list with detected kinect index
 */
void MainWindow::putKcombo()
{
    if( numDevices == 0 ){//num devices 0 => no kinect connected
        ui->combo->addItem("No kinect detected");
        ui->textEdit->setText(" No kinect detected, unable to start");
        ui->textEdit->show();
        ui->pbGo->setEnabled(false);
        ui->pbStop->setEnabled(false);
    }else{
        for( int i = 0; i < numDevices ; i++){
            QString str;
            ui->combo->addItem(str.setNum(i));
        }
        ui->textEdit->setText(" Select kinect in combo box to start\n1-click combo\n2-click device number in combo\n3-click Go");
    }
}

/*!
 * \brief MainWindow::startK
 * init device to handle kinect of indexK
 * \param indexK
 */
void MainWindow::startK(int indexK)
{
    device = &freenect.createDevice<Apikinect>(indexK);
    device->startVideo();
    device->startDepth();
    currentDeviceIndex = indexK;
}
/*!
 * \brief MainWindow::stopK destroy kinect handler
 * \param index index kinect handler index to be destroyed
 */
void MainWindow::stopK(int indexK)
{
    device->stopDepth();
    device->stopVideo();
    freenect.deleteDevice(indexK);
    currentDeviceIndex = -1;
    device = NULL;
}
/*!
 * \brief MainWindow::loop
 * working horse retrieving video & depth info
 * and pouring it to p3Buf (point cloud: 3D+color)
 */
void MainWindow::loop()
{
    flag = 1;
    while( flag ){
        timeVector.resize(0);
        QTime t;

        t.start();//---------------------------------------------time.start
        device->getRGB(videoBuf);
        timeVector.push_back(t.elapsed());//---------------------timeVector[0]
        if( ui->tab_2->m_srvK.m_bEnvioColor ){
            videoDataReady();//paint video on gvVideo
        }

        t.start();//---------------------------------------------time.start
        device->getDepth(depthBuf);
        timeVector.push_back(t.elapsed());//---------------------timeVector[1]
        if( ui->tab_2->m_srvK.m_bEnvioDepth )
            depthDataReady();//paint depth on gvDepth

//        qApp->processEvents();//stay responsive to button click

        if( ui->tab_2->m_srvK.m_bEnvio3D && ui->tab_2->m_srvK.m_bEnvioBarrido){//all buffers
            t.start();//---------------------------------------------time.start
            device->getAll(p3Buf,barridoBuf);
            timeVector.push_back(t.elapsed());//---------------------timeVector[2]

            t.start();//---------------------------------------------time.start
            ui->glWidget->setpCloud(p3Buf,p3Buf.size());///---DEBUG remove p3Buf.size()
            ui->glWidget->repaint();//paint points cloud on glwidget
            timeVector.push_back(t.elapsed());//---------------------timeVector[3]
            t.start();//---------------------------------------------time.start
            barridoDataReady();//paint Barrido (barre)
            timeVector.push_back(t.elapsed());//---------------------timeVector[4]
        }

        printTimeVector(timeVector);

        if(!(ui->tab_2->m_srvK.m_bEnvio3D) && ui->tab_2->m_srvK.m_bEnvioBarrido){//only swept ("barrido")
            t.start();//---------------------------------------------time.start
            device->getBarrido(barridoBuf);
            timeVector.push_back(t.elapsed());//---------------------timeVector[5]
            barridoDataReady();//paint Barrido (barre)
            qDebug("NO DEBERÍA ESTAR EN SOLO BARRE");
        }else if(ui->tab_2->m_srvK.m_bEnvio2D){
            t.start();//---------------------------------------------time.start
            device->get2(p2Buf);//to control 2D calc
            timeVector.push_back(t.elapsed());//---------------------timeVector[6]
            qDebug("NO DEBERÍA ESTAR EN SOLO 2D");
        }

        //printTimeVector(timeVector);

        qApp->processEvents();//stay responsive to button click
    }
}
/*!
 * \brief MainWindow::stoploop
 * convinience funtion to stop loop seting wile(flag)=0
 */
void MainWindow::stoploop()
{
    flag = 0;
}
/*!
 * \brief MainWindow::printTimeVector
 * aux function to control time spend in calculus or painting
 * \param timeV
 * vector to save data
 */
void MainWindow::printTimeVector(std::vector<int> &timeV)
{
    QString str,aux;
    str = "get video = ";
    aux.setNum(timeV[0]);
    str.append(aux);
    aux = " \nget depth = ";
    str.append(aux);
    aux.setNum(timeV[1]);
    str.append(aux);
    aux = " \nget buffer = ";
    str.append(aux);
    aux.setNum(timeV[2]);
    str.append(aux);
    aux = "\npinta3D = ";
    str.append(aux);
    aux.setNum(timeV[3]);
    str.append(aux);
    aux = "\npintaB = ";
    str.append(aux);
    aux.setNum(timeV[4]);
    str.append(aux);
    ui->textEdit->setText(str);
}

void MainWindow::getAll()///-------probar exhaustívamente-------------DEBUG
{
    point3c p3;
    RGBQ color;///-----------------------------------------------------------CORREGIR
    p3Buf.resize(1);///------------------------------resize(0)--------DEBUG
    for(int i=0;i<360;i++) barridoBuf[i]=0;

    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    //------------------------------------------------------time pre buffers
    for (int i = 0; i < 480*640; ++i)
    {
        // Convert from image plane coordinates to world coordinates
        if( (p3.z = depthBuf[i]) != 0  ){                  // Z = d
            p3.x = (i%640-(640-1)/2.f)*depthBuf[i]/f;      // X = (x - cx) * d / fx
            p3.y = (i/640 - (480-1)/2.f) * depthBuf[i] / f;// Y = (y - cy) * d / fy
            color.rgbRed = videoBuf[3*i+0];    // R
            color.rgbGreen = videoBuf[3*i+1];  // G
            color.rgbBlue = videoBuf[3*i+2];   // B
            color.rgbReserved = 0;
            p3.color = color;
            p3Buf.push_back(p3);//MainWindow::p3Buf
//time pre barrer
            int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
            uint32_t length = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm
            if( barridoBuf[index]==0 || barridoBuf[index]>length)
                barridoBuf[index]=length;
//time post barrer  difference*numpoints = time barrer
        }
    }//----------------------------------------------------------time post buffers
}

void MainWindow::get3D()
{
    point3c p3;
    RGBQ color;

    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
//time pre buffers
    for (int i = 0; i < 480*640; ++i)///-----------------------------------CORREGIR
    {
        // Convert from image plane coordinates to world coordinates
        if( (p3.z = depthBuf[i]) != 0  ){                  // Z = d
            p3.x = (i%640-(640-1)/2.f)*depthBuf[i]/f;      // X = (x - cx) * d / fx
            p3.y = (i/640 - (480-1)/2.f) * depthBuf[i] / f;// Y = (y - cy) * d / fy
            color.rgbRed = videoBuf[3*i+0];    // R
            color.rgbGreen = videoBuf[3*i+1];  // G
            color.rgbBlue = videoBuf[3*i+2];   // B
            color.rgbReserved = 0;
            p3.color = color;
            p3Buf.push_back(p3);//MainWindow::p3Buf
        }
    }
//time post buffers
}

void MainWindow::get2D()
{
    point2 p2;
    p2Buf.resize(1);///--------------------------------------------------CORREGIR
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    //------------------------------------------------------time pre buffers
    for (int i = 0; i < 480*640; ++i)
    {
        // Convert from image plane coordinates to world coordinates
        if( (p2.z = depthBuf[i]) != 0  ){                  // Z = d
            p2.x = (i%640-(640-1)/2.f)*depthBuf[i]/f;      // X = (x - cx) * d / fx
            p2Buf.push_back(p2);//MainWindow::p2Buf
        }
    }//----------------------------------------------------------time post buffers
}

void MainWindow::getBarrido()
{
    point3c p3;///------------------------------------------------------CORREGIR
    for(int i=0;i<360;i++) barridoBuf[i]=0;
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    //------------------------------------------------------time pre buffers
    for (int i = 0; i < 480*640; ++i)
    {
        if( (p3.z = depthBuf[i]) != 0  ){                  // Z = d
            p3.x = (i%640-(640-1)/2.f)*depthBuf[i]/f;      // X = (x - cx) * d / fx
            int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
            uint32_t length = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm
            if( barridoBuf[index]==0 || barridoBuf[index]>length)
                barridoBuf[index]=length;
        }
    }//----------------------------------------------------------time post buffers
}

/*!
 * \brief MainWindow::on_pbGo_clicked start selected kinect data flow
 */
void MainWindow::on_pbGo_clicked()///--------------------------DEBUG
{
    //ui->pbGo->setEnabled(false);
    int index = ui->combo->currentText().toInt();
    //startK(index);
    currentDeviceIndex = index;
    //loop();
}
/*!
 * \brief MainWindow::on_pbStop_clicked stop kinect data flow and delete handler
 */
void MainWindow::on_pbStop_clicked()
{
    ui->pbStop->setEnabled(false);
    stoploop();
    int index = ui->combo->currentText().toInt();
    if( index == currentDeviceIndex ){
        stopK(index);
    }
}
/*!
 * \brief MainWindow::on_combo_activated
 * when combo item selected -> buttons activated
 * \param index
 */
void MainWindow::on_combo_activated(const QString &arg1)
{
    int index = arg1.toInt();
    if ( index < 0 || index >= numDevices ){
        ui->textEdit->setText(" ERROR kinect index out of bounds. Restart.");
        return;
    }
    if( currentDeviceIndex == -1 ){
        ui->pbGo->setEnabled(true);
        ui->pbStop->setEnabled(false);
    }else if( currentDeviceIndex == index ){
        ui->pbGo->setEnabled(false);
        ui->pbStop->setEnabled(true);
    }else{
        ui->textEdit->setText(" First stop running kinect, then start the other.");
    }
}

/*!
 * \brief MainWindow::startServer
 * start QTcpServer listening at port 9999 and connect to attendNewClient()
 */
void MainWindow::startServer()
{
    if( !mainServer->listen(QHostAddress::Any,SRVKPORT) ){
        ui->textEdit->setText(mainServer->errorString());
        mainServer->close();
        return;
    }

    connect(mainServer, SIGNAL(newConnection()), this, SLOT(attendNewClient()));
}
/*!
 * \brief MainWindow::attendNewClient
 * when client connection incoming create a new AttendClient and bind
 */
void MainWindow::attendNewClient()///------test with concurrent clients----------DEBUG
{
    qDebug("MainWindow::startServer");
    attendant = new AttendClient(mainServer->nextPendingConnection(),&ptrToBuffers,this);
    if( attendant == NULL ) ui->textEdit->setText("BAD_ALLOC  AttendClient");
    attendClients.push_back(attendant);

    connect(attendant,SIGNAL(newSrvKinect(srvKinect)),this,SLOT(updateSrvKinect(srvKinect)));
}

/*!
 * \brief MainWindow::closeEvent
 * override window close event to stop loop and delete apikinect handler.
 * \param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    //this->~MainWindow();
    //exit(0);
}
