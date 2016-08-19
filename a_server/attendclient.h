/*
 * Copyright (c) 2016  Gabriel Alzamora.
 *
 * This code is licensed to you under the terms of the
 * GNU General Public License. See LICENSE file for the
 * text of the license, or the following URL:
 * https://www.gnu.org/licenses/gpl.html
 */

#ifndef ATTENDCLIENT_H
#define ATTENDCLIENT_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "data.h"

class AttendClient : public QObject
{
    Q_OBJECT
public:
    explicit AttendClient(QTcpSocket *socket, pBuf *ptrToBuffers, QObject *parent=0);
//    explicit AttendClient(QTcpSocket *socket, std::vector<uint8_t> &vectorVideo, QObject *parent=0);//DEBUG
    ~AttendClient();

signals:
    void newSrvKinect(srvKinect newSrvK);

public slots:
    void startServers();
    void readSrvKdata();

    void incomingVideo();
    void sendVideo();

    void incomingDepth();
    void sendDepth();

    void incoming3d();
    void send3d();
    void incoming2d();
    void send2d();

    void incomingBarrido();
    void sendBarrido();

    void incomingAccel();
    void sendAccel();

private:
    QTcpSocket *m_socket;//!< as srvK socket
    quint64 sizeSrvK;
    quint8 flagSrvK;
    QHostAddress peerAddr;
    quint16 peerPort;
    pBuf structBuffers;

    srvKinect srvK;

    QTcpServer *s_video;
    QTcpSocket *skt_video;
    quint64 sizeVideo;
    quint8 flagVideo;
    //QImage imgVideo;
    //std::vector<uint8_t> m_vectorVideo;

    QTcpServer *s_depth;
    QTcpSocket *skt_depth;
    quint64 sizeDepth;
    quint8 flagDepth;

    QTcpServer *s_3d;
    QTcpSocket *skt_3d;
    quint64 size3d;

    QTcpServer *s_2d;
    QTcpSocket *skt_2d;
    quint64 size2d;

    QTcpServer *s_barrido;
    QTcpSocket *skt_barrido;
    quint64 sizeBarrido;
    quint8 flagBarrido;

    QTcpServer *s_accel;
    QTcpSocket *skt_accel;
    quint64 sizeAccel;
};

#endif // ATTENDCLIENT_H
