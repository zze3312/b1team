#include "../header/MapClass.h"
#include "../header/MonsterClass.h"
#include "../header/CharacterClass.h"

MonsterClass monFunc;
CharacterClass userFunc;

void MapClass::mapInit(User *loginCharacter) {
    setMap(loginCharacter -> pos.floor);
    if (loginCharacter -> pos.floor > 0) {
        setMonster(loginCharacter);
    }
}

void MapClass::setMap(int mapNum){
    string filePath = ROOT_PATH + "maps/floor_" + std::to_string(mapNum) + ".txt";
    FILE *fp = fopen(filePath.c_str(), "rt");

    fread(map, 1, 2550, fp);
    fclose(fp);
}

Position MapClass::setPortal() {
    Position pos;
    int cnt = 0;

    while (1) {
        int randomRow = rand() % ROW_SIZE;
        int randomCol = rand() % (COL_SIZE - 1);
        if(map[randomRow][randomCol] == MAP_ICON_NUM_0) {
            map[randomRow][randomCol] = MAP_ICON_NUM_6;
            pos.row = randomRow;
            pos.col = randomCol;
            pos.floor = NULL;
            return pos;
        }
    }

}

void MapClass::setCharacter(User *loginCharacter) {

    if (!(map[loginCharacter -> pos.row][loginCharacter -> pos.col] >= '1' && map[loginCharacter -> pos.row][loginCharacter -> pos.col] <= '9') || map[loginCharacter -> pos.row][loginCharacter -> pos.col] == '6') {
        map[loginCharacter -> lastPos.row][loginCharacter -> lastPos.col] = loginCharacter -> beforeBlock;
        loginCharacter -> beforeBlock = map[loginCharacter -> pos.row][loginCharacter -> pos.col];

        map[loginCharacter -> pos.row][loginCharacter -> pos.col] = 'U';
    }else {
        loginCharacter -> pos.row = loginCharacter -> lastPos.row;
        loginCharacter -> pos.col = loginCharacter -> lastPos.col;
    }
}
void MapClass::setMonster(User *loginCharacter) {
    const int CREATE_MONSTERS = 20;
    Monster monsterList[CREATE_MONSTERS];
    for (int i = 0; i < CREATE_MONSTERS; i++) {
        Monster temp = {NULL, "", 0,0, 0, 0};
        monsterList[i] = temp;
    }

    int idx = 0;
    while (1) {
        int randomPosRow = rand() % (ROW_SIZE - 2) + 1;
        int randomPosCol = rand() % (COL_SIZE - 2) + 1;
        bool flag = false;

        if (map[randomPosRow][randomPosCol] != '0') {
            continue;
        }

        for (int i = 0; i < idx; i++) {
            if (monsterList[i].pos.row == randomPosRow && monsterList[i].pos.col == randomPosCol) {
                flag = true;
                break;
            }
        }

        if (flag) {
            continue;
        }else {
            monsterList[idx].pos.row = randomPosRow;
            monsterList[idx].pos.col = randomPosCol;
        }

        idx++;
        if (idx >= CREATE_MONSTERS) break;
    }

    for (int i = 0; i < CREATE_MONSTERS; i++) {
        int randomSoldier = rand() % 10;
        int randomBaphomet = rand() % 10;
        int randomLdnk = rand() % 10;
        int randomCsd = rand() % 20;
        int randomMonster = 0;
        switch (loginCharacter->pos.floor) {
            case 1:
                monsterList[i].id = ORC_NUM;
                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
            break;
            case 2:
                monsterList[i].id = ZOMBIE_NUM;
                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
            break;
            case 3:
                randomMonster = rand() % 2;

                if (randomMonster == 0) monsterList[i].id = ZOMBIE_NUM;
                else monsterList[i].id = GHOUL_NUM;

                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
            break;
            case 4:
                randomMonster = rand() % 3;

                if (randomMonster == 0) monsterList[i].id = ZOMBIE_NUM;
                else if (randomMonster == 1) monsterList[i].id = GHOUL_NUM;
                else monsterList[i].id = SKELETON_NUM;

                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
            break;
            case 5:
                randomMonster = rand() % 3;

                if (randomMonster == 0) monsterList[i].id = GHOUL_NUM;
                else if (randomMonster == 1) monsterList[i].id = SKELETON_NUM;
                else monsterList[i].id = SPA_TOY_NUM;

                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
                if (randomBaphomet < 2) monsterList[i].id = BAPHOMET_NUM;
            break;
            case 6:
                randomMonster = rand() % 3;

                if (randomMonster == 0) monsterList[i].id = GHOUL_NUM;
                else if (randomMonster == 1) monsterList[i].id = SKELETON_NUM;
                else monsterList[i].id = SPA_TOY_NUM;

                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
                if (randomBaphomet < 2) monsterList[i].id = BAPHOMET_NUM;
                if (randomLdnk < 1) monsterList[i].id = LDNK_NUM;
            break;
            case 7:
                monsterList[i].id = SPA_TOY_NUM;

                if (randomSoldier < 3) monsterList[i].id = SOLDIER_NUM;
                if (randomBaphomet < 2) monsterList[i].id = BAPHOMET_NUM;
                if (randomCsd < 1) monsterList[i].id = CSD_NUM;
            break;
        }
    }

    for (int i = 0; i < CREATE_MONSTERS; i++) {
        map[monsterList[i].pos.row][monsterList[i].pos.col] = monsterList[i].id;
        //printf("%d. map[%d][%d] = %c\n",i ,monsterList[i].pos.row, monsterList[i].pos.col, monsterList[i].id);
    }
}

void MapClass::printMap(User *loginCharacter) {
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

    // for (int i = startRow; i < endRow; i++) {
    //     for (int j = startCol; j < endCol; j++) {

    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
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

void MapClass::printStatus(User *loginCharacter) {
    cout << "------------------------------------------------" << endl;
    cout << " 캐릭터명 : " << loginCharacter -> nickname << endl;
    cout << " 레벨     : " << loginCharacter -> lvl << endl;
    cout << " 경험치   : " << loginCharacter -> exp << " / " << loginCharacter -> maxExp << endl;
    cout << " 체력     : " << loginCharacter -> hp << " / " << loginCharacter -> maxHp <<endl;
    cout << " 상태     : ";
    if (loginCharacter -> dieYn == 'N')
        cout << "정상" << endl;
    else
        cout << "죽음" << endl;
    cout << " 현재 층   : " << loginCharacter -> pos.floor << "층" << endl;
    cout << " 현재 좌표   : [" << loginCharacter -> pos.row << ", " << loginCharacter -> pos.col << "]" << endl;
    cout << "------------------------------------------------" << endl;
}