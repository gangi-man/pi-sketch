#include "rotary_encoder.h"
#include "hardware/gpio.h"
#include <stdio.h>


RotaryEncoder* RotaryEncoder::RotaryEncoderList[RotaryEncoder::RotaryEncoderCount];


void RotaryEncoder::register_interrupt(uint8_t encoderNumber, RotaryEncoder* encoder)
{
    if (encoderNumber < RotaryEncoderCount) {
        RotaryEncoderList[encoderNumber] = encoder;

        gpio_set_irq_enabled_with_callback(
            encoder->portA(),
            GPIO_IRQ_EDGE_RISE,
            true,
            RotaryEncoder::rising_edge_callback
            );
    }
}

void RotaryEncoder::rising_edge_callback(uint gpio, uint32_t event)
{
    RotaryEncoder* encoder = 0;
    
    for (uint8_t i=0; i<RotaryEncoder::RotaryEncoderCount; i++) {
        if (RotaryEncoderList[i]->m_portA == gpio)
            encoder = RotaryEncoderList[i];
    }

    if (encoder) {
        if (gpio_get(encoder->m_portB))
            encoder->m_value--;
        else
            encoder->m_value++;
    }
}


void RotaryEncoder::initialize()
{
    gpio_init(m_portA);
    gpio_init(m_portB);

    gpio_set_dir(m_portA, GPIO_IN);
    gpio_set_dir(m_portB, GPIO_IN);

    register_interrupt(m_id, this);
}
