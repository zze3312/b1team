#ifndef TYPES_H
#define TYPES_H

#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <unistd.h>
#include <ctype.h>
#include <termios.h>
//#include <direct.h>

using namespace std;

const int ROW_SIZE = 50;
const int COL_SIZE = 51;

const int RESET_ROW = 18;
const int RESET_COL = 25;

const int EQUIP_MASK = 0; //머리
const int EQUIP_ARMOR = 1; //갑바
const int EQUIP_SHOES = 2; //신발
const int EQUIP_GLOVES = 3; //장갑
const int EQUIP_CLOAK = 4; //망토

const string ROOT_PATH = "/home/lms/project/b1team/data/";
//const string ROOT_PATH = "C:/Users/jh/CLionProjects/b1team/data/";
static termios orig_termios;

struct Position{
    int row;
    int col;
    int floor;
};

struct Login{
    string id;
    string pwd;
};

struct Skill{
    int id;
    string name;
    double damage;
    int coolTime;
    int useSp;
};

struct Stat {
    int str; //힘
    int dex; //민첩
    int intl; //지능
};

struct Character{
    string id;
    string nickname;
    int lvl;
    int exp;
    int maxExp;
    int nowEquipmentId[5];
    int nowWeaponId;
    int jobId;
    string jobName;
    int hp;
    int maxHp;
    int sp;
    int maxSp;
    char dieYn;
    char beforeBlock;
    int minDamage;
    int statPoint;
    Stat userStat;
    Position pos;
    Position lastPos;
    Position savePos[7];
    Skill userSkill[2];
};

struct Monster{
    char id;
    string name;
    int hp;
    int exp;
    Position pos;
};

struct Job{
    int id;
    string name;
    Skill skillId[5];
};

struct EquipmentItem{
    int id;
    string name;
    int minLevel;
    int useJobId;
};

struct ConsumptionItem{
    int id;
    string name;
    string explanation;
};

struct EquipmentSet{
    int equipmentSet;
    int addStat[5]; // 스탯 개수 임시 5개
    string setEffectName;
    string setEffectEX;
};

#endif // TYPES_H개
