#pragma once
#include <stdint.h>
#include "hardware/irq.h"


class RotaryEncoder {

    static RotaryEncoder* RotaryEncoderList[];

    static void register_interrupt(uint8_t encoderNumber, RotaryEncoder* encoder);
    static void rising_edge_callback(uint gpio, uint32_t events);

public:
    uint8_t m_id;
    uint8_t m_portA;
    uint8_t m_portB;

    int16_t m_value;
    
public:
    static const int RotaryEncoderCount = 2;
    
    RotaryEncoder(uint8_t id, uint8_t portA, uint8_t portB) :
        m_id(id), m_portA(portA), m_portB(portB) { }

    void initialize();

    void setValue(int16_t value) { m_value = value; }
    int16_t getValue() { return m_value; }

    inline uint8_t portA() { return m_portA; }
    inline uint8_t portB() { return m_portB; }
};
