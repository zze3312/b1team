#include "../header/MapClass.h"

void MapClass::mapInit(char map[ROW_SIZE][COL_SIZE], string mapNum){
    char filePath[100] = "";

    strcat(filePath, ROOT_PATH.c_str());
    strcat(filePath, "maps/floor_");
    strcat(filePath, mapNum.c_str());
    strcat(filePath, ".txt");

    FILE *fp = fopen(filePath, "rt");

    fread(map, 1, 2550, fp);
    fclose(fp);
}

void MapClass::mapPrint(char map[ROW_SIZE][COL_SIZE]) {
    for (int i = 0; i < ROW_SIZE; i++) {
        for (int j = 0; j < COL_SIZE - 1; j++) {
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
            }
        }
        printf("\n");
    }
}