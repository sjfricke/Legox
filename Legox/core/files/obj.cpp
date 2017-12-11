#include "File.h"

#define VOXELIZER_IMPLEMENTATION
#include "voxelizer.h"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <iostream>
#include <sstream>
#include <fstream>


int File::parseOBJ(CubeEngine* cubes) {

//    vertexData vertices[] = {
//        // Vertex data for face 0
//        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v0
//        {QVector3D( 1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v1
//        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v2
//        {QVector3D( 1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v3

//        // Vertex data for face 1
//        {QVector3D( 1.0, -1.0,  1.0), QVector3D(0.0, 1.0, 0.0)}, // v4
//        {QVector3D( 1.0, -1.0, -1.0), QVector3D(0.0, 1.0, 0.0)}, // v5
//        {QVector3D( 1.0,  1.0,  1.0), QVector3D(0.0, 1.0, 0.0)}, // v6
//        {QVector3D( 1.0,  1.0, -1.0), QVector3D(0.0, 1.0, 0.0)}, // v7

//        // Vertex data for face 2
//        {QVector3D( 1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v8
//        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)},  // v9
//        {QVector3D( 1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v10
//        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)},  // v11

//        // Vertex data for face 3
//        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v12
//        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v13
//        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v14
//        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)},  // v15

//        // Vertex data for face 4
//        {QVector3D(-1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v16
//        {QVector3D( 1.0, -1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v17
//        {QVector3D(-1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v18
//        {QVector3D( 1.0, -1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v19

//        // Vertex data for face 5
//        {QVector3D(-1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v20
//        {QVector3D( 1.0,  1.0,  1.0), QVector3D(1.0, 0.0, 0.0)}, // v21
//        {QVector3D(-1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}, // v22
//        {QVector3D( 1.0,  1.0, -1.0), QVector3D(1.0, 0.0, 0.0)}  // v23
//    };


//    GLushort indices[] = {
//             0,  1,  2,  3,  3,     // Face 0 - triangle strip ( v0,  v1,  v2,  v3)
//             4,  4,  5,  6,  7,  7, // Face 1 - triangle strip ( v4,  v5,  v6,  v7)
//             8,  8,  9, 10, 11, 11, // Face 2 - triangle strip ( v8,  v9, v10, v11)
//            12, 12, 13, 14, 15, 15, // Face 3 - triangle strip (v12, v13, v14, v15)
//            16, 16, 17, 18, 19, 19, // Face 4 - triangle strip (v16, v17, v18, v19)
//            20, 20, 21, 22, 23      // Face 5 - triangle strip (v20, v21, v22, v23)
//        };



    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string err;
    bool ret = tinyobj::LoadObj(shapes, materials, err, m_path.c_str(), NULL);

    if (!ret) { return -1; }
    qDebug() << "size shapes" << shapes.size();

    int vert = shapes[0].mesh.positions.size() / 3;
    int ind = shapes[0].mesh.indices.size();

    cubes->init(vert,ind);
QVector3D color;
    for (size_t i = 0; i < shapes.size(); i++) {

        for (size_t f = 0; f < shapes[0].mesh.indices.size(); f++) {
            static_cast<GLushort*>(cubes->m_indices)[f] = static_cast<GLushort>(shapes[i].mesh.indices[f]);
        }
        for (size_t v = 0; v < shapes[0].mesh.positions.size() / 3; v++) {
            if (shapes[i].mesh.positions[3*v+1] < -1.4) {color = QVector3D(1.0,0.0,0.0);}
           else if (shapes[i].mesh.positions[3*v+1] < -.8){ color = QVector3D(0.0,1.0,0.0);}
           else if (shapes[i].mesh.positions[3*v+1] < .2) {color = QVector3D(0.0,0.0,1.0);}
           else if (shapes[i].mesh.positions[3*v+1] < .4){ color = QVector3D(1.0,1.0,0.0);}
           else if (shapes[i].mesh.positions[3*v+1] < 1) {color = QVector3D(0.0,1.0,1.0);}
            else { color = QVector3D(1.0,0.0,1.0);}
            vertexData temp = {
                QVector3D(shapes[0].mesh.positions[3*v+0], shapes[i].mesh.positions[3*v+1], shapes[i].mesh.positions[3*v+2]),
                color
            };
            memcpy(static_cast<void*>(&(cubes->m_vertices[v])),static_cast<void*>(&temp), sizeof(vertexData));
        }

    }


    //memcpy(cubes->m_indices, static_cast<void*>(&indices), sizeof(GLushort) * ind);

    cubes->setupCubes(vert, ind);
    return 0;
}
