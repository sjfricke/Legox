#include "Bloxs.h"

Bloxs::Bloxs(int xSize, int ySize, int zSize)
{
    m_size = {xSize, ySize, zSize};
    // Fast ceiling for uint div
    // q = 1 + ((x - 1) / y); // if x != 0

    m_bloxSize.x = 1 + ((m_size.x - 1) / 8);
    m_bloxSize.y = 1 + ((m_size.y - 1) / 8);
    m_bloxSize.z = 1 + ((m_size.z - 1) / 8);

    m_rotation = {0,0,0};
    m_translation = {0,0,0};
    m_scale = {0,0,0};

    m_data = new uint8_t**[m_size.z];
    for(int z = 0; z < m_size.z; ++z) {
        m_data[z] = new uint8_t*[m_size.x];
        for(int x = 0; x < m_size.x; ++x) {
            m_data[z][x] = new uint8_t[m_size.y];
            for(int y = 0; y < m_size.y; ++y) {
                m_data[z][x][y] = 0;
            }
        }
    }
}

Bloxs::~Bloxs()
{
    for(int z = 0; z < m_size.z; ++z) {
        for(int x = 0; x < m_size.x; ++x) {
           delete m_data[z][x];
        }
        delete m_data[z];
    }
    delete m_data;
}

void Bloxs::populateData()
{
    // Hardcode testing test_1000 design
    m_data[0][3][1] = 0x1; m_data[0][3][2] = 0x1; m_data[0][3][3] = 0x1;
    m_data[0][4][1] = 0x1; m_data[0][4][2] = 0x1; m_data[0][4][3] = 0x1;
    m_data[1][3][2] = 0x1; m_data[1][3][3] = 0x1; m_data[1][4][2] = 0x1;  m_data[1][4][3] = 0x1;
    m_data[2][3][3] = 0x1; m_data[2][3][4] = 0x1; m_data[2][3][5] = 0x1;  m_data[2][3][6] = 0x1;
    m_data[2][4][3] = 0x1; m_data[2][4][4] = 0x1; m_data[2][4][5] = 0x1;  m_data[2][4][6] = 0x1;
}
