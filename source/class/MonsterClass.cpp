#include "../header/MonsterClass.h"

void MonsterClass::setMonsterToMap(char map[ROW_SIZE][COL_SIZE], const string &mapNum) {
    //TODO : 맵 벽 추가 이후 해당부분 체크하는 프로세스 추가

    const int CREATE_MONSTERS = 20;
    Monster monsterList[CREATE_MONSTERS];
    for (int i = 0; i < CREATE_MONSTERS; i++) {
        Monster temp = {NULL, "", 0,0, 0, 0};
        monsterList[i] = temp;
    }

    int idx = 0;
    while (1) {
        int randomPosRow = rand() % 48 + 1;
        int randomPosCol = rand() % 48 + 1;
        bool flag = false;

        if (map[randomPosRow][randomPosCol] != '0') {
            cout << "악 여긴벽!" << endl;
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
        switch (atoi(mapNum.c_str())) {
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
        printf("%d. map[%d][%d] = %c\n",i ,monsterList[i].pos.row, monsterList[i].pos.col, monsterList[i].id);
    }
}

void MonsterClass::setMonster(Monster *monster, User *loginCharacter) {
    //Monster *monster = new Monster();
    const string SOLDIER_NAME[5] = {"김대현", "박민제", "김도엽", "김지현", "임정규"};
    int randomSoldierName = rand() % 5;
    switch(monster -> id) {
        case ORC_NUM:
            monster -> name = "오크전사";
            monster -> hp   = rand() % 50 + 50;
            monster -> exp  = 10;
        break;
        case ZOMBIE_NUM:
            monster -> name = "좀비";
            monster -> hp   = rand() % 80 + 50;
            monster -> exp  = 30;
        break;
        case GHOUL_NUM:
            monster -> name = "구울";
            monster -> hp   = rand() % 160 + 120;
            monster -> exp  = 50;
        break;
        case SKELETON_NUM:
            monster -> name = "해골";
            monster -> hp   = rand() % 60 + 200;
            monster -> exp  = 100;
        break;
        case SPA_TOY_NUM:
            monster -> name = "스파토이";
            monster -> hp   = rand() % 100 + 260;
            monster -> exp  = 200;
        break;
        case SOLDIER_NUM:
            monster -> name = SOLDIER_NAME[randomSoldierName];
            monster -> hp   = loginCharacter -> hp * 200;
            monster -> exp  = loginCharacter -> maxExp * 0.1;
        break;
        case BAPHOMET_NUM:
            monster -> name = "바포메트";
            monster -> hp   = loginCharacter -> hp * 500;
            monster -> exp  = loginCharacter -> maxExp * 0.15;
        break;
        case LDNK_NUM:
            monster -> name = "이동녀크";
            monster -> hp   = loginCharacter -> hp * 700;
            monster -> exp  = loginCharacter -> maxExp * 0.2;
        break;
        case CSD_NUM:
            monster -> name = "최상달";
            monster -> hp   = loginCharacter -> hp * 1000;
            monster -> exp  = loginCharacter -> maxExp * 0.3;
        break;
        default: break;
    }
}

void MonsterClass::meetMonster(Monster *monster, User *loginCharacter) {
    char selectMenu = NULL;
    setMonster(monster, loginCharacter);

    while (monster -> hp > 0 && loginCharacter -> hp > 0) {
        cout << "몬스터 " << monster -> name << "을 만났습니다." << endl;
        cout << "몬스터의 현재 체력 : " << monster -> hp << endl;
        cout << loginCharacter -> nickname << "의 현재 체력 : " << loginCharacter -> hp << endl;
        cout << "---------------------------------------" << endl;
        cout << "1. 공격" << endl;
        cout << "2. 아이템 사용" << endl;
        cout << "3. 도망" << endl;
        cout << "---------------------------------------" << endl;
        cin >> selectMenu;
        switch (selectMenu - '0') {
            case 1:
                cout << "공격합니다" << endl;
                // TODO : 데미지수정
                monster -> hp -= 500000;
            break;
            case 2:
                cout << "아이템을 사용합니다" << endl;
            break;
            case 3:
                cout << "도망갑니다" << endl;
            break;
            default:break;
        }
        int attack = 0;
        switch(monster -> id) {
            case ORC_NUM:
                attack = rand() % 5 + 10;
            break;
            case ZOMBIE_NUM:
                attack = rand() % 13 + 17;
            break;
            case GHOUL_NUM:
                attack = rand() % 25 + 20;
            break;
            case SKELETON_NUM:
                attack = rand() % 27 + 28;
            break;
            case SPA_TOY_NUM:
                attack = rand() % 43 + 32;
            break;
            case SOLDIER_NUM:
                attack = rand() % 200 + 100;
            break;
            case BAPHOMET_NUM:
                attack = rand() % 270 + 180;
            break;
            case LDNK_NUM:
                attack = rand() % 250 + 300;
            break;
            case CSD_NUM:
                attack = rand() % 800 + 500;
            break;
            default: break;
        }
        loginCharacter -> hp -= attack;
    }
    if (loginCharacter -> hp <= 0) {
        cout << "몬스터 " << monster -> name << "에게 당했습니다!!" << endl;
    }else {
        cout << "몬스터 " << monster -> name << "을 해치웠습니다!!" << endl;
    }


}

