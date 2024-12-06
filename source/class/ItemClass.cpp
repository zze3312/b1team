#include "../header/ItemClass.h"

void ItemClass::updateInventory() // 미완성
{
    // 장비 불러오기
    string folderPath = ROOT_PATH + "userData/" + user->id + "/" + user->nickname + "/equipInv.txt";

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
    string folderPath2 = ROOT_PATH + "userData/" + user->id + "/" + user->nickname + "/consumableInv.txt";
    cout << folderPath2 << endl;

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
    string folderPath3 = ROOT_PATH + "userData/" + user->id + "/" + user->nickname + "/goldInv.txt";

    FILE * fp3 = fopen(folderPath3.c_str(), "rt");

    char str3[10000];
    fgets(str3,sizeof(str3),fp3);
    inv->gold = atoi(str3);

    fclose(fp3);
}

void ItemClass::dropItem(Inventory inv) // 완성, 얻은 아이템이 뭔지 확정하고, 인벤토리에 추가까지 해주는 함수
{


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

void ItemClass::readInfoItemName() // 완성
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

void ItemClass::tryEnhance(int tryConsumable) // 미완성
{
    while (1)
    {
        cout << "               강화할 장비를 선택해주세요.\n";
        cout << "=======================================================\n";
        cout << "1. " << user->nowEquipmentId[0] << endl;
        cout << "2. " << user->nowEquipmentId[1] << endl;
        cout << "3. " << user->nowEquipmentId[2] << endl;
        cout << "4. " << user->nowEquipmentId[3] << endl;
        cout << "5. " << user->nowEquipmentId[4] << endl;
        cout << "6. " << user->nowWeaponId << endl;
        cout << "=======================================================\n";

        //string choice;
        //cin >> choice;
        char choice[3];
        read(0, &choice, sizeof(choice));
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
            if (choice[0] == '6')
            {
                cout << "강화 성공!\n"; // TODO : 구현 예정
            }
            else if (choice[0] > '0' && choice[0] < '6')
            {
                cout << "강화 성공!\n"; // TODO : 구현 예정
            }
            else
            {
                continue;
            }
        }
        else
        {
            if (choice[0] == '6')
            {
                cout << inv->equipmentList[user->nowWeaponId] << "가 파괴되었습니다...\n";
                user->nowWeaponId = 0;
            }
            else if (choice[0] > '0' && choice[0] < '6')
            {
                cout << inv->equipmentList[user->nowEquipmentId[stoi(choice)-1]] << "가 파괴되었습니다...\n";
                user->nowEquipmentId[stoi(choice)-1] = 0;
            }
            else
            {
                continue;
            }
        }

    }
}

void ItemClass::wearEquip(int tryEquip) // 완성
{
    if (user->jobId == inv->equipJobList[tryEquip] || inv->equipJobList[tryEquip] == 0)
    {
        for (int i = 0; i < 6; i++)
        {
            if (i == inv->equipTypeList[tryEquip])
            {
                if (user->nowEquipmentId[i] == 0)
                {
                    user->nowEquipmentId[i] = inv->equipNumList[tryEquip];
                    cout << inv->equipNameList[tryEquip] << " 착용 완료! \n";
                    sleep(2);
                    system("clear");
                    inv->equipmentList[tryEquip]--;
                    return;
                }
                else if (user->nowWeaponId == 0)
                {
                    user->nowWeaponId - inv->equipNumList[tryEquip];
                    cout << inv->equipNameList[tryEquip] << " 착용 완료! \n";
                    sleep(2);
                    system("clear");
                    inv->equipmentList[tryEquip]--;
                }
                else
                {
                    cout << "=======================================================\n";
                    cout << "착용중인 장비가 있습니다!! 먼저 장비를 해제하고 와주세요\n";
                    sleep(2);
                    system("clear");
                    return;
                }
            }
        }
    }
    else
    {
        cout << "=======================================================\n";
        cout << "직업에 맞는 장비를 착용해주세요!!\n";
        cout << "현재 직업: " << user->jobId << endl;
        cout << "선택한 아이템의 착용 조건 : " << inv->equipJobList[tryEquip] << endl;
        sleep(2);
        system("clear");
    }

}

