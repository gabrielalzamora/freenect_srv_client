
#include <QNetworkInterface>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "apikinect.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    numDevices = freenect.deviceCount();
    init();
    setServerIp();
    putKcombo();
    barreInit();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sceneVideo;
    delete sceneDepth;
    delete sceneBarre;
    if( imgVideo != NULL ) delete imgVideo;
    if( imgDepth != NULL ) delete imgDepth;
    if( imgBarre != NULL ) delete imgBarre;
    if(currentDeviceIndex !=-1){
        stoploop();
        stopK(currentDeviceIndex);
    }
}
/**
 * @brief MainWindow::videoDataReady
 * draw video image (on ui->gvVideo sceneVideo using data from buf vector)
 * @param buf
 */
void MainWindow::videoDataReady()
{
    if( imgVideo != NULL ) delete imgVideo;
//    imgVideo = new QImage(buf.data(),640,480,QImage::Format_RGB888);
    imgVideo = new QImage(videoBuf.data(),640,480,QImage::Format_RGB888);
    sceneVideo->addPixmap(QPixmap::fromImage(*imgVideo).scaled(320,240,Qt::KeepAspectRatio));
    ui->gvVideo->show();
}
/**
 * @brief MainWindow::depthDataReady
 * draw depth image (on ui->gvDepth sceneDepth using data from buf vector)
 * @param buf
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
/**
 * @brief MainWindow::barreDataReady
 * draw barrido (barre) (on ui->gvBarre sceneBarre using
 */
void MainWindow::barreDataReady()
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
        if(barreBuf[i] == 0) continue;//no data info no plot
        y = 235-(235*barreBuf[i]/4000);//divide barreBuf[i] by max mesured distance to fit in screen
        x = 320*(360-i)/360;
//        qDebug("  x = %d   y = %d , barre = %d",x,y, barreBuf[i]);
        ellipseVector.push_back(new QGraphicsEllipseItem(x,y,1.0,1.0));
        sceneBarre->addItem(ellipseVector[aux]);
        aux++;
    }
//    qDebug("  x = %d   y = %d , barre = %d",x,y, barreBuf[180]);
    ui->gvBarre->show();
}
/**
 * @brief MainWindow::barreInit
 * draw axes on sceneBarre to show on gvBarre
 */
void MainWindow::barreInit()
{
    ui->gvBarre->setBackgroundBrush(QColor(200,240,240,255));//light blue
    sceneBarre->setBackgroundBrush(QColor(200,240,240,255));
    QPen ejesPen = QPen(QColor(0,0,0,255));//black
    ejesPen.setWidth(2);
    QLine ejex = QLine(5,230,315,230);
    QLine ejey = QLine(160,230,160,5);
    sceneBarre->addLine(ejex,ejesPen);
    sceneBarre->addLine(ejey,ejesPen);

}
/**
 * @brief MainWindow::init
 * convenience function to initiate members
 */
void MainWindow::init()
{
    device = NULL;
    currentDeviceIndex = -1;
    flag = false;
    videoBuf.resize(640*480*3);
    depthBuf.resize(640*480);
    p3Buf.reserve(300000);//max number of points
    p3Buf.resize(0);//initially we have none
    barreBuf.resize(360);
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
}
/**
 * @brief MainWindow::setServerIp
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
/**
 * @brief MainWindow::putKcombo
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
/**
 * @brief MainWindow::startK
 * init device to handle kinect of indexK
 * @param indexK
 */
void MainWindow::startK(int indexK)
{
    device = &freenect.createDevice<Apikinect>(indexK);
    device->startVideo();
    device->startDepth();
    currentDeviceIndex = indexK;
}
/**
 * @brief MainWindow::stopK destroy kinect handler
 * @param index index kinect handler index to be destroyed
 */
void MainWindow::stopK(int indexK)
{
    device->stopDepth();
    device->stopVideo();
    freenect.deleteDevice(indexK);
    currentDeviceIndex = -1;
    device = NULL;
}
/**
 * @brief MainWindow::loop
 * working horse retrieving video & depth info
 * and pouring it to p3Buf (point cloud: 3D+color)
 */
void MainWindow::loop()
{
    flag = 1;
//    int count(0);//number of points in bufferCloud
//    int countLimit(0);//stop while(flag) if no points DEBUG

    while( flag ){

        device->getRGB(videoBuf);
        videoDataReady();//paint video on gvVideo
        device->getDepth(depthBuf);
        depthDataReady();//paint depth on gvDepth

        device->getAll(p3Buf,barreBuf);
        ui->glWidget->setpCloud(p3Buf,p3Buf.size());///---DEBUG remove p3Buf.size()
        ui->glWidget->repaint();//paint points cloud on glwidget
        barreDataReady();//paint Barrido (barre)

        qApp->processEvents();//stay responsive to button click
    }
}
/**
 * @brief MainWindow::stoploop
 * convinience funtion to stop loop seting wile(flag)=0
 */
void MainWindow::stoploop()
{
    flag = 0;
}
/**
 * @brief MainWindow::on_pbGo_clicked start selected kinect data flow
 */
void MainWindow::on_pbGo_clicked()
{
    ui->pbGo->setEnabled(false);
    int index = ui->combo->currentText().toInt();
    startK(index);
    currentDeviceIndex = index;
    loop();
}
/**
 * @brief MainWindow::on_pbStop_clicked stop kinect data flow and delete handler
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
/**
 * @brief MainWindow::on_combo_activated
 * when combo item selected -> buttons activated
 * @param index
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

void MainWindow::attendNewClient()
{

}
/* Al parecer pasa por ~MainWindow al cerrar ¿por qué se queja a veces?
 * @brief MainWindow::closeEvent
 * override window close event to stop loop and delete apikinect handler
 * @param event
 *//*
void MainWindow::closeEvent(QCloseEvent *event)
{
    this->~MainWindow();
    exit(0);
}*/
