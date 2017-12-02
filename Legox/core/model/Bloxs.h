/* Bloxs
 * This class is used to represent that intermediate data of the blocks
 * Origin of Bloxs is the top left corner facing front of machine
 * Data is stored in ZXY fashion so each layers (XY) is together
 */
#ifndef _CORE_MODEL_BLOX_H_
#define _CORE_MODEL_BLOX_H_

#include <stdint.h>
#include "../utils/utils.h"

using namespace std;

class Bloxs
{
public:
    Bloxs(int xSize, int ySize, int zSize);
    ~Bloxs();

    void populateData();
private:

    // Size of total blocks in each direction
    vec3 m_size;

    // internal bloxs to make up size
    vec3 m_bloxSize;

    vec3 m_rotation;
    vec3 m_translation;
    vec3 m_scale;

    // m_data[z][x][y] where [x][y] are a layer
    uint8_t*** m_data;

};

#endif
