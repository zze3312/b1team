#include "../header/NpcClass.h"

#include "../header/ItemClass.h"

void NpcClass::meetPriest() {
    char selectMenu = NULL;
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
        heal();
    }else if (selectMenu == '2') {
        rebirth();
    }else if (selectMenu == '3') {
        levelUp();
    }else if (selectMenu == '4') {
        getWork();
    }else {
        cout << " 잘못된 선택입니다." << endl;
    }
}

void NpcClass::heal(){
    if (user -> dieYn == 'N') {
        user -> hp = user -> maxHp;
        usleep(500000);
        cout << " 체력을 모두 회복합니다." << endl;
        user -> sp = user -> maxSp;
        usleep(500000);
        cout << " 마나를 모두 회복합니다." << endl;
        usleep(500000);
        cout << "------------------------------------------------" << endl;
    }else {
        usleep(500000);
        cout << " 죽은사람을 회복시켜드릴 순 없습니다." << endl;
        usleep(500000);
        cout << " 설마 양아치처럼 그냥 회복하려고 하신건 아니시겠죠?" << endl;
        usleep(500000);
        cout << " 먼저 부활을 해주세요." << endl;
        usleep(500000);
        cout << "------------------------------------------------" << endl;
    }
    //sleep(1);
    usleep(500000);
}

void NpcClass::rebirth() {
    ItemClass *userItem = new ItemClass(user);
    int payGold = rand() % 500 + (user -> lvl * 100); //레벨 비례 증가
    char selectMenu = NULL;
    cout << " 부활하시려면 골드가 필요합니다." << endl;
    cout << " 현재 금액 : " << userItem -> getGold() << endl;
    //sleep(1);
    usleep(500000);
    cout << " 부활 비용 : " << payGold << endl;
    //sleep(1);
    usleep(500000);
    cout << "------------------------------------------------" << endl;
    //sleep(1);
    usleep(500000);
    if (userItem -> getGold() < payGold) {
        cout << " 부활금액이 부족합니다." << endl;
        usleep(500000);
        cout << " 사채업자에게 돈을 빌려오세요" << endl;
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        usleep(500000);
    }else {
        cout << " 부활 하시겠습니까?";
        cin >> selectMenu;
        if (towupper(selectMenu) == 'Y') {
            userItem -> useGold(payGold);
            user -> hp = user -> maxHp * 0.1;
            user -> dieYn = 'N';
            cout << "\n 부활하셨습니다." << endl;
            usleep(500000);
            cout << "------------------------------------------------" << endl;
            usleep(500000);
        }else {
            cout << "\n 에휴... 아.. 아닙니다.." << endl;
            usleep(500000);
            cout << "------------------------------------------------" << endl;
            usleep(500000);
        }
    }
    userItem->closeInven();
    delete userItem;
}

void NpcClass::levelUp() {
    ItemClass *userItem = new ItemClass(user);
    if (user -> lvl == 10) {
        cout << "이미 최대 레벨에 도달하셨습니다." << endl;
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        usleep(500000);
        return;
    }

    if (user -> exp >= user -> maxExp && user -> exp != 0) {
        int payGold = 0; //레벨 비례 증가
        char selectMenu = NULL;

        switch (user -> lvl) {
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
        cout << " 현재 금액 : " << userItem -> getGold() << endl;
        cout << " 레벨업 비용 : " << payGold << endl;
        cout << "------------------------------------------------" << endl;
        if (userItem -> getGold() < payGold) {
            cout << " 레벨업 금액이 부족합니다." << endl;
            cout << " 돈이 없으면 레벨업 하실 수 없습니다." << endl;
            cout << " 사채업자에게 돈을 빌려오세요" << endl;
        }else {
            cout << " 레벨업 하시겠습니까?";
            cin >> selectMenu;
            if (towupper(selectMenu) == 'Y') {
                userItem->useGold(payGold);
                user -> lvl ++;
                user -> statPoint += 10;
            }
        }
    }else {
        cout << "더 강해져서 돌아오세요" << endl;
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        usleep(500000);
    }
    userItem->closeInven();
    delete userItem;
}

void NpcClass::getWork() {
    if (user -> lvl > 3) {
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
            user -> jobId = selectMenu - '0';
            getInfo();
        }
    }else {
        cout << "더 강해져서 돌아오세요" << endl;
        usleep(500000);
        cout << "------------------------------------------------" << endl;
        usleep(500000);
    }
}

void NpcClass::getInfo() {
    switch (user -> jobId) {
        case 1:
            user -> jobName = "검술사";
        break;
        case 2:
            user -> jobName = "마법사";
        break;
        case 3:
            user -> jobName = "궁술사";
        break;
        case 4:
            user -> jobName = "창술사";
        break;
        case 5:
            user -> jobName = "암살자";
        break;
        default:
            user -> jobName = "무직";
        break;
    }

    string filePath = ROOT_PATH + "skillInfo.txt";
    FILE *fp = fopen(filePath.c_str(), "rt");
    char bfr[100] = "";
    int i = 0;
    while (fgets(bfr, sizeof(bfr), fp)) {
        int jobId = atoi(strtok(bfr, ","));
        if ( jobId == user -> jobId ) {
            Skill temp;
            temp.id = atoi(strtok(NULL, ","));
            temp.name = strtok(NULL, ",");
            temp.coolTime = atoi(strtok(NULL, ","));
            temp.useSp = atoi(strtok(NULL, ","));
            temp.damage = atoi(strtok(NULL, ","));
            user -> userSkill[i] = temp;
            i++;
        }
    }
}

