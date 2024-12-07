#ifndef ITEMCLASS_H
#define ITEMCLASS_H

#include "types.h"

typedef struct {
    int equipmentID; // 인벤토리에서 출력할 아이템 번호순 (즉 0개는 포함 x)
    int haveEquip[100]; // 1개 이상인 장비 출력용
    int consumableID; // 소모품 번호순
    int haveConsum[8]; // 1개 이상인 장비 출력용
    string name; 

    int equipmentList[100]; // "rt"로 기존 파일에 있는 보유개수 불러옴, 현재 유저 인벤
    int consumableList[8]; // 똑같이 기존 파일에 있는 거 담아옴, 현재 유저 인벤벤
    int gold;

    int tierD; // 1티어
    int tierC; // 2티어
    int tierB; // 3티어
    int tierA; // 4티어 얻었을 때 드랍 유무 담아주는 변수
    int teleportHome; 
    int teleportAny;
    int enhanceEquip;
    int elixir;

    int equipD; 
    int equipC; // 도감 번호중에 랜덤으로 드랍
    int equipB;
    int equipA;

    int potionD; // 포션 드랍 유무 결정
    int potionC;
    int potionB;
    int potionA;

    // 정보 담기 (txt에서 읽어오고 여기에 담음)

    // 장비
    int equipNumList[100];
    string equipNameList[100];
    string equipTierList[100];
    int equipSetNumList[100];
    string equipSpecList[100];
    int equipTypeList[100]; // 뒤에서 2번째
    int equipJobList[100]; // 맨 뒤뒤
    // 소모품
    string consumableNumList[8];
    string consumableNameList[8];
    string consumableTierList[8];
    string consumableEXList[8];
    // 세트효과
    string setEffectNumList[15];
    string setEffectNameList[15];
    string setEffectEXList[15];

} Inventory;




class ItemClass {
    Inventory *inv = new Inventory();
    Character *user = new Character();

    public:
        ItemClass(Character *loginCharacter) : user(loginCharacter) {
            updateInventory();
            readInfoItemName();
        }
        void updateInventory();
        void dropItem(Inventory inv);
        void readInfoItemName();
        void tryEnhance(int tryConsumable);
        void wearEquip(int tryEquip);
        void useConsumable(int tryConsumable);
        void showNowEquip();

        void equipInventory();        
        void consumableInventory();

        void openInventory(); // 인벤토리 오픈
        void closeInven(); // 인벤토리 저장 기능
        void ifDeathInven(); // 죽었을 때 아이템 잃는 기능
};



#endif //ITEMCLASS_H
