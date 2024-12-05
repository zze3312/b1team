#include "../header/NpcClass.h"
#include "../header/MonsterClass.h"

MonsterClass msFunc;

void NpcClass::meetPriest(User *loginCharacter) {
    //TODO : 성직자 왜움직임???? 성직자 왜 해치워짐????
    char selectMenu = NULL;
    int gold = 500;
    system("clear");
    cout << "------------------------------------------------" << endl;
    cout << " 1. 체력회복하기" << endl;
    //sleep(1);
    usleep(500000);
    cout << " 2. 부활" << endl;
    //sleep(1);
    usleep(500000);
    cout << " 3. 레벨업" << endl;
    //sleep(1);
    usleep(500000);
    cout << " 4. 전직(3레벨 이상)" << endl;
    //sleep(1);
    usleep(500000);
    cout << "------------------------------------------------" << endl;
    cin >> selectMenu;
    if (selectMenu == '1') {
        heal(loginCharacter);
    }else if (selectMenu == '2') {
        rebirth(loginCharacter, &gold);
    }else if (selectMenu == '3') {
        levelUp(loginCharacter, &gold);
    }else if (selectMenu == '4') {
        getWork(loginCharacter);
    }else {
        cout << " 잘못된 선택입니다." << endl;
    }
}

void NpcClass::heal(User *loginCharacter){
    if (loginCharacter -> dieYn == 'N') {
        //sleep(1);
        usleep(500000);
        cout << " 체력을 모두 회복합니다." << endl;
        //sleep(1);
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        loginCharacter -> hp = loginCharacter -> maxHp;
    }else {
        //sleep(1);
        usleep(500000);
        cout << " 죽은사람을 회복시켜드릴 순 없습니다." << endl;
        //sleep(1);
        usleep(500000);
        cout << " 설마 양아치처럼 그냥 회복하려고 하신건 아니시겠죠?" << endl;
        //sleep(1);
        usleep(500000);
        cout << " 먼저 부활을 해주세요." << endl;
        //sleep(1);
        usleep(500000);
        cout << "------------------------------------------------" << endl;
    }
    //sleep(1);
    usleep(500000);
}

// TODO : 골드 추가 후 금액지불 프로세스 추가해야됨(파라메터도 수정해야됨)
void NpcClass::rebirth(User *loginCharacter, int *userGold) {
    int payGold = rand() % 500 + (loginCharacter -> lvl * 100); //레벨 비례 증가
    char selectMenu = NULL;
    cout << " 부활하시려면 골드가 필요합니다." << endl;
    //sleep(1);
    usleep(500000);
    cout << " 부활 비용 : " << payGold << endl;
    //sleep(1);
    usleep(500000);
    cout << "------------------------------------------------" << endl;
    //sleep(1);
    usleep(500000);
    if (*userGold < payGold) {
        cout << " 부활금액이 부족합니다." << endl;
        //sleep(1);
        usleep(500000);
        cout << " 사채업자에게 돈을 빌려오세요" << endl;
        //sleep(1);
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        //sleep(1);
        usleep(500000);
    }else {
        cout << " 부활 하시겠습니까?";
        cin >> selectMenu;
        if (towupper(selectMenu) == 'Y') {
            *userGold -= payGold;
            loginCharacter -> hp = loginCharacter -> maxHp * 0.1;
            loginCharacter -> dieYn = 'N';
            cout << "\n 부활하셨습니다." << endl;
            //sleep(1);
            usleep(500000);
            cout << "------------------------------------------------" << endl;
            //sleep(1);
            usleep(500000);
        }else {
            cout << "\n 에휴... 아.. 아닙니다.." << endl;
            //sleep(1);
            usleep(500000);
            cout << "------------------------------------------------" << endl;
            //sleep(1);
            usleep(500000);
        }
    }

}

