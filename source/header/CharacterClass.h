#ifndef USER_H
#define USER_H

#include "types.h"

class CharacterClass{
    public:
        bool characterSelect(Login *, User *);
        void characterAccount(Login *);
        void move(User *, char);
        void gameSave(User *);
};


#endif //USER_H
