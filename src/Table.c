#include <stdlib.h>
#include <string.h>
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
    size_t idx;
    if (!table || !user || table->len == MAX_TABLE_SIZE) {
        return 0;
    }
    idx = table->len;
    memcpy((table->users)+idx, user, sizeof(User_t));
    table->len++;
    return 1;
}

