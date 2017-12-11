#include "File.h"
#include <QString>
#include <QDebug>

File::File(string filePath)
    : m_path(filePath)
{

#ifdef _WIN32
    m_name = m_path.substr(m_path.find_last_of('\\') + 1); // escape character
#else
    m_name = m_path.substr(m_path.find_last_of('/') + 1);
#endif
    m_ext = m_name.substr(m_name.find('.') + 1);
    m_type = findType(m_ext);
}

File::~File()
{
}

void File::printInfo() {
    qDebug() << m_path.c_str() << " " << m_name.c_str() << " " << m_ext.c_str();
}

int File::parseFile(CubeEngine* cubes) {
    switch(m_type) {
        case UNKNOWN:
            return -1;
        case STL:
            return parseSTL();
        case OBJ:
            return parseOBJ(cubes);
        default:
            return -1;
    }
}

File::fileType File::findType(string ext) {
    if (0 == ext.compare("stl")) {
        return STL;
    } else if (0 == ext.compare("obj")) {
        return OBJ;
    } else{
        return UNKNOWN;
    }
}
