#ifndef FRAMEGL_H
#define FRAMEGL_H

#include <QOpenGLWidget>
#include <GL/glu.h>
#include <mutex>
#include "data.h"


class FrameGL : public QOpenGLWidget
{
    Q_OBJECT
public:
    explicit FrameGL(QWidget *parent = 0);
    ~FrameGL();

    QSize minimumSizeHint() const Q_DECL_OVERRIDE;
    QSize sizeHint() const Q_DECL_OVERRIDE;
//    void rotateBy(int xAngle, int yAngle, int zAngle);
    void setClearColor(const QColor &color);

signals:
    void clicked();
    void xRotChange(float angle);
    void yRotChange(float angle);
    void zRotChange(int angle);

public slots:
    void setpCloud(std::vector<point3c> c, int count);
    void initializeGL() Q_DECL_OVERRIDE;
    void paintGL() Q_DECL_OVERRIDE;
    void resizeGL(int width, int height) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void wheelEvent(QWheelEvent *event) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

    void drawCloud();//auxiliar, simplifica paintGL(), dibuja pts
    void drawAxis();//aux funtion, paint reference axes
    void drawLines();//aux lines, esto es de RAUL

private:
    std::mutex mtxCloud;//think better if it's neccesary
    std::vector<point3c> pCloud;///< keep points cloud info
    int sizeCloud;///< number of points should = pCloud.size()

    QColor clearColor;
    QPoint lastPosition;
    int width, height;//resized window width & height
    int xRot, yRot, zRot;//mouse rotation x,y,z
    int m_x, m_y, m_z;//mouse mouve x,y,z
    float anglex, angley;//panning angles
    float zoom;//zoom factor
};

#endif // FRAMEGL_H
