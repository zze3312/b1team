#include "../header/MapClass.h"
#include "../header/CharacterClass.h"
#include "../header/MonsterClass.h"
#include "../header/NpcClass.h"

CharacterClass userFunc;

void MapClass::mapInit(Character *loginCharacter) {
    setMap(loginCharacter -> pos.floor);
    if (loginCharacter -> pos.floor > 0) {
        setMonster(loginCharacter);
        if (loginCharacter -> pos.floor < 7) {
            setPortal();
        }
        setDownFloor(setPortal());
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

void MapClass::setCharacter(Character *loginCharacter) {
    if (loginCharacter -> jobName.empty()) {
        NpcClass *npc = new NpcClass(loginCharacter);
        npc -> getInfo();
    }

    if (!(map[loginCharacter -> pos.row][loginCharacter -> pos.col] >= '1' && map[loginCharacter -> pos.row][loginCharacter -> pos.col] <= '4')
        || map[loginCharacter -> pos.row][loginCharacter -> pos.col] == '6') {
        map[loginCharacter -> lastPos.row][loginCharacter -> lastPos.col] = loginCharacter -> beforeBlock;
        loginCharacter -> beforeBlock = map[loginCharacter -> pos.row][loginCharacter -> pos.col];

        map[loginCharacter -> pos.row][loginCharacter -> pos.col] = 'U';
    }else {
        loginCharacter -> pos.row = loginCharacter -> lastPos.row;
        loginCharacter -> pos.col = loginCharacter -> lastPos.col;
    }
}
void MapClass::setMonster(Character *loginCharacter) {
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
        int randomMonster = rand() % 20;
        switch (loginCharacter->pos.floor) {
            case 1:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else monsterList[i].id = ORC_NUM;
            break;
            case 2:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else monsterList[i].id = ZOMBIE_NUM;
            break;
            case 3:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else if (randomMonster < 14) monsterList[i].id = ZOMBIE_NUM;
                else monsterList[i].id = GHOUL_NUM;
            break;
            case 4:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else if (randomMonster < 10)monsterList[i].id = ZOMBIE_NUM;
                else if (randomMonster < 15) monsterList[i].id = GHOUL_NUM;
                else monsterList[i].id = SKELETON_NUM;
            break;
            case 5:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else if (randomMonster < 10) monsterList[i].id = BAPHOMET_NUM;
                else if (randomMonster < 14)monsterList[i].id = GHOUL_NUM;
                else if (randomMonster < 17) monsterList[i].id = SKELETON_NUM;
                else monsterList[i].id = SPA_TOY_NUM;
            break;
            case 6:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else if (randomMonster < 10) monsterList[i].id = BAPHOMET_NUM;
                else if (randomMonster < 12) monsterList[i].id = LDNK_NUM;
                else if (randomMonster < 16)monsterList[i].id = GHOUL_NUM;
                else if (randomMonster < 17) monsterList[i].id = SKELETON_NUM;
                else monsterList[i].id = SPA_TOY_NUM;
            break;
            case 7:
                if (randomMonster < 6) monsterList[i].id = SOLDIER_NUM;
                else if (randomMonster < 10) monsterList[i].id = BAPHOMET_NUM;
                else if (randomMonster < 11) monsterList[i].id = CSD_NUM;
                else if (randomMonster < 14)monsterList[i].id = GHOUL_NUM;
                else if (randomMonster < 17) monsterList[i].id = SKELETON_NUM;
                else monsterList[i].id = SPA_TOY_NUM;
            break;
        }
    }

    for (int i = 0; i < CREATE_MONSTERS; i++) {
        map[monsterList[i].pos.row][monsterList[i].pos.col] = monsterList[i].id;
        //printf("%d. map[%d][%d] = %c\n",i ,monsterList[i].pos.row, monsterList[i].pos.col, monsterList[i].id);
    }
}

void MapClass::printMap(Character *loginCharacter) {
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

void MapClass::printStatus(Character *loginCharacter) {
    cout << "------------------------------------------------" << endl;
    cout << " 캐릭터명 : " << loginCharacter -> nickname << endl;
    cout << " 레벨     : " << loginCharacter -> lvl << endl;
    cout << " 경험치   : " << loginCharacter -> exp << " / " << loginCharacter -> maxExp << endl;
    cout << " 체력     : " << loginCharacter -> hp << " / " << loginCharacter -> maxHp <<endl;
    cout << " 마나     : " << loginCharacter -> sp << " / " << loginCharacter -> maxSp <<endl;
    cout << " 직업     : " << loginCharacter -> jobName << endl;
    cout << " 상태     : ";
    if (loginCharacter -> dieYn == 'N')
        cout << "정상" << endl;
    else
        cout << "죽음" << endl;
    cout << " 현재 층   : ";
    if (loginCharacter -> pos.floor > 0) {
        cout << loginCharacter -> pos.floor << "층" << endl;
    }else {
        cout << "마을" << endl;
    }


    cout << " 현재 좌표   : [" << loginCharacter -> pos.row << ", " << loginCharacter -> pos.col << "]" << endl;
    cout << "------------------------------------------------" << endl;
}

void MapClass::mapEvent(Character *loginCharacter) {
    //포탈아이콘을 만나면
    if (loginCharacter -> beforeBlock == MAP_ICON_NUM_6) {
        moveFloor(loginCharacter);
    }
    //몬스터를 만나면
    else if (!isdigit(loginCharacter -> beforeBlock)) {
        MonsterClass *monFunc = new MonsterClass(loginCharacter, loginCharacter -> beforeBlock);
        monFunc->meetMonster();
        delete monFunc;
        //죽었다면
        if (loginCharacter -> dieYn == 'Y') {
            mapInit(loginCharacter);
            setCharacter(loginCharacter);
            return;
        }
    }
    //npc_성직자를 만나면
    else if (loginCharacter -> beforeBlock == MAP_ICON_NUM_8) {
        NpcClass * npcFunc = new NpcClass(loginCharacter);
        npcFunc -> meetPriest();
        delete npcFunc;
    }
    //npc_결투장소환사를 만나면
    else if (loginCharacter -> beforeBlock == MAP_ICON_NUM_5) {
        char mon = NULL;

        int randomMon = rand() % 7;
        switch (randomMon) {
            case 0:
                mon = ORC_NUM;
            break;
            case 1:
                mon = ZOMBIE_NUM;
            break;
            case 2:
                mon = GHOUL_NUM;
            break;
            case 3:
                mon = SKELETON_NUM;
            break;
            case 4:
                mon = SPA_TOY_NUM;
            break;
            case 5:
                mon = SOLDIER_NUM;
            break;
            case 6:
                mon = BAPHOMET_NUM;
            break;
        }
        NpcClass * npcFunc = new NpcClass(loginCharacter);
        MonsterClass *monster = new MonsterClass(loginCharacter, mon);
        npcFunc -> meetFight(monster);
        delete npcFunc;
        delete monster;
    }
    //npc_잡화상을 만나면
    else if (loginCharacter -> beforeBlock == MAP_ICON_NUM_7) {
        NpcClass * npcFunc = new NpcClass(loginCharacter);
        npcFunc -> shopNPC();
        delete npcFunc;
    }
    //npc_잡화상을 만나면
    else if (loginCharacter -> beforeBlock == MAP_ICON_NUM_9) {
        NpcClass * npcFunc = new NpcClass(loginCharacter);
        npcFunc -> smithNPC();
        delete npcFunc;
    }
}

void MapClass::moveFloor(Character *loginCharacter) {
    //올라가는지 내려가는지 체크
    if ((loginCharacter -> pos.row == downFloor -> row && loginCharacter -> pos.col == downFloor -> col) && loginCharacter -> pos.floor != 0 ) {
        loginCharacter -> pos.floor --;
    }else {
        loginCharacter -> pos.floor ++;
    }

    //던전 안
    mapInit(loginCharacter);
    if (loginCharacter -> pos.floor == 7) {
        //해당층 입구포탈 위치로 간다
        loginCharacter -> pos.row = downFloor -> row;
        loginCharacter -> pos.col = downFloor -> col;
        loginCharacter -> lastPos.row = downFloor -> row;
        loginCharacter -> lastPos.col = downFloor -> col;
    }else if (loginCharacter -> pos.floor != 0) {
        //해당층 입구포탈 위치로 간다
        loginCharacter -> pos.row = downFloor -> row;
        loginCharacter -> pos.col = downFloor -> col;
        loginCharacter -> lastPos.row = downFloor -> row;
        loginCharacter -> lastPos.col = downFloor -> col;

    }else {
        //던전 > 마을
        *downFloor = {0,0};
        //마을 던전 입구 좌표 : 49 26
        loginCharacter -> pos.row = 49;
        loginCharacter -> pos.col = 26;
        loginCharacter -> lastPos.row = 49;
        loginCharacter -> lastPos.col = 26;
    }
    setCharacter(loginCharacter);
}

void MapClass::setDownFloor(Position inputPos) {
    *downFloor = inputPos;
}