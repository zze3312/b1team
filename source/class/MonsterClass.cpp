#include "../header/MonsterClass.h"


void MonsterClass::getMonsterName(Monster *monster, User *loginCharacter) {
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
    int randomSoldier = rand() % 20;
    char soldierYn = 'N';
    getMonsterName(monster, loginCharacter);


    while (monster -> hp > 0 && loginCharacter -> hp > 0) {
        system("clear");
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
                if (randomSoldier < 6) soldierYn = 'Y';
            break;
            case BAPHOMET_NUM:
                attack = rand() % 270 + 180;
                if (randomSoldier < 4) soldierYn = 'Y';
            break;
            case LDNK_NUM:
                attack = rand() % 250 + 300;
                if (randomSoldier < 2) soldierYn = 'Y';
            break;
            case CSD_NUM:
                attack = rand() % 800 + 500;
                if (randomSoldier < 1) soldierYn = 'Y';
            break;
            default: break;
        }
        loginCharacter -> hp -= attack;
    }
    if (loginCharacter -> hp <= 0) {
        cout << "몬스터 " << monster -> name << "에게 당했습니다!!" << endl;
        if (loginCharacter -> hp < 0) {
            loginCharacter -> hp = 0;
            loginCharacter -> dieYn = 'Y';
            loginCharacter -> pos.row = RESET_ROW;
            loginCharacter -> pos.col = RESET_COL;
            loginCharacter -> lastPos.row = RESET_ROW;
            loginCharacter -> lastPos.col = RESET_COL;
            loginCharacter -> beforeBlock = '0';
            loginCharacter -> pos.floor = '0';
            loginCharacter -> dieYn = 'Y';
        }
        //TODO : 보상부분 (약탈)

        return;
    }else {
        cout << "몬스터 " << monster -> name << "을 해치웠습니다!!" << endl;
        //TODO : 용사 등장 프로세스 추가
        if (soldierYn == 'Y') {
            Monster *newMonster = new Monster();
            newMonster -> id = SOLDIER_NUM;
            getMonsterName(newMonster, loginCharacter);
            cout << "다른 용사가 당신이 몬스터를 무찌른 걸 보고 빼앗으러 왔습니다." << endl;
            cout << "못된 용사 " << newMonster -> name << "을 무찌르고 보상을 차지하세요!" << endl;
            cout << newMonster -> name << "의 현재 체력 : " << monster -> hp << endl;
            cout << loginCharacter -> nickname << "의 현재 체력 : " << loginCharacter -> hp << endl;
            cout << "---------------------------------------" << endl;
            cout << "1. 공격" << endl;
            cout << "2. 아이템 사용" << endl;
            cout << "3. 도망" << endl;
            cout << "---------------------------------------" << endl;
            cin >> selectMenu;
            while (newMonster -> hp > 0 && loginCharacter -> hp > 0) {
                if (loginCharacter -> hp < 0) {
                    loginCharacter -> hp = 0;
                    loginCharacter -> dieYn = 'Y';
                    loginCharacter -> pos.row = RESET_ROW;
                    loginCharacter -> pos.col = RESET_COL;
                    loginCharacter -> lastPos.row = RESET_ROW;
                    loginCharacter -> lastPos.col = RESET_COL;
                    loginCharacter -> beforeBlock = '0';
                    loginCharacter -> pos.floor = '0';
                    loginCharacter -> dieYn = 'Y';
                }
                switch (selectMenu - '0') {
                    case 1:
                        cout << "공격합니다" << endl;
                    // TODO : 데미지수정
                    newMonster -> hp -= 500000;
                    break;
                    case 2:
                        cout << "아이템을 사용합니다" << endl;
                    break;
                    case 3:
                        cout << "도망갑니다" << endl;
                    break;
                    default:break;
                }
            }
        }
        //TODO : 보상부분 (획득)
    }
}

