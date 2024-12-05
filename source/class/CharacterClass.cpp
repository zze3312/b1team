#include "../header/CharacterClass.h"



bool CharacterClass::characterSelect(Login *loginUser, User *loginCharacter) {
    char str[30] = "";

    char selectMenu = NULL;
    string filePath = ROOT_PATH + "userData/" + loginUser->id + "/character.txt";
    User tempUser[3];

    while (true) {
        int cnt = 0;
        system("clear");
        cout << "현재 생성된 캐릭터" << endl;
        cout << "-----------------------------------" << endl;

        FILE * fp = fopen(filePath.c_str(), "rt");

        while (fgets(str, sizeof(str), fp)) {
            tempUser[cnt].nickname = strtok(str, "\n");
            if (tempUser[cnt].nickname.size() != 0) {
                cout << cnt + 1 << ". " << tempUser[cnt].nickname << endl;
                cnt++;
            }
        }
        fclose(fp);

        if (cnt == 0) {
            cout << "현재 생성된 캐릭터가 없습니다." << endl;
        }
        cout << "-----------------------------------" << endl;
        if (cnt < 3) {
            cout << "0. 캐릭터 생성" << endl;
        }

        cout << "접속할 캐릭터나 캐릭터 생성을 선택해주세요 : ";
        cin >> selectMenu;

        if (selectMenu - '0' == 0) {
            characterAccount(loginUser);
        }else {
            loginCharacter -> id = loginUser -> id;
            loginCharacter -> nickname = tempUser[ selectMenu - '0' - 1 ].nickname;
            filePath = ROOT_PATH + "userData/" + loginUser->id + "/" + tempUser[ selectMenu - '0' - 1 ].nickname + "/characterInfo.txt";

            fp = fopen(filePath.c_str(), "rt");

            char bfr[100] = "";
            fgets(bfr, sizeof(bfr), fp);
            loginCharacter -> lvl = atoi(strtok(bfr, ","));
            loginCharacter -> exp = atoi(strtok(NULL, ","));
            loginCharacter -> nowEquipmentId[EQUIP_MASK] = atoi(strtok(NULL, ","));
            loginCharacter -> nowEquipmentId[EQUIP_ARMOR] = atoi(strtok(NULL, ","));
            loginCharacter -> nowEquipmentId[EQUIP_SHOES] = atoi(strtok(NULL, ","));
            loginCharacter -> nowEquipmentId[EQUIP_GLOVES] = atoi(strtok(NULL, ","));
            loginCharacter -> nowEquipmentId[EQUIP_CLOAK] = atoi(strtok(NULL, ","));
            loginCharacter -> nowWeaponId = atoi(strtok(NULL, ","));
            loginCharacter -> jobId = atoi(strtok(NULL, ","));
            loginCharacter -> dieYn = strtok(NULL, ",")[0];
            loginCharacter -> hp = atoi(strtok(NULL, ","));
            loginCharacter -> sp = atoi(strtok(NULL, ","));
            loginCharacter -> pos.row = atoi(strtok(NULL, ","));
            loginCharacter -> pos.col = atoi(strtok(NULL, ","));
            loginCharacter -> pos.floor = atoi(strtok(NULL, "\n"));
            fclose(fp);


            //직업명 불러오기
            getJobName(loginCharacter);

            //레벨별 정보 불러오기
            filePath = ROOT_PATH + "levelInfo.txt";
            fp = fopen(filePath.c_str(), "rt");
            while (fgets(bfr, sizeof(bfr), fp)) {
                if (loginCharacter -> lvl == atoi(strtok(bfr, ","))) {
                    loginCharacter -> maxExp = atoi(strtok(NULL, ","));
                    loginCharacter -> maxHp = atoi(strtok(NULL, "\n"));
                    break;
                }
            }

            loginCharacter -> beforeBlock = '0';
            loginCharacter -> lastPos.row = loginCharacter -> pos.row;
            loginCharacter -> lastPos.col = loginCharacter -> pos.col;
            // cout << "접속한 캐릭터 : " << tempUser[ selectMenu - '0' - 1 ].nickname << endl;
            return true;
        }
    }
}

void CharacterClass::characterAccount(Login *loginUser)
{
    using namespace std;
    User accountCharacter;
    string filePath = ROOT_PATH + "userData/" + loginUser->id + "/character.txt";

    system("clear");

    FILE * fp  = fopen(filePath.c_str(), "at");
    cout << "닉네임 : ";
    cin >> accountCharacter.nickname;
    fprintf(fp, "%s\n", accountCharacter.nickname.c_str());
    fclose(fp);

    //생성한 캐릭터 디렉터리
    string folderPath = ROOT_PATH + "userData/" + loginUser->id + "/" + accountCharacter.nickname;
    mkdir(folderPath.c_str(), 0777);
    //mkdir(folderPath);

    filePath = folderPath + "/characterInfo.txt";

    //캐릭터정보 저장 파일
    fp = fopen(filePath.c_str(), "wt");
    // 캐릭터 생성 초기 값
    // lvl, exp, 전체경험치, 장비1, 장비2, 장비3, 장비4, 장비5, 무기, 직업ID, hp, sp, 좌표row, 좌표col, 층
    fprintf(fp, "1,0,0,0,0,0,0,0,0,N,100,100,18,25,0\n");
    fclose(fp);

    //캐릭터 인벤토리 정보 저장 파일
    filePath = folderPath + "/equipInv.txt";
    fp = fopen(filePath.c_str(), "wt");
    fprintf(fp, "");
    fclose(fp);

    filePath = folderPath + "/comsumableInv.txt";
    fp = fopen(filePath.c_str(), "wt");
    fprintf(fp, "");
    fclose(fp);

    filePath = folderPath + "/goldInv.txt";
    fp = fopen(filePath.c_str(), "wt");
    fprintf(fp, "");
    fclose(fp);

    cout << "캐릭터가 생성되었습니다!" << endl;
    sleep(1);
}

