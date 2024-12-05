#include <time.h>
#include "header/types.h"

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

void updateInventory(Inventory * inv, User * user)
{
    // 장비 불러오기
    string folderPath = ROOT_PATH + "userData/" + "doyeop" + "/" + "teamless" + "/equipInv.txt";
    // TODO : "doyeop", "teamless" 임시로 집어넣음, 사용자와 닉네임 값 집어넣어야함

    FILE * fp = fopen(folderPath.c_str(), "rt");

    char str[100];
    int i = 0;

    while (fgets(str,sizeof(str),fp))
    {
        inv->equipmentList[i] = atoi(str);
        i++;
    }

    fclose(fp);

    // 소모품 불러오기
    string folderPath2 = ROOT_PATH + "userData/" + "doyeop" + "/" + "teamless" + "/consumableInv.txt";

    FILE * fp2 = fopen(folderPath2.c_str(), "rt");

    char str2[100];
    i = 0;

    while (fgets(str2,sizeof(str2),fp2))
    {
        inv->consumableList[i] = atoi(str2);
        i++;
    }
    
    fclose(fp2);

    // 골드 불러오기
    string folderPath3 = ROOT_PATH + "userData/" + "doyeop" + "/" + "teamless" + "/goldInv.txt";

    FILE * fp3 = fopen(folderPath3.c_str(), "rt");

    char str3[10000];
    fgets(str3,sizeof(str3),fp3);
    inv->gold = atoi(str3);
    
    fclose(fp3);
}

void dropItem(Inventory inv) // 얻은 아이템이 뭔지 확정하고, 인벤토리에 추가까지 해주는 함수
{
    srand((int)time(NULL));

    // 랜덤값 필요한 드랍템들
    int equipC;
    int equipB;
    int equipA;
    int teleportAny;
    int elixir;
    
    if (inv.tierC == 1) // 0 - 못얻음, 1 - 얻음
    {
        equipC = rand() % 30 + 11;
        inv.equipmentList[equipC - 1] += 1;
    }
    if (inv.tierB == 1)
    {   
        equipB = rand() % 30 + 41;
        inv.equipmentList[equipB - 1] += 1;
    }
    if (inv.tierA == 1)
    {
        equipA = rand() % 30 + 71;
        inv.equipmentList[equipA - 1] += 1;
    }
    if (inv.potionC == 1)
    {
        inv.consumableList[1] += 1;
    }
    if (inv.potionB == 1)
    {
        inv.consumableList[2] += 1;
    }
    if (inv.potionA == 1)
    {
        inv.consumableList[3] += 1;
    }
    if (inv.teleportHome == 1)
    {
        inv.consumableList[4] += 1;
    }
    if (inv.teleportAny == 1)
    {
        teleportAny = rand() % 3 + 1;
        inv.consumableList[5] += teleportAny;
    }
    if (inv.elixir == 1)
    {
        elixir = rand() % 3 + 1;
        inv.consumableList[6] += elixir;
    }

}

void readInfoItemName(Inventory * inv)
{
    // 장비 정보 불러오기
    string folderPath = ROOT_PATH + "item/equipment.txt";

    FILE * fp = fopen(folderPath.c_str(), "rt");

    char str[1000];
    char * tempNum;
    char * tempName;
    char * tempTier;
    char * tempSetNum;
    char * tempSpec;
    char * tempType;
    char * tempJob;

    int i = 0;

    while (fgets(str,sizeof(str),fp))
    {
        tempNum = strtok(str,",");
        tempName = strtok(NULL, ",");
        tempTier = strtok(NULL, ",");
        tempSetNum = strtok(NULL, ",");
        tempSpec = strtok(NULL, ",");
        tempType = strtok(NULL, ",");
        tempJob = strtok(NULL, "\n");

        inv->equipNumList[i] = atoi(tempNum);
        inv->equipNameList[i] = tempName;
        inv->equipTierList[i] = tempTier;
        inv->equipSetNumList[i] = atoi(tempSetNum);
        inv->equipSpecList[i] = tempSpec;
        inv->equipTypeList[i] = atoi(tempType);
        inv->equipJobList[i] = atoi(tempJob);

        i++;
    }
    fclose(fp);

    // 소모품 정보 불러오기
    string folderPath2 = ROOT_PATH + "item/consumable.txt";

    FILE * fp2 = fopen(folderPath2.c_str(), "rt");

    char str2[1000];
    i = 0;

    while (fgets(str2,sizeof(str2),fp2))
    {
        tempNum = strtok(str2,",");
        tempName = strtok(NULL, ",");
        tempTier = strtok(NULL, ",");
        tempSetNum = strtok(NULL, "\n");

        inv->consumableNumList[i] = tempNum;
        inv->consumableNameList[i] = tempName;
        inv->consumableTierList[i] = tempTier;
        inv->consumableEXList[i] = tempSetNum;

        i++;
    }
    fclose(fp2);

    // 세트효과 정보 불러오기
    string folderPath3 = ROOT_PATH + "item/setEffect.txt";

    FILE * fp3 = fopen(folderPath3.c_str(), "rt");

    char str3[100];
    i = 0;

    while (fgets(str3,sizeof(str3),fp3))
    {
        tempNum = strtok(str3, ",");
        tempName = strtok(NULL, ",");
        tempTier = strtok(NULL, "\n");

        inv->setEffectNumList[i] = tempNum;
        inv->setEffectNameList[i] = tempName;
        inv->setEffectEXList[i] = tempTier;

        i++;
    }
    fclose(fp3);

}

