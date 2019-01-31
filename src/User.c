#include <string.h>
#include <stdlib.h>
#include "User.h"

User_t* new_User() {
    User_t *new_user = (User_t*)malloc(sizeof(User_t));
    new_user->id = 0;
    memset(new_user->name, 0, 255);
    memset(new_user->email, 0, 255);
    new_user->age = 0;
    return new_user;
}

/*
 * Allocate new space for User_t
 * The caller should free the return space
 */
User_t* command_to_User(Command_t *cmd) {
    return NULL;
}

