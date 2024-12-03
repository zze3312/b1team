#include "header/types.h"

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
        strcat(folderPath,"/item/setEffect.txt");

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
    strcat(folderPath,"/item/clothes.txt");

    FILE * fp = fopen(folderPath, "rt");

    char str[100] = "";

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

// TODO : void 현재 적용중인 세트효과 보기, 없다면 부족한 파츠 출력



int main()
{
    User user;
    user.nowEquipmentId[0] = 81; // 추후 삭제
    user.nowEquipmentId[1] = 82;
    user.nowEquipmentId[2] = 83;
    user.nowEquipmentId[3] = 84;
    user.nowEquipmentId[4] = 85;
    checkSet(user.nowEquipmentId);
}