void tryEnhance(Inventory * inv, User * user, int tryConsumable)
{
    while (1)
    {
        cout << "               강화할 장비를 선택해주세요.\n";
        cout << "=======================================================\n";
        cout << "1. " << user->nowWeaponId << endl;
        cout << "2. " << user->nowEquipmentId[0] << endl;
        cout << "3. " << user->nowEquipmentId[1] << endl;
        cout << "4. " << user->nowEquipmentId[2] << endl;
        cout << "5. " << user->nowEquipmentId[3] << endl;
        cout << "6. " << user->nowEquipmentId[4] << endl;
        cout << "=======================================================\n";

        string choice;
        cin >> choice;
        system("clear");

        int prob; // 확률

        if (tryConsumable == 7) // 엘릭서일 경우 확률 100퍼
        {
            prob = 0;
        }
        else if (tryConsumable == 8) // 강화 주문서일 경우 20퍼
        {
            prob = rand() & 5;
        }

        if (prob == 0)
        {
            if (choice == "1")
            {
                user->nowWeaponId; 
            }
            else if (stoi(choice) > 1 && stoi(choice) < 7)
            {
                /* code */
            }
            else
            {
                continue;
            }
        }
        else
        {
            cout << "파괴!\n";
        }
        
    }
}

void wearEquip(Inventory * inv, User * user, int tryEquip)
{
    inv->equipTypeList[tryEquip];
    
    if (user->jobId == inv->equipJobList[tryEquip])
    {
        for (int i = 0; i < 6; i++)
        {
            if (i == inv->equipTypeList[tryEquip])
            {
                if (user->nowEquipmentId[i] == 0)
                {
                    user->nowEquipmentId[i] = inv->equipNumList[tryEquip];
                    cout << inv->equipNameList[tryEquip] << " 착용 완료! \n";
                    inv->equipmentList[tryEquip]--;
                    return;
                }
                else if (user->nowWeaponId == 0)
                {
                    user->nowWeaponId - inv->equipNumList[tryEquip];
                    cout << inv->equipNameList[tryEquip] << " 착용 완료! \n";
                    inv->equipmentList[tryEquip]--;
                }
                else
                {
                    cout << "=======================================================\n";
                    cout << "착용중인 장비가 있습니다!! 먼저 장비를 해제하고 와주세요\n";
                    return;
                }
            }
        }
    }
    
}

void useConsumable(Inventory * inv, User * user, int tryConsumable)
{
    switch (tryConsumable)
    {
    case 1: // 빨간물약 > 포션은 쿹타임 있어야 할까요
        user->hp += user->maxHp / 10;
        cout << "체력을 " << user->maxHp / 10 << "만큼 회복했다!\n";
        inv->consumableList[0]--;
        break;
    case 2: // 주황물약
        user->hp += user->maxHp * (3/10); // 소수점 괜찮나..?
        cout << "체력을 " << user->maxHp * (3/10) << "만큼 회복했다!\n";
        inv->consumableList[1]--;
        break;
    case 3: // 맑은물약
        user->hp += user->maxHp / 2;
        cout << "체력을 " << user->maxHp / 2 << "만큼 회복했다!\n";
        inv->consumableList[2]--;
        break;
    case 4: // 고농도물약
        user->hp += user->maxHp;
        cout << "체력을 모두 회복했다!\n";
        inv->consumableList[3]--;
        break;
    case 5: // 마을이동주문서
        // 좌표 row 45, col 14, floor 0
        inv->consumableList[4]--;
        break;
    case 6: // 순간이동주문서
        // 새 좌표 생성 / 좌표 이동 / 뒤로가기 함수 필요
        break;
    case 7: // 엘릭서
        tryEnhance(inv, user, tryConsumable);
        break;
    case 8: // 장비강화주문서
        tryEnhance(inv, user, tryConsumable);
        break;
    default:
        break;
    }
    
    
    
}

