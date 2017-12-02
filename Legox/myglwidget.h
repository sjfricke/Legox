// myglwidget.h

#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include <QtOpenGL/QGLWidget>
#include <QtOpenGL/QGLFunctions>

#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>

QT_BEGIN_NAMESPACE
class QBasicTimer;
class QGLShaderProgram;
QT_END_NAMESPACE

// forward declaration
class CubeEngine;

class MyGLWidget : public QGLWidget,  protected QGLFunctions
{
    Q_OBJECT
public:
    explicit MyGLWidget(QWidget *parent = 0);
    ~MyGLWidget();

protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void timerEvent(QTimerEvent *e);

    void translateEvent(QMouseEvent *e);
    void rotateEvent(QMouseEvent *e);
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();


private:
    QBasicTimer *m_timer;
    QGLShaderProgram *m_program;
    CubeEngine *m_cubes;

    GLuint m_texture;

    QMatrix4x4 m_projection;

    int       m_clickSide; // -1 == left, 1 == right
    QVector2D m_clickStartR;
    QVector2D m_clickLastR;
    QVector2D m_clickStartL;
    QVector2D m_clickLastL;

    QMatrix4x4 m_viewMatrix;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QVector3D m_rotation;
    QQuaternion rotation;
};

#endif
