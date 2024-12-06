#ifndef USER_H
#define USER_H

#include "types.h"

class CharacterClass{
    public:
        bool characterSelect(Login *, Character *);
        void characterAccount(Login *);
        void move(Character *, char);
        void gameSave(Character *);
        void statWindow(Character *);
};


#endif //USER_H
