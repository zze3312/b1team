#ifndef PLAYCLASS_H
#define PLAYCLASS_H

#include "types.h"

class PlayClass {
    public:
        void play(User *);
        void beforePlay (Login *, User *);
        void echoOff();
        void echoOn();
        void clearBuffer();
};



#endif //PLAYCLASS_H
