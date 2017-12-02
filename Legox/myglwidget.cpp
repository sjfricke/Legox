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
      timer(new QBasicTimer),
      program(new QGLShaderProgram),
      cubes(new CubeEngine)
{
//    xRot = 0;
//    yRot = 0;
//    zRot = 0;
}

MyGLWidget::~MyGLWidget()
{
    delete timer; timer = 0;
    delete program; program = 0;
    delete cubes; cubes = 0;

    deleteTexture(texture);
}

//QSize MyGLWidget::minimumSizeHint() const
//{
//    return QSize(50, 50);
//}

//QSize MyGLWidget::sizeHint() const
//{
//    return QSize(400, 400);
//}

void MyGLWidget::mousePressEvent(QMouseEvent *e)
{
    // Saving mouse press position
    mousePressPosition = QVector2D(e->pos());
}

void MyGLWidget::mouseReleaseEvent(QMouseEvent *e)
{
    // Mouse release position - mouse press position
    QVector2D diff = QVector2D(e->pos()) - mousePressPosition;

    // Rotation axis is perpendicular to the mouse position difference
    // vector
    QVector3D n = QVector3D(diff.y(), diff.x(), 0.0).normalized();

    // Accelerate angular speed relative to the length of the mouse sweep
    qreal acc = diff.length() / 100.0;

    // Calculate new rotation axis as weighted sum
    rotationAxis = (rotationAxis * angularSpeed + n * acc).normalized();

    // Increase angular speed
    angularSpeed += acc;
}

void MyGLWidget::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);

    // Decrease angular speed (friction)
    angularSpeed *= 0.99;

    // Stop rotation when speed goes below threshold
    if (angularSpeed < 0.01)
        angularSpeed = 0.0;
    else {
        // Update rotation
        rotation = QQuaternion::fromAxisAndAngle(rotationAxis, angularSpeed) * rotation;

        // Update scene
        updateGL();
    }
}


void MyGLWidget::initializeGL()
{
    initializeGLFunctions();

    qglClearColor(Qt::white);

    qDebug() << "Initializing shaders...";
    initShaders();

    qDebug() << "Initializing textures...";
    initTextures();

    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);

    // Enable back face culling
    glEnable(GL_CULL_FACE);

    qDebug() << "Initializing cubes...";
    cubes->init();

    // using QBasicTimer because its faster that QTimer
    timer->start(12, this);
}

void MyGLWidget::initShaders()
{
    // Overriding system locale until shaders are compiled
    setlocale(LC_NUMERIC, "C");

    // Compiling vertex shader
    if (!program->addShaderFromSourceFile(QGLShader::Vertex, ":/vshader.glsl"))
        close();

    // Compiling fragment shader
    if (!program->addShaderFromSourceFile(QGLShader::Fragment, ":/fshader.glsl"))
        close();

    // Linking shader pipeline
    if (!program->link())
        close();

    // Binding shader pipeline for use
    if (!program->bind())
        close();

    // Restore system locale
    setlocale(LC_ALL, "");
}

void MyGLWidget::initTextures()
{
//    // Loading cube.png to texture unit 0
//    glActiveTexture(GL_TEXTURE0);
//    glEnable(GL_TEXTURE_2D);
//    texture = bindTexture(QImage(":/cube.png"));

//    // Set nearest filtering mode for texture minification
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

//    // Set bilinear filtering mode for texture magnification
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

//    // Wrap texture coordinates by repeating
//    // f.ex. texture coordinate (1.1, 1.2) is same as (0.1, 0.2)
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void MyGLWidget::resizeGL(int w, int h)
{
    // Set OpenGL viewport to cover whole widget
    glViewport(0, 0, w, h);

    // Calculate aspect ratio
    qreal aspect = (qreal)w / ((qreal)h?h:1);

    // Set near plane to 3.0, far plane to 7.0, field of view 45 degrees
    const qreal zNear = 3.0, zFar = 7.0, fov = 45.0;

    // Reset projection
    projection.setToIdentity();

    // Set perspective projection
    projection.perspective(fov, aspect, zNear, zFar);
}

void MyGLWidget::paintGL()
{
    // Clear color and depth buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Calculate model view transformation
    QMatrix4x4 matrix;
    matrix.translate(0.0, 0.0, -5.0);
    matrix.rotate(rotation);

    // Set modelview-projection matrix
    program->setUniformValue("mvp_matrix", projection * matrix);

    // Using texture unit 0 which contains cube.png
    program->setUniformValue("texture", 0);

    // Draw cube geometry
    cubes->drawCubes(program);
}

//static void qNormalizeAngle(int &angle)
//{
//    while (angle < 0)
//        angle += 360 * 16;
//    while (angle > 360)
//        angle -= 360 * 16;
//}

//void MyGLWidget::setXRotation(int angle)
//{
//    qNormalizeAngle(angle);
//    if (angle != xRot) {
//        xRot = angle;
//        emit xRotationChanged(angle);
//        updateGL();
//    }
//}

//void MyGLWidget::setYRotation(int angle)
//{
//    qNormalizeAngle(angle);
//    if (angle != yRot) {
//        yRot = angle;
//        emit yRotationChanged(angle);
//        updateGL();
//    }
//}

//void MyGLWidget::setZRotation(int angle)
//{
//    qNormalizeAngle(angle);
//    if (angle != zRot) {
//        zRot = angle;
//        emit zRotationChanged(angle);
//        updateGL();
//    }
//}

//void MyGLWidget::initializeGL()
//{
//    qglClearColor(Qt::white);

//    glEnable(GL_DEPTH_TEST);
//    glEnable(GL_CULL_FACE);
//    glShadeModel(GL_SMOOTH);
//    glEnable(GL_LIGHTING);
//    glEnable(GL_LIGHT0);

//    static GLfloat lightPosition[4] = { 0, 50, 100, 1.0 };
//    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
//}

//void MyGLWidget::paintGL()
//{
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glLoadIdentity();
//    glTranslatef(0.0, 0.0, -10.0);
//    glRotatef(xRot / 16.0, 1.0, 0.0, 0.0);
//    glRotatef(yRot / 16.0, 0.0, 1.0, 0.0);
//    glRotatef(zRot / 16.0, 0.0, 0.0, 1.0);
//    draw();
//}

//void MyGLWidget::resizeGL(int width, int height)
//{
//    int side = qMin(width, height);
//    glViewport((width - side) / 2, (height - side) / 2, side, side);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//#ifdef QT_OPENGL_ES_1
//    glOrthof(-2, +2, -2, +2, 1.0, 15.0);
//#else
//    glOrtho(-2, +2, -2, +2, 1.0, 15.0);
//#endif
//    glMatrixMode(GL_MODELVIEW);
//}

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
