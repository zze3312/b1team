#include "../header/CharacterClass.h"

bool CharacterClass::characterSelect(Login *loginUser, Character *loginCharacter) {
    char str[30] = "";

    char selectMenu = NULL;
    string filePath = ROOT_PATH + "userData/" + loginUser->id + "/character.txt";
    Character tempUser[3];

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
            loginCharacter -> pos.floor = atoi(strtok(NULL, ","));
            loginCharacter -> userStat.str = atoi(strtok(NULL, ","));
            loginCharacter -> userStat.dex = atoi(strtok(NULL, ","));
            loginCharacter -> userStat.intl = atoi(strtok(NULL, ","));
            loginCharacter -> statPoint = atoi(strtok(NULL, "\n"));

            for (int i = 0; i < 7; i ++) {
                fgets(bfr, sizeof(bfr), fp);
                loginCharacter -> savePos[i].floor = atoi(strtok(bfr, ","));
                loginCharacter -> savePos[i].floor = atoi(strtok(NULL, ","));
                loginCharacter -> savePos[i].floor = atoi(strtok(NULL, "\n"));
            }

            fclose(fp);

            //레벨별 정보 불러오기
            filePath = ROOT_PATH + "levelInfo.txt";
            fp = fopen(filePath.c_str(), "rt");
            while (fgets(bfr, sizeof(bfr), fp)) {
                if (loginCharacter -> lvl == atoi(strtok(bfr, ","))) {
                    loginCharacter -> maxExp = atoi(strtok(NULL, ","));
                    loginCharacter -> maxHp = atoi(strtok(NULL, ","));
                    loginCharacter -> minDamage = atoi(strtok(NULL, ","));
                    if (loginCharacter -> jobId != 2){
                        loginCharacter -> maxSp = atoi(strtok(NULL, "\n"));
                    }else {
                        loginCharacter -> maxSp = atoi(strtok(NULL, "\n")) * 1.5;
                    }
                    break;
                }
            }
            fclose(fp);

            //나머지 값 세팅
            loginCharacter -> beforeBlock = '0';
            loginCharacter -> lastPos.row = loginCharacter -> pos.row;
            loginCharacter -> lastPos.col = loginCharacter -> pos.col;
            loginCharacter -> jobName = "";
            // cout << "접속한 캐릭터 : " << tempUser[ selectMenu - '0' - 1 ].nickname << endl;
            return true;
        }
    }
}

void CharacterClass::characterAccount(Login *loginUser)
{
    using namespace std;
    Character accountCharacter;
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
    // lvl, exp, 장비1, 장비2, 장비3, 장비4, 장비5, 무기, 직업ID, 사망여부, hp, sp, 좌표row, 좌표col, 층, 힘, 민첩, 지능, 보유스탯포인트
    // 줄바꿈 이 후 portal정보(floor,row,col 순서로 7개)
    fprintf(fp, "1,0,10,6,7,8,9,1,0,N,100,100,18,25,0,0,0,0,0\n");
    fprintf(fp, "0,0,0\n");
    fprintf(fp, "0,0,0\n");
    fprintf(fp, "0,0,0\n");
    fprintf(fp, "0,0,0\n");
    fprintf(fp, "0,0,0\n");
    fprintf(fp, "0,0,0\n");
    fprintf(fp, "0,0,0\n");

    fclose(fp);

    //캐릭터 인벤토리 정보 저장 파일
    filePath = folderPath + "/equipInv.txt";
    fp = fopen(filePath.c_str(), "wt");
    string fileText = "";
    for (int i = 0; i < 1100; i++) {
        fileText += "0\n";
    }
    fprintf(fp, fileText.c_str());
    fclose(fp);

    filePath = folderPath + "/consumableInv.txt";
    fp = fopen(filePath.c_str(), "wt");
    fprintf(fp, "0\n0\n0\n0\n0\n0\n0\n0\n");
    fclose(fp);

    filePath = folderPath + "/goldInv.txt";
    fp = fopen(filePath.c_str(), "wt");
    fprintf(fp, "300");
    fclose(fp);

    cout << "캐릭터가 생성되었습니다!" << endl;
    //sleep(1);
    usleep(500000);
}