void ItemClass::useConsumable(int tryConsumable) // 미완성
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
        tryEnhance(tryConsumable);
        break;
    case 8: // 장비강화주문서
        tryEnhance(tryConsumable);
        break;
    default:
        break;
    }



}

void ItemClass::showNowEquip() // 완성
{
    while (1)
    {
        string set[2];
        int current[5]; // 이름이 너무 길어서 여기에 담음

        for (int i = 0; i < 5; i++)
        {
            current[i] = inv->equipSetNumList[user->nowEquipmentId[i]-1];
        }
        
        
        if (current[0] == 0 || current[1] == 0 || current[2] == 0 || current[3] == 0 || current[4] == 0 || user->nowWeaponId == 0)
        {
            set[0] = "없음";
            set[1] = "없음";
        }
        else if (current[0] == current[1] && current[1] == current[2] && current[2] == current[3] && current[3] == current[4] && current[4] == inv->equipSetNumList[user->nowWeaponId-1])
        {
            set[0] = inv->setEffectNameList[current[0]];
            set[1] = inv->setEffectEXList[current[0]];
        }
        


        cout << "========================================\n";
        cout << "  착용중인 장비       (q. 뒤로가기)\n";
        cout << "========================================\n";
        cout << "1. 마스크:" << user->nowEquipmentId[0] << endl;
        cout << "2. 갑옷:" << user->nowEquipmentId[1] << endl;
        cout << "3. 신발:" << user->nowEquipmentId[2] << endl;
        cout << "4. 장갑:" << user->nowEquipmentId[3] << endl;
        cout << "5. 망토:" << user->nowEquipmentId[4] << endl;
        cout << "6. 무기:" << user->nowWeaponId << endl;
        cout << "========================================\n";
        cout << "적용중인 세트: " << set[0] << endl;
        cout << "효과: " << set[1] << endl;
        cout << "========================================\n";
        cout << "원하는 번호를 입력해서 착용해제\n";

        // string choice;
        // cin >> choice;
        
        char choice[3];
        read(0, &choice, sizeof(choice));
        system("clear");

        if (choice[0] == 'q')
        {
            break;
        }
        else if (choice[0] > '0' && choice[0] < '6')
        {
            int num = atoi(choice)-1;

            if (user->nowEquipmentId[num] != 0)
            {
                cout << "방어구 " << inv->equipNameList[user->nowEquipmentId[num]-1] << " 장착 해제\n";
                inv->equipmentList[user->nowEquipmentId[num]-1]++;
                user->nowEquipmentId[num] = 0;
                continue;
            }
            else
            {
                cout << "해제할 장비가 없습니다!\n";
                sleep(2);
                system("clear");                
                continue;
            }
            
        }
        else if (choice[0] == '6')
        {
            if (user->nowWeaponId != 0)
            {
                cout << "무기 " << inv->equipNameList[user->nowWeaponId-1] << " 장착 해제\n";
                inv->equipmentList[user->nowWeaponId-1]++;
                user->nowWeaponId = 0;
                continue;
            }
            else
            {
                cout << "해제할 장비가 없습니다!\n";
                sleep(2);
                system("clear");                
                continue;
            }
        }
        else
        {
            continue;
        }
    }
}