void showNowEquip(Inventory * inv, User * user)
{
    while (1)
    {
        cout << "========================================\n";
        cout << "  착용중인 장비       (q. 뒤로가기)\n";
        cout << "========================================\n";
        cout << user->nowEquipmentId[0] << endl;
        cout << user->nowEquipmentId[1] << endl;
        cout << user->nowEquipmentId[2] << endl;
        cout << user->nowEquipmentId[3] << endl;
        cout << user->nowEquipmentId[4] << endl;
        cout << user->nowWeaponId << endl;
        cout << "========================================\n";

        string choice;
        cin >> choice;
        system("clear");

        if (choice == "q")
        {
            break;
        }
        else
        {
            continue;
        }
    }
}

void equipInventory(Inventory * inv, User * user)
{
    int i;
    
    while (1)
    {   
        cout << "========================================\n";
        cout << "  보유한 장비 (상세 정보: 번호 입력)\n";
        cout << "========================================\n";
        cout << "  q. 뒤로가기\n";
        cout << "========================================\n";

        string choice;
        inv->equipmentID = 0;

        for (i = 0; i < 100; i++)
        {
            if (inv->equipmentList[i] != 0)
            {
                inv->equipmentID++;
                inv->haveEquip[inv->equipmentID - 1] = i;
                cout << inv->equipmentID << ". " << inv->equipNameList[i] 
                    << " " << inv->equipmentList[i] << "개" << endl;
            }
        }

        cout << "========================================\n";
        cin >> choice;
        system("clear");

        string choiceTwo;

        if (choice == "q")
        {
            break;
        }
        else if (stoi(choice) <= inv->equipmentID && stoi(choice) > 0)
        {
            while (1)
            {
                int tryEquip = inv->haveEquip[stoi(choice)-1]; // 현재 선택한 장비의 씨리얼 넘버 의미미
                cout << "========================================\n";
                cout << inv->equipNameList[tryEquip] << endl;
                cout << "========================================\n";
                cout << "장비 번호: " << inv->equipNumList[tryEquip] << endl;
                cout << "장비 티어: " << inv->equipTierList[tryEquip] << endl;
                cout << "효과: " << inv->equipSpecList[tryEquip] << endl;
                cout << "종류: " << inv->equipTypeList[tryEquip] << endl;
                cout << "착용 가능한 직업: " << inv->equipJobList[tryEquip] << endl;
                cout << "========================================\n";
                cout << "1. 착용하기  2. 세트효과 확인  q. 뒤로가기\n";
                cout << "========================================\n";
                
                cin >> choiceTwo;
                system("clear");

                if (choiceTwo == "1")
                {
                    wearEquip(inv, user, tryEquip);
                    break;
                }
                else if (choiceTwo == "2")
                {
                    cout << "========================================\n";
                    cout << "세트 이름: " << inv->setEffectNameList[inv->equipSetNumList[tryEquip]-1] << endl;
                    cout << "세트효과: " << inv->setEffectEXList[inv->equipSetNumList[tryEquip]-1] << endl;
                    cout << "========================================\n";
                    
                    continue;
                }
                else if (choiceTwo == "q")
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            continue;
        }
        else
        {
            continue;
        }
        
    }
}

void consumableInventory(Inventory * inv, User * user)
{
    int i;

    while (1)
    {
        cout << "========================================\n";
        cout << "  보유한 소모품 (상세 정보: 번호 입력)\n";
        cout << "========================================\n";
        cout << "  q. 뒤로가기\n";
        cout << "========================================\n";

        string choice;
        inv->consumableID = 0;

        for (i = 0; i < 8; i++)
        {
            if (inv->consumableList[i] != 0)
            {
                inv->haveConsum[inv->consumableID] = i;
                cout << inv->consumableID + 1 << ". " << inv->consumableNameList[i]
                    << " " << inv->consumableList[i] << "개" << endl;
                inv->consumableID++;
            }
        }

        cout << "========================================\n";
        cin >> choice;
        system("clear");

        string choiceTwo;
        
        if (choice == "q")
        {
            break;
        }
        else if (stoi(choice) <= inv->consumableID && stoi(choice) > 0)
        {
            while (1)
            {
                int tryConsumable = inv->haveConsum[stoi(choice)-1]; // 선택한 소모품의 씨리얼 넘버
                cout << "========================================\n";
                cout << inv->consumableNameList[tryConsumable] << endl;
                cout << "========================================\n";
                cout << "소모품 번호: " << inv->consumableNumList[tryConsumable] << endl;
                cout << "소모품 티어: " << inv->consumableTierList[tryConsumable] << endl;
                cout << "소모품 설명: " << inv->consumableEXList[tryConsumable] << endl;
                cout << "========================================\n";
                cout << "1. 사용하기  q. 뒤로가기\n";
                cout << "========================================\n";

                cin >> choiceTwo;
                system("clear");

                if (choiceTwo == "1")
                {
                    useConsumable(inv, user, tryConsumable);
                    continue;
                }
                else if (choiceTwo == "q")
                {
                    break;
                }
                else
                {
                    continue;
                }
            }
            continue;
        }
        else
        {
            continue;
        }
    }
    

    

}

void openInventory(Inventory * inv, User * user)
{
    string choice;
    
    while (1)
    {
        cout << "현재 보유한 골드 : " << inv->gold << endl;
        cout << "========================================\n";
        cout << "1. 장비\n";
        cout << "2. 소모품\n";
        cout << "3. 착용중인 장비\n";
        cout << "q. 뒤로가기\n";
        cout << "========================================\n";
        cin >> choice;
        system("clear");

        if (choice == "1")
        {
            equipInventory(inv, user);
            continue;
        }
        else if (choice == "2")
        {
            consumableInventory(inv, user);
            continue;
        }
        else if (choice == "3")
        {
            showNowEquip(inv, user);
            continue;
        }
        else if (choice == "q")
        {
            break;
        }
        else
        {
            cout << "제대로 된 숫자를 입력해라!\n";
            continue;
        }
    }
    
}



void onSet(EquipmentSet set)
{
    char str[100] = "";
    int tempSetID;
    char * tempSetName;
    char * tempEffect;

    

    if (set.equipmentSet == 0)
    {
        cout << "현재 세트효과 없음" << endl;
    }
    else
    {
        char folderPath[100] = "";
        strcat(folderPath, ROOT_PATH.c_str());
        strcat(folderPath,"item/setEffect.txt");

        FILE * fp = fopen(folderPath, "rt");

        while(fgets(str, sizeof(str), fp))
        {
            tempSetID = atoi(strtok(str,","));
            tempSetName = strtok(NULL, ",");
            tempEffect = strtok(NULL, "\n");

            if (tempSetID == set.equipmentSet)
            {
                set.setEffectName = tempSetName;
                set.setEffectEX = tempEffect;
                // TODO : set.addStat[i]도 반영해야함
                break;
            }

        }
    }
    cout << "세트효과 이름 : " << set.setEffectName << endl;
    cout << "세부능력 : " << set.setEffectEX << endl;
    // TODO : 스탯들 늘려주는거 setEffect.txt에 ,로 추가 
}

void checkSet(int userEquipment[5])
{
    EquipmentSet set;
    char folderPath[100] = "";
    strcat(folderPath, ROOT_PATH.c_str());
    strcat(folderPath,"item/equipment.txt");

    FILE * fp = fopen(folderPath, "rt");

    char str[100];

    int checkSet[5];

    int tempItemID;
    char * tempItemName;
    char * tempItemTier;
    int tempItemEffect;

    int i;


    while(fgets(str, sizeof(str), fp))
    {
        tempItemID = atoi(strtok(str,","));
        tempItemName = strtok(NULL, ",");
        tempItemTier = strtok(NULL, ",");
        tempItemEffect = atoi(strtok(NULL, "\n"));

        for (i = 0; i < 5; i++)
        {
            if (tempItemID == userEquipment[i])
            {
                checkSet[i] = tempItemEffect;
            }
        }
    }

    if (checkSet[0] == checkSet[1] && checkSet[1] == checkSet[2] && checkSet[2] == checkSet[3] && checkSet[3] == checkSet[4])
    {
        cout << "세트효과 발동!" << endl; // 출력문 없애기 1
        set.equipmentSet = checkSet[0];
        onSet(set);
    }
    else // 출력확인용, 추후 삭제
    {
        cout << "현재 세트효과 없음" << endl;
    }
    
    // 확인용
    cout << "갑옷 시리얼넘버 : " << userEquipment[0] << endl;
    cout << "신발 시리얼넘버 : " << userEquipment[1] << endl;
    cout << "장갑 시리얼넘버 : " << userEquipment[2] << endl;
    cout << "망토 시리얼넘버 : " << userEquipment[3] << endl;
    cout << "마스크 시리얼넘버 : " << userEquipment[4] << endl;
    cout << "갑옷 세트번호 : " << checkSet[0] << endl;
    cout << "신발 세트번호 : " << checkSet[1] << endl;
    cout << "장갑 세트번호 : " << checkSet[2] << endl;
    cout << "망토 세트번호 : " << checkSet[3] << endl;
    cout << "마스크 세트번호 : " << checkSet[4] << endl;
}

int main()
{
    User user;
    Inventory inv;

    user.jobId = 1;
    
    user.nowEquipmentId[0] = 0; // 추후 삭제
    user.nowEquipmentId[1] = 0;
    user.nowEquipmentId[2] = 0;
    user.nowEquipmentId[3] = 0;
    user.nowEquipmentId[4] = 0;
    user.nowWeaponId = 0;
    

    updateInventory(&inv, &user);
    readInfoItemName(&inv);
    openInventory(&inv, &user);

    checkSet(user.nowEquipmentId);
}