void CharacterClass::move(Character *loginCharacter, char moveKey) {
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

void CharacterClass::gameSave(Character *loginCharacter) {
    string filePath = ROOT_PATH;
    filePath += "userData/" + loginCharacter -> id + "/" + loginCharacter -> nickname + "/" + "characterInfo.txt";
    FILE *fp = fopen(filePath.c_str(), "wt");

    if (fp == NULL) {
        cout << "잘못된 파일입니다." << endl;
    }

    fprintf(fp, "%d,%d,%d,%d,%d,%d,%d,%d,%d,%c,%d,%d,%d,%d,%d,%d,%d,%d,%d\n"
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
        , loginCharacter -> pos.floor
        , loginCharacter -> userStat.str
        , loginCharacter -> userStat.dex
        , loginCharacter -> userStat.intl
        , loginCharacter -> statPoint);
    for (int i = 0; i < 7; i++) {
        fprintf(fp, "%d,%d,%d\n", loginCharacter -> savePos[i].floor, loginCharacter -> savePos[i].row, loginCharacter -> savePos[i].col);
    }
    fclose(fp);
}

void CharacterClass::statWindow(Character *loginCharacter) {
    char inputKey = NULL;
    system("clear");
    cout << "============================================" << endl;
    cout << "              현재 캐릭터 능력치" << endl;
    cout << "=============================================" << endl;
    cout << "  1. 근력 : " << loginCharacter -> userStat.str << endl;
    cout << "  2. 민첩 : " << loginCharacter -> userStat.dex << endl;
    cout << "  3. 지능 : " << loginCharacter -> userStat.intl << endl;
    cout << "=============================================" << endl;
    cout << " 보유 능력치 포인트 : " << loginCharacter -> statPoint << endl;
    cout << "=============================================" << endl;
    if (loginCharacter -> statPoint > 0) {
        cout << " 1. 능력치 분배" << endl;
    }
    cout << " q. 돌아가기" << endl;
    read(0, &inputKey, sizeof(inputKey));
    if (inputKey == '1') {
        while (loginCharacter -> statPoint > 0) {
            system("clear");
            cout << "============================================" << endl;
            cout << "              현재 캐릭터 능력치" << endl;
            cout << "=============================================" << endl;
            cout << "  1. 근력 : " << loginCharacter -> userStat.str << endl;
            cout << "  2. 민첩 : " << loginCharacter -> userStat.dex << endl;
            cout << "  3. 지능 : " << loginCharacter -> userStat.intl << endl;
            cout << "=============================================" << endl;
            cout << " 보유 능력치 포인트 : " << loginCharacter -> statPoint << endl;
            cout << "=============================================" << endl;
            cout << " 분배하실 능력치를 선택해주세요.(q : 돌아가기)" << endl;
            read(0, &inputKey, sizeof(inputKey));
            if (inputKey == '1') {
                cout << " 능력치 포인트를 \' 근력 \'에 투자하시겠습니까?" << endl;
                cout << "   1. 예" << endl;
                cout << "   2. 아니오" << endl;
                read(0, &inputKey, sizeof(inputKey));
                if (inputKey == '1') {
                    loginCharacter -> userStat.str ++;
                    loginCharacter -> statPoint --;
                    cout << " \' 근력 \'이 상승하셨습니다." << endl;
                }
            }else if (inputKey == '2') {
                cout << " 능력치 포인트를 \' 민첩 \'에 투자하시겠습니까?" << endl;
                cout << "   1. 예" << endl;
                cout << "   2. 아니오" << endl;
                read(0, &inputKey, sizeof(inputKey));
                if (inputKey == '1') {
                    loginCharacter -> userStat.dex ++;
                    loginCharacter -> statPoint --;
                    cout << " \' 민첩 \'이 상승하셨습니다." << endl;
                }
            }else if (inputKey == '3') {
                cout << " 능력치 포인트를 \' 지능 \'에 투자하시겠습니까?" << endl;
                cout << "   1. 예" << endl;
                cout << "   2. 아니오" << endl;
                read(0, &inputKey, sizeof(inputKey));
                if (inputKey == '1') {
                    loginCharacter -> userStat.intl ++;
                    loginCharacter -> statPoint --;
                    cout << " \' 지능 \'이 상승하셨습니다." << endl;
                }
            }else if (inputKey == 'q') {
                break;
            }else {
                cout << " 잘못된 입력입니다." << endl;
            }
        }
    }
}

//텔레포트 주문서
void CharacterClass::teleportItem(Character *loginCharacter) {
    //type == 1이면 마을이동 / type == 2이면 순간이동
    char inputKey = NULL;
    while (1){
        system("clear");
        cout << "==================================================" << endl;
        cout << " 주문서 사용" << endl;
        cout << " 1. 마을이동 주문서" << endl;
        cout << " 2. 순간이동 주문서" << endl;
        cout << " q. 닫기" << endl;
        read(0, &inputKey, sizeof(inputKey));
        while (1) {
            if (inputKey == '1') {
                system("clear");
                cout << "==================================================" << endl;
                cout << "마을이동 주문서를 사용하시겠습니까?" << endl;
                cout << "1. 사용하기" << endl;
                cout << "q. 뒤로가기" << endl;
                read(0, &inputKey, sizeof(inputKey));
                cout << "==================================================" << endl;
                if (inputKey == '1') {
                    cout << "마을로 이동합니다.." << endl;
                    usleep(1000000);
                    // 좌표 row 45, col 14, floor 0
                    loginCharacter -> pos.row = 45;
                    loginCharacter -> pos.col = 14;
                    loginCharacter -> lastPos.row = 45;
                    loginCharacter -> lastPos.col = 14;
                    loginCharacter -> beforeBlock = '0';
                    loginCharacter -> pos.floor = 0;
                    return;
                }else if (inputKey == 'q') {
                    break;
                }
            }else if (inputKey == '2') {
                system("clear");
                cout << "==================================================" << endl;
                cout << "순간이동 주문서를 사용하시겠습니까?" << endl;
                cout << "1. 사용하기" << endl;
                cout << "2. 위치 저장하기" << endl;
                cout << "q. 뒤로가기" << endl;
                read(0, &inputKey, sizeof(inputKey));

                while (1) {
                    system("clear");
                    cout << "==================================================" << endl;
                    if (inputKey == '1') {
                        cout << "이동하실 위치를 선택해 주세요." << endl;
                        for (int i = 0; i < 7; i ++ ) {
                            cout << i + 1 << ". ";
                            if (loginCharacter -> savePos[i].col != 0 && loginCharacter -> savePos[i].row != 0) {
                                if (loginCharacter -> savePos[i].floor != 0) {
                                    cout << loginCharacter -> savePos[i].floor << "층";
                                }else {
                                    cout << "마을" ;
                                }
                                cout << " [ " << loginCharacter -> savePos[i].row << " , " << loginCharacter -> savePos[i].col << " ]" << endl;
                            }
                            else {
                                cout << "저장된 좌표 없음" << endl;
                            }
                        }
                        cout << "q : 뒤로가기" << endl;
                        read(0, &inputKey, sizeof(inputKey));
                        while (1) {
                            if (isdigit(inputKey) && inputKey - '0' <= 7 ) {
                                inputKey = inputKey - '0';
                                cout << "==================================================" << endl;
                                cout << "선택한 위치 : ";
                                if (loginCharacter -> savePos[inputKey - 1].floor != 0) {
                                    cout << loginCharacter -> savePos[inputKey - 1].floor  << "층";
                                }else {
                                    cout << "마을" ;
                                }
                                cout << " [ " << loginCharacter -> savePos[inputKey - 1].row << " , " << loginCharacter -> savePos[inputKey - 1].col << " ]";
                                cout << " 로 이동합니다..." << endl;
                                usleep(1000000);
                                loginCharacter -> pos.row = loginCharacter -> savePos[inputKey - 1].row;
                                loginCharacter -> pos.col = loginCharacter -> savePos[inputKey - 1].col;
                                loginCharacter -> lastPos.row = loginCharacter -> savePos[inputKey - 1].row;
                                loginCharacter -> lastPos.col = loginCharacter -> savePos[inputKey - 1].col;
                                loginCharacter -> beforeBlock = '0';
                                loginCharacter -> pos.floor = loginCharacter -> savePos[inputKey - 1].floor;

                                return;
                            }
                            else if (inputKey == 'q') {
                                break;
                            }
                            else {
                                cout << "잘못된 입력입니다." << endl;
                                break;
                            }
                        }
                    }
                    else if (inputKey == '2') {
                        while (1) {
                            system("clear");
                            cout << "==================================================" << endl;
                            cout << "저장시킬 번호를 입력해주세요." << endl;
                            for (int i = 0; i < 7; i ++ ) {
                                cout << i + 1 << ". ";
                                if (loginCharacter -> savePos[i].col != 0 && loginCharacter -> savePos[i].row != 0) {
                                    if (loginCharacter -> savePos[i].floor != 0) {
                                        cout << loginCharacter -> savePos[i].floor << "층";
                                    }else {
                                        cout << "마을" ;
                                    }
                                    cout << " [ " << loginCharacter -> savePos[i].row << " , " << loginCharacter -> savePos[i].col << " ]" << endl;
                                }else {
                                    cout << "저장된 좌표 없음" << endl;
                                }
                            }
                            read(0, &inputKey, sizeof(inputKey));
                            if (isdigit(inputKey) && inputKey - '0' <= 7 ) {
                                loginCharacter -> savePos[inputKey - '0' - 1].floor = loginCharacter -> pos.floor;
                                loginCharacter -> savePos[inputKey - '0' - 1].row = loginCharacter -> pos.row;
                                loginCharacter -> savePos[inputKey - '0' - 1].col = loginCharacter -> pos.col;
                                cout << "저장되었습니다..." << endl;
                                usleep(1000000);
                                return;
                            }else if (inputKey == 'q') {
                                break ;
                            }else {
                                cout << "잘못된 입력입니다." << endl;
                                continue;
                            }
                        }
                    }
                    else if (inputKey == 'q') {
                        break ;
                    }
                    else {
                        cout << "잘못된 입력입니다." << endl;
                        break;
                    }
                }
            }else if (inputKey == 'q') {
                break;
            }else {
                cout << "잘못된 입력입니다." << endl;
                break;
            }
        }
    }
}