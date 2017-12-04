#include "CubeEngine.h"

#include <QVector2D>
#include <QVector3D>



CubeEngine::CubeEngine()
    : vboIds(new GLuint[2]),
      m_cubeCount(0),
      m_vertices(NULL),
      m_indices(NULL)
{
}

CubeEngine::~CubeEngine()
{
    glDeleteBuffers(2, vboIds);
    delete[] vboIds;
    if (m_vertices != NULL) { free(m_vertices); }
    if (m_indices != NULL) { free(m_indices); }

}

void CubeEngine::init()
{
    initializeGLFunctions();

    // Generate 2 VBOs
    glGenBuffers(2, vboIds);

    int cubes = 2;
    m_vertices = (vertexData*)malloc(sizeof(vertexData) * 24 * cubes);
    m_indices = (void*)malloc(sizeof(GLushort) * 34 * cubes);

    if (m_vertices == NULL) { qDebug() << "FAILL VERTICES MALLOC"; }
    if (m_indices == NULL) { qDebug() << "FAILL INDICES MALLOC";  }

    // Initializes cube geometry and transfers it to VBOs
    addCube(QVector3D(2.0,0.0,0.0), QVector3D(0.0,1.0,0.0));
    addCube(QVector3D(0.0,0.0,0.0), QVector3D(1.0,0.0,0.0));
    setupCubes();
}

