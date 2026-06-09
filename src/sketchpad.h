#pragma once
#include "buffer.h"
#include "video_configuration.h"


class Sketchpad {
    FrameBuffer<Video::Height, Video::Width> m_buffer;

    uint8_t m_color;
    int16_t m_x;
    int16_t m_y;

public:
    Sketchpad();
    FrameBuffer<Video::Height, Video::Width>* buffer() { return &m_buffer; }

    void move(int16_t dx, int16_t dy);
};
