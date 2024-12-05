#ifndef USER_H
#define USER_H

#include "types.h"

class CharacterClass{
    public:
        bool characterSelect(Login *, User *);
        void characterAccount(Login *);
        void die(User *);
        void rebirth(User *, int *);
        void levelUp(User *, int *);
        void getWork(User *);
        void getJobName(User *);
        void move(User *, char);
        void gameSave(User *);
};


#endif //USER_H
