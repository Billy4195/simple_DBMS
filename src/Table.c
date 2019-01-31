#include <stdlib.h>
#include "Table.h"

Table_t *new_Table() {
    Table_t *table = (Table_t*)malloc(sizeof(Table_t));
    table->capacity = MAX_TABLE_SIZE;
    table->len = 0;
    table->users = (User_t*)malloc(
                            sizeof(User_t) * MAX_TABLE_SIZE);
    return table;
}


int add_User(Table_t *table, User_t *user) {
    if (!table || !user) {
        return 0;
    }
    return 1;
}

