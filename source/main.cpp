#include "header/types.h"
#include "header/LoginClass.h"
#include "header/PlayClass.h"


LoginClass logFunc; //사용자 로그인 관련 기능
PlayClass playFunc;


Login *loginUser = new Login(); //로그인 사용자 정보 담김
Character *loginCharacter = new Character(); //접속한 캐릭터 정보 담김

int main(){
    srand(time(NULL));
    char selectMenu = NULL;

    while(1){

        system("clear");
        cout << "메인화면" << endl;
        cout << "1. 로그인" << endl;
        cout << "2. 회원가입" << endl;
        cout << "3. 종료" << endl;
        cout << "실행하실 메뉴를 선택해주세요" << endl;
        cin >> selectMenu;

        switch (selectMenu - '0') {
            case 1:
                // login 성공 시 true 반환됨
                if (logFunc.login(loginUser)) {
                    playFunc.beforePlay(loginUser, loginCharacter);
                }
            break;
            case 2:
                // 회원가입
                logFunc.join();
            break;
            case 3:
                // 종료
                cout << "게임을 종료합니다." << endl;
                // 종료 시 동적할당 되어있던 정보들 제거
                delete loginUser;
                delete loginCharacter;

                // 프로그램 종료
                exit(0);
            break;
        }
        //playFunc.echoOn();
        //sleep(1);
        usleep(500000);
    }
}
