#include "types.h"
#include <cstring>

void Login_account(User * loginUser)
{
    using namespace std;
    Login inputID;
    Login standID;

    cout << "로그인 하실 ID를 입력해주세요 : \n";
    cin >> inputID.id;

    char folderPath[100] = "/home/lms/project/b1team/";
    strcat(folderPath, "ID_chest.txt");

    FILE * fp = fopen(folderPath, "rt");


    char str[100] = "";

    while (fgets(str, sizeof(str), fp))
    {
        standID.id = strtok(str, ",");
        standID.pwd = strtok(NULL, "\n");
        if (inputID.id == standID.id)
        {
            while (1)
            {
                cout << "비밀번호를 입력해주세요. (취소하려면 cancel)\n";
                cin >> inputID.pwd;
                if (inputID.pwd == standID.pwd)
                {
                    cout << "로그인 성공!" << endl;
                    loginUser->id = inputID.id;
                    return;
                }
                else if (inputID.pwd == "cancel")
                {
                    cout << "처음 화면으로 돌아갑니다.\n";
                    return;
                }
                else
                {
                    cout << "틀린 비밀번호입니다!! \n";
                    continue;
                }
            }
        }
    }
    fclose(fp);

    cout << "존재하지 않는 ID입니다! 먼저 회원가입을 해주세요. \n";

}

void Nickname_account(User * loginUser)
{
    using namespace std;

    char folderPath[100] = "/home/lms/project/b1team/data/userData/";
    char tempPath[100] = "";
    char txtPath[100] = "/nickname.txt";
    strcat(tempPath, folderPath);
    strcat(tempPath, loginUser->id.c_str());
    strcat(tempPath, txtPath);

    FILE * fp  = fopen(tempPath, "rt");

    char str[100];
    fgets(str, sizeof(str), fp);
    
    loginUser->nickname = str;
    cout << "닉네임! : " << str << endl;

}


int main()
{
    User loginUser;
    while (1)
    {
        Login_account(&loginUser);
        cout << "현재 로그인 정보 : " << loginUser.id << endl;
        Nickname_account(&loginUser);
    }


}