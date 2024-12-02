#include <cstring>

#include "types.h"

enum {
    MAP_ICON_NUM_0 = 0,
    MAP_ICON_NUM_1 = 1,
    MAP_ICON_NUM_2 = 2,
    MAP_ICON_NUM_3 = 3,
};

const string MAP_ICON[4] = {
    "🟩",
    "🟫",
    "😀",
    "🤣"};


void mapInit(char [50][51], string);
void mapPrint(char [50][51]);

int main(){
    char map[50][51] = {0};
    string mapNumber = "1";
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
                case MAP_ICON_NUM_0:
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_0].c_str());
                break;
                case MAP_ICON_NUM_1:
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_1].c_str());
                break;
                case MAP_ICON_NUM_2:
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_2].c_str());
                break;
                case MAP_ICON_NUM_3:
                    printf("%5s", MAP_ICON[MAP_ICON_NUM_3].c_str());
                break;
            }
        }
        printf("\n");
    }
}