#include "../header/MonsterClass.h"


void MonsterClass::getMonsterName() {
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
            monster -> hp   = user -> hp * 200;
            monster -> exp  = user -> maxExp * 0.1;
        break;
        case BAPHOMET_NUM:
            monster -> name = "바포메트";
            monster -> hp   = user -> hp * 500;
            monster -> exp  = user -> maxExp * 0.15;
        break;
        case LDNK_NUM:
            monster -> name = "이동녀크";
            monster -> hp   = user -> hp * 700;
            monster -> exp  = user -> maxExp * 0.2;
        break;
        case CSD_NUM:
            monster -> name = "최상달";
            monster -> hp   = user -> hp * 1000;
            monster -> exp  = user -> maxExp * 0.3;
        break;
        default: break;
    }
}

void MonsterClass::meetMonster() {
    char selectMenu = NULL;
    int attack = 0;
    int randomSoldier = rand() % 20;
    char soldierYn = 'N';
    getMonsterName();
    system("clear");

    cout << monster -> name << "을(를) 만났습니다." << endl;
    //sleep(1);
    usleep(500000);
    while (monster -> hp > 0 && user -> hp > 0) {
        cout << "---------------------------------------" << endl;
        //sleep(1);
        usleep(500000);
        cout << monster -> name <<"의 현재 체력 : " << monster -> hp << endl;
        //sleep(1);
        usleep(500000);
        cout << user -> nickname << "의 현재 체력 : " << user -> hp << endl;
        //sleep(1);
        usleep(500000);
        cout << "---------------------------------------" << endl;
        //sleep(1);
        usleep(500000);
        cout << "1. 공격" << endl;
        //sleep(1);
        usleep(500000);
        cout << "2. 아이템 사용" << endl;
        //sleep(1);
        usleep(500000);
        cout << "3. 도망" << endl;
        //sleep(1);
        usleep(500000);
        cout << "---------------------------------------" << endl;
        cin >> selectMenu;
        if (selectMenu - '0' == 1) {
            cout << "공격합니다" << endl;
            //sleep(1);
            usleep(500000);
            // TODO : 데미지 밸런스 패치 필요(우선 임시로 레벨별 최소값만 줌)
            attack = rand() % (int)(30.0 * (user->lvl / 10.0)) + user -> minDamage;
            cout << "플레이어의 공격! : " << attack << "만큼의 피해를 주었습니다." << endl;
            monster -> hp -= attack;
            //sleep(1);
            usleep(500000);
        }else if (selectMenu - '0' == 2){
            cout << "아이템을 사용합니다" << endl;
            //sleep(1);
            usleep(500000);
        }else if (selectMenu - '0' == 3) {
            cout << "도망갑니다" << endl;
            //sleep(1);
            usleep(500000);
            break;
        }else {
            cout << "잘못된 선택입니다." << endl;
            //sleep(1);
            usleep(500000);
            continue;
        }

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
        cout << monster -> name << "의 공격! : " << attack << "만큼의 피해를 입었습니다." << endl;
        user -> hp -= attack;
        //sleep(1);
        usleep(500000);
    }
    if (user -> hp <= 0) {
        cout << monster -> name << "에게 당했습니다!!" << endl;
        //sleep(1);
        usleep(500000);
        if (user -> hp < 0) {
            user -> hp = 0;
            user -> dieYn = 'Y';
            user -> pos.row = RESET_ROW;
            user -> pos.col = RESET_COL;
            user -> lastPos.row = RESET_ROW;
            user -> lastPos.col = RESET_COL;
            user -> beforeBlock = '0';
            user -> pos.floor = 0;
            user -> dieYn = 'Y';
        }
        //TODO : 보상부분 (약탈)

        return;
    }else if (monster -> hp <= 0){
        cout << monster -> name << "을 해치웠습니다!!" << endl;
        if (!(isdigit(user -> beforeBlock))) {
            user -> beforeBlock = '0';
        }

        //sleep(1);
        usleep(500000);
        user -> exp += monster -> exp;
        cout << "경험치 " << monster -> exp << "를 얻었습니다." << endl;
        //sleep(1);
        usleep(500000);
        cout << "---------------------------------------" << endl;
        if (soldierYn == 'Y') {
            Monster *newMonster = new Monster();
            newMonster -> id = SOLDIER_NUM;
            getMonsterName();
            cout << "다른 용사가 당신이 " << monster -> name << "을(를) 무찌른 걸 보고 빼앗으러 왔습니다." << endl;
            //sleep(1);
            usleep(500000);
            cout << "못된 용사 " << newMonster -> name << "을(를) 무찌르고 보상을 차지하세요!" << endl;
            //sleep(1);
            usleep(500000);

            while (newMonster -> hp > 0 && user -> hp > 0) {
                cout << "---------------------------------------" << endl;
                //sleep(1);
                usleep(500000);
                cout << newMonster -> name <<"의 현재 체력 : " << newMonster -> hp << endl;
                //sleep(1);
                usleep(500000);
                cout << user -> nickname << "의 현재 체력 : " << user -> hp << endl;
                //sleep(1);
                usleep(500000);
                cout << "---------------------------------------" << endl;
                //sleep(1);
                usleep(500000);
                cout << "1. 공격" << endl;
                //sleep(1);
                usleep(500000);
                cout << "2. 아이템 사용" << endl;
                //sleep(1);
                usleep(500000);
                cout << "3. 도망" << endl;
                //sleep(1);
                usleep(500000);
                cout << "---------------------------------------" << endl;
                cin >> selectMenu;
                if (selectMenu - '0' == 1) {
                    cout << "공격합니다" << endl;
                    //sleep(1);
                    usleep(500000);
                    // TODO : 데미지 밸런스 패치 필요(우선 임시로 레벨별 최소값만 줌)
                    attack = rand() % (int)(30.0 * (user->lvl / 10.0)) + user -> minDamage;
                    cout << "플레이어의 공격! : " << attack << "만큼의 피해를 주었습니다." << endl;
                    newMonster -> hp -= attack;
                    //sleep(1);
                    usleep(500000);
                }else if (selectMenu - '0' == 2){
                    cout << "아이템을 사용합니다" << endl;
                    //sleep(1);
                    usleep(500000);
                }else if (selectMenu - '0' == 3) {
                    cout << "도망갑니다" << endl;
                    //sleep(1);
                    usleep(500000);
                    break;
                }else {
                    cout << "잘못된 선택입니다." << endl;
                    //sleep(1);
                    usleep(500000);
                    continue;
                }

                cout << newMonster -> name << "의 공격! : " << attack << "만큼의 피해를 입었습니다." << endl;
                user -> hp -= attack;
                usleep(500000);
            }


        }

        if (user -> hp < 0) {
            user -> hp = 0;
            user -> dieYn = 'Y';
            user -> pos.row = RESET_ROW;
            user -> pos.col = RESET_COL;
            user -> lastPos.row = RESET_ROW;
            user -> lastPos.col = RESET_COL;
            user -> beforeBlock = '0';
            user -> pos.floor = 0;
            user -> dieYn = 'Y';
        }

        //sleep(1);
        usleep(500000);
        //TODO : 보상부분 (획득)
    }
}

