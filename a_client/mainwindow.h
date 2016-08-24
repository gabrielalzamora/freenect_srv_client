#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTime>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTcpSocket>
#include <QHostAddress>
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

public slots:
    void setHost();
    void dataChanged();

private slots:
    //server
    void initConnection();
    void closeConnection();
    void socketErrorVideo();
    //video
    void initVideo();
    void finalizeVideo();
    void readDataVideo();
    //depth
    void initDepth();
    void finalizeDepth();
    void readDataDepth();
    //3D
    void init3D();
    void finalize3D();
    void readData3D();
    //2D
    //barrido
    void barridoAxes();
    void initBarrido();
    void finalizeBarrido();
    void readDataBarrido();

private:
    Ui::MainWindow *ui;
//    QString host;
    QHostAddress hostAddr;//------------------DEBUG
//    int port;//------------------DEBUG
    QTcpSocket *skt_srvK;
    int connectedServer;
//Video
    QTcpSocket *skt_video;
    int connectedVideo;
    quint64 sizeVideo;
    QGraphicsScene *sceneVideo;
    QGraphicsItem *itemVideo;
//Depth
    QTcpSocket *skt_depth;
    int connectedDepth;
    quint64 sizeDepth;
    QGraphicsScene *sceneDepth;
    QGraphicsItem *itemDepth;
//3D
    QTcpSocket *skt_3D;
    int connected3D;
    quint64 size3D;
    std::vector<point3c> p3Buf;
//2D
    QTcpSocket *skt_2D;
//Barrido
    QTcpSocket *skt_barrido;
    int connectedBarrido;
    quint64 sizeBarrido;
    QGraphicsScene *sceneBarrido;
    QGraphicsEllipseItem *ellipse;//!< holds single Barrido point to add to sceneBarrido
    std::vector<QGraphicsEllipseItem*> ellipseVector;//!< holds barrido points to paint in ellipse
    std::vector<uint32_t> barridoBuf;

    QTcpSocket *skt_accel;
    std::vector<int> timeVector;//msecs
    QTime qt_video, qt_depth, qt_3, qt_2, qt_barrido;
};

#endif // MAINWINDOW_H
