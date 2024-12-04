#ifndef USER_H
#define USER_H

#include "types.h"

class CharacterClass{
    public:
        bool characterSelect(Login *, User *);
        void characterAccount(Login *);
        void printStatus(User *);
        void setCharacter(char [ROW_SIZE][COL_SIZE], User *);
        void die(User *);
        void rebirth(User *, int *);
        void levelUp(User *, int *);
        void getWork(User *);
        void getJobName(User *);
        void move(User *, char);
};


#endif //USER_H
