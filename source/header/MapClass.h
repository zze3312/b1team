#ifndef MAPCLASS_H
#define MAPCLASS_H

#include "types.h"


class MapClass {
    private:
        char (*map)[51] = new char[ROW_SIZE][COL_SIZE];
        enum {
            MAP_ICON_NUM_0  = '0',
            MAP_ICON_NUM_1  = '1',
            MAP_ICON_NUM_2  = '2',
            MAP_ICON_NUM_3  = '3',
            MAP_ICON_NUM_4  = '4',
            MAP_ICON_NUM_5  = '5',
            MAP_ICON_NUM_6  = '6',
            MAP_ICON_NUM_7  = '7',
            MAP_ICON_NUM_8  = '8',
            MAP_ICON_NUM_9  = '9',
            ORC_NUM         = 'O',  //10
            ZOMBIE_NUM      = 'Z',  //11
            GHOUL_NUM       = 'G',  //12
            SKELETON_NUM    = 'S',  //13
            SPA_TOY_NUM     = 'T',  //14
            SOLDIER_NUM     = 'L',  //15
            BAPHOMET_NUM    = 'B',  //16
            LDNK_NUM        = 'D',  //17
            CSD_NUM         = 'C',  //18
            USER_NUM        = 'U',  //19
        };

        const string MAP_ICON[21] = {
            "🟩",    //0
            "🟫",    //1
            "🏪",    //2
            "⛪",    //3
            "⚒️",    //4
            "⚔️",    //5
            "🕳️",    //6
            "🧑‍🚀",    //7
            "👼",    //8
            "👺",    //9 
            "👹",    //10
            "🧟",    //11
            "👾",    //12
            "💀",    //13
            "🤡",    //14
            "🦹",    //15
            "🐃",    //16
            "💩",    //17
            "🧛",    //18
            "🕺",    //19
            "👻"     //20
            };
        // 도적 🕵️🥷 사망 🤸
    public:
        void mapInit(User *);
        void setMap(int);
        Position setPortal();
        void setCharacter(User *);
        void setMonster(User *);
        void printMap(User *);
        void printStatus(User *);
        void charGoPortal(User *);
};



#endif //MAPCLASS_H
