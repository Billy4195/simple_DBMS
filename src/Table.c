#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "Table.h"

Table_t *new_Table(char *file_name) {
    Table_t *table = (Table_t*)malloc(sizeof(Table_t));
    table->capacity = MAX_TABLE_SIZE;
    table->len = 0;
    table->users = (User_t*)malloc(
                            sizeof(User_t) * MAX_TABLE_SIZE);
    table->fp = NULL;
    table->file_name = NULL;
    if (file_name != NULL) {
        struct stat st;
        if (stat(file_name, &st) != 0) {
            //Create new file
            table->fp = fopen(file_name, "wb");
        } else {
            table->fp = fopen(file_name, "a+b");
            table->len = st.st_size / sizeof(User_t);
        }
        table->file_name = strdup(file_name);
    }
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

/*
 * Return value is the archived table len
 */
int archive_table(Table_t *table) {
    size_t archived_len;
    struct stat st;

    if (stat(table->file_name, &st) == 0) {
        archived_len = st.st_size / sizeof(User_t);
    } else {
        archived_len = 0;
    }
    fwrite((void*)(table->users+archived_len), \
            sizeof(User_t), table->len-archived_len, \
            table->fp);

    fclose(table->fp);
    free(table->file_name);
    table->fp = NULL;
    table->file_name = NULL;
    return table->len;
}

