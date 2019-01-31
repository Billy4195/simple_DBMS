#ifndef USER_H
#define USER_H
#include "Command.h"

typedef struct User {
    unsigned int id;
    char name[255];
    char email[255];
    unsigned int age;
} User_t;

User_t* new_User();
User_t* command_to_User(Command_t *cmd);

#endif
