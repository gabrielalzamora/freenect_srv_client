
#include <vector>
#include "attendclient.h"

#define SRVKPORT 10003
#define DEPTHPORT 10004
#define VIDEOPORT 10005
#define THREEPORT 10006
#define TWOPORT 10007
#define BARRIDOPORT 10008
#define ACCELPORT 10009

/*!
 * \class AttendClient
 * \brief is created for each client connected to server.
 *
 * Handle all comunications between server and client
 */

/*!
 * \brief constructor
 * \param socket
 * \param ptrToBuffers
 * \param parent
 */
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
/*!
 * \brief destructor
 */
AttendClient::~AttendClient()
{
    if(s_video->isListening()){
        if(skt_video->isValid()){
            skt_video->disconnectFromHost();
            if( !skt_video->waitForDisconnected(3000) ){
                skt_video->abort();
            }
        }
        s_video->disconnect();
    }
    if(s_depth->isListening()){
        if(skt_depth->isValid()){
            skt_depth->disconnectFromHost();
            if( !skt_depth->waitForDisconnected(3000) ){
                skt_depth->abort();
            }
        }
        s_depth->disconnect();
    }
    if(s_3d->isListening()){
        if(skt_3d->isValid()){
            skt_3d->disconnectFromHost();
            if( !skt_3d->waitForDisconnected(3000) ){
                skt_3d->abort();
            }
        }
        s_3d->disconnect();
    }
    if(s_2d->isListening()){
        if(skt_2d->isValid()){
            skt_2d->disconnectFromHost();
            if( !skt_2d->waitForDisconnected(3000) ){
                skt_2d->abort();
            }
        }
        s_2d->disconnect();
    }
    if(s_barrido->isListening()){
        if(skt_barrido->isValid()){
            skt_barrido->disconnectFromHost();
            if( !skt_barrido->waitForDisconnected(3000) ){
                skt_barrido->abort();
            }
        }
        s_barrido->disconnect();
    }
    if(s_accel->isListening()){
        if(skt_accel->isValid()){
            skt_accel->disconnectFromHost();
            if( !skt_accel->waitForDisconnected(3000) ){
                skt_accel->abort();
            }
        }
        s_accel->disconnect();
    }
}
/*!
 * \brief create servers to listen client
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

    sizeSrvK = sizeVideo = sizeDepth = size3d = size2d = sizeBarrido = sizeAccel = 0;
}
/*!
 * \brief read srvKinect new value when sended by client
 */
void AttendClient::readSrvKdata()
{
    qDebug("AttendClient::readSrvKdata");
    //-------------------------------------------------------read client msg
    QDataStream in(m_socket);//read client petition
    in.setVersion(QDataStream::Qt_5_0);

    if (sizeSrvK == 0) {//check there's enough bytes to read
        if (m_socket->bytesAvailable() < sizeof(quint64))
            return;
        in >> sizeSrvK;//read and save into quint64 sizeSrvK
    }
    if (m_socket->bytesAvailable() < sizeSrvK){//check there's enough bytes to read
        return;//if not wait till you have all data size video says
    }

    in >> flagSrvK;//flag = 0 will stop and disconnect, != 0 read srvK
    qDebug("tamaño: %u  info: %u", sizeSrvK, flagSrvK);//DEBUG
    if( !flagSrvK ){
        m_socket->disconnectFromHost();
        qDebug("Cliente ordena desconectar");
        this->deleteLater();
        this->~AttendClient();
        return;
    }//--------------- only goes ahead if all data received & flagSrvK != 0
    in >> srvK.m_fAngulo;
    in >> srvK.m_iAnguloKinect;
    in >> srvK.m_fAltura;
    in >> srvK.m_fYMin;
    in >> srvK.m_fYMax;
    in >> srvK.m_fZMax;
    in >> srvK.m_ulRefresco3D;
    in >> srvK.m_usModulo3D;
    in >> srvK.m_bEnvio3D;
    in >> srvK.m_bEnvio2D;
    in >> srvK.m_bEnvioBarrido;
    in >> srvK.m_bCompress3D;
    in >> srvK.m_iBarridoEcu;
    in >> srvK.m_iBarridoYMin;
    in >> srvK.m_iBarridoYMax;
    in >> srvK.m_ulRefrescoDepth;
    in >> srvK.m_bEnvioDepth;
    in >> srvK.m_bCompressDepth;
    in >> srvK.m_ulRefrescoColor;
    in >> srvK.m_bEnvioColor;
    in >> srvK.m_bCompressColor;
    emit newSrvKinect(srvK);
    sizeSrvK = 0;//to allow reading next message size
}

