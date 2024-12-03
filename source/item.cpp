#include "header/types.h"

void checkSet()
{
    char folderPath[100] = "";
    strcat(folderPath, ROOT_PATH.c_str());
    strcat(folderPath,"/item/clothes.txt");

    FILE * fp = fopen(folderPath, "rt");

    char str[1000] = "";

    int checkSet[5];
    int tempItemID;
    int tempItemEffect;
    

    int userEquipment[5] = {96,97,98,99,100}; // 임시, user.nowEquipmentId[5]로 가져올 예정

    int i;


    while(fgets(str, sizeof(str), fp))
    {
        tempItemID = atoi(strtok(str,","));
        strtok(NULL, ",");
        strtok(NULL, ",");
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
        cout << "세트효과 발동!" << endl; // 세트효과 넣기
        onSet();
    }
    else
    {
        cout << "세트 아이템이 아닙니다.." << endl; // 없어도 됨
    }
    
    // 확인용
    cout << "1번 아이템 : " << userEquipment[0] << endl;
    cout << "2번 아이템 : " << userEquipment[1] << endl;
    cout << "3번 아이템 : " << userEquipment[2] << endl;
    cout << "4번 아이템 : " << userEquipment[3] << endl;
    cout << "5번 아이템 : " << userEquipment[4] << endl;
    cout << "1번 세트 : " << checkSet[0] << endl;
    cout << "2번 세트 : " << checkSet[1] << endl;
    cout << "3번 세트 : " << checkSet[2] << endl;
    cout << "4번 세트 : " << checkSet[3] << endl;
    cout << "5번 세트 : " << checkSet[4] << endl;


}

void onSet()
{

}

int main()
{
    checkSet();
}

