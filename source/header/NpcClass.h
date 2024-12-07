#ifndef NPCCLASS_H
#define NPCCLASS_H

#include "MonsterClass.h"
#include "types.h"

class NpcClass {
    Character *user = new Character();

    void rebirth();
    void heal();
    void levelUp();
    void getWork();
    void grinNPC();
    void psychoNPC();
    void boredNPC();
    void sosoSmithNPC();
    void angrySmithNPC();
    void buyEquip();
    void buyConsumable();
    void enhanceAct();
    void enhanceWizzard();
public:
    NpcClass(Character *loginCharacter) : user(loginCharacter) {}
    void meetPriest();
    void meetFight(MonsterClass *);
    void getInfo();
    void shopNPC();
    void smithNPC();
};

#endif //NPCCLASS_H
