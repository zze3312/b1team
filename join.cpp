#include <cstring>

#include "types.h"
#include <sys/stat.h>
#include <sys/types.h>



void join();
using namespace std;

int main(){
    join();

    return 0;
}

void join() {
    Login joinInfo;
    Login tempUser;
    cout << "회원가입" << endl;
    cout << "아이디 : ";
    cin >> joinInfo.id;
    cout << "비밀번호 : ";
    cin >> joinInfo.pwd;

    char folderPath[100] = "/home/lms/CLionProjects/b1team/data/";
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

        strcpy(folderPath, "/home/lms/CLionProjects/b1team/data/");
        strcat(folderPath, "userData/");
        strcat(folderPath, joinInfo.id.c_str());
        mkdir(folderPath, 0777);

        strcat(folderPath, "/joinFin.txt");
        fp = fopen(folderPath, "at");
        fprintf(fp, "회원가입완료!");


        cout << "회원가입이 되셨습니다";

    }else {
        cout << "이미 존재하는 아이디입니다." << endl;
    }

}