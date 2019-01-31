#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "InputBuffer.h"
#include "Util.h"
#include "Table.h"


int main() {
    InputBuffer_t *input_buffer = new_InputBuffer();
    Command_t *cmd = new_Command();
    Table_t *table = new_Table();
    int cmd_type;
    for (;;) {
        print_prompt();
        read_input(input_buffer);
        cmd_type = parse_input(input_buffer->buffer, cmd);
        if (cmd_type == BUILT_IN_CMD) {
            handle_builtin_cmd(cmd);
        } else if (cmd_type == QUERY_CMD) {
            handle_query_cmd(table, cmd);
        } else if (cmd_type == UNRECOG_CMD) {
            printf("Unrecognized command '%s'.\n", input_buffer->buffer);
        }
        cleanup_Command(cmd);
        clean_InputBuffer(input_buffer);
    }
    return 0;
}
