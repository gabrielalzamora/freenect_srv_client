
#include <vector>
#include "attendclient.h"

#define SRVKPORT 10003
#define DEPTHPORT 10004
#define VIDEOPORT 10005
#define THREEPORT 10006
#define TWOPORT 10007
#define BARRIDOPORT 10008
#define ACCELPORT 10009


AttendClient::AttendClient(QTcpSocket *socket, pBuf *ptrToBuffers, QObject *parent) : QObject(parent)
{
    qDebug("AttendClient::AttendClient");
    peerAddr = socket->peerAddress();
    peerPort = socket->peerPort();
    m_socket = socket;
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readSrvKdata()));
    qDebug() << "  peerAddr = " << peerAddr.toString();
    qDebug("  peerPort = %u",peerPort);

    structBuffers.ptrVideoBuf=ptrToBuffers->ptrVideoBuf;
    structBuffers.ptrDepthBuf=ptrToBuffers->ptrDepthBuf;
    structBuffers.ptrP3Buf = ptrToBuffers->ptrP3Buf;
    structBuffers.ptrP2Buf = ptrToBuffers->ptrP2Buf;
    structBuffers.ptrBarridoBuf = ptrToBuffers->ptrBarridoBuf;
    structBuffers.ptrAccel = ptrToBuffers->ptrAccel;

    startServers();
}
/**--------------------------overloaded DEBUG
 * @brief AttendClient::AttendClient--------------------------overloaded DEBUG
 */
/*
AttendClient::AttendClient(QTcpSocket *socket, std::vector<uint8_t> &vectorVideo, QObject *parent) : QObject(parent)
{
    qDebug("AttendClient::AttendClient");
    peerAddr = socket->peerAddress();
    peerPort = socket->peerPort();
    m_socket = socket;
    m_vectorVideo = vectorVideo;
    connect(m_socket,SIGNAL(readyRead()),this,SLOT(readSrvKdata()));
    qDebug() << "  peerAddr = " << peerAddr.toString();
    qDebug("  peerPort = %u",peerPort);

    startServers();
}
*/
AttendClient::~AttendClient()
{

}
/**
 * @brief AttendClient::startServers
 * start servers that will attend client
 */
void AttendClient::startServers()
{
    s_video = new QTcpServer(this);
    skt_video = new QTcpSocket(this);

    s_depth = new QTcpServer(this);
    //skt_depth = new QTcpSocket(this);
    s_3d = new QTcpServer(this);
    //skt_3d = new QTcpSocket(this);
    s_2d = new QTcpServer(this);
    //skt_2d = new QTcpSocket(this);
    s_barrido = new QTcpServer(this);
    //skt_barrido = new QTcpSocket(this);
    s_accel = new QTcpServer(this);
    //skt_accel = new QTcpSocket(this);

    s_video->listen(QHostAddress::Any,VIDEOPORT);
    connect(s_video,SIGNAL(newConnection()),this,SLOT(incomingVideo()));

    s_depth->listen(QHostAddress::Any,DEPTHPORT);
    connect(s_depth,SIGNAL(newConnection()),this,SLOT(incomingDepth()));
    s_3d->listen(QHostAddress::Any,THREEPORT);
    connect(s_3d,SIGNAL(newConnection()),this,SLOT(incoming3d()));
    s_2d->listen(QHostAddress::Any,TWOPORT);
    connect(s_2d,SIGNAL(newConnection()),this,SLOT(incoming2d()));
    s_barrido->listen(QHostAddress::Any,BARRIDOPORT);
    connect(s_barrido,SIGNAL(newConnection()),this,SLOT(incomingBarrido()));
    s_accel->listen(QHostAddress::Any,ACCELPORT);
    connect(s_accel,SIGNAL(newConnection()),this,SLOT(incomingAccel()));

    sizeVideo = sizeDepth = size3d = size2d = sizeBarrido = sizeAccel = 0;
}

void AttendClient::readSrvKdata()
{

}

/**
 * @brief AttendClient::incomingVideo
 * incoming connection bind to a socket in order to I/O data
 */
void AttendClient::incomingVideo()
{
    skt_video = s_video->nextPendingConnection();
    connect(skt_video,SIGNAL(readyRead()),this,SLOT(sendVideo()));
}

/**
 * @brief AttendClient::sendVideo
 * send video frame (image) through skt_video to client
 */
void AttendClient::sendVideo()
{
    qDebug("AttendClient::sendVideo");

    if(skt_video->peerAddress() == peerAddr){//AttendClient only attend single client
        qDebug("  es mi cliente :o)");

    }else{///-------Al revés -> cuando acabes DEBUG  if != return (menos código, más simple)
        qDebug("  otro cliente :o(  %u yo %u ",skt_video->peerAddress().toIPv4Address(),peerAddr.toIPv4Address());
        return;//if client is not our client wait for next connection
    }

    //---------------------------------read client msg
    QDataStream in(skt_video);//read client petition
    in.setVersion(QDataStream::Qt_5_0);

    if (sizeVideo == 0) {//check there's enough bytes to read
        if (skt_video->bytesAvailable() < sizeof(quint64))
            return;
        in >> sizeVideo;//read and save into quint64 sizeVideo
    }
    if (skt_video->bytesAvailable() < sizeVideo){//check there's enough bytes to read
        return;//if not wait till you have all data size video says
    }

    in >> flagVideo;//flag = 0 will stop and disconnect, != 0 send image
    qDebug("tamaño: %u  info: %u", sizeVideo, flagVideo);//DEBUG
    if( !flagVideo ){
        skt_video->disconnectFromHost();
        qDebug("Cliente ordena desconectar VIDEO");
        return;
    }//--------------- only goes ahead if all data received & flagVideo != 0
    sizeVideo = 0;//to allow reading next message size
//--------------------------------------------------------------------create & send video frame as QImage
//    qDebug("  attend tamaño vector video = %u",structBuffers.ptrVideoBuf->size());
//std::vector<uint8_t> auxVector(*structBuffers.ptrVideoBuf);
//qDebug("  attend tamaño vector video = %u",auxVector.size());
    QImage image;
//image = QImage(auxVector.data(),640,480,QImage::Format_RGB888);
    image = QImage(structBuffers.ptrVideoBuf->data(),640,480,QImage::Format_RGB888);///--------------DEBUG
//imgVideo = QImage("/home/nadie/apikinect/img/cl415pintada.jpg");///--------------DEBUG

    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << image;
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//set buff size at beginning

    qDebug("  tamaño antes enviado: %u",(buff.size()-sizeof(quint64))) ;//DEBUG

    skt_video->write(buff);//enviamos


}

/**
 * @brief AttendClient::incomingDepth
 * incoming connection bind to a socket in order to I/O data
 */
void AttendClient::incomingDepth()
{
    skt_depth = s_depth->nextPendingConnection();
    connect(skt_depth,SIGNAL(readyRead()),this,SLOT(sendDepth()));
}

void AttendClient::sendDepth()
{

}

void AttendClient::incoming3d()
{

}

void AttendClient::send3d()
{

}

void AttendClient::incoming2d()
{

}

void AttendClient::send2d()
{

}

void AttendClient::incomingBarrido()
{

}

void AttendClient::sendBarrido()
{

}

void AttendClient::incomingAccel()
{

}

void AttendClient::sendAccel()
{

}
