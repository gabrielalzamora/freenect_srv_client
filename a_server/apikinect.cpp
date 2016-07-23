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
 * @brief Apikinect::getAll
 * funtion to retrieve point cloud & swetp ("barre") from video & depth data
 * @param buffer3 buffer to receive point cloud
 * @param bufferB buffer to receive swept ("barre")
 */
void Apikinect::getAll(std::vector<point3c> &buffer3, std::vector<uint32_t> &bufferB)
{
    point3c p3;
    RGBQ color;
    buffer3.resize(1);
    for(int i=0;i<360;i++) bufferB[i]=0;
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    //------------------------------------------------------time pre buffers
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
            buffer3.push_back(p3);//MainWindow::p3Buf
//time pre barrer
            int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
            uint32_t length = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm
            if( bufferB[index]==0 || bufferB[index]>length)
                bufferB[index]=length;
//time post barrer  difference*numpoints = time barrer
        }
    }//----------------------------------------------------------time post buffers
}

/**
 * @brief Apikinect::get3d
 * 3 dimention + color point cloud in buffer from video & depth data
 * @param buffer  where point cloud is stored
 * @return number of point3d in buffer = buffer.size()
 */
int Apikinect::get3d(std::vector<point3c> &buffer)
{
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
            buffer.push_back(p3);//MainWindow::p3Buf
        }
    }
//time post buffers
    return buffer.size();
}

/**
 * @brief Apikinect::get2
 * 2 dimention point cloud in buffer from video & depth data
 * @param buffer where point cloud is stored
 * @return number of point2d in buffer = buffer.size()
 */
int Apikinect::get2(std::vector<point2> &buffer)
{
    point2 p2;
    buffer.resize(1);
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    //------------------------------------------------------time pre buffers
    for (int i = 0; i < 480*640; ++i)
    {
        // Convert from image plane coordinates to world coordinates
        if( (p2.z = m_buffer_depth[i]) != 0  ){                  // Z = d
            p2.x = (i%640-(640-1)/2.f)*m_buffer_depth[i]/f;      // X = (x - cx) * d / fx
            buffer.push_back(p2);//MainWindow::p2Buf
        }
    }//----------------------------------------------------------time post buffers
    return buffer.size();
}

/**
 * @brief Apikinect::getBarrer
 * 360 vector with distance at each angle 0º where camara is centered
 * and from -89.5º to 90º each 1/2 degree (180*2=360 values)
 * @param buffer where 360 distance values are stored
 * @return number of points should be 360=buffer.size()
 */
int Apikinect::getBarrido(std::vector<uint32_t> &buffer)
{
    point3c p3;
    for(int i=0;i<360;i++) buffer[i]=0;
    float f = 595.f;//intrinsec kinect camera parameter fx=fy=f
    //------------------------------------------------------time pre buffers
    for (int i = 0; i < 480*640; ++i)
    {
        if( (p3.z = m_buffer_depth[i]) != 0  ){                  // Z = d
            p3.x = (i%640-(640-1)/2.f)*m_buffer_depth[i]/f;      // X = (x - cx) * d / fx
            int index = 180-int(2*atan(double(p3.x)/double(p3.z))*180/M_PI);
            uint32_t length = uint32_t(sqrt( p3.x*p3.x + p3.z*p3.z ));//distance en mm
            if( buffer[index]==0 || buffer[index]>length)
                buffer[index]=length;
        }
    }//----------------------------------------------------------time post buffers
    return buffer.size();
}
