#ifndef STADT_H
#define STADT_H
#include "region.h"


typedef struct{
    int stadtId;
    char name[101];
    int einwohner;
    int gebietId;
    int meeresHoehe;
} Stadt;


typedef struct {
    Stadt **stadt;
    int count;
    int allocated;
} StadtList;

typedef struct {
    int stadtStart;
    int stadtEnd;
    int distance;
} Street;
typedef struct
{
    Street **street;
    int count;
    int allocated;
} StreetList;

StadtList *
newStadtList();
Stadt *newStadt(StadtList *sl);

StreetList *newStreetList();
Street *newStreet(StreetList *streetList);
void readStadtList(StadtList *sl, char *fileName);
void printStadt(Stadt *s);
void GetAllDistancesFromCity(StadtList *sl2, Stadt *s, StreetList *streetList);

void readStreetList(StreetList *streetList, char *fileName);
// Use this with cautions. Simulated destroyer for a city!
void TheDestroyer(StadtList *sl, RegionList *rl, int id, StreetList *streetList);

void printStadtWithId(StadtList *sl, int id);
void GetPopulationSize(StadtList *sl, int id);

void WriteAfterMathData();

void stringSubst(char *s, char old, char _new); // geh�rt eigtl. nicht hierher

#endif