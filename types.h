#ifndef TYPES_H
#define TYPES_H

#include <iostream>

#define EQUIP_MASK 0; //머리
#define EQUIP_ARMOR 1; //갑바
#define EQUIP_SHOES 2; //신발
#define EQUIP_GLOVES 3; //장갑
#define EQUIP_CLOAK 4; //망토


typedef struct{
    int row;
    int col;
} Position;

typedef struct{
    std::string id;
    int pwd;
} Login;

typedef struct{
    std::string id;
    std::string nickname;
    int lvl;
    int exp;
    int nowEquipment[5];
    int nowWeapon;
    int jobId;
    int hp;
    int sp;
    Position pos;
    Position savePos[7];
} User;

typedef struct{
    int id;
    std::string name;
    int hp;
    int appearanceProbability; //등장확률
    Position pos;
} Monster;

typedef struct {
    int id;
    std::string  name;
    double damage;
    int coolTime;
    int useSp;
} Skill;

typedef struct {
    int id;
    std::string name;
    Skill skillId[5];
} Job;

typedef struct {
    int id;
    std::string  name;
    int minLevel;
    int useJobId;
} EquipmentItem;

typedef struct {
    int id;
    std::string name;
    std::string explanation;
} ConsumptionItem;

#endif // TYPES_H