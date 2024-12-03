#include <cstring>
#include <unistd.h>

#include "header/types.h"
#include <sys/stat.h>
#include <sys/types.h>

void join();
void mainMenu();
bool loginAccount(Login *) ;
bool characterSelect(Login *, User *);
void characterAccount(Login *);

int main(){

    mainMenu();

    return 0;
}

void mainMenu(){
    Login loginUser;
    char selectMenu = NULL;
    system("clear");
    cout << "메인화면" << endl;
    cout << "1. 로그인" << endl;
    cout << "2. 회원가입" << endl;
    cout << "3. 종료" << endl;
    cout << "실행하실 메뉴를 선택해주세요" << endl;

    cin >> selectMenu;

    switch (selectMenu - '0') {
        case 1:

            if (loginAccount(&loginUser)) {
                system("clear");
                cout << "현재 로그인 정보 : " << loginUser.id << endl;
                User loginCharacter;
                if (characterSelect(&loginUser, &loginCharacter)) {
                    system("clear");
                    cout << "캐릭터 선택 성공\n";
                    cout << "접속한 캐릭터명 : " << loginCharacter.nickname << endl;
                    // cout << "접속한 캐릭터레벨 : " << loginCharacter.lvl << endl;
                    // cout << "접속한 캐릭터경험치 : " << loginCharacter.exp << endl;
                    // cout << "접속한 캐릭터장비1 : " << loginCharacter.nowEquipmentId[0] << endl;
                    // cout << "접속한 캐릭터장비2 : " << loginCharacter.nowEquipmentId[1] << endl;
                    // cout << "접속한 캐릭터장비3 : " << loginCharacter.nowEquipmentId[2] << endl;
                    // cout << "접속한 캐릭터장비4 : " << loginCharacter.nowEquipmentId[3] << endl;
                    // cout << "접속한 캐릭터장비5 : " << loginCharacter.nowEquipmentId[4] << endl;
                    // cout << "접속한 캐릭터무기 : " << loginCharacter.nowWeaponId << endl;
                    // cout << "접속한 캐릭터체력 : " << loginCharacter.hp << endl;
                    // cout << "접속한 캐릭터스킬포인트 : " << loginCharacter.sp << endl;
                    // cout << "접속한 캐릭터row : " << loginCharacter.pos.row << endl;
                    // cout << "접속한 캐릭터col : " << loginCharacter.pos.col << endl;
                }else {

                    cout << "캐릭터 선택 실패" << endl;
                }
            }else {
                cout << "로그인 실패" << endl;
            }
        break;
        case 2:
            join();
        break;
        case 3:
            cout << "게임을 종료합니다." << endl;
            exit(0);
        break;

        sleep(1);
    }
}

void join() {
    Login joinInfo;
    Login tempUser;
    system("clear");
    cout << "회원가입" << endl;
    cout << "아이디 : ";
    cin >> joinInfo.id;
    cout << "비밀번호 : ";
    cin >> joinInfo.pwd;

    char folderPath[100] = "";
    strcat(folderPath, ROOT_PATH.c_str());
    strcat(folderPath, "userInfo.txt");
    char buffer[100] = "";
    char flag = 'Y';

    FILE * fp = fopen(folderPath, "rt");
    while (fgets(buffer, sizeof(buffer), fp))
    {
        tempUser.id = strtok(buffer, ",");
        tempUser.pwd = strtok(NULL, "\n");


        if (joinInfo.id == tempUser.id)
        {
            flag = 'N';
            break;
        }
    }
    fclose(fp);

    if (flag == 'Y') {
        fp = fopen(folderPath, "at");
        fprintf(fp, "%s,%s\n", joinInfo.id.c_str(), joinInfo.pwd.c_str());
        fclose(fp);

        strcpy(folderPath, ROOT_PATH.c_str());
        strcat(folderPath, "userData/");
        strcat(folderPath, joinInfo.id.c_str());
        mkdir(folderPath, 0777);

        strcat(folderPath, "/character.txt");
        fp = fopen(folderPath, "at");
        fprintf(fp, "");


        cout << "회원가입이 되셨습니다";

    }else {
        cout << "이미 존재하는 아이디입니다." << endl;
    }

}

