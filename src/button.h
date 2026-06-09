#pragma once
#include <stdint.h>


class Button {
    uint8_t m_port;
public:
    Button(uint8_t port) : m_port(port) {}

    void initialize();
    bool check();
};
