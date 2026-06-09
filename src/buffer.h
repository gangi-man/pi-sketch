#pragma once
#include <stdint.h>

template<int HEIGHT, int WIDTH> class FrameBuffer {
    static bool gradation_table_init;
    static uint8_t gradation_table_x[WIDTH];
    static uint8_t gradation_table_y[HEIGHT];

    uint8_t m_buffer[HEIGHT][WIDTH];

public:
    static void initialize_gradation_table();
    
    FrameBuffer();
    inline void setPixel(uint16_t x, uint16_t y, uint8_t color);
    inline uint8_t getPixel(uint16_t x, uint16_t y);

    inline void copyScanline(uint8_t* scanline, uint16_t y);

    void clear(uint8_t color = 0x00);
};


template<int HEIGHT, int WIDTH>
bool FrameBuffer<HEIGHT, WIDTH>::gradation_table_init = false;

template<int HEIGHT, int WIDTH>
    uint8_t FrameBuffer<HEIGHT, WIDTH>::gradation_table_x[WIDTH] = {};

template<int HEIGHT, int WIDTH>
    uint8_t FrameBuffer<HEIGHT, WIDTH>::gradation_table_y[HEIGHT] = {};

template<int HEIGHT, int WIDTH>
void FrameBuffer<HEIGHT, WIDTH>::initialize_gradation_table()
{
    if (gradation_table_init)
        return;

    for (uint16_t x=0; x<WIDTH; x++)
        gradation_table_x[x] = 16 * x / WIDTH;
    for (uint16_t y=0; y<HEIGHT; y++)
        gradation_table_y[y] = 16 * y / HEIGHT;

    gradation_table_init = true;
}

template<int HEIGHT, int WIDTH>
FrameBuffer<HEIGHT, WIDTH>::FrameBuffer()
{
    clear(0x00);
}

template<int HEIGHT, int WIDTH>
void FrameBuffer<HEIGHT, WIDTH>::setPixel(uint16_t x, uint16_t y, uint8_t color)
{
    m_buffer[y][x] = color;
}

template<int HEIGHT, int WIDTH>
uint8_t FrameBuffer<HEIGHT, WIDTH>::getPixel(uint16_t x, uint16_t y)
{
    return m_buffer[y][x];
}

template<int HEIGHT, int WIDTH>
void FrameBuffer<HEIGHT, WIDTH>::copyScanline(uint8_t* scanline, uint16_t y)
{
    for (uint16_t x = 0; x<WIDTH; x++)
        *scanline++ = m_buffer[y][x];
}

template<int HEIGHT, int WIDTH>
void FrameBuffer<HEIGHT, WIDTH>::clear(uint8_t color)
{
    for (uint16_t y=0; y<HEIGHT; y++)
        for (uint16_t x=0; x<WIDTH; x++)
            m_buffer[y][x] = color;
}

