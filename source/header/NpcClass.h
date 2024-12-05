#ifndef NPCCLASS_H
#define NPCCLASS_H

#include "types.h"

class NpcClass {
    public:
        void meetPriest(User *);
        void getJobName(User *);
    private:
        void rebirth(User *, int *);
        void heal(User *);
        void levelUp(User *, int *);
        void getWork(User *);

};



#endif //NPCCLASS_H
