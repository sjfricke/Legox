#include "Legox.h"

Legox::Legox()
    : mp_file(nullptr),
      m_cubes(new CubeEngine)
{
    mp_history = new History();
}

Legox::~Legox()
{
    if (mp_history != nullptr) { delete mp_history; }
    if (mp_file != nullptr) { delete mp_file; }
    for (int i = m_bloxsList.size(); i > 0; i--) {
        delete m_bloxsList.at(i);
    }
    delete m_cubes; m_cubes = 0;
}

int Legox::newFile(QString filePath, CubeEngine* cubes ) {
    if (nullptr != mp_file) { delete mp_file; }

    mp_file = new File(filePath.toStdString());

    int rv = mp_file->parseFile(cubes);

    return rv; // rv == returnValue
}
