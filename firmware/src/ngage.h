#ifndef NGAGE_H
#define NGAGE_H

#define NGAGE_DISPLAY_WIDTH  176
#define NGAGE_DISPLAY_HEIGHT 208
#define NGAGE_BUFFER_WIDTH   (NGAGE_DISPLAY_WIDTH * 2)
#define NGAGE_BUFFER_SIZE    (NGAGE_WIDTH * NGAGE_HEIGHT) * 2

#include "display_buffer_rgb565.h"

void update_display_buffer(void);

#endif /* NGAGE_H */
