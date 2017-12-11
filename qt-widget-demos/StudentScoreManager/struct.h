#ifndef STRUCT_H
#define STRUCT_H

#include "head.h"

typedef struct student
{
    char num[MAX];
    char name[MAX];
    char sex[MAX];
    char ID[MAX];
    char address[MAX];
    int chinese;
    int math;
    int english;
    int klass;
    double avarage;
}Stu;

typedef struct key
{
    char account[ACCOUNTLENGTH];
    char password[PASSWORDLENGTH];
    char admin[ACCOUNTLENGTH];
}Key;

#endif // STRUCT_H
