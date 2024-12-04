#ifndef PLAYCLASS_H
#define PLAYCLASS_H

#include "types.h"

class PlayClass {
    public:
        void play(char (*)[COL_SIZE] , User *);
        void beforePlay (Login *, User *, char (*)[COL_SIZE]);
    private:
        void echoOff();
        void echoOn();
        void clearBuffer();
};



#endif //PLAYCLASS_H
