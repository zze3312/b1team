#include "../header/MapClass.h"
#include "../header/MonsterClass.h"
#include "../header/CharacterClass.h"

MonsterClass monFunc;
CharacterClass userFunc;

void MapClass::mapInit(char map[ROW_SIZE][COL_SIZE], string mapNum, User *loginCharacter) {
    setMap(map, mapNum);
    userFunc.setCharacter(map, loginCharacter);
    monFunc.setMonsterToMap(map, mapNum);
}

void MapClass::setMap(char map[ROW_SIZE][COL_SIZE], string mapNum){
    char filePath[100] = "";

    strcat(filePath, ROOT_PATH.c_str());
    strcat(filePath, "maps/floor_");
    strcat(filePath, mapNum.c_str());
    strcat(filePath, ".txt");

    FILE *fp = fopen(filePath, "rt");

    fread(map, 1, 2550, fp);
    fclose(fp);
}

void MapClass::printMap(char map[ROW_SIZE][COL_SIZE], User *loginCharacter) {
    int startCol = 0;
    int endCol = 0;
    int startRow = 0;
    int endRow = 0;

    if (loginCharacter -> pos.col - 8 <= 0) {
        startCol = 0;
        endCol = 16;
    }else if (loginCharacter -> pos.col + 8 >= COL_SIZE - 1) {
        startCol = COL_SIZE - 17;
        endCol = COL_SIZE - 1;
    }else {
        startCol = loginCharacter -> pos.col - 8;
        endCol = loginCharacter -> pos.col + 8;
    }

    if (loginCharacter -> pos.row - 8 <= 0) {
        startRow = 0;
        endRow = 16;
    }else if (loginCharacter -> pos.row + 8 >= ROW_SIZE) {
        startRow = ROW_SIZE - 16;
        endRow = ROW_SIZE;
    }else {
        startRow = loginCharacter -> pos.row - 8;
        endRow = loginCharacter -> pos.row + 8;
    }

    for (int i = startRow; i < endRow; i++) {
        for (int j = startCol; j < endCol; j++) {
            //printf("%c", map[i][j]);
            switch (map[i][j]) {
                case MAP_ICON_NUM_0: // 0. 바닥
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_0 - '0'].c_str());
                break;
                case MAP_ICON_NUM_1: // 1. 벽
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_1 - '0'].c_str());
                break;
                case MAP_ICON_NUM_2: // 2. 판도라의 상점
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_2 - '0'].c_str());
                break;
                case MAP_ICON_NUM_3: // 3. 성소
                    printf("%4s", MAP_ICON[MAP_ICON_NUM_3 - '0'].c_str());
                break;
                case MAP_ICON_NUM_4: // 4. 제련소
                    printf("%8s", MAP_ICON[MAP_ICON_NUM_4 - '0'].c_str());
                break;
                case MAP_ICON_NUM_5: // 5. 결투장
                    printf("%8s", MAP_ICON[MAP_ICON_NUM_5 - '0'].c_str());
                break;
                case MAP_ICON_NUM_6: // 6. 말하는 섬 던전 입구
                    printf("%9s", MAP_ICON[MAP_ICON_NUM_6 - '0'].c_str());
                break;
                case MAP_ICON_NUM_7: // 7. 상점 주인
                    printf("%12s", MAP_ICON[MAP_ICON_NUM_7 - '0'].c_str());
                break;
                case MAP_ICON_NUM_8: // 8. 성직자
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_8 - '0'].c_str());
                break;
                case MAP_ICON_NUM_9: // 9. 대장장이(드워프)
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_9 - '0'].c_str());
                break;
                case ORC_NUM:
                    printf("%5s", MAP_ICON[10].c_str());
                break;
                case ZOMBIE_NUM:
                    printf("%5s", MAP_ICON[11].c_str());
                break;
                case GHOUL_NUM:
                    printf("%5s", MAP_ICON[12].c_str());
                break;
                case SKELETON_NUM:
                    printf("%5s", MAP_ICON[13].c_str());
                break;
                case SPA_TOY_NUM:
                    printf("%5s", MAP_ICON[14].c_str());
                break;
                case SOLDIER_NUM:
                    printf("%5s", MAP_ICON[15].c_str());
                break;
                case BAPHOMET_NUM:
                    printf("%5s", MAP_ICON[16].c_str());
                break;
                case LDNK_NUM:
                    printf("%5s", MAP_ICON[17].c_str());
                break;
                case CSD_NUM:
                    printf("%5s", MAP_ICON[18].c_str());
                break;
                case USER_NUM:
                    if (loginCharacter -> dieYn == 'Y') {
                        printf("%5s", MAP_ICON[20].c_str());
                    }else {
                        printf("%5s", MAP_ICON[19].c_str());
                    }

                break;
            }
        }
        printf("\n");
    }
}

