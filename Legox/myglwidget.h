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
    void timerEvent(QTimerEvent *e);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void initShaders();
    void initTextures();

private:
    QBasicTimer *timer;
    QGLShaderProgram *program;
    CubeEngine *cubes;

    GLuint texture;

    QMatrix4x4 projection;

    QVector2D mousePressPosition;
    QVector3D rotationAxis;
    qreal angularSpeed;
    QQuaternion rotation;
};

//public slots:
//    // slots for xyz-rotation slider
//    void setXRotation(int angle);
//    void setYRotation(int angle);
//    void setZRotation(int angle);

//signals:
//    // signaling rotation from mouse movement
//    void xRotationChanged(int angle);
//    void yRotationChanged(int angle);
//    void zRotationChanged(int angle);


#endif // MYGLWIDGET_H

