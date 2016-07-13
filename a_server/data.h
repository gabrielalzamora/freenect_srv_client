#ifndef DATOS_H
#define DATOS_H

#include <QWidget>

typedef struct tagRGBQ{
    uint8_t rgbRed;
    uint8_t rgbGreen;
    uint8_t rgbBlue;
    uint8_t rgbReserved;
}RGBQ;

typedef struct punto3DyColor{
    int16_t x;
    int16_t y;
    int16_t z;
    RGBQ color;
}point3c;

typedef struct punto2D{
    int16_t x;
    int16_t z;
}point2;

typedef struct SrvKinect{
    double m_fAngulo;
    int8_t m_iAnguloKinect;
    double m_fAltura;
    double m_fYMin;
    double m_fYMax;
    double m_fZMax;
    uint32_t m_ulRefresco3D;
    uint8_t m_usModulo3D;
    uint8_t m_bEnvio3D;
    uint8_t m_bEnvio2D;
    uint8_t m_bEnvioBarrido;
    uint8_t m_bCompress3D;
    int32_t m_iBarridoEcu;
    int32_t m_iBarridoYMin;
    int32_t m_iBarridoYMax;
    uint32_t m_ulRefrescoDepth;
    uint8_t m_bEnvioDepth;
    uint8_t m_bCompressDepth;
    uint32_t m_ulRefrescoColor;
    uint8_t m_bEnvioColor;
    uint8_t m_bCompressColor;
}srvKinect;

class Datos : public QWidget
{
    Q_OBJECT
public:
    explicit Datos(QWidget *parent = 0);

signals:
    void srvKchanged(srvKinect newSrvK);

public slots:
    //void setSrvK(srvK newSrvK);
    //srvK getSrvK();

private:
    double m_fAngulo;
    int8_t m_iAnguloKinect;
    double m_fAltura;
    double m_fYMin;
    double m_fYMax;
    double m_fZMax;
    uint32_t m_ulRefresco3D;
    uint8_t m_usModulo3D;
    uint8_t m_bEnvio3D;
    uint8_t m_bEnvio2D;
    uint8_t m_bEnvioBarrido;
    uint8_t m_bCompress3D;
    int32_t m_iBarridoEcu;
    int32_t m_iBarridoYMin;
    int32_t m_iBarridoYMax;
    uint32_t m_ulRefrescoDepth;
    uint8_t m_bEnvioDepth;
    uint8_t m_bCompressDepth;
    uint32_t m_ulRefrescoColor;
    uint8_t m_bEnvioColor;
    uint8_t m_bCompressColor;

};

#endif // DATOS_H
