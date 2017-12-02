/* History
 * This is where all session history is stored in stack for two reason
 * First to allow for undo and redo of commands
 * Second to save project status and monitor other info
 */

#ifndef _CORE_SESSION_HISTORY_H_
#define _CORE_SESSION_HISTORY_H_

#include <stack>

using namespace std;

class History
{
public:
    History();
    ~History();

    typedef enum {
        ROTATE,
        TRANSLATE,
        SCALE,
        ADD_BLOX,
        DELETE_BLOX
    } historyOperations;

    typedef struct {
        historyOperations operation;
        int               valueX;
        int               valueY;
        int               valueZ;
    } historyStack;

private:

    stack<historyStack> m_stack;

};

#endif
