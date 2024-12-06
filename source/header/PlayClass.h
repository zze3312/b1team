#ifndef PLAYCLASS_H
#define PLAYCLASS_H

#include "types.h"

class PlayClass {

    public:
        void play(Character *);
        void beforePlay (Login *, Character *);
        void echoOff();
        void echoOn();
        void clearBuffer();
};

#endif //PLAYCLASS_H
