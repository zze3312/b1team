#include <cstring>

#include "header/types.h"

enum {
    MAP_ICON_NUM_0 = 0,
    MAP_ICON_NUM_1 = 1,
    MAP_ICON_NUM_2 = 2,
    MAP_ICON_NUM_3 = 3,
    MAP_ICON_NUM_4 = 4,
    MAP_ICON_NUM_5 = 5,
    MAP_ICON_NUM_6 = 6,
    MAP_ICON_NUM_7 = 7,
    MAP_ICON_NUM_8 = 8,
    MAP_ICON_NUM_9 = 9
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

void mapInit(char [50][51], string);
void mapPrint(char [50][51]);

int main(){
    char map[50][51] = {0};
    string mapNumber = "0";
    mapInit(map, mapNumber);
    mapPrint(map);
}

void mapInit(char map[50][51], string mapNum){
    char filePath[100] = "";

    strcat(filePath, ROOT_PATH.c_str());
    strcat(filePath, "maps/floor_");
    strcat(filePath, mapNum.c_str());
    strcat(filePath, ".txt");

    FILE *fp = fopen(filePath, "rt");

    fread(map, 1, 2550, fp);
    fclose(fp);
}

void mapPrint(char map[50][51]) {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            switch (map[i][j] - '0') {
                case MAP_ICON_NUM_0: // 0. 바닥
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_0].c_str()); 
                break;
                case MAP_ICON_NUM_1: // 1. 벽
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_1].c_str());
                break;
                case MAP_ICON_NUM_2: // 2. 판도라의 상점
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_2].c_str());
                break;
                case MAP_ICON_NUM_3: // 3. 성소
                    printf("%4s", MAP_ICON[MAP_ICON_NUM_3].c_str());
                break;
                case MAP_ICON_NUM_4: // 4. 제련소
                    printf("%8s", MAP_ICON[MAP_ICON_NUM_4].c_str());
                break;
                case MAP_ICON_NUM_5: // 5. 결투장
                    printf("%8s", MAP_ICON[MAP_ICON_NUM_5].c_str());
                break;
                case MAP_ICON_NUM_6: // 6. 말하는 섬 던전 입구
                    printf("%9s", MAP_ICON[MAP_ICON_NUM_6].c_str());
                break;
                case MAP_ICON_NUM_7: // 7. 상점 주인
                    printf("%12s", MAP_ICON[MAP_ICON_NUM_7].c_str());
                break;
                case MAP_ICON_NUM_8: // 8. 성직자
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_8].c_str());
                break;
                case MAP_ICON_NUM_9: // 9. 대장장이(드워프)
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_9].c_str());
                break;
            }
        }
        printf("\n");
    }
}