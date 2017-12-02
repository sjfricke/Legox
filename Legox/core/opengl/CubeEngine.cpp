#include "CubeEngine.h"

#include <QVector2D>
#include <QVector3D>

struct VertexData
{
    QVector3D position;
    QVector3D color;
};

CubeEngine::CubeEngine()
    : vboIds(new GLuint[2])
{
}

CubeEngine::~CubeEngine()
{
    glDeleteBuffers(2, vboIds);
    delete[] vboIds;
}

void CubeEngine::init()
{
    initializeGLFunctions();

    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    // Initializes cube geometry and transfers it to VBOs
    initCubes();
}

void CubeEngine::initCubes()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    VertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v0
        {QVector3D( 1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v1
        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v2
        {QVector3D( 1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v3

        // Vertex data for face 1
        {QVector3D( 1.0, -1.0,  1.0), QVector3D(0.0, 1.0, 0.0)}, // v4
        {QVector3D( 1.0, -1.0, -1.0), QVector3D(0.0, 1.0, 0.0)}, // v5
        {QVector3D( 1.0,  1.0,  1.0), QVector3D(0.0, 1.0, 0.0)}, // v6
        {QVector3D( 1.0,  1.0, -1.0), QVector3D(0.0, 1.0, 0.0)}, // v7

        // Vertex data for face 2
        {QVector3D( 1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v8
        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)},  // v9
        {QVector3D( 1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v10
        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)},  // v11

        // Vertex data for face 3
        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v12
        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v13
        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v14
        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v15

        // Vertex data for face 4
        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v16
        {QVector3D( 1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v17
        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v18
        {QVector3D( 1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v19

        // Vertex data for face 5
        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v20
        {QVector3D( 1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v21
        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v22
        {QVector3D( 1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}  // v23
    };

    // Indices for drawing cube faces using triangle strips.
    // Triangle strips can be connected by duplicating indices
    // between the strips. If connecting strips have opposite
    // vertex order then last index of the first strip and first
    // index of the second strip needs to be duplicated. If
    // connecting strips have same vertex order then only last
    // index of the first strip needs to be duplicated.
    GLushort indices[] = {
         0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
        16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
        20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(VertexData), vertices, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

void CubeEngine::drawCubes(QGLShaderProgram *program)
{
    // Tell OpenGL which VBOs to use
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);

    // Offset for position
    int offset = 0;

    // Tell OpenGL programmable pipeline how to locate vertex position data
    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34, GL_UNSIGNED_SHORT, 0);
}
