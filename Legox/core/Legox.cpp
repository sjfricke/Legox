#include "Legox.h"

Legox::Legox()
    : mp_file(nullptr)
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
}

int Legox::newFile(QString filePath) {
    if (nullptr != mp_file) { delete mp_file; }

    mp_file = new File(filePath.toStdString());
    int rv = mp_file->parseFile();

    return rv; // rv == returnValue
}