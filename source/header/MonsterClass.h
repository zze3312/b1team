//
// Created by lms on 24. 12. 3.
//

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
    public:
        void getMonsterName(Monster *, User *);
        void meetMonster(Monster *, User *);
};



#endif //MONSTERCLASS_H
