#ifndef USER_H
#define USER_H

typedef struct User {
    unsigned int id;
    char name[255];
    char email[255];
    unsigned int age;
} User_t;

User_t* new_User();

#endif