bool loginAccount(Login * loginUser) {
    using namespace std;
    Login inputID;
    Login standID;
    system("clear");
    cout << "로그인 (뒤로가시려면 q)" << endl;
    cout << "ID : ";
    cin >> inputID.id;

    if (inputID.id == "q") {
        return false;
    }

    cout << "비밀번호 : ";
    cin >> inputID.pwd;

    char str[100] = "";
    char flag = 'N';
    char folderPath[100] = "";

    strcat(folderPath, ROOT_PATH.c_str());
    strcat(folderPath, "userInfo.txt");

    FILE * fp = fopen(folderPath, "rt");

    while (fgets(str, sizeof(str), fp)) {
        standID.id = strtok(str, ",");
        standID.pwd = strtok(NULL, "\n");
        if (inputID.id == standID.id && inputID.pwd == standID.pwd) {
            flag = 'Y';
            break;
        }
    }
    fclose(fp);

    if(flag == 'Y') {
        cout << "로그인 성공!" << endl;
        loginUser -> id = inputID.id;
        sleep(2);
        return true;
    }else{
        cout << "존재하지 않는 ID입니다! 먼저 회원가입을 해주세요. \n";
        sleep(2);
        return false;
    }

}

bool characterSelect(Login *loginUser, User *loginCharacter) {
    char str[30] = "";
    int cnt = 0;
    char selectMenu = NULL;
    char folderPath[100] = "";
    User tempUser[3];

    strcat(folderPath, ROOT_PATH.c_str());
    strcat(folderPath, "userData/");
    strcat(folderPath, loginUser->id.c_str());
    strcat(folderPath, "/character.txt");

    cout << "현재 생성된 캐릭터" << endl;
    cout << "-----------------------------------" << endl;

    FILE * fp = fopen(folderPath, "rt");

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
        strcpy(folderPath, ROOT_PATH.c_str());
        strcat(folderPath, "userData/");
        strcat(folderPath, loginUser->id.c_str());
        strcat(folderPath, "/");
        strcat(folderPath, tempUser[ selectMenu - '0' - 1 ].nickname.c_str());
        strcat(folderPath, "/");
        strcat(folderPath, "characterInfo.txt");

        fp = fopen(folderPath, "rt");

        char bfr[100] = "";
        fgets(bfr, sizeof(bfr), fp);
        loginCharacter -> lvl = atoi(strtok(bfr, ","));
        loginCharacter -> exp = atoi(strtok(NULL, ","));
        loginCharacter -> nowEquipmentId[0] = atoi(strtok(NULL, ","));
        loginCharacter -> nowEquipmentId[1] = atoi(strtok(NULL, ","));
        loginCharacter -> nowEquipmentId[2] = atoi(strtok(NULL, ","));
        loginCharacter -> nowEquipmentId[3] = atoi(strtok(NULL, ","));
        loginCharacter -> nowEquipmentId[4] = atoi(strtok(NULL, ","));
        loginCharacter -> nowWeaponId = atoi(strtok(NULL, ","));
        loginCharacter -> jobId = atoi(strtok(NULL, ","));
        loginCharacter -> hp = atoi(strtok(NULL, ","));
        loginCharacter -> sp = atoi(strtok(NULL, ","));
        loginCharacter -> pos.row = atoi(strtok(NULL, ","));
        loginCharacter -> pos.col = atoi(strtok(NULL, "\n"));

        cout << "접속한 캐릭터 : " << tempUser[ selectMenu - '0' - 1 ].nickname << endl;
        return true;
    }

    return false;
}

void characterAccount(Login *loginUser)
{
    using namespace std;
    User accountCharacter;
    char folderPath[100] = "";

    system("clear");

    strcat(folderPath, ROOT_PATH.c_str());
    strcat(folderPath, "userData/");
    strcat(folderPath, loginUser->id.c_str());
    strcat(folderPath, "/character.txt");

    FILE * fp  = fopen(folderPath, "at");
    cout << "닉네임 : ";
    cin >> accountCharacter.nickname;
    fprintf(fp, "%s\n", accountCharacter.nickname.c_str());
    fclose(fp);

    //생성한 캐릭터 디렉터리
    strcpy(folderPath, ROOT_PATH.c_str());
    strcat(folderPath, "userData/");
    strcat(folderPath, loginUser->id.c_str());
    strcat(folderPath, "/");
    strcat(folderPath, accountCharacter.nickname.c_str());
    mkdir(folderPath, 0777);

    char tempFolderPath[100] = "";
    strcat(folderPath, "/");
    strcpy(tempFolderPath, folderPath);

    //캐릭터정보 저장 파일
    strcat(folderPath, "characterInfo.txt");
    fp = fopen(folderPath, "wt");
    // 캐릭터 생성 초기 값
    // lvl, exp, 장비1, 장비2, 장비3, 장비4, 장비5, 무기, 직업ID, hp, sp, 좌표row, 좌표col
    fprintf(fp, "1,0,0,0,0,0,0,0,0,100,100,1,1\n");
    fclose(fp);

    //캐릭터 인벤토리 정보 저장 파일
    strcpy(folderPath, tempFolderPath);
    strcat(folderPath, "inventoryInfo.txt");
    fp = fopen(folderPath, "wt");
    fprintf(fp, "");
    fclose(fp);

}