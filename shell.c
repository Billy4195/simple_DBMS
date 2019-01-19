#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputBuffer.h"
#include "Util.h"


int main() {
    InputBuffer_t *input_buffer = new_InputBuffer();
    for (;;) {
        print_prompt();
        read_input(input_buffer);
        if (!strncmp(input_buffer->buffer, ".exit", 4)) {
            break;
        } else {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
        clean_InputBuffer(input_buffer);
    }
    return 0;
}