void NpcClass::meetFight(MonsterClass *mon) {
    ItemClass *userItem = new ItemClass(user);
    char selectMenu = NULL;
    system("clear");
    cout << "---------------------------------------" << endl;
    usleep(500000);
    cout << " 여기는 몬스터를 랜덤으로 소환하여 전투할 수 있는 결투장입니다." << endl;
    usleep(500000);
    if (user -> dieYn == 'Y') {
        cout << "사망자는 몬스터를 소환할 수 없습니다." << endl;
        usleep(500000);
        return;
    }else {
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
            if (userItem -> getGold() >= 5000) {
                userItem -> useGold(5000);
                cout << " 몬스터를 소환합니다." << endl;
                usleep(500000);
                mon -> meetMonster();
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

    userItem -> closeInven();
    delete userItem;
}


//--

void NpcClass::grinNPC() // 상점
{
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡿⠟⠟⠿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⢍⠢⡨⡨⣈⢢⢈⠪⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠣⡑⡄⣗⡵⣫⢮⡳⡕⡕⣽⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢟⢋⢋⢋⠛⠿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡢⡢⣻⣪⢯⡳⣫⢝⢮⡺⣪⢞⣞⢮⢯⡻⣽⡻⡿⣿⢣⢣⢢⣢⡢⣅⠑⠌⢝⣿⣿⣿⣿⣿\n";
    cout << "⡿⣿⣿⢿⣿⣿⣻⣿⣿⣻⣿⣷⣕⢕⡕⣇⠯⠪⠣⠣⠩⠪⡡⡑⠍⠕⢝⢚⠮⡻⡮⣳⢧⣻⣪⣞⢮⡣⡕⠄⢝⣿⣿⣟⣿\n";
    cout << "⣿⣿⣿⣿⣿⢿⣿⡿⣿⣿⣿⢟⢝⠜⢌⠢⠡⡡⠡⠡⠡⡑⡐⠌⢌⢊⠢⠡⡑⢌⠪⡑⠯⣺⣺⡪⣗⡯⡪⡈⠢⣿⣿⣿⣿\n";
    cout << "⣻⣿⣿⣯⣿⣿⣿⣿⣿⣿⢫⠪⠢⡑⡄⡗⣝⢮⢻⢜⡐⡐⠌⢌⢂⠢⠡⡑⢌⠢⡑⢌⠪⠢⡳⣝⢾⡸⡸⣸⣼⣿⣿⣟⣿\n";
    cout << "⣿⣿⡿⣿⣿⣿⢿⣿⣽⢇⠇⢅⢑⢜⢜⢜⢜⢜⢕⢇⠇⠌⢌⢂⠢⠡⡑⢌⠢⡑⢌⢦⣣⢵⡨⠪⡳⣳⣿⣽⣿⣿⣿⣿⣿\n";
    cout << "⣿⡿⣿⣿⣿⣻⣿⣿⡳⠡⡑⡐⡸⡘⣐⡐⡄⢅⢣⢳⠡⡑⡐⠄⢅⠑⢌⠢⡑⢌⢧⢳⢕⢯⢞⡕⢌⢪⢿⣿⣿⣟⣿⣾⣿\n";
    cout << "⣟⣿⣿⣿⣿⣿⣿⡗⡍⡂⡂⠢⡱⡸⡰⡸⡨⡣⡂⢇⢑⠐⠌⢌⠢⡑⢄⠑⠌⢜⢜⠜⠕⢝⢵⣻⢐⢕⢝⣿⣽⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣽⣿⣿⢪⢂⠢⡈⡂⢏⢎⢎⢎⢎⢎⢊⢂⠢⠡⡑⢄⠑⢌⠢⠡⠡⠱⢡⢱⢱⢥⡑⢵⢑⢐⢕⣿⣿⣿⡿⣿⣽\n";
    cout << "⣿⣿⣻⣽⣿⣿⣗⢕⢅⢑⠐⠌⢌⢘⢘⠘⢌⢂⢂⠢⡡⡱⡨⣢⡑⡄⠅⠅⢅⢑⢕⢕⢕⢕⢕⡱⡑⡐⢕⣽⣯⣿⣿⣿⣿\n";
    cout << "⣻⣿⣿⣿⣿⣿⣗⡕⡕⡄⢅⢑⢐⠐⢄⢑⢐⢐⢔⢵⢹⢪⢫⢺⢺⡪⡧⣑⠐⢄⠱⡱⡱⡱⡱⡑⡐⢌⢪⢾⣿⣿⣿⢿⣿\n";
    cout << "⣿⣿⡿⣿⣻⣽⣿⡮⣪⢪⢪⢢⢢⢱⢰⢰⢱⢱⢱⢑⢑⢐⠐⢄⠑⢕⢝⢧⡣⡢⡑⠌⢌⢊⢂⢂⢊⠢⡱⣿⣿⣿⣿⣿⣿\n";
    cout << "⣯⣿⣿⣿⣿⣿⣿⣿⣗⣕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⠐⢄⠑⢄⢑⠐⢕⢝⢮⢲⢨⢈⢂⢂⢂⢂⢢⢱⢝⣿⣿⣿⣯⣿⣿\n";
    cout << "⢿⣿⣿⢿⣿⣿⢿⣿⣿⣷⣯⣎⢎⡎⡎⡎⡎⡎⡎⡎⡎⡢⡑⡐⢄⢕⢕⢕⢕⢕⢕⢕⢆⢆⢆⢎⢎⢎⣿⣿⣿⣷⣿⣿⣿\n";
    cout << "⣿⣿⢿⣿⣿⢿⣿⣿⣻⣿⣟⡿⣟⢞⣞⣜⡮⡺⡸⡜⣜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢜⢬⣿⣿⣿⣿⣿⣻⣿⣿\n";
    cout << "⣽⣿⣿⣿⣿⣿⣿⡿⡿⡳⡣⡏⣎⢞⢮⢳⣝⣎⢪⠪⡪⡪⡣⣓⡵⣕⣕⢕⣕⢕⢕⢕⢕⢕⠑⢄⢑⢘⣿⣿⣯⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⢿⢏⠫⡑⢜⢜⢌⢏⢞⢼⢱⢹⢸⢪⢾⢵⡳⡵⣮⢻⢽⡽⣇⢯⢺⢸⢽⡜⡜⡜⢔⢑⢐⣰⣴⣿⣿⣿⣿⣿⣿⣽\n";
    cout << "=================================================================\n";
}

void NpcClass::psychoNPC() // 상점
{
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠫⠡⠡⠡⡑⡙⡛⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⡿⡛⠍⠍⠌⠍⢝⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢱⠡⣕⢵⢕⡖⣔⡐⡐⢝⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⢋⠢⢨⢨⢜⣜⢬⢢⢪⢿⢿⡻⣻⡫⡯⣫⢯⢯⣫⢮⡣⡯⡳⣯⡺⣕⡗⡌⡂⣺⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣽⣿⣯⣿⣿⣯⢇⠢⢡⡳⡽⣕⣗⢝⢎⢮⢳⢕⡝⡮⡺⡝⡮⡫⡳⡳⡽⣝⢽⣝⢮⣞⢵⢝⢜⢜⣼⣿⣿⣿⣽⣿⣯⣿⣿\n";
    cout << "⣿⣿⣿⣿⣟⣿⡢⡡⡱⡯⣻⢪⡪⡎⡧⡫⡊⡣⠡⠡⡑⡐⡐⠌⢌⢂⢊⠢⡑⢕⢝⠮⡯⣳⢵⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟\n";
    cout << "⣿⣿⣷⣿⣿⣿⣿⣼⡸⡹⡸⡸⡸⡈⡂⡂⠢⠨⠨⡈⡂⡂⡪⠨⡂⡢⠡⡑⢌⣂⡢⡑⢌⢕⢯⡻⣿⣿⣿⣿⣾⣿⣷⣿⣿\n";
    cout << "⣻⣷⣿⣿⣿⣿⣻⣿⣿⢹⠘⢌⢂⢂⣢⡨⠨⡈⡂⡂⡂⠢⡈⡂⠢⠨⠨⣼⡿⡛⡛⠷⣇⠢⡑⢝⢞⣿⣿⣻⣿⣿⣟⣿⣿\n";
    cout << "⣿⣿⣿⣿⣯⣿⣿⣿⢕⢕⢑⢐⡴⡛⡓⢟⣧⡂⡂⠢⡈⡂⠢⠨⠨⠨⠨⣿⢑⠐⠌⠌⢝⣷⡨⡢⡙⣞⣿⣿⣿⣯⣿⣿⣿\n";
    cout << "⣻⣿⣿⣾⣿⣿⣿⡯⡪⡂⡂⣯⢑⠐⢌⠂⢯⡇⢌⢂⠢⠨⠨⠨⠨⠨⠨⣿⡆⠅⢅⢑⠐⢽⣇⠪⠨⡪⡾⣿⣻⣿⣿⣿⣿\n";
    cout << "⣿⣿⣟⣿⣯⣿⣿⢕⢕⢐⢸⣇⠢⡑⢄⢑⢸⡗⡐⠄⠅⠅⠅⠅⠅⠅⠅⠽⣿⡌⡂⠢⠡⣽⣷⠡⡑⢌⢞⣿⣿⣿⣿⣷⣿\n";
    cout << "⠪⡿⣿⣿⣿⣿⣿⢕⢔⢐⢸⣳⡐⢌⢂⢂⣯⡇⠌⠌⠌⠌⠌⠌⠌⠌⠌⠌⠽⣿⣷⣷⣿⣿⡇⠕⢌⠢⡳⣽⣿⡿⣷⣿⣿\n";
    cout << "⡱⣑⢻⢿⣿⣯⣿⢕⢔⠐⠄⢯⢷⢦⣲⢽⡺⠨⠨⠨⠨⡨⡨⡬⡨⡌⡌⠌⢌⢊⢛⠞⢟⠪⠨⠨⠢⢡⡫⣞⣿⣿⣿⣿⣿\n";
    cout << "⢜⢜⢜⢜⢿⣿⢿⡣⡅⢅⠑⢌⠻⠽⠺⠝⠅⠅⢅⢕⢵⢱⢝⢮⢫⢞⡽⡵⣱⢐⠄⠅⠅⠅⠅⢅⢕⢵⢹⣺⣿⣿⣿⢿⣿\n";
    cout << "⢕⢕⢕⢕⢕⢽⢿⣟⡜⡄⡑⠄⠅⠅⠅⠅⠅⡅⡇⡇⡇⡣⠡⡑⡑⢕⢝⢮⡳⡳⣕⢕⢕⢕⢕⢕⢝⢜⣼⣿⣿⣿⣿⣿⣿\n";
    cout << "⢜⢜⡜⡼⣸⣸⡼⣻⣮⡪⡪⡌⡌⡌⡌⡌⡎⡎⡎⡮⡨⡈⡂⠢⡈⠢⡑⡕⡝⡎⡎⡎⡎⡎⡎⡎⣮⣾⣿⣿⣿⣷⣿⣿⣿\n";
    cout << "⣵⣷⣿⣿⣿⣿⣿⣯⣻⣾⣕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢕⢔⢌⠢⡈⡂⡪⡪⡪⡪⡪⡪⡪⣪⢾⣾⣿⣿⣿⣿⣯⣿⣿⣿⣽\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⡿⡈⢞⣆⢍⢺⢸⢜⡜⣜⢜⢕⢵⢱⢕⢕⢕⢕⢕⢕⢕⢕⡕⣗⢿⣜⢮⡿⣝⡿⣿⣿⣾⣿⣿⣿⣽⣿\n";
    cout << "⣿⣿⣟⣿⣾⣿⣿⣷⣬⣢⡙⣗⣕⡕⡵⣣⢳⢭⢳⡹⣝⢵⢱⢳⢕⢧⢗⢷⢽⣞⣗⣟⣾⣗⡝⡎⡮⡳⣙⢛⢿⣷⣿⣿⣿\n";
    cout << "⣿⣽⣿⣿⣿⣿⣾⣿⣿⣿⣿⣷⣹⣣⡯⡪⡪⡪⡪⣺⢸⢸⢸⡪⣎⢮⢫⢯⡳⣗⣽⣺⢸⢺⣇⣇⢇⢕⠐⠅⠅⢽⣿⣿⣻\n";
    cout << "=================================================================\n";
}

void NpcClass::boredNPC() // 상점
{
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⢿⢿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠫⢉⡂⡆⡆⡆⡂⠢⡙⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠨⢨⢲⢕⣝⢮⢮⢪⢪⢪⢪⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n";
    cout << "⣿⣻⣿⡿⣿⣿⣿⣿⣿⡇⠅⠕⢕⢇⢗⢝⢪⢪⢪⢪⢚⢻⢛⠿⠿⠿⣿⣿⣿⣿⣿⡟⡕⡄⡑⡐⠄⢍⢛⢿⣿⣿⣿⡿⣟\n";
    cout << "⣿⣿⣿⣿⣿⣿⢿⣻⣿⣿⣮⠨⡢⡢⠱⢑⢑⠡⠡⠡⠡⠡⠡⢉⢊⢃⠒⠬⡩⣙⢛⢇⢇⢕⢕⢵⢝⡆⣆⠢⠹⣿⣿⢿⣿\n";
    cout << "⣿⣯⣷⣿⣿⢿⣿⣿⣿⡿⡫⠪⠨⠠⢁⢂⠂⠌⠌⠌⠌⠌⠌⡐⡐⡐⠨⢐⢐⠠⠑⠕⡕⡕⡝⢮⡳⣝⢮⢪⢂⢺⣿⣿⣿\n";
    cout << "⣾⣿⣿⢿⣿⣿⣿⣿⢏⢂⠂⠅⢅⢕⢢⢣⠣⡅⠅⠅⠅⠅⠅⡂⡂⡂⠅⡂⡂⠌⠌⡐⠨⠘⢜⢔⢝⢜⠎⢎⠢⣹⣿⣿⣻\n";
    cout << "⣿⢿⣾⣿⣿⣿⣻⠡⢁⠂⠌⡌⡎⡎⡎⡎⢮⣾⠨⠨⠨⠨⢐⢐⢐⠠⢁⢂⠂⠅⠅⡂⠅⠅⡂⡑⢕⢕⢕⣑⣵⣿⣿⣿⡿\n";
    cout << "⣿⣿⣿⡿⣿⣿⠣⢁⠂⠌⢄⣧⡇⢕⢌⠪⣾⡟⠨⠨⠨⠨⢐⢐⢐⠨⢐⢐⠨⣨⢪⢪⢣⢣⢂⠂⠌⢎⢾⣿⣿⣿⣿⡿⣿\n";
    cout << "⡿⣯⣿⣿⣿⠣⡑⡐⠨⠨⠈⣿⣧⣕⣵⣽⡿⠡⠡⠡⠡⢁⢂⢂⠂⠌⡐⡐⣨⣿⠣⡣⡣⡣⡣⠨⠨⠈⡎⣿⣿⣿⡿⣿⣿\n";
    cout << "⣿⣿⣿⢿⡇⢕⢐⠠⠡⠡⠡⢈⢛⢛⢛⠩⠠⠡⡡⡡⣁⢂⢂⠂⠌⡐⡐⡐⣸⣿⡑⢕⢕⢕⢕⠅⠅⠅⢸⢸⣿⣿⣿⣿⣟\n";
    cout << "⣿⣿⣾⣿⡇⢕⢐⠌⠌⠌⠌⡐⡐⡐⡐⡌⡎⢎⠎⠎⠎⠎⢎⢎⢆⢆⢂⢂⠘⣿⣮⣢⣱⣽⡷⠡⠡⠡⢸⢐⣿⣿⣿⣾⣿\n";
    cout << "⣽⣾⣿⣿⡇⢕⢐⠅⠕⠅⠕⢔⢌⠪⠪⠪⠪⠢⠡⠡⠡⢁⢂⠢⡑⡕⡕⡔⡐⡈⡛⠿⠟⠫⠨⠨⠨⠨⡸⡐⣿⣿⣿⣽⣿\n";
    cout << "⢿⣿⣟⣿⣿⡔⠄⠅⠅⠅⠅⠅⠅⢕⢑⠅⠅⠅⠅⠅⠅⡂⡂⡂⡂⡪⡪⡪⡢⡂⡂⠅⠅⠅⠅⠅⠅⢅⢇⢣⣿⣿⣿⣻⣿\n";
    cout << "⣿⡿⣿⡿⣿⣿⣌⠌⠌⠌⠌⠌⢌⢂⠢⠡⠡⠡⠡⠡⢁⢂⢂⢂⢂⠪⡪⡪⡪⡪⡢⡡⡡⠡⠡⠡⡡⡱⡑⢵⣿⣿⣿⢿⣿\n";
    cout << "⣷⣿⣿⣿⣿⣿⣿⣮⣌⡌⠌⠌⡂⠢⠡⠡⠡⠡⠡⢁⢂⢂⢂⠢⡑⢕⢌⠪⡪⡪⡪⡪⡪⡪⡱⡑⢕⢌⢪⣿⣿⣿⡿⣿⣿\n";
    cout << "⣿⣿⣻⣿⡟⡛⠿⢿⣿⣿⣷⣥⣂⠅⠅⠅⠅⠅⠅⡂⡂⡂⠢⡑⢌⢂⠢⡑⡐⠌⢌⢌⠪⡨⡊⡊⡢⢡⣿⣿⣿⣟⣿⣿⣷\n";
    cout << "⣿⣟⣿⣿⠁⡂⠅⡂⡢⡩⣙⢛⠻⠿⡮⣬⠨⠨⢐⢐⢐⠠⢁⢂⢂⢂⢑⠐⠌⢌⢂⠢⡑⡐⣐⣰⣼⣿⣿⣯⣷⣿⣿⣿⣯\n";
    cout << "⣿⢿⣿⣿⣄⡂⠅⡂⠪⡪⡪⡪⡪⡣⡪⡢⡹⡸⡸⡸⡰⡑⡆⡖⡔⡖⡶⡾⣾⣶⣶⣶⣶⣶⣿⣿⣿⣿⣿⣿⣿⣿⣿⣯⣿\n";
    cout << "⣿⣿⢿⣻⣿⣿⣷⣮⣂⣢⢨⢸⡸⣜⣮⣺⢜⡮⣪⢪⢪⢪⢪⢪⠪⡪⡪⡪⡪⡍⡛⢿⣿⣿⣿⣿⣿⣿⣯⣿⣯⣿⣾⣿⣟\n";
    cout << "=================================================================\n";
}

void NpcClass::sosoSmithNPC()
{
    cout << "⣿⠋⠁⠀⢀⠀⡀⢀⠀⠀⢀⣀⢄⣄⢤⢔⣖⢬⢌⣗⢽⢮⡳⣯⣺⡲⣖⡤⣄⣀⠀⠠⠐⠠⢀⢂⠢⢢⠱⡐⡵⣫⢞⡽⣿\n";
    cout << "⡇⠀⢀⠈⢀⠀⢀⡠⣔⢮⡳⣳⢳⡱⡽⣕⢷⢝⢗⡝⡕⡝⡝⠮⡺⡹⡳⡋⡛⢾⢽⡠⠀⠁⢐⠠⢑⠅⢕⢐⣝⢷⣝⢾⢝\n";
    cout << "⡇⠀⠀⠄⢀⢴⢵⢹⣪⡳⡝⡎⣞⢮⢡⠰⡑⢅⠣⢢⢑⠬⡘⡌⡢⡱⡨⢣⢒⢜⠽⣮⡪⣦⡀⠨⢐⢅⠣⡑⣜⣗⢵⢝⣕\n";
    cout << "⡇⠀⠂⢀⢗⣝⢦⢒⢕⢕⢕⢕⠕⡡⠢⡑⢌⠪⡘⢄⢅⢒⠔⡢⢒⠔⠜⡄⢥⠱⣱⢱⢹⡺⣖⡀⠂⢆⠣⡑⣕⣗⢕⢧⡣\n";
    cout << "⡇⠀⠀⢸⢰⢪⢪⢊⢎⢎⠎⡢⢑⠌⡪⠨⠢⡑⡌⡢⠢⡑⡌⢆⠕⡑⡕⢜⢰⢡⢱⢱⡓⣎⢻⢺⣎⠐⡅⢕⢕⢮⡳⡕⡧\n";
    cout << "⡇⠀⠀⢂⢇⢇⠕⡜⡜⢔⠡⠢⡑⢌⠢⡑⢅⠕⡰⠨⡊⡔⢌⠆⡕⡢⢢⠣⡨⣂⠣⢣⢳⡱⣣⢣⢟⡆⠨⡂⣏⢗⢵⢝⡮\n";
    cout << "⡇⠀⠀⡪⡪⡸⢨⢪⠪⠠⡡⡑⢌⠢⡑⢌⠢⡑⠜⢌⢆⠪⡂⢇⢪⠸⡰⡑⢕⠢⡹⡸⡜⣜⢎⢧⢻⣳⠀⡪⡪⡝⣎⢗⣟\n";
    cout << "⡇⠀⠀⡕⡜⠬⢀⢎⠌⢌⠢⠨⡂⢕⠨⠂⠑⠁⢁⠡⢢⢑⢅⠣⠡⠣⠪⡘⢌⢆⠌⠘⢜⢎⢗⣝⢜⢾⡀⠆⡇⣏⢎⢗⡝\n";
    cout << "⡇⠀⠀⡇⡕⡍⡊⡎⠨⡠⠑⠁⠈⠀⠀⠀⡀⡢⢡⢑⠱⡐⡅⢕⢍⢪⠪⡸⡨⡢⡣⡢⡀⠈⠑⠊⠗⡽⠄⢅⢣⢣⢳⢱⡹\n";
    cout << "⡇⠀⠀⡇⢎⢢⢃⢇⠅⠢⡡⠡⠀⡀⠔⡨⡂⡊⡔⠌⡌⢢⢊⠆⡕⢌⢎⢢⢱⠸⣐⢑⢌⢂⢀⠠⡢⣹⠁⡢⢊⢎⢎⢇⢗\n";
    cout << "⡇⠀⠐⡸⡘⡌⡎⣒⠨⠨⡠⢑⠐⡜⡜⠜⠘⠘⠸⡱⡌⡢⡡⡃⢎⢢⠱⡡⢢⢳⢜⠮⠺⠜⣶⡢⡱⡕⠨⡐⢅⢣⢳⢹⢸\n";
    cout << "⡇⠀⠀⡕⢜⢌⢪⢒⠨⢂⠊⢄⢱⢑⠅⠀⠀⠀⡀⢜⢜⠔⡌⢜⠌⢆⢣⠱⢱⢝⡎⢀⠀⢀⠈⣿⢪⠂⠕⡨⢂⢇⢇⢗⢕\n";
    cout << "⡇⠀⠀⡪⡊⡆⢕⠁⠕⡠⠡⠡⡂⢇⢇⢆⠤⡄⡆⡧⡣⠱⡨⡂⢇⢕⢢⠩⡪⡣⣏⢆⢄⡄⡴⡻⡔⠨⡈⡂⡊⢆⢇⢗⢕\n";
    cout << "⡇⠀⠀⡂⡕⢜⢐⢆⡃⠢⢑⠡⠂⠅⢅⠅⢌⠄⢅⠁⠌⠪⡐⠌⡆⡪⠢⡑⠌⢎⡊⣋⡣⡫⠭⡅⡅⡀⢂⠊⢌⠘⢌⢃⢃\n";
    cout << "⡇⠀⠀⢱⢘⠌⡆⢕⢜⠨⠐⡁⠪⠨⢂⠅⢕⠨⡂⢕⠡⡨⢘⠌⢢⢊⢎⠪⡘⡔⢜⠔⡅⡇⡇⡇⡝⡜⣆⠌⠐⠅⢕⢐⠅\n";
    cout << "⡇⠀⡈⠠⢱⠨⡢⠱⡨⡂⠅⡊⠌⢌⢂⠕⡐⡡⢊⠔⡑⢌⢂⢢⠠⡑⢔⢑⢄⠜⡔⢕⢱⠸⡰⡑⡕⢕⢜⢵⠈⠈⠂⠂⠅\n";
    cout << "⡇⠠⠐⢀⠨⢒⠸⡈⢎⢌⢂⠌⢌⢂⠢⠨⢂⠌⡂⡪⢐⠅⡪⡐⡱⢨⠢⡱⠰⡱⡘⡜⢔⢕⢱⢑⢕⢕⢕⢵⡁⠈⡀⢁⠀\n";
    cout << "⡇⠀⡐⠀⠀⢈⠪⡨⠢⡱⡐⠠⡁⡂⠅⠅⠕⡈⡂⡪⢐⢑⠔⢌⠌⡆⢕⠸⡨⠢⡑⡘⡌⡢⡑⠈⢢⢣⢪⢎⠢⡢⡀⠂⠄\n";
    cout << "⡇⠀⠀⡀⠈⠀⠈⢢⠑⡌⢆⠕⢐⠨⡈⡪⢈⢂⢊⠄⢕⢐⠅⠥⡑⢌⢆⠣⡊⡪⡘⡌⢆⢣⠱⡑⡌⡖⡕⠡⠢⡙⣜⢄⠐\n";
    cout << "⡇⠀⠀⡀⠠⠀⠀⠀⠑⡌⠢⡍⢔⢐⢐⢐⠡⢂⠅⠪⡐⢔⠡⡃⡊⢆⠢⠣⡑⡌⡪⡘⢌⢆⠇⠇⡋⠈⠄⠨⢈⠢⡸⡱⡥\n";
    cout << "⡇⠀⠀⡀⠀⠀⠀⠐⠀⠈⠨⠸⡰⡀⡂⡂⠅⡢⠡⡑⠌⡂⢕⠨⡨⢂⠣⡃⢕⠌⡢⡊⡆⠃⠀⠁⠄⠡⢈⠐⠠⠈⠔⡑⣝\n";
    cout << "⡇⠀⠀⠀⠠⠐⠀⠀⡀⠀⡀⠐⠈⡢⠡⠂⠅⢂⠅⠢⡑⠨⡂⠕⡨⠢⡑⢌⢆⢊⢆⠪⠀⢀⠐⠈⠔⢌⢂⠪⡘⠜⡌⡺⡸\n";
    cout << "⡇⠀⠀⠈⠀⠀⠀⠀⠀⠀⠀⡄⠆⡊⢌⢪⠨⡐⡨⢂⢊⠌⠔⡡⢊⠌⡌⡢⠢⡑⠀⠠⠀⢀⠀⠄⡑⢅⠥⡑⢌⠪⠢⡑⠭\n";
    cout << "⡇⠀⠀⠁⠀⢀⠀⠠⠀⠠⠐⠔⡈⢄⠪⡢⡁⠨⢄⢂⢂⢊⠌⢔⠐⢅⠢⡊⢜⠐⠈⠀⢀⠀⢀⠀⢀⠂⠐⢈⠀⠅⠃⡑⠑\n";
    cout << "⡇⠀⠀⠐⠈⠀⠀⠀⠀⠀⢀⢌⢪⠀⢇⢆⠅⠀⠈⢢⢑⢄⢀⠀⢁⢠⢒⢜⠜⠀⠀⠂⠀⢀⠀⠄⠀⠂⠡⠐⠀⠌⡀⠂⡁\n";
    cout << "=================================================================\n";
}

void NpcClass::angrySmithNPC()
{
    cout << "⣿⠛⠉⠉⠉⠉⢉⡉⠉⡉⣿⡿⢫⡻⡫⣫⢟⠏⡝⣽⣿⣿⣿⣿⡿⡿⢿⣟⣿⣿⣿⣿⣿⣿⣿⣝⣋⠉⠉⠉⠉⠉⠉⠻⣿\n";
    cout << "⠃⠀⠀⠀⠀⢀⣸⣿⣾⣻⣳⡼⣪⣾⡟⢕⠡⡪⣼⢿⣙⡪⣣⡲⣕⢝⢮⡺⡜⡮⡪⣎⢧⢫⡳⠿⣦⣑⣄⠀⠀⠀⠀⠀⢸\n";
    cout << "⠀⠀⠀⠀⠀⠟⠟⠙⢾⣿⣟⣿⣿⣻⣷⡵⣗⢯⢳⢕⢵⡹⡜⡮⣪⠳⠕⡃⡫⡊⡋⢎⠮⣳⢹⢝⢼⣙⢿⣷⠀⠀⠀⠀⢸\n";
    cout << "⠀⠂⠀⠀⢰⡄⠀⢀⣸⣿⣟⣿⣽⡿⡳⡝⡮⣪⢳⡹⣕⢵⢝⢎⡖⣝⢝⡜⡮⣪⢫⡺⡜⡦⡍⣗⡳⣕⢧⢝⢇⠀⠀⠂⢸\n";
    cout << "⢀⠀⠀⡀⢺⣷⣾⡿⡯⡫⣿⡿⡯⢮⡳⡝⡮⣪⢳⢕⢧⡳⡝⡮⢚⢌⡆⡦⣪⢢⢆⢦⡱⣉⠺⣜⢮⢎⣗⢽⢌⠂⠀⠀⢸\n";
    cout << "⠀⠀⠀⠀⢰⣿⣷⢏⠇⡕⣿⢯⢝⢵⡱⡝⡮⣪⡳⡝⡮⡺⡪⡮⣫⢣⠏⡞⣎⢗⣝⢵⢍⢎⢯⡪⡮⡳⣕⢗⡕⡆⠁⠀⢸\n";
    cout << "⠀⠁⠀⠠⠘⣿⣽⢸⢨⣾⡯⡳⡝⡖⡌⠈⠚⠜⠜⠎⠗⠝⠎⠞⠘⠀⣜⡚⠼⢱⠣⣓⢗⠄⠁⠃⠓⠝⡜⢵⠹⠂⠀⠄⢸\n";
    cout << "⠈⡀⠂⡀⠂⣿⡯⣺⣿⣿⢙⢮⣓⡩⢈⠐⠀⠈⠀⠁⠀⠁⢀⠀⠄⢪⡪⣊⠯⠲⡙⡜⡜⢈⠠⠐⠀⠀⠄⠀⠀⢈⠀⡀⢸\n";
    cout << "⠀⠄⠂⡀⠂⠍⣯⣿⣿⣽⢨⡳⡪⠊⠁⡀⠄⠁⠀⡁⠀⡁⡀⠄⠂⡁⠌⠊⠎⠇⡋⡐⡐⣐⣠⣂⡄⠂⠀⠐⠈⡀⢀⠀⢸\n";
    cout << "⡈⢐⠠⠀⠂⢡⢻⣿⣾⡯⢢⡳⡕⡧⡣⡀⠄⣤⣵⣾⡿⣶⣦⣌⢐⠠⠈⠌⡈⡐⢀⢂⣴⣿⡻⣟⢿⣿⣌⢆⢤⡈⢀⢈⢸\n";
    cout << "⡐⢀⢐⢀⠡⠐⣽⣻⣾⣿⠨⡎⣗⡝⡮⡣⣽⣿⠋⠌⡐⠨⡙⣿⣧⠠⢁⢂⠐⡀⡂⣾⣻⢃⢂⠂⠅⠝⣿⣎⢧⠁⡂⡂⢸\n";
    cout << "⣦⣲⢶⢶⣺⣵⢻⡼⣿⣻⢀⢯⡪⡮⣫⡺⣿⡧⠡⠁⠄⠡⢐⢸⣿⠐⡀⢂⠐⡀⢂⢻⣿⡐⡐⠨⢐⢡⣿⢺⠂⡂⡐⠐⢸\n";
    cout << "⣷⣻⣟⣯⣷⣻⠹⣿⢑⠽⡇⢰⢳⡹⣜⢎⢿⣿⣬⡨⠨⣨⢴⣿⠏⡐⢐⢀⠂⡂⢂⠘⠯⣿⡦⡵⣐⡛⡣⠣⢂⠐⡀⠂⢸\n";
    cout << "⡧⡿⣞⣷⡻⡪⢱⢸⡕⡐⣧⢁⢳⡹⡜⡝⡬⢬⢱⢭⢩⠭⣛⢉⢐⠐⡀⣆⢎⢦⢢⢕⢽⡐⡮⡺⡲⣕⡝⣕⢄⠊⢄⢈⢸\n";
    cout << "⡾⣽⠗⢕⠌⡜⡐⡨⢻⡀⢿⡆⡊⡪⡮⡫⡮⡳⡳⣕⣝⢝⢼⢜⢲⠌⡜⡪⡝⢪⡳⣹⢑⢵⢝⢮⡳⡵⣹⢪⢮⠈⠔⡠⢸\n";
    cout << "⢟⢅⢣⠡⡃⡪⡐⡂⡻⡎⡌⢿⡄⢫⢎⢯⢎⢯⡺⣜⢼⡱⡳⡝⣎⢯⢸⡪⣎⢆⢅⠅⣪⢳⡹⣪⡺⡪⡮⡳⢕⢬⢨⠠⣼\n";
    cout << "⡱⢐⠅⢕⢌⠢⡊⡢⡂⢕⠨⠐⢌⠌⣗⢝⢮⢳⡹⣜⢮⢮⢳⢝⡎⣗⡕⡧⡳⣝⢵⡹⣌⣚⢜⡪⣪⡫⡪⣎⢧⢳⠁⢄⣿\n";
    cout << "⣬⡢⠣⡑⢔⢑⢌⢂⢪⢰⣦⢑⠔⡡⡘⢵⢝⢵⢝⢮⢺⡪⡳⣕⢽⢜⡎⡯⡺⣜⢕⢧⡳⡕⡧⡫⡮⣪⡫⢎⠮⡣⣧⢿⣽\n";
    cout << "⣷⣻⢷⣅⢣⢒⠔⠅⡂⢅⠟⡂⢕⢐⠌⠪⡱⢝⢮⢳⡣⡯⡺⣪⢳⢕⣝⢮⢳⢕⡝⡮⡺⠜⡪⠅⡓⢔⢐⢡⣢⢿⣽⣻⢾\n";
    cout << "⣗⣿⢽⡯⣷⣆⣣⣿⡎⣆⣷⢕⢁⠢⡐⢅⠢⡑⡙⢮⢺⡪⡫⣎⢗⣕⢧⢳⡹⢊⢌⢆⢮⢊⢆⢣⣱⡵⣞⣿⣺⣟⢞⡽⣿\n";
    cout << "⢺⡽⣯⣟⡷⣷⣻⣿⣷⣅⢏⠆⢕⠨⡢⠀⢕⠰⢈⠢⢑⢙⢎⢮⢣⡳⡕⡧⣣⢢⡺⡸⣐⡦⣗⣯⢷⡿⣽⣞⡷⢣⢱⡿⣽\n";
    cout << "⡽⣯⢷⡯⣿⡽⣾⣿⣾⡋⢆⠣⡣⣗⢌⢌⠂⠁⢐⢐⢀⠀⠀⠈⠑⢱⠹⡘⡊⣕⡵⣞⣷⣻⡽⣾⢯⣟⡷⣯⢇⠣⡽⣽⣻\n";
    cout << "⣿⣿⣽⣯⣷⣻⣽⣗⣯⣞⣷⣧⣝⣿⣎⣢⣅⣄⣔⣰⣐⣁⣅⣬⣼⣲⣵⣖⣿⣺⣽⣻⣞⣷⣻⣽⣯⣷⣻⣽⣪⣨⣿⣽⣿\n";
    cout << "=================================================================\n";
}

void NpcClass::buyEquip()
{
    ItemClass *userItem = new ItemClass(user);
    while (1)
    {

        grinNPC();
        cout << "판도라: 초보자를 위한 장비들을 팔고 있어요!\n";
        cout << "1. 기본검    2. 기본스태프  3. 기본활    4. 기본창    5. 기본단검\n";
        cout << "6. 기본갑빠  7. 기본장화    8. 기본장갑  9. 기본망토   0. 기본마스크\n";
        cout << "q. 뒤로가기\n";
        cout << "=================================================================\n";

        // string choice;
        // cin >> choice;
        char choice;
        read(0, &choice, sizeof(choice));
        system("clear");

        if (choice == 'q')
        {
            break;
        }
        else if (isdigit(choice))
        {
            int num, price;

            num = choice - '0' - 1;
            if (choice - '0' < 6)
            {
                price = 50;
            }
            else
            {
                price = 30;
            }
            while (1)
            {
                grinNPC();
                cout << "판도라: " << userItem -> getEquipName(num) << "을 구매하실 건가요?\n";
                cout << userItem -> getEquipName(num) << ": " << userItem -> getSpecName(num) << ", " << userItem -> getEquipType(num) << endl;
                cout << "가격: " << price << "원\n";
                cout << "보유한 골드: " << userItem -> getGold() << endl;
                cout << "1. 구매하기  q. 뒤로가기\n";
                cout << "=================================================================\n";

                read(0, &choice, sizeof(choice));
                system("clear");

                if (choice == 'q')
                {
                    break;
                }
                else if (choice == '1')
                {
                    if (userItem -> getGold() > price)
                    {
                        grinNPC();
                        cout << "구매해주셔서 감사합니다!\n";
                        cout << userItem -> getEquipName(num) << " 구매, " << price << "원 차감\n";
                        userItem -> useGold(price);
                        userItem -> closeInven();
                        sleep(2);
                        system("clear");
                        break;
                    }
                    else
                    {
                        boredNPC();
                        cout << "앗! 보유하신 골드가 부족해요...다른 상품을 보시겠어요?\n";
                        sleep(2);
                        system("clear");
                        break;
                    }

                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            continue;
        }
        delete userItem;
    }
}

void NpcClass::buyConsumable()
{
    ItemClass *userItem = new ItemClass(user);
    while (1)
    {
        grinNPC();
        cout << "판도라: 말섬 상점산 특제 상품이에요!\n";
        cout << "1. 빨간물약  2. 마을이동주문서  q. 뒤로가기\n";
        cout << "=================================================================\n";

        char choice;
        read(0, &choice, sizeof(choice));
        // string choice;
        // cin >> choice;
        system("clear");

        if (choice == 'q')
        {
            break;
        }
        else if (choice == '1' || choice == '2')
        {
            int num, price;
            if (choice == '1')
            {
                num = 0;
                price = 30;
            }
            else
            {
                num = 4;
                price = 100;
            }
            while (1)
            {
                grinNPC();
                cout << "판도라: " << userItem -> getItemName(num) << "을 구매하실 건가요?\n";
                cout << "inv->consumableNameList[num]" << ": " << "inv->consumableEXList[num]" << endl;
                cout << "가격: " << price << "원\n";
                cout << "보유한 골드: " << "inv->gold" << endl;
                cout << "1. 구매하기  q. 뒤로가기\n";
                cout << "=================================================================\n";

                read(0, &choice, sizeof(choice));
                system("clear");

                if (choice == 'q')
                {
                    break;
                }
                else if (choice == '1')
                {
                    if (userItem -> getGold() > price)
                    {
                        grinNPC();
                        cout << "구매해주셔서 감사합니다!\n";
                        cout << userItem -> getItemName(num) << " 구매, " << price << "원 차감\n";
                        userItem -> useGold(price);
                        userItem -> closeInven();
                        sleep(2);
                        system("clear");
                        break;
                    }
                    else
                    {
                        boredNPC();
                        cout << "앗! 보유하신 골드가 부족해요...다른 상품을 보시겠어요?\n";
                        sleep(2);
                        system("clear");
                        break;
                    }

                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            continue;
        }
    }
    delete userItem;
}

void NpcClass::shopNPC()
{
    system("clear");
    srand((int)time(NULL));

    while(1)
    {
        grinNPC();
        cout << "판도라: 어서오세요! 24시간 내내 열려있는 말섬 상점입니다!\n";
        cout << "1. 구매하기  2. 판매하기  3. 농담하기  q. 나가기\n";
        cout << "=================================================================\n";

        // string choice;
        // cin >> choice;
        char choice;
        read(0, &choice, sizeof(choice));
        system("clear");

        if (choice == 'q')
        {
            grinNPC();
            cout << "판도라: 감사합니다 용사님! 다음에 또 뵐게요!\n";
            cout << "=================================================================\n";
            sleep(2);
            system("clear");
            // closeInven();
            break;
        }
        else if (choice == '1')
        {
            while (1)
            {
                grinNPC();
                cout << "판도라: 뭘 구매하실 건가요?\n";
                cout << "1. 장비  2. 소모품  q. 뒤로가기\n";
                cout << "=================================================================\n";

                cin >> choice;
                system("clear");

                if (choice == 'q')
                {
                    break;
                }
                else if (choice == '1')
                {
                    buyEquip();
                    continue;
                }
                else if (choice == '2')
                {
                    buyConsumable();
                    continue;
                }
                else
                {
                    continue;
                }
            }
        }
        else if (choice == '2')
        {
            // TODO : 판매
            cout << "구현 예정\n";
        }
        else if (choice == '3')
        {
            int reactNum = rand() % 10;

            if (reactNum < 7)
            {
                grinNPC();
                cout << "판도라: 용사님은 농담도 잘하시네요!\n";
                sleep(2);
                system("clear");
                continue;
            }
            else if (reactNum < 9)
            {
                boredNPC();
                cout << "판도라: 하하하..재밌네요\n";
                sleep(2);
                system("clear");
                continue;
            }
            else
            {
                psychoNPC();
                cout << "나레이션: 판도라가 갑자기 무서운 표정으로 노려보더니 상점에서 내쫓았다..\n";
                sleep(2);
                system("clear");
                // closeInven();
                break;
            }
        }
        else
        {
            continue;
        }
    }
}

void NpcClass::smithNPC()
{
    system("clear");
    while(1)
    {
        sosoSmithNPC();
        cout << "대장장이: 어서오게.\n";
        cout << "1. 구매하기  2. 농담하기  q. 나가기\n";
        cout << "=================================================================\n";

        // string choice;
        // cin >> choice;
        char choice;
        read(0, &choice, sizeof(choice));
        system("clear");

        if (choice == 'q')
        {
            sosoSmithNPC();
            cout << "대장장이: 다음에 또 보자고.\n";
            cout << "=================================================================\n";
            sleep(2);
            system("clear");
            // closeInven();
            break;
        }
        else if (choice == '1')
        {
            while (1)
            {
                sosoSmithNPC();
                cout << "대장장이: 강화주문서를 사려고? 하나당 300원이야.\n";
                cout << "inv->consumableNameList[7]" << ", " << "inv->consumableEXList[7]" << endl;
                cout << "보유한 골드: " << "inv->gold" << endl;
                cout << "1. 구매하기  2. 직접 강화는 안 해주시나요?  q. 뒤로가기\n";
                cout << "=================================================================\n";

                //cin >> choice;
                read(0, &choice, sizeof(choice));
                system("clear");

                if (choice == 'q')
                {
                    break;
                }
                else if (choice == '1')
                {
                    // if (inv->gold > 300)
                    // {
                            sosoSmithNPC();
                            cout << "잘 사용하라고.\n";
                            cout << "inv->consumableNameList[7]" << " 구매, 300원 차감\n";
                            // inv->gold -= 300;
                            sleep(2);
                            system("clear");
                            continue;
                    // }
                    // else
                    // {
                    //     sosoSmithNPC();
                    //     cout << "자네, 돈이 부족한데?\n";
                    //     sleep(2);
                    //     system("clear");
                    //     break;
                    // }

                }
                else if (choice == '2')
                {
                    angrySmithNPC();
                    cout << "대장장이: 이놈! 쓸데없는 소리 말고 저기 코쟁이한테 가라!\n";
                    sleep(1);
                    cout << "나레이션: 화난 대장장이가 당신을 대장간에서 쫓아냈습니다...\n";
                    sleep(2);
                    system("clear");
                    // closeInven();
                    return;
                }
                else
                {
                    continue;
                }
            }
        }
        else if (choice == '2')
        {
            angrySmithNPC();
            cout << "나레이션: 분노한 대장장이가 당신을 쫓아냈습니다.....\n";
            sleep(2);
            system("clear");
            // closeInven();
            break;
        }
        else
        {
            continue;
        }
    }
}

void NpcClass::enhanceAct()
{
    while (1)
    {
        cout << "인첸트마법사: 강화 하시려구요..? 어떤 장비를 강화 하실 건가요?\n";
        cout << "1. 마스크   2. 갑옷   3. 신발   4. 장갑   5. 망토   6. 무기\n";
        cout << "=================================================================\n";

        string choice;
        cin >> choice;
        system("clear");

        if (choice == "q")
        {
            cout << "인첸트마법사: 또 오세요...\n";
            break;
        }
        else if (choice == "6")
        {
            while (1)
            {
                cout << "인첸트마법사: 강화 비용은 10000골드입니다...\n";
                cout << "보유한 골드: " << "inv->gold" << endl;
                cout << "=================================================================\n";
                cout << "나레이션: 강화 레벨이 -10 ~ +10 됩니다.";
                cout << "<경고!> 강화 수치가 0보다 낮아지면 장비가 파괴됩니다.\n";
                cout << "=================================================================\n";
                cout << "정말 강화를 진행하시겠습니까?\n";
                cout << "1. 예   2. 아니오\n";
                cout << "=================================================================\n";

                string choice;
                cin >> choice;
                system("clear");

                int prob = rand() % 21 -10;

                if (choice == "1")
                {
                    // if ("inv->gold" < 10000)
                    // {
                    //     cout << "인첸트마법사: 골드가 모자라시네요..\n";
                    //     sleep(1);
                    //     break;
                    // }
                    // cout << "강화중";
                    // for (int i = 0; i < 10; i++)
                    // {
                    //     cout << ".";
                    //     usleep(300000);
                    // }
                    system("clear");
                    cout << "=================================================================\n";
                    cout << "                           강화 완료!\n";
                    cout << "=================================================================\n";
                    sleep(3);
                    // if ((user->nowWeaponId-1) % 10 + prob < 0)
                    // {
                    //     cout << prob << " 당첨!\n";
                    //     sleep(1);
                    //     cout << "장비 레벨이 0 아래로 내려가서 장비가 파괴됩니다...\n";
                    //     sleep(2);
                    //     system("clear");
                    //     user->nowWeaponId = 0;
                    // }
                    // else if ((user->nowWeaponId-1) % 10 + prob > 10)
                    // {
                    //     cout << prob << " 당첨!\n";
                    //     sleep(1);
                    //     cout << "축하합니다! 최대 강화에 도달하였습니다.\n";
                    //     sleep(2);
                    //     system("clear");
                    //     if (user->nowWeaponId <= 100)
                    //     {
                    //         user->nowWeaponId = user->nowWeaponId * 10 + 99;
                    //     }
                    //     else
                    //     {
                    //         user->nowWeaponId = user->nowWeaponId - (user->nowWeaponId % 10) + 10;
                    //     }
                    // }

                }
                else if (choice == "2")
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
        else if (choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5")
        {
            while (1)
            {
                cout << "인첸트마법사: 강화 비용은 10000골드입니다...\n";
                cout << "보유한 골드: " << "inv->gold" << endl;
                cout << "=================================================================\n";
                cout << "나레이션: 강화 레벨이 -10 ~ +10 됩니다.";
                cout << "<경고!> 강화 수치가 0보다 낮아지면 장비가 파괴됩니다.\n";
                cout << "=================================================================\n";
                cout << "정말 강화를 진행하시겠습니까?\n";
                cout << "1. 예   2. 아니오\n";
                cout << "=================================================================\n";

                string choice;
                cin >> choice;
                system("clear");

                int prob = rand() % 21 -10;

                if (choice == "1")
                {
                    // if ("inv->gold" < 10000)
                    // {
                    //     cout << "인첸트마법사: 골드가 모자라시네요..\n";
                    //     sleep(1);
                    //     break;
                    // }
                    // cout << "강화중";
                    // for (int i = 0; i < 10; i++)
                    // {
                    //     cout << ".";
                    //     usleep(300000);
                    // }
                    system("clear");
                    cout << "=================================================================\n";
                    cout << "                           강화 완료!\n";
                    cout << "=================================================================\n";
                    sleep(3);
                    // if ()
                    // {

                    // }


                }
                else if (choice == "2")
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
        }
        else
        {
            continue;
        }
    }

}

void NpcClass::enhanceWizzard()
{
    while(1)
    {
        sosoSmithNPC();
        cout << "인첸트마법사: 어서오세요..\n";
        cout << "1. 강화하기  q. 나가기\n";
        cout << "=================================================================\n";

        string choice;
        cin >> choice;
        system("clear");

        if (choice == "q")
        {
            sosoSmithNPC();
            cout << "인첸트마법사: 또 오세요..\n";
            cout << "=================================================================\n";
            sleep(2);
            system("clear");
            // closeInven();
            break;
        }
        else if (choice == "1")
        {
            enhanceAct();
            continue;
        }
        else
        {
            continue;
        }
    }

}