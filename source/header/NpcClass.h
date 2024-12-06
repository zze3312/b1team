#ifndef NPCCLASS_H
#define NPCCLASS_H

#include "MonsterClass.h"
#include "types.h"

class NpcClass {
    Character *user = new Character();

    void rebirth(int *);
    void heal();
    void levelUp(int *);
    void getWork();
public:
    NpcClass(Character *loginCharacter) : user(loginCharacter) {}
    void meetPriest();
    void meetFight(MonsterClass *, int *);
    void getJobName();
};

#endif //NPCCLASS_H
