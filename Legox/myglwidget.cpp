// myglwidget.cpp

#include "myglwidget.h"
#include "core/opengl/CubeEngine.h"

#include <QtWidgets>
#include <QtOpenGL>
#include <QBasicTimer>
#include <QMouseEvent>
#include <QDebug>

#include <math.h>
#include <locale.h>

MyGLWidget::MyGLWidget(QWidget *parent)
    :  QGLWidget(parent),
      m_timer(new QBasicTimer),
      m_program(new QGLShaderProgram),
      m_cubes(new CubeEngine)
{
    m_translate = {0.0, 0.0, -5.0};
    m_rotation = {0.0, 0.0, 0.0};
    m_zoom = 0;
}

MyGLWidget::~MyGLWidget()
{
    delete m_timer; m_timer = 0;
    delete m_program; m_program = 0;
    delete m_cubes; m_cubes = 0;

    deleteTexture(m_texture);
}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
    if (e->button() == Qt::MouseButton::LeftButton) { // left
        m_clickSide = -1;
        m_clickStartL = QVector2D(e->pos());
    } else if (e->button() == Qt::MouseButton::RightButton) { // right
        m_clickSide = 1;
        m_clickStartR = QVector2D(e->pos());
        m_clickLastR = QVector2D(e->pos());
    }
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
    if (e->buttons() & Qt::LeftButton) { // left
        m_clickLastL = QVector2D(e->pos()) - m_clickStartL;
        rotateEvent(e);
    } else if (e->buttons() & Qt::RightButton) { // right
        translateEvent(e);
    }
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void MyGLWidget::wheelEvent(QWheelEvent *e)
{
    if (e->delta() > 0) {
        if (m_translate.z() < 0) {
            m_translate.setZ(m_translate.z() + 1.0);
        }
    } else {
        m_translate.setZ(m_translate.z() - 1.0);
    }

    updateGL();
}


void MyGLWidget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

//    // Decrease angular speed (friction)
//    angularSpeed *= 0.99;

//    // Stop rotation when speed goes below threshold
//    if (angularSpeed < 0.01)
//        angularSpeed = 0.0;
//    else {
//        // Update rotation
//        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

//        // Update scene
//        updateGL();
//    }
}

void MyGLWidget::translateEvent(QMouseEvent *e)
{
    QVector2D diff =  m_clickLastR - QVector2D(e->pos());
    m_translate.setX(m_translate.x() - (diff.x() / 100));
    m_translate.setY(m_translate.y() + (diff.y() / 100));

    m_clickLastR = QVector2D(e->pos());
    updateGL();
}

void MyGLWidget::rotateEvent(QMouseEvent *e)
{
    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(m_clickLastL.y(), m_clickLastL.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = m_clickLastL.length() / 200.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis + n * acc).normalized();

    // Increase angular speed
    //angularSpeed += acc;

    // Update rotation
    rotation = QQuaternion::fromAxisAndAngle(rotationAxis, acc) * rotation;

    // Update scene
    updateGL();
}

void MyGLWidget::initializeGL()
{
    initializeGLFunctions();

    qglClearColor(Qt::white);

    qDebug() << "Initializing shaders...";
    initShaders();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    qDebug() << "Initializing cubes...";
    m_cubes->init();

    // using QBasicTimer because its faster that QTimer
    m_timer->start(12, this);
}

void MyGLWidget::initShaders()
{
    // Overriding system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compiling vertex shader
    if (!m_program->addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compiling fragment shader
    if (!m_program->addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Linking shader pipeline
    if (!m_program->link())
        close();

    // Binding shader pipeline for use
    if (!m_program->bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void MyGLWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = (qreal)w / ((qreal)h?h:1);

    const qreal m_zNear = 2.0, m_zFar = 100.0, m_fov = 45.0;

    // Reset projection
    m_projection.setToIdentity();

    // Set perspective projection
    m_projection.perspective(m_fov, aspect, m_zNear, m_zFar);
}

void MyGLWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 m_viewMatrix;
    m_viewMatrix.translate(m_translate);
    m_viewMatrix.rotate(rotation);

    // Set modelview-projection matrix
    m_program->setUniformValue("mvp_matrix", m_projection * m_viewMatrix);

    // Using texture unit 0 which contains cube.png
    m_program->setUniformValue("texture", 0);

    // Draw cube geometry
    m_cubes->drawCubes(m_program);
}

static void qNormalizeAngle(int &angle)
{
    while (angle < 0)
        angle += 360 * 16;
    while (angle > 360)
        angle -= 360 * 16;
}

void MyGLWidget::setXRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_rotation.x()) {
        m_rotation.setX(angle);
        updateGL();
    }
}

void MyGLWidget::setYRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_rotation.y()) {
        m_rotation.setY(angle);
        updateGL();
    }
}

void MyGLWidget::setZRotation(int angle)
{
    qNormalizeAngle(angle);
    if (angle != m_rotation.z()) {
        m_rotation.setZ(angle);
        updateGL();
    }
}


//void MyGLWidget::mousePressEvent(QMouseEvent *event)
//{
//    lastPos = event->pos();
//}

//void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
//{
//    int dx = event->x() - lastPos.x();
//    int dy = event->y() - lastPos.y();

//    if (event->buttons() & Qt::LeftButton) {
//        setXRotation(xRot + 8 * dy);
//        setYRotation(yRot + 8 * dx);
//    } else if (event->buttons() & Qt::RightButton) {
//        setXRotation(xRot + 8 * dy);
//        setZRotation(zRot + 8 * dx);
//    }

//    lastPos = event->pos();
//}
