#include "../header/LoginClass.h"


void LoginClass::join() {
    Login joinInfo;
    Login tempUser;
    system("clear");
    cout << "회원가입" << endl;
    cout << "아이디 : ";
    cin >> joinInfo.id;
    if (joinInfo.id == "q") return;
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
        //mkdir(folderPath);

        strcat(folderPath, "/character.txt");
        fp = fopen(folderPath, "at");
        fprintf(fp, "");


        cout << "회원가입이 되셨습니다";

    }else {
        cout << "이미 존재하는 아이디입니다." << endl;
    }

}

bool LoginClass::login(Login * loginUser) {
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