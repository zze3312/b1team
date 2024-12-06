#ifndef MONSTERCLASS_H
#define MONSTERCLASS_H
#include "types.h"



class MonsterClass {
    private:
        enum {
            ORC_NUM = 'O',
            ZOMBIE_NUM = 'Z',
            GHOUL_NUM = 'G',
            SKELETON_NUM = 'S',
            SPA_TOY_NUM = 'T',
            SOLDIER_NUM = 'L',
            BAPHOMET_NUM = 'B',
            LDNK_NUM = 'D',
            CSD_NUM = 'C',
        };

        Monster *monster = new Monster();
        Character *user = new Character();
    public:
        MonsterClass(Character *loginCharacter, char monNum) : user(loginCharacter) {
            monster -> id = monNum;
        }
        void getMonsterName();
        void meetMonster();
};



#endif //MONSTERCLASS_H
