#ifndef MAPCLASS_H
#define MAPCLASS_H

#include "types.h"


class MapClass {
    private:
        enum {
            MAP_ICON_NUM_0 = '0',
            MAP_ICON_NUM_1 = '1',
            MAP_ICON_NUM_2 = '2',
            MAP_ICON_NUM_3 = '3',
            MAP_ICON_NUM_4 = '4',
            MAP_ICON_NUM_5 = '5',
            MAP_ICON_NUM_6 = '6',
            MAP_ICON_NUM_7 = '7',
            MAP_ICON_NUM_8 = '8',
            MAP_ICON_NUM_9 = '9'
        };

        const string MAP_ICON[10] = {
            "🟩",
            "🟫",
            "🏪",
            "⛪",
            "⚒️",
            "⚔️",
            "🕳️",
            "🧑‍🚀",
            "👼",
            "👺"
            };
        // 도적 🕵️🥷 사망 🤸
    public:
        void mapInit(char [ROW_SIZE][COL_SIZE], string);
        void mapPrint(char [ROW_SIZE][COL_SIZE]);
};



#endif //MAPCLASS_H
