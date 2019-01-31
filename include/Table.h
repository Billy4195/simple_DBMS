#ifndef TABLE_H
#define TABLE_H
#include <stdlib.h>
#include "User.h"

#define MAX_TABLE_SIZE 10000

typedef struct Table {
    size_t capacity;
    size_t len;
    User_t *users;
} Table_t;

Table_t *new_Table();
int add_User(Table_t *table, User_t *user);

#endif