void ItemClass::equipInventory() // 완성
{
    int i;

    while (1)
    {
        cout << "========================================\n";
        cout << "  보유한 장비 (입력 후 엔터)\n";
        cout << "========================================\n";
        cout << "  q. 뒤로가기\n";
        cout << "========================================\n";

        char choice[4];
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

        if (choice[0] == 'q')
        {
            break;
        }
        else if (!isdigit(choice[0]) || (!isdigit(choice[1]) && choice[1] == ' ') || (!isdigit(choice[2]) && choice[2] == ' '))
        {
            continue;
        }
        else if (stoi(choice) <= inv->equipmentID && stoi(choice) > 0)
        {
            while (1)
            {
                int tryEquip = inv->haveEquip[stoi(choice)-1]; // 현재 선택한 장비의 씨리얼 넘버 의미
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

                // cin >> choiceTwo;
                char choice2;
                read(0, &choice2, sizeof(choice2));
                system("clear");

                if (choice2 == '1')
                {
                    wearEquip(tryEquip);
                    break;
                }
                else if (choice2 == '2')
                {
                    if (inv->equipSetNumList[tryEquip] == 0)
                    {
                        cout << "========================================\n";
                        cout << "세트 이름: " << "없음" << endl;
                        cout << "세트효과: " << "없음" << endl;
                        cout << "========================================\n";
                        continue;
                    }
                    else
                    {
                        cout << "========================================\n";
                        cout << "세트 이름: " << inv->setEffectNameList[inv->equipSetNumList[tryEquip]-1] << endl;
                        cout << "세트효과: " << inv->setEffectEXList[inv->equipSetNumList[tryEquip]-1] << endl;
                        cout << "========================================\n";
                        continue;
                    }
                }
                else if (choice2 == 'q')
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

void ItemClass::consumableInventory() // 완성
{
    int i;

    while (1)
    {
        cout << "========================================\n";
        cout << "  보유한 소모품 (상세 정보: 번호 입력)\n";
        cout << "========================================\n";
        cout << "  q. 뒤로가기\n";
        cout << "========================================\n";

        // string choice;
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
        // cin >> choice;
        char choice[3];
        read(0, &choice, sizeof(choice));
        system("clear");

        //string choiceTwo;

        if (choice[0] == 'q')
        {
            break;
        }
        else if (choice[0] <= inv->consumableID + '0' && choice[0] > '0')
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

                //cin >> choiceTwo;
                read(0, &choice, sizeof(choice));
                system("clear");

                if (choice[0] == '1')
                {
                    useConsumable(tryConsumable);
                    sleep(1);
                    continue;
                }
                else if (choice[0] == 'q')
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

void ItemClass::openInventory() // 완성
{
    char choice[3];
    //string choice;

    while (1)
    {
        system("clear");
        cout << "현재 보유한 골드 : " << inv->gold << endl;
        cout << "========================================\n";
        cout << "1. 장비\n";
        cout << "2. 소모품\n";
        cout << "3. 착용중인 장비\n";
        cout << "q. 뒤로가기\n";
        cout << "========================================\n";
        //cin >> choice;
        read(0, &choice, sizeof(choice));
        system("clear");

        if (choice[0] == '1')
        {
            equipInventory();
            continue;
        }
        else if (choice[0] == '2')
        {
            consumableInventory();
            continue;
        }
        else if (choice[0] == '3')
        {
            showNowEquip();
            continue;
        }
        else if (choice[0] == 'q')
        {
            closeInven();
            break;
        }
        else
        {
            cout << "제대로 된 숫자를 입력해라!\n";
            continue;
        }
    }

}

void ItemClass::closeInven()
{
    // 장비 저장
    string folderPath = ROOT_PATH + "userData/" + user->id + "/" + user->nickname + "/equipInv.txt";

    FILE * fp = fopen(folderPath.c_str(), "wt");

    for (int i = 0; i < 100; i++)
    {
        fprintf(fp, "%d\n", inv->equipmentList[i]);
    }

    fclose(fp);

    // 소모품 저장
    string folderPath2 = ROOT_PATH + "userData/" + user->id + "/" + user->nickname + "/consumableInv.txt";

    FILE * fp2 = fopen(folderPath2.c_str(), "wt");

    for (int i = 0; i < 8; i++)
    {
        fprintf(fp2, "%d\n", inv->consumableList[i]);
    }

    fclose(fp2);

    // 골드 저장
    string folderPath3 = ROOT_PATH + "userData/" + user->id + "/" + user->nickname + "/goldInv.txt";

    FILE * fp3 = fopen(folderPath3.c_str(), "wt");

    fprintf(fp3, "%d\n", inv->gold);

    fclose(fp3);

}