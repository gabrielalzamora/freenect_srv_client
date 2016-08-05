#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
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

private:
    Ui::MainWindow *ui;
//    QString host;
    QHostAddress hostAddr;//------------------DEBUG
//    int port;//------------------DEBUG
    QTcpSocket *skt_srvK;
    int connectedServer;

    QTcpSocket *skt_video;
    int connectedVideo;
    quint64 sizeVideo;
    QGraphicsScene *sceneVideo;
    QGraphicsItem *itemVideo;

    QTcpSocket *skt_depth;
    int connectedDepth;
    quint64 sizeDepth;
    QGraphicsScene *sceneDepth;
    QGraphicsItem *itemDepth;

    QTcpSocket *skt_3D;
    QTcpSocket *skt_2D;
    QTcpSocket *skt_barrido;
    QTcpSocket *skt_accel;

};

#endif // MAINWINDOW_H
