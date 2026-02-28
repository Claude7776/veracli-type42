#include <stdlib.h>
#include <time.h>
#include <stdint.h>
#include "config.h"
#include "utils.h"

void generate_random(uint8_t *buffer, size_t len)
{
    size_t i;

    if (!buffer || len == 0)
        return;
    srand((unsigned int)time(NULL));
    i = 0;
    while (i < len)
    {
        buffer[i] = rand() % 256;
        i++;
    }
}
