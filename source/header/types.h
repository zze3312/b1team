#ifndef TYPES_H
#define TYPES_H

#include <iostream>

using namespace std;

const int EQUIP_MASK = 0; //머리
const int EQUIP_ARMOR = 1; //갑바
const int EQUIP_SHOES = 2; //신발
const int EQUIP_GLOVES = 3; //장갑
const int EQUIP_CLOAK = 4; //망토

const string ROOT_PATH = "/home/lms/project/b1team/data/";

typedef struct{
    int row;
    int col;
} Position;

typedef struct{
    string id;
    string pwd;
} Login;

typedef struct{
    string id;
    string nickname;
    int lvl;
    int exp;
    int nowEquipmentId[5];
    int nowWeaponId;
    int jobId;
    string jobName;
    int hp;
    int sp;
    Position pos;
    Position savePos[7];
} User;

typedef struct{
    int id;
    string name;
    int hp;
    int appearanceProbability; //등장확률
    Position pos;
} Monster;

typedef struct {
    int id;
    string  name;
    double damage;
    int coolTime;
    int useSp;
} Skill;

typedef struct {
    int id;
    string name;
    Skill skillId[5];
} Job;

typedef struct {
    int id;
    string  name;
    int minLevel;
    int useJobId;
} EquipmentItem;

typedef struct {
    int id;
    string name;
    string explanation;
} ConsumptionItem;

#endif // TYPES_H
