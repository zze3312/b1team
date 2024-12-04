#include "../header/PlayClass.h"
#include "../header/MapClass.h"
#include "../header/MonsterClass.h"
#include "../header/CharacterClass.h"

MapClass mapFunc;
MonsterClass msFunc;
CharacterClass charFunc; //캐릭터 관련 기능 담김

void PlayClass::play(char (*map)[COL_SIZE], User *loginCharacter) {
    char inputKey[3];
    // 시작시 맵 셋팅
    mapFunc.setMap(map, loginCharacter -> pos.floor);
    charFunc.setCharacter(map, loginCharacter);
    if (atoi(loginCharacter -> pos.floor.c_str()) > 0) {
        // 마을이 아니면 몬스터 셋팅
        msFunc.setMonsterToMap(map, loginCharacter -> pos.floor);
    }
    system("clear");
    mapFunc.printMap(map, loginCharacter);
    charFunc.printStatus(loginCharacter);

    while (true) {
        echoOff();
        read(0, &inputKey, sizeof(inputKey));
        //TODO : 게임 플레이 전반적인 진행 프로세스 추가
        if (inputKey[0] == 27 && inputKey[1] == 91) {
            charFunc.move(loginCharacter, inputKey[2]);
            charFunc.setCharacter(map, loginCharacter);
        }else if (inputKey[0] == 47) {
            //TODO : / 이후 사용한 단축키 기능 실행
            cout << "동작할 작업" << endl;
            cout << " q : 종료" << endl;
            read(0, &inputKey, sizeof(inputKey));
            //cout << inputKey << endl;
            if (inputKey[0] == 'q') {
                // TODO : 로그아웃 프로세스 추가
                break;
            }

            if (inputKey[0] == 't') {
                Monster *monster = new Monster();
                monster -> id = 'L';
                msFunc.meetMonster(monster, loginCharacter);
            }
            sleep(1);
        }
        // 맵 및 상태창
        system("clear");
        mapFunc.printMap(map, loginCharacter);
        charFunc.printStatus(loginCharacter);
        if (inputKey[0] == 'q') break;
    }
}

void PlayClass::beforePlay (Login *loginUser, User *loginCharacter, char (*map)[COL_SIZE]) {
    if (charFunc.characterSelect(loginUser, loginCharacter)) {
        play(map, loginCharacter);
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