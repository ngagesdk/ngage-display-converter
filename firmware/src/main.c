#include <stdbool.h>
#include <stdint.h>
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

#include "frame_buffer_rgb565.h"
#include "ngage.h"

// DVDD 1.2V (1.1V seems ok too)
#define VREG_VSEL  VREG_VOLTAGE_1_20
#define DVI_TIMING dvi_timing_640x480p_60hz

struct dvi_inst dvi0;

void core1_main()
{
    dvi_register_irqs_this_core(&dvi0, DMA_IRQ_0);
    while (queue_is_empty(&dvi0.q_colour_valid))
    {
        __wfe();
    }
    dvi_start(&dvi0);
    dvi_scanbuf_main_16bpp(&dvi0);
}

int main()
{
    vreg_set_voltage(VREG_VSEL);
    sleep_ms(10);
    set_sys_clock_khz(DVI_TIMING.bit_clk_khz, true);

    setup_default_uart();

    dvi0.timing  = &DVI_TIMING;
    dvi0.ser_cfg = DVI_DEFAULT_SERIAL_CONFIG;
    dvi_init(&dvi0, next_striped_spin_lock_num(), next_striped_spin_lock_num());

    // Core 1 will wait until it sees the first colour buffer, then
    // start up the DVI signalling.
    multicore_launch_core1(core1_main);

    // Pass out pointers into our preprepared image, discard the
    // pointers when returned to us.
    while(true)
    {
        uint disp_line = 0;

        update_display_buffer();

        for (uint8_t curr_line = DISPLAY_OFFSET_Y; curr_line < (DISPLAY_OFFSET_Y + NGAGE_DISPLAY_HEIGHT); ++curr_line)
        {
            for (uint disp_pos = 0; disp_pos < NGAGE_BUFFER_WIDTH; ++disp_pos)
            {
                frame_buffer_rgb565[((curr_line * FRAME_WIDTH) * 2) + (DISPLAY_OFFSET_X + disp_pos)] =
                    display_buffer_rgb565[(disp_line * NGAGE_BUFFER_WIDTH) + disp_pos];
            }
            disp_line++;
        }
        disp_line = 0;

        for (uint8_t curr_line = 0; curr_line < FRAME_HEIGHT; ++curr_line)
        {
            uint16_t* scanline = &((uint16_t*)frame_buffer_rgb565)[curr_line * FRAME_WIDTH];
            queue_add_blocking_u32(&dvi0.q_colour_valid, &scanline);
            while (queue_try_remove_u32(&dvi0.q_colour_free, &scanline));
        }
    }
}
