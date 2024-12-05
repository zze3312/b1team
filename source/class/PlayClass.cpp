#include "../header/PlayClass.h"
#include "../header/MapClass.h"
#include "../header/MonsterClass.h"
#include "../header/CharacterClass.h"

MapClass mapFunc;
MonsterClass msFunc;
CharacterClass charFunc; //캐릭터 관련 기능 담김

void PlayClass::play(User *loginCharacter) {
    char inputKey[3];
    Position upFloor = {0, 0};
    Position downFloor = {0, 0};
    // 시작시 맵 셋팅
    mapFunc.mapInit(loginCharacter);
    // 맵 및 상태창
    system("clear");
    if (loginCharacter -> pos.floor > 0) {
        upFloor = mapFunc.setPortal();
        downFloor = mapFunc.setPortal();
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
            cout << " q : 종료" << endl;
            read(0, &inputKey, sizeof(inputKey));
            //cout << inputKey << endl;
            if (inputKey[0] == 'q') {
                charFunc.gameSave(loginCharacter);
                break;
            }

            if (inputKey[0] == 't') {
                Monster *monster = new Monster();
                monster -> id = 'L';
                msFunc.meetMonster(monster, loginCharacter);
            }

            sleep(1);
        }
        mapFunc.setCharacter(loginCharacter);
        if (loginCharacter -> beforeBlock == '6') {
            //올라가는지 내려가는지 체크
            if ((loginCharacter -> pos.row == upFloor.row && loginCharacter -> pos.col == upFloor.col) || loginCharacter -> pos.floor == 0 ) {
                loginCharacter -> pos.floor ++;
            }else {
                loginCharacter -> pos.floor --;
            }

            //던전 안
            mapFunc.mapInit(loginCharacter);
            if (loginCharacter -> pos.floor != 0) {
                //포탈의 위치 바꾸고
                upFloor = mapFunc.setPortal();
                downFloor = mapFunc.setPortal();

                //해당층 입구포탈 위치로 간다
                loginCharacter -> pos.row = downFloor.row;
                loginCharacter -> pos.col = downFloor.col;
                loginCharacter -> lastPos.row = downFloor.row;
                loginCharacter -> lastPos.col = downFloor.col;

            }else {
                //던전 > 마을
                upFloor = {0,0};
                downFloor = {0,0};
                //마을 던전 입구 좌표 : 49 26
                loginCharacter -> pos.row = 49;
                loginCharacter -> pos.col = 26;
                loginCharacter -> lastPos.row = 49;
                loginCharacter -> lastPos.col = 26;
            }
            mapFunc.setCharacter(loginCharacter);
        }


        // 맵 및 상태창
        system("clear");

        mapFunc.printMap(loginCharacter);
        mapFunc.printStatus(loginCharacter);
    }
}

void PlayClass::beforePlay (Login *loginUser, User *loginCharacter) {
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