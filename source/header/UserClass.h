#ifndef USER_H
#define USER_H

#include "types.h"

class UserClass{
    public:
        void join();
        bool login(Login *) ;
        bool characterSelect(Login *, User *);
        void characterAccount(Login *);
};


#endif //USER_H
