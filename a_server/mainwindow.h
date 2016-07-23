#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTime>
#include <mutex>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTcpServer>
#include <QMainWindow>
#include "apikinect.h"
#include "attendclient.h"
#include "framegl.h"
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:


public slots:
    void videoDataReady();//print videoBuf
    void depthDataReady();//print depthBuf
    void barridoDataReady();//print BarridoBuf
    void barridoInit();//paint axes
    void updateKinect();//send ledOption and angle to kinect

private slots:
    void init();
    void setServerIp();
    void putKcombo();
    void startK(int indexK);
    void stopK(int indexK);
    void loop();
    void stoploop();
    void on_pbGo_clicked();
    void on_pbStop_clicked();
    void on_combo_activated(const QString &arg1);

    void printTimeVector(std::vector<int> &timeV);

    void attendNewClient();

protected:
    void closeEvent(QCloseEvent *event) Q_DECL_OVERRIDE;

private:
    Ui::MainWindow *ui;
    QGraphicsScene *sceneVideo;
    QGraphicsScene *sceneDepth;
    QGraphicsScene *sceneBarre;
    QImage *imgVideo;
    QImage *imgDepth;
    QImage *imgBarre;
    QGraphicsEllipseItem *ellipse;
    std::vector<QGraphicsEllipseItem*> ellipseVector;
    QPainter *ptpt;

//    Data *data;///< object that contain all configuration data from tab: data
    srvKinect mw_srvK;///copy of data->m_srvK just to debug connect(data,this) problems-----DEBUG

    freenect_context *context;///< point to usb context associated to kinect data handling
    Freenect::Freenect freenect;///< Freenect class object to start events thread and Devices
    Apikinect *device;

    std::vector<uint8_t> videoBuf;///< container of video info from kinect
    std::vector<uint16_t> depthBuf;///< container of depth info from kinect
    std::vector<point3c> p3Buf;///< container of points cloud <- video+depth
    std::vector<point2> p2Buf;///< container of 2D points = (point cloud) - color - z
    std::vector<uint32_t> barridoBuf;///< barridoBuf contains distance on angle (360-i)/2 degrees, xOz plane
    int flag;///< 0 stop loop(), otherwise let loop() run
    int numDevices;///< number of detected kinects
    int currentDeviceIndex;///< index of active kinect
    std::vector<double> accel;///< acceleration components x,y,z (y ~ 9,81 if m_iAnguloKinect=0)

    std::mutex mutexVideo;//tal vez un mutexArray[enum]
    std::mutex mutexDepth;
    std::mutex mutex3;
    std::mutex mutex2;
    std::mutex mutexBarre;
    std::mutex mutexAccel;

    QTcpServer *mainServer;
    std::vector<AttendClient> attnClients;///< active AttendClient (to access them)

    std::vector<int> timeVector;//msecs

};

#endif // MAINWINDOW_H
