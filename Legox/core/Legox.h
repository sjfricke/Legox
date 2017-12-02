/* Legox
 * This is the "main" class that bridges the UI with the core data
 * When someone saves or loads a project they are saving/loading the Legox instance
*/

#ifndef _CORE_LEGOX_H_
#define _CORE_LEGOX_H_

#include "model/Bloxs.h"
#include "files/File.h"
#include "session/History.h"

#include <stdint.h>

#include <string>
#include <vector>

#include <QString>

using namespace std;

class Legox
{
public:
    Legox();
    ~Legox();

    // Creates a new file and parses it to blox data
    // Returns 0 on success
    int       newFile(QString filePath);

    History*  getHistory(void) { return mp_history; }

private:

    vector<Bloxs*> m_bloxsList;
    File*          mp_file;
    History*       mp_history;
};

#endif
