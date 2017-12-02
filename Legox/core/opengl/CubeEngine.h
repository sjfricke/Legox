#ifndef _CORE_OPENGL_CUBEENGINE_H
#define _CORE_OPENGL_CUBEENGINE_H

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>

class CubeEngine : protected QGLFunctions
{
public:
    CubeEngine();
    ~CubeEngine();

    void init();

    void drawCubes(QGLShaderProgram *program);

private:
    void initCubes();

    GLuint *vboIds;
};

#endif // _CORE_OPENGL_CUBEENGINE_H
