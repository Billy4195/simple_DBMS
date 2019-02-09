#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "Table.h"

Table_t *new_Table(char *file_name) {
    Table_t *table = (Table_t*)malloc(sizeof(Table_t));
    memset((void*)table, 0, sizeof(Table_t));
    table->capacity = MAX_TABLE_SIZE;
    table->len = 0;
    table->users = (User_t*)malloc(
                            sizeof(User_t) * MAX_TABLE_SIZE);
    table->cache_map = (unsigned char*)malloc(sizeof(char)*MAX_TABLE_SIZE);
    memset(table->cache_map, 0, sizeof(char)*MAX_TABLE_SIZE);
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
    table->cache_map[idx] = 1;
    table->len++;
    return 1;
}

/*
 * Return value is the archived table len
 */
int archive_table(Table_t *table) {
    size_t archived_len;
    struct stat st;

    if (table->fp == NULL) {
        return 0;
    }
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

/*
 * Loading the db file will overwrite the existed records in table, only if the ``file_name`` is NULL
 * Return value: the number of records in the db file
 */
int load_table(Table_t *table, char *file_name) {
    return 0;
}

User_t* get_User(Table_t *table, size_t idx) {
    size_t archived_len;
    struct stat st;
    if (!table->cache_map[idx]) {
        if (idx > MAX_TABLE_SIZE) {
            goto error;
        }
        if (stat(table->file_name, &st) != 0) {
            goto error;
        }
        archived_len = st.st_size / sizeof(User_t);
        if (idx >= archived_len) {
            //neither in file, nor in memory
            goto error;
        }

        fseek(table->fp, idx*sizeof(User_t), SEEK_SET);
        fread(table->users+idx, sizeof(User_t), 1, table->fp);
        table->cache_map[idx] = 1;
    }
    return table->users+idx;

error:
    return NULL;
}

