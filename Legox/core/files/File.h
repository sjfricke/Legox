#ifndef _CORE_FILES_FILE_H_
#define _CORE_FILES_FILE_H_

#include <string>

#include "voxelizer.h"

using namespace std;

class File
{
public:
    File(string filePath);
	~File();

    // Parses file according to file type
    // Returns 0 on success
    int parseFile();

    void printInfo();

    // List of all files that we support importing
    enum fileType {
        UNKNOWN,
        STL,
        OBJ
    };

private:

    int parseSTL();
    int parseOBJ();

    // Takes extention and returns type
    fileType findType(string ext);

    string m_name;
    string m_path;
    string m_ext;
    fileType m_type;
};

#endif
