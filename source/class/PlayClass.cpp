#include "../header/PlayClass.h"
#include "../header/MapClass.h"
#include "../header/CharacterClass.h"
#include "../header/ItemClass.h"

MapClass mapFunc;
CharacterClass charFunc; //캐릭터 관련 기능 담김

void PlayClass::play(Character *loginCharacter) {
    char inputKey[3];
    // 시작시 맵 셋팅
    mapFunc.mapInit(loginCharacter);
    // 맵 및 상태창
    system("clear");
    if (loginCharacter -> pos.floor > 0) {
        mapFunc.setPortal();
        mapFunc.setDownFloor(mapFunc.setPortal());
    }
    mapFunc.setCharacter(loginCharacter);
    mapFunc.printMap(loginCharacter);
    mapFunc.printStatus(loginCharacter);

    while (true) {
        echoOff();

        //TODO : 게임 플레이 전반적인 진행 프로세스 추가
        read(0, &inputKey, sizeof(inputKey));
        if (inputKey[0] == 27 && inputKey[1] == 91) {
            charFunc.move(loginCharacter, inputKey[2]);
        }else if (inputKey[0] == 47) {
            //TODO : / 이후 사용한 단축키 기능 실행
            cout << "동작할 작업" << endl;
            cout << " i : 인벤토리" << endl;
            cout << " s : 능력치" << endl;
            cout << " t : 텔레포트" << endl;
            cout << " q : 종료" << endl;
            read(0, &inputKey, sizeof(inputKey));
            //cout << inputKey << endl;
            if (inputKey[0] == 'i') {
                ItemClass *itemFunc = new ItemClass(loginCharacter);
                itemFunc -> openInventory();
                delete itemFunc;
            }else if (inputKey[0] == 's') {
                charFunc.statWindow(loginCharacter);
            }else if (inputKey[0] == 't') {
                charFunc.teleportItem(loginCharacter);
                mapFunc.setMap(loginCharacter -> pos.floor);
            }else if (inputKey[0] == 'q') {
                charFunc.gameSave(loginCharacter);
                return;
            }
            ////sleep(1);
            usleep(500000);
        }
        mapFunc.setCharacter(loginCharacter);
        mapFunc.mapEvent(loginCharacter);

        // 맵 및 상태창
        system("clear");

        mapFunc.printMap(loginCharacter);
        mapFunc.printStatus(loginCharacter);



    }
}

void PlayClass::beforePlay (Login *loginUser, Character *loginCharacter) {
    if (charFunc.characterSelect(loginUser, loginCharacter)) {
        play(loginCharacter);
    }
}

void PlayClass::echoOff(){
    termios new_termios;

    tcgetattr(STDIN_FILENO, &orig_termios);
    new_termios = orig_termios;
    new_termios.c_lflag &= ~ICANON;    // non-canonical input 설정
    new_termios.c_lflag &= ~ECHO;      // 입력 시 터미널에 보이지 않게
    new_termios.c_cc[VMIN] = 1;        // 최소 입력 버퍼 크기
    new_termios.c_cc[VTIME] = 0;       //버퍼 비우는 시간 (timeout)
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

}

void PlayClass::echoOn(){
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

void PlayClass::clearBuffer()
{
    while (getchar() != '\n');
}