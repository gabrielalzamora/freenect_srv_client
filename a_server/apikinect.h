

#ifndef APIKINECT_H
#define APIKINECT_H

#include <mutex>
#include <vector>
#include <libfreenect.hpp>
#include "data.h"

class Apikinect : public Freenect::FreenectDevice
{

public:
    explicit Apikinect(freenect_context *_ctx, int _index);

public:
    void VideoCallback(void *_rgb, uint32_t timestamp);// Do not call directly, even in child
    void DepthCallback(void *_depth, uint32_t timestamp);// Do not call directly, even in child
    bool getRGB(std::vector<uint8_t> &buffer);
    bool getDepth(std::vector<uint16_t> &buffer);

    void getAll(std::vector<point3c> &buffer3,std::vector<uint32_t> &bufferB);
    int get3d(std::vector<point3c> &buffer);
    int get2(std::vector<point2> &buffer);
    int getBarrido(std::vector<uint32_t> &buffer);///Barre o Barrido para todo; pero para de poner variantes

private:
    std::mutex m_rgb_mutex;///< mutex to ensure video frame data save access
    std::mutex m_depth_mutex;///< mutex to ensure video frame data save access
    std::mutex m_mutex_3D;///< mutex to protect 3D data read/write operations
    std::mutex m_mutex_barre;///< mutex to ensure save barre read/write operations
    std::vector<uint8_t> m_buffer_video;///< buffer to store usb incoming video frame (see VideoCallback)
    std::vector<uint16_t> m_buffer_depth;///< buffer to store usb incoming depth frame (see DepthCallback)
    bool m_new_rgb_frame;///< flag true if we have new frame data in m_buffer_video, otherwise false
    bool m_new_depth_frame;///< flag true if we have new frame data in m_buffer_depth, otherwise false

    std::vector<point3c> m_buffer_3;///< buffer to store three dimention plus color points
    std::vector<point2> m_buffer_2;///< buffer to store point cloud proyected to floor plane
    std::vector<uint32_t> m_buffer_B;///< buffer to hold distances seen on each azimut angle
};

#endif // APIKINECT_H
