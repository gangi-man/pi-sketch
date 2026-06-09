#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hardware/clocks.h"
#include "hardware/irq.h"
#include "hardware/sync.h"
#include "hardware/gpio.h"
#include "hardware/vreg.h"

#include "dvi.h"
#include "dvi_serialiser.h"
#include "common_dvi_pin_configs.h"

#include "video_configuration.h"
#include "buffer.h"
#include "button.h"
#include "rotary_encoder.h"
#include "sketchpad.h"


#define VREG_VSEL VREG_VOLTAGE_1_20
#define DVI_TIMING dvi_timing_640x480p_60hz


Button ButtonDismiss(20);
Button ButtonEnter(26);

RotaryEncoder RotarySwitchLeft(0, 21, 22);
RotaryEncoder RotarySwitchRight(1, 27, 28);

Sketchpad PiSketchpad;

struct dvi_inst dvi0;

void core1_main()
{
    dvi_register_irqs_this_core(&dvi0, DMA_IRQ_0);
    while (queue_is_empty(&dvi0.q_colour_valid))
        __wfe();

    dvi_start(&dvi0);
    dvi_scanbuf_main_8bpp(&dvi0);
}


static volatile int cb_counter = 0;
void scan_callback()
{
    cb_counter++;
}

inline void wait_until_last_scanline()
{
    while ( ((cb_counter*2) % (Video::Height)) != 0)
        ;
}

void initialize_dvi()
{
    vreg_set_voltage(VREG_VSEL);
    sleep_ms(10);
    set_sys_clock_khz(DVI_TIMING.bit_clk_khz, true);

    setup_default_uart();

    dvi0.timing = &DVI_TIMING;
    dvi0.ser_cfg = DVI_DEFAULT_SERIAL_CONFIG;
    dvi0.scanline_callback = scan_callback;
    dvi_init(&dvi0, next_striped_spin_lock_num(), next_striped_spin_lock_num());

    multicore_launch_core1(core1_main);
}


void initialize_switches()
{
    RotarySwitchLeft.initialize();
    RotarySwitchRight.initialize();

    ButtonDismiss.initialize();
    ButtonEnter.initialize();
}


void update_scanlines()
{
    uint8_t line_buffer[Video::Width];
    uint8_t* scanline;
    
    for (uint y=0; y<Video::Height; y++) {
        PiSketchpad.buffer()->copyScanline(line_buffer, y);
        scanline = line_buffer;
        queue_add_blocking_u32(&dvi0.q_colour_valid, &scanline);
        y = (y + 1) % Video::Height;
        while (queue_try_remove_u32(&dvi0.q_colour_free, &scanline)) {
        }
    }
}

int main() {
    stdio_init_all();
    initialize_dvi();
    initialize_switches();

    
    const uint8_t DefaultColor = 0x1c;

    PiSketchpad.buffer()->clear(DefaultColor);
    while(true) {
        update_scanlines();
        wait_until_last_scanline();

        PiSketchpad.move(RotarySwitchLeft.getValue(),
                         -2*RotarySwitchRight.getValue());

        RotarySwitchLeft.setValue(0);
        RotarySwitchRight.setValue(0);

        if (ButtonEnter.check())
            PiSketchpad.buffer()->clear(DefaultColor);

        if (ButtonDismiss.check())
            ;
    }
}
