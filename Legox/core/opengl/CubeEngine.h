#ifndef _CORE_OPENGL_CUBEENGINE_H
#define _CORE_OPENGL_CUBEENGINE_H

#include <QtOpenGL/QGLFunctions>
#include <QtOpenGL/QGLShaderProgram>

typedef struct
{
    QVector3D position;
    QVector3D color;
} vertexData;

class CubeEngine : protected QGLFunctions
{
public:
    CubeEngine();
    ~CubeEngine();


    void init(int vert, int ind);

    void addCube(QVector3D pos, QVector3D color = QVector3D(1.0,0.0,0.0));
    void setupCubes(int vert, int ind);
    void drawCubes(QGLShaderProgram *program);

    vertexData* m_vertices;
    void*       m_indices;

private:

    void initCubes();
    int m_int;
    GLuint*     vboIds;
//    vertexData* m_vertices;
//    void*       m_indices;
    GLushort    m_cubeCount;
};

#endif // _CORE_OPENGL_CUBEENGINE_H