// TODO : 골드 추가 후 금액지불 프로세스 추가해야됨(파라메터도 수정해야됨)
void NpcClass::levelUp(User *loginCharacter, int *userGold) {
    if (loginCharacter -> lvl == 10) {
        cout << "이미 최대 레벨에 도달하셨습니다." << endl;
        //sleep(1);
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        //sleep(1);
        usleep(500000);
        return;
    }

    if (loginCharacter -> exp >= loginCharacter -> maxExp && loginCharacter -> exp != 0) {
        int payGold = 0; //레벨 비례 증가
        char selectMenu = NULL;

        switch (loginCharacter -> lvl) {
            case 1:
                payGold = rand() % 50 + 100;// 100~150
            break;
            case 2:
                payGold = rand() % 200 + 300;// 300~500
            break;
            case 3:
                payGold = rand() % 500 + 500;// 500~1000
            break;
            case 4:
                payGold = rand() % 1000 + 1000;// 1000~2000
            break;
            case 5:
                payGold = rand() % 3000 + 2000;// 2000~5000
            break;
            case 6:
                payGold = rand() % 5000 + 5000;// 5000~10000
            break;
            case 7:
                payGold = rand() % 5000 + 5000;// 5000~10000
            break;
            case 8:
                payGold = rand() % 5000 + 5000;// 5000~10000
            break;
            case 9:
                payGold = rand() % 5000 + 5000;// 5000~10000
            break;
        }

        cout << " 레벨업 하시려면 골드가 필요합니다." << endl;
        cout << " 레벨업 비용 : " << payGold << endl;
        cout << "------------------------------------------------" << endl;
        if (*userGold < payGold) {
            cout << " 레벨업 금액이 부족합니다." << endl;
            cout << " 돈이 없으면 레벨업 하실 수 없습니다." << endl;
            cout << " 사채업자에게 돈을 빌려오세요" << endl;
        }else {
            cout << " 레벨업 하시겠습니까?";
            cin >> selectMenu;
            if (towupper(selectMenu) == 'Y') {
                *userGold -= payGold;
                loginCharacter -> lvl ++;
            }
        }
    }else {
        cout << "더 강해져서 돌아오세요" << endl;
        //sleep(1);
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        //sleep(1);
        usleep(500000);
    }

}

void NpcClass::getWork(User *loginCharacter) {
    char selectMenu = NULL;
    cout << " 전직하실 직업을 선택해 주세요. " << endl;
    cout << " 1. 검술사" << endl;
    cout << " 2. 마법사" << endl;
    cout << " 3. 궁술사" << endl;
    cout << " 4. 창술사" << endl;
    cout << " 5. 암살자" << endl;
    cout << "------------------------------------------------" << endl;
    cin >> selectMenu;

    if (isdigit(selectMenu)) {
        loginCharacter -> jobId = selectMenu - '0';
        getJobName(loginCharacter);
    }
}

void NpcClass::getJobName(User *loginCharacter) {
    switch (loginCharacter -> jobId) {
        case 1:
            loginCharacter -> jobName = "검술사";
        break;
        case 2:
            loginCharacter -> jobName = "마법사";
        break;
        case 3:
            loginCharacter -> jobName = "궁술사";
        break;
        case 4:
            loginCharacter -> jobName = "창술사";
        break;
        case 5:
            loginCharacter -> jobName = "암살자";
        break;
        default:
            loginCharacter -> jobName = "무직";
        break;
    }
}

void NpcClass::meetFight(Monster *mon, User *loginCharacter, int *gold) {
    char selectMenu = NULL;
    system("clear");
    cout << "---------------------------------------" << endl;
    usleep(500000);
    cout << " 여기는 몬스터를 랜덤으로 소환하여 전투할 수 있는 결투장입니다." << endl;
    usleep(500000);
    cout << " 몬스터를 소환하는데 5000골드가 소모됩니다." << endl;
    usleep(500000);
    cout << " 어떤 몬스터가 소환될지 모릅니다." << endl;
    usleep(500000);
    cout << " 그래도 소환하시겠습니까?." << endl;
    usleep(500000);
    cout << "---------------------------------------" << endl;
    usleep(500000);
    cout << " 1. 소환" << endl;
    usleep(500000);
    cout << " 2. 취소" << endl;
    usleep(500000);
    cout << "---------------------------------------" << endl;
    cin >> selectMenu;

    if (towupper(selectMenu) == '1') {
        if (*gold >= 5000) {
            cout << " 몬스터를 소환합니다." << endl;
            usleep(500000);
            msFunc.meetMonster(mon, loginCharacter);
        }else {
            cout << " 골드가 부족합니다." << endl;
            usleep(500000);
            cout << " 골드가 부족하면 소환할 수 없습니다." << endl;
            usleep(500000);
            cout << " 사채업자에게 돈을 빌려오세요." << endl;
            usleep(500000);
        }
    }else {
        cout << " 안녕히가세요." << endl;
        usleep(500000);
    }

}
