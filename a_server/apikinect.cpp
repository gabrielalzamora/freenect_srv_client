
#include <math.h>       // sqrt(), atan()
#include "apikinect.h"


/**
 * @brief Apikinect::Apikinect holds all kinect device properties to read & handel it
 * @param _ctx
 * @param _index
 */
Apikinect::Apikinect(freenect_context *_ctx, int _index)
    : Freenect::FreenectDevice(_ctx, _index),
      m_buffer_video(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),
      m_buffer_depth(freenect_find_depth_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_DEPTH_REGISTERED).bytes / 2),
      m_new_rgb_frame(false), m_new_depth_frame(false)
{
    setDepthFormat(FREENECT_DEPTH_REGISTERED);

    m_buffer_B.resize(360);
}

/**
 * @brief Apikinect::VideoCallback is called if usb video event in Freenect::m_thread
 * @param _rgb      points buffer where to save usb incoming video frame
 * @param timestamp
 */
void Apikinect::VideoCallback(void *_rgb, uint32_t timestamp)
{
    std::lock_guard<std::mutex> lock(m_rgb_mutex);//lock will be destroy when exit VideoCallback
    uint8_t* rgb = static_cast<uint8_t*>(_rgb);
    copy(rgb, rgb+getVideoBufferSize(), m_buffer_video.begin());
    m_new_rgb_frame = true;
}

/**
 * @brief Apikinect::DepthCallback is called if usb depth event in Freenect::m_thread
 * @param _depth    points buffer shere to save usb incoming depth frame
 * @param timestamp
 */
void Apikinect::DepthCallback(void *_depth, uint32_t timestamp)
{
    std::lock_guard<std::mutex> lock(m_depth_mutex);
    uint16_t* depth = static_cast<uint16_t*>(_depth);
    copy(depth, depth+getDepthBufferSize()/2, m_buffer_depth.begin());
    m_new_depth_frame = true;
}

/**
 * @brief Apikinect::getRGB retrieve video frame
 * @param buffer    point to buffer where new video frame is stored
 * @return          true if we have new video frame, false if not new
 */
bool Apikinect::getRGB(std::vector<uint8_t> &buffer)
{
    std::lock_guard<std::mutex> lock(m_rgb_mutex);
    if (!m_new_rgb_frame)
        return false;
    buffer.swap(m_buffer_video);
    m_new_rgb_frame = false;
    return true;
}

/**
 * @brief Apikinect::getDepth retrieve depth frame
 * @param buffer    point to buffer where new depth frame is stored
 * @return          true if we have new depth frame, false if not new
 */
bool Apikinect::getDepth(std::vector<uint16_t> &buffer)
{
    std::lock_guard<std::mutex> lock(m_depth_mutex);
    if (!m_new_depth_frame)
        return false;
    buffer.swap(m_buffer_depth);
    m_new_depth_frame = false;
    return true;
}

/**
 * @brief Apikinect::get3d 3 dimention + color points in buffer
 * plus 2D and Barrer buffers filled with last data available
 * @param buffer
 * @return number of point3d in buffer
 */
int Apikinect::get3d(std::vector<point3c> &buffer)
{
    point2 p2;
    point3c p3;
    RGBQ color;
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
//time pre buffers

    for (int i = 0; i < 480*640; ++i)
    {
        // Convert from image plane coordinates to world coordinates
        if( (p3.z = m_buffer_depth[i]) != 0  ){                  // Z = d
            p3.x = (i%640-(640-1)/2.f)*m_buffer_depth[i]/f;      // X = (x - cx) * d / fx
            p3.y = (i/640 - (480-1)/2.f) * m_buffer_depth[i] / f;// Y = (y - cy) * d / fy
            color.rgbRed = m_buffer_video[3*i+0];    // R
            color.rgbGreen = m_buffer_video[3*i+1];  // G
            color.rgbBlue = m_buffer_video[3*i+2];   // B
            color.rgbReserved = 0;
            p3.color = color;
            ///estás usando dos buffers, a ver si con uno te basta; pero recuerda pintar pantalla
            /// persistencia de la memoria, etc...
            buffer.push_back(p3);//MainWindow::p3Buf
            m_buffer_3.push_back(p3);//Apikinect::m_buffer_3

            p2.x = p3.x;//two dimentions point cloud
            p2.z = p3.z;
            m_buffer_2.push_back(p2);
//time pre barrer
            int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
            uint32_t length = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm
            if( m_buffer_B[index] > length )
                m_buffer_B[index] = length;
//time post barrer  difference*numpoints = time barrer
        }
    }
//time post buffers
    int i = buffer.size();
    return i;//buffer.size();
}

int Apikinect::get2(std::vector<point2> &buffer)
{
    buffer.swap(m_buffer_2);
    return buffer.size();
}

void Apikinect::getBarrer(std::vector<uint32_t> &buffer)
{
    buffer.swap(m_buffer_B);
}