/*!
 * \brief incoming connection bind to a socket in order to I/O data
 */
void AttendClient::incomingVideo()
{
    skt_video = s_video->nextPendingConnection();
    connect(skt_video,SIGNAL(readyRead()),this,SLOT(sendVideo()));
}
/*!
 * \brief send video frame (image) through skt_video to client
 */
void AttendClient::sendVideo()
{
    qDebug("AttendClient::sendVideo");

    if(skt_video->peerAddress() == peerAddr){//AttendClient only attend single client
        qDebug("  es mi cliente :o)");

    }else{///-------Al revés -> cuando acabes DEBUG  if != return (menos código, más simple)
        qDebug("  otro cliente :o(  %u yo %u ",skt_video->peerAddress().toIPv4Address(),peerAddr.toIPv4Address());
        return;//if client is not our client wait for next connection
    }///--------------- cuando simplificado quita else{} -----------------DEBUG

    //-------------------------------------------------------read client msg
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

//----------------------------------------------------------------create & send video frame as QImage
    QImage image = QImage(structBuffers.ptrVideoBuf->data(),640,480,QImage::Format_RGB888);
    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << image;
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//set buff size at beginning
//    qDebug("  tamaño antes enviado: %u",(buff.size()-sizeof(quint64))) ;//DEBUG
    skt_video->write(buff);//enviamos
}

/*!
 * \brief incoming connection bind to a socket in order to I/O data
 */
void AttendClient::incomingDepth()
{
    skt_depth = s_depth->nextPendingConnection();
    connect(skt_depth,SIGNAL(readyRead()),this,SLOT(sendDepth()));
}
/*!
 * \brief send depth frame (image) through skt_depth to client
 */
void AttendClient::sendDepth()
{
    qDebug("AttendClient::sendDepth");

    if(skt_depth->peerAddress() != peerAddr){//AttendClient only attend single client
        qDebug("  otro cliente :o(  %u yo %u ",skt_depth->peerAddress().toIPv4Address(),peerAddr.toIPv4Address());
        return;//if client is not our client wait for next connection
    }

    //-------------------------------------------------------read client msg
    QDataStream in(skt_depth);//read client petition
    in.setVersion(QDataStream::Qt_5_0);

    if (sizeDepth == 0) {//check there's enough bytes to read
        if (skt_depth->bytesAvailable() < sizeof(quint64))
            return;
        in >> sizeDepth;//read and save into quint64 sizeDepth
    }
    if (skt_depth->bytesAvailable() < sizeDepth){//check there's enough bytes to read
        return;//if not wait till you have all data size video says
    }

    in >> flagDepth;//flag = 0 will stop and disconnect, != 0 send image
    qDebug("tamaño: %u  info: %u", sizeDepth, flagDepth);//DEBUG
    if( !flagDepth ){
        skt_depth->disconnectFromHost();
        qDebug("Cliente ordena desconectar Depth");
        return;
    }//--------------- only goes ahead if all data received & flagDepth != 0
    sizeDepth = 0;//to allow reading next message size

//----------------------------------------------------------------create & send depth frame as QImage
    QImage image = QImage(640,480,QImage::Format_Grayscale8);
    unsigned char r,g,b, distaChar;
    for(int x = 0; x < 640; x++){
        for(int y = 0; y < 480; y++){
            int value = (*structBuffers.ptrDepthBuf)[(x+y*640)];//value is distance in mm
            distaChar = value/39;//to transform distance to 8bit grey
            r=g=b=distaChar;
            image.setPixel(x,y,qRgb(r,g,b));
        }
    }

    QByteArray buff;
    QDataStream out(&buff, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_0);
    out << quint64(0) << image;
    out.device()->seek(0);//puntero a inicio buff
    out << quint64(buff.size() - sizeof(quint64));//set buff size at beginning
//    qDebug("  tamaño antes enviado: %u",(buff.size()-sizeof(quint64))) ;//DEBUG
    skt_depth->write(buff);//enviamos
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