void CubeEngine::initCubes()
{
    // For cube we would need only 8 vertices but we have to
    // duplicate vertex for each face because texture coordinate
    // is different.
    vertexData vertices[] = {
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

    vertexData vertices2[] = {
        // Vertex data for face 0
        {QVector3D(0.0, 0.0, 2.0), QVector3D(0.0, 0.0, 1.0)},  // v0
        {QVector3D(2.0, 0.0, 2.0), QVector3D(0.0, 0.0, 1.0)}, // v1
        {QVector3D(0.0, 2.0, 2.0), QVector3D(0.0, 0.0, 1.0)},  // v2
        {QVector3D(2.0, 2.0, 2.0), QVector3D(0.0, 0.0, 1.0)}, // v3

        // Vertex data for face 1
        {QVector3D(2.0, 0.0, 2.0), QVector3D(1.0, 1.0, 0.0)}, // v4
        {QVector3D(2.0, 0.0, 0.0), QVector3D(1.0, 1.0, 0.0)}, // v5
        {QVector3D(2.0, 2.0, 2.0), QVector3D(1.0, 1.0, 0.0)}, // v6
        {QVector3D(2.0, 2.0, 0.0), QVector3D(1.0, 1.0, 0.0)}, // v7

        // Vertex data for face 2
        {QVector3D(2.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v8
        {QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0)},  // v9
        {QVector3D(2.0, 2.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v10
        {QVector3D(0.0, 2.0, 0.0), QVector3D(0.0, 0.0, 1.0)},  // v11

        // Vertex data for face 3
        {QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v12
        {QVector3D(0.0, 0.0, 2.0), QVector3D(0.0, 0.0, 1.0)},  // v13
        {QVector3D(0.0, 2.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v14
        {QVector3D(0.0, 2.0, 2.0), QVector3D(0.0, 0.0, 1.0)},  // v15

        // Vertex data for face 4
        {QVector3D(0.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v16
        {QVector3D(2.0, 0.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v17
        {QVector3D(0.0, 0.0, 2.0), QVector3D(0.0, 0.0, 1.0)}, // v18
        {QVector3D(2.0, 0.0, 2.0), QVector3D(0.0, 0.0, 1.0)}, // v19

        // Vertex data for face 5
        {QVector3D(0.0, 2.0, 2.0), QVector3D(0.0, 0.0, 1.0)}, // v20
        {QVector3D(2.0, 2.0, 2.0), QVector3D(0.0, 0.0, 1.0)}, // v21
        {QVector3D(0.0, 2.0, 0.0), QVector3D(0.0, 0.0, 1.0)}, // v22
        {QVector3D(2.0, 2.0, 0.0), QVector3D(0.0, 0.0, 1.0)}  // v23
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

    GLushort indices2[] = {
         24,  25,  26,  27,  27,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
         28,  28,  29,  30, 31,  31, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
         32,  32,  33, 34, 35, 35, // Face 2 - triangle strip ( v8,  v9, v10, v11)
        36, 36, 37, 38, 39, 39, // Face 3 - triangle strip (v12, v13, v14, v15)
        40, 40, 41, 42, 43, 43, // Face 4 - triangle strip (v16, v17, v18, v19)
        44, 44, 45, 46, 47      // Face 5 - triangle strip (v20, v21, v22, v23)
    };

    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(vertexData), vertices2, GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(GLushort), indices, GL_STATIC_DRAW);
}

void CubeEngine::addCube(QVector3D pos, QVector3D color)
{
    float x = pos.x();
    float y = pos.y();
    float z = pos.z();
    GLushort c = static_cast<GLushort>(m_cubeCount * (GLushort)24);

    vertexData vertices[] = {
        // Vertex data for face 0
        {QVector3D(x-1.0, y-1.0, z+1.0), color},  // v0
        {QVector3D(x+1.0, y-1.0, z+1.0), color}, // v1
        {QVector3D(x-1.0, y+1.0, z+1.0), color},  // v2
        {QVector3D(x+1.0, y+1.0, z+1.0), color}, // v3

        // Vertex data for face 1
        {QVector3D(x+1.0, y-1.0, z+1.0), color}, // v4
        {QVector3D(x+1.0, y-1.0, z-1.0), color}, // v5
        {QVector3D(x+1.0, y+1.0, z+1.0), color}, // v6
        {QVector3D(x+1.0, y+1.0, z-1.0), color}, // v7

        // Vertex data for face 2
        {QVector3D(x+1.0, y-1.0, z-1.0), color}, // v8
        {QVector3D(x-1.0, y-1.0, z-1.0), color},  // v9
        {QVector3D(x+1.0, y+1.0, z-1.0), color}, // v10
        {QVector3D(x-1.0, y+1.0, z-1.0), color},  // v11

        // Vertex data for face 3
        {QVector3D(x-1.0, y-1.0, z-1.0), color}, // v12
        {QVector3D(x-1.0, y-1.0, z+1.0), color},  // v13
        {QVector3D(x-1.0, y+1.0, z-1.0), color}, // v14
        {QVector3D(x-1.0, y+1.0, z+1.0), color},  // v15

        // Vertex data for face 4
        {QVector3D(x-1.0, y-1.0, z-1.0), color}, // v16
        {QVector3D(x+1.0, y-1.0, z-1.0), color}, // v17
        {QVector3D(x-1.0, y-1.0, z+1.0), color}, // v18
        {QVector3D(x+1.0, y-1.0, z+1.0), color}, // v19

        // Vertex data for face 5
        {QVector3D(x-1.0, y+1.0, z+1.0), color}, // v20
        {QVector3D(x+1.0, y+1.0, z+1.0), color}, // v21
        {QVector3D(x-1.0, y+1.0, z-1.0), color}, // v22
        {QVector3D(x+1.0, y+1.0, z-1.0), color}  // v23
    };

    GLushort indices[] = {
                c+(GLushort)0,  c+(GLushort)1,  c+(GLushort)2,  c+(GLushort)3,  c+(GLushort)3,        // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
                c+(GLushort)4,  c+(GLushort)4,  c+(GLushort)5,  c+(GLushort)6,  c+(GLushort)7,  c+(GLushort)7,  // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
                c+(GLushort)8,  c+(GLushort)8,  c+(GLushort)9,  c+(GLushort)10, c+(GLushort)11, c+(GLushort)11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
                c+(GLushort)12, c+(GLushort)12, c+(GLushort)13, c+(GLushort)14, c+(GLushort)15, c+(GLushort)15, // Face 3 - triangle strip (v12, v13, v14, v15)
                c+(GLushort)16, c+(GLushort)16, c+(GLushort)17, c+(GLushort)18, c+(GLushort)19, c+(GLushort)19, // Face 4 - triangle strip (v16, v17, v18, v19)
                c+(GLushort)20, c+(GLushort)20, c+(GLushort)21, c+(GLushort)22, c+(GLushort)23        // Face 5 - triangle strip (v20, v21, v22, v23)
            };
    qDebug() << indices[0];

    memcpy(static_cast<void*>(&m_vertices[m_cubeCount*24]),static_cast<void*>(&vertices), sizeof(vertexData) * 24);
    memcpy(m_indices + (m_cubeCount*34*sizeof(GLushort)), static_cast<void*>(&indices), sizeof(GLushort) * 34);

    m_cubeCount++;
}

void CubeEngine::setupCubes()
{
    // Transfer vertex data to VBO 0
    glBindBuffer(GL_ARRAY_BUFFER, vboIds[0]);
    glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(vertexData) * m_cubeCount, static_cast<void*>(m_vertices), GL_STATIC_DRAW);

    // Transfer index data to VBO 1
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIds[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 34 * sizeof(GLushort) * m_cubeCount, static_cast<void*>(m_indices), GL_STATIC_DRAW);
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
    glVertexAttribPointer(vertexLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (const void *)offset);

    // Offset for texture coordinate
    offset += sizeof(QVector3D);

    int colorLocation = program->attributeLocation("a_color");
    program->enableAttributeArray(colorLocation);
    glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, sizeof(vertexData), (const void *)offset);

    // Draw cube geometry using indices from VBO 1
    glDrawElements(GL_TRIANGLE_STRIP, 34 * m_cubeCount, GL_UNSIGNED_SHORT, 0);
}
