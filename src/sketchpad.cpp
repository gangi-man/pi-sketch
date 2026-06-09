#include "sketchpad.h"
#include <stdio.h>


Sketchpad::Sketchpad()
{
    m_color = 0xe0;
    m_x = Video::Width / 2;
    m_y = Video::Height / 2;
}

void Sketchpad::move(int16_t dx, int16_t dy)
{
    m_x += dx;
    if (m_x < 0)
        m_x = 0;
    if (m_x >= Video::Width)
        m_x = Video::Width - 1;

    m_y += dy;
    if (m_y < 0)
        m_y = 0;
    if (m_y >= Video::Height-4)
        m_y = Video::Height - 5; // FIXME vsync issue

    m_buffer.setPixel(m_x, m_y, 0xe0);
    m_buffer.setPixel(m_x, m_y+1, 0xe0);
}
