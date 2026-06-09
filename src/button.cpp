#include "button.h"
#include "hardware/gpio.h"


void Button::initialize()
{
    gpio_init(m_port);
    gpio_set_dir(m_port, GPIO_IN);
    gpio_pull_up(m_port);
}

bool Button::check()
{
    return !gpio_get(m_port);
}
