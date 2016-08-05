#ifndef TYPEKINECT_H
#define TYPEKINECT_H

#include <cstdint>
#include <vector>

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

typedef struct ptrBuf{
    std::vector<uint8_t> *ptrVideoBuf;///< container of video info from kinect
    std::vector<uint16_t> *ptrDepthBuf;///< container of depth info from kinect
    std::vector<point3c> *ptrP3Buf;///< container of points cloud <- video+depth
    std::vector<point2> *ptrP2Buf;///< container of 2D points = (point cloud) - color - z
    std::vector<uint32_t> *ptrBarridoBuf;///< barridoBuf contains distance to closer object on angle (360-i)/2 degrees, xOz plane (horizontal to camera)
    std::vector<double> *ptrAccel;///< acceleration components x,y,z (y ~ 9,81 if m_iAnguloKinect=0)
}pBuf;

#endif // TYPEKINECT_H