// TODO : 골드 추가 후 금액지불 프로세스 추가해야됨(파라메터도 수정해야됨)
void CharacterClass::rebirth(User *loginCharacter, int *userGold) {
    int payGold = rand() % 500 + (loginCharacter -> lvl * 100); //레벨 비례 증가
    char selectMenu = NULL;

    cout << "------------------------------------------------" << endl;
    cout << " 부활하시려면 골드가 필요합니다." << endl;
    cout << " 부활 비용 : " << payGold << endl;
    cout << "------------------------------------------------" << endl;
    if (*userGold < payGold) {
        cout << "부활금액이 부족합니다." << endl;
        cout << "사채업자에게 돈을 빌려오세요" << endl;
    }else {
        cout << " 부활 하시겠습니까?";
        cin >> selectMenu;
        if (towupper(selectMenu) == 'Y') {
            *userGold -= payGold;
            loginCharacter -> hp = loginCharacter -> maxHp * 0.1;
        }
    }
}
// TODO : 골드 추가 후 금액지불 프로세스 추가해야됨(파라메터도 수정해야됨)
void CharacterClass::levelUp(User *loginCharacter, int *userGold) {
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

    cout << "------------------------------------------------" << endl;
    cout << " 레벨업 하시려면 골드가 필요합니다." << endl;
    cout << " 레벨업 비용 : " << payGold << endl;
    cout << "------------------------------------------------" << endl;
    if (*userGold < payGold) {
        cout << "레벨업 금액이 부족합니다." << endl;
        cout << "사채업자에게 돈을 빌려오세요" << endl;
    }else {
        cout << " 레벨업 하시겠습니까?";
        cin >> selectMenu;
        if (towupper(selectMenu) == 'Y') {
            *userGold -= payGold;
            loginCharacter -> lvl ++;
        }
    }
}

void CharacterClass::getWork(User *loginCharacter) {
    char selectMenu = NULL;
    cout << "------------------------------------------------" << endl;
    cout << " 전직하실 직업을 선택해 주세요. " << endl;
    cout << " 1. 검술사" << endl;
    cout << " 2. 마법사" << endl;
    cout << " 3. 궁술사" << endl;
    cout << " 4. 창술사" << endl;
    cout << " 5. 암살자" << endl;
    cout << "------------------------------------------------" << endl;
    cin >> selectMenu;

    if (isdigit(selectMenu)) {
        loginCharacter -> jobId = selectMenu;
        getJobName(loginCharacter);
    }
}

void CharacterClass::getJobName(User *loginCharacter) {
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

void CharacterClass::move(User *loginCharacter, char moveKey) {
    loginCharacter -> lastPos.row = loginCharacter -> pos.row;
    loginCharacter -> lastPos.col = loginCharacter -> pos.col;

    if (moveKey == 65) {
        loginCharacter->pos.row --;
    }else if (moveKey == 66) {
        loginCharacter->pos.row ++;
    }else if (moveKey == 67) {
        loginCharacter->pos.col ++;
    }else if (moveKey == 68) {
        loginCharacter->pos.col --;
    }else {
        cout << "잘못된 입력입니다." << endl;
    }
}

void CharacterClass::gameSave(User *loginCharacter) {
    string filePath = ROOT_PATH;
    filePath += "userData/" + loginCharacter -> id + "/" + loginCharacter -> nickname + "/" + "characterInfo.txt";
    FILE *fp = fopen(filePath.c_str(), "wt");

    if (fp == NULL) {
        cout << "잘못된 파일입니다." << endl;
    }

    fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%c,%d,%d,%d,%d,%d\n"
        , loginCharacter -> lvl
        , loginCharacter -> exp
        , loginCharacter -> nowEquipmentId[EQUIP_MASK]
        , loginCharacter -> nowEquipmentId[EQUIP_ARMOR]
        , loginCharacter -> nowEquipmentId[EQUIP_SHOES]
        , loginCharacter -> nowEquipmentId[EQUIP_GLOVES]
        , loginCharacter -> nowEquipmentId[EQUIP_CLOAK]
        , loginCharacter -> nowWeaponId
        , loginCharacter -> jobId
        , loginCharacter -> dieYn
        , loginCharacter -> hp
        , loginCharacter -> sp
        , loginCharacter -> pos.row
        , loginCharacter -> pos.col
        , loginCharacter -> pos.floor);
    fclose(fp);
}