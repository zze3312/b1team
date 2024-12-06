#ifndef ITEMCLASS_H
#define ITEMCLASS_H

#include "types.h"

typedef struct {
    int equipmentID; // 인벤토리에서 출력할 아이템 번호순 (즉 0개는 포함 x)
    int haveEquip[100];
    int consumableID;
    int haveConsum[8];
    string name;

    int equipmentList[100]; // "rt"로 기존 파일에 있는 보유개수 불러옴
    int consumableList[8];
    int gold;

    int tierD;
    int tierC;
    int tierB;
    int tierA;
    int teleportHome;
    int teleportAny;
    int enhanceEquip;
    int elixir;

    int equipD;
    int equipC;
    int equipB;
    int equipA;

    int potionD;
    int potionC;
    int potionB;
    int potionA;

    // 정보 담기

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
        void openInventory();
        void onSet(EquipmentSet set);
        void checkSet(int userEquipment[5]);
};



#endif //ITEMCLASS_H
