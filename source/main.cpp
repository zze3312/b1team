#include "header/types.h"
#include "header/UserClass.h"
#include "header/MapClass.h"
#include "header/MonsterClass.h"

int main(){
    srand(time(NULL));
    Login *loginUser = new Login(); //로그인 사용자 정보 담김
    User *loginCharacter = new User(); //접속한 캐릭터 정보 담김
    UserClass userFunc; //사용자 관련 기능 담김
    char selectMenu = NULL;

    system("clear");
    cout << "메인화면" << endl;
    cout << "1. 로그인" << endl;
    cout << "2. 회원가입" << endl;
    cout << "3. 종료" << endl;
    cout << "실행하실 메뉴를 선택해주세요" << endl;
    cin >> selectMenu;

    // 메뉴 선택 후 char형을 int형으로 변환하여 switch문 사용
    switch (selectMenu - '0') {
        case 1:
            // login 성공 시 true 반환됨
            if (userFunc.login(loginUser)) {
                system("clear");
                cout << "현재 로그인 정보 : " << loginUser -> id << endl;

                // 캐릭터 접속 성공 시 true 반환됨
                if (userFunc.characterSelect(loginUser, loginCharacter)) {
                    system("clear");
                    cout << "캐릭터 선택 성공\n";
                    // 캐릭터 정보 확인
                    cout << "접속한 캐릭터명 : " << loginCharacter -> nickname << endl;
                    // cout << "접속한 캐릭터레벨 : " << loginCharacter -> lvl << endl;
                    // cout << "접속한 캐릭터경험치 : " << loginCharacter -> exp << endl;
                    // cout << "접속한 캐릭터레벨업 요구 경험치 : " << loginCharacter -> maxExp << endl;
                    // cout << "접속한 캐릭터장비_머리 : " << loginCharacter -> nowEquipmentId[EQUIP_MASK] << endl;
                    // cout << "접속한 캐릭터장비_갑바 : " << loginCharacter -> nowEquipmentId[EQUIP_ARMOR] << endl;
                    // cout << "접속한 캐릭터장비_신발 : " << loginCharacter -> nowEquipmentId[EQUIP_SHOES] << endl;
                    // cout << "접속한 캐릭터장비_장갑 : " << loginCharacter -> nowEquipmentId[EQUIP_GLOVES] << endl;
                    // cout << "접속한 캐릭터장비_망토 : " << loginCharacter -> nowEquipmentId[EQUIP_CLOAK] << endl;
                    // cout << "접속한 캐릭터무기 : " << loginCharacter -> nowWeaponId << endl;
                    // cout << "접속한 캐릭터체력 : " << loginCharacter -> hp << endl;
                    // cout << "접속한 캐릭터스킬포인트 : " << loginCharacter -> sp << endl;
                    // cout << "접속한 캐릭터row : " << loginCharacter.pos -> row << endl;
                    // cout << "접속한 캐릭터col : " << loginCharacter.pos -> col << endl;
                }else {
                    cout << "캐릭터 선택 실패" << endl;
                }
            }else {
                cout << "로그인 실패" << endl;
            }
        break;
        case 2:
            // 회원가입
            userFunc.join();
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
        case 4:
            system("clear");
            cout << "맵테스트" << endl;
            MapClass mapFunc;
            char map[ROW_SIZE][COL_SIZE] = {0};
            string mapNumber = "0";
            mapFunc.mapInit(map, mapNumber);
            mapFunc.mapPrint(map);
        break;
        case 5:
            system("clear");
            cout << "전투테스트" << endl;
            MonsterClass msFunc;

    }
    sleep(1);
}
