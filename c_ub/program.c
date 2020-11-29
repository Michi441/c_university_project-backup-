//Michael Lenort
#include <stdio.h>
#include <stdlib.h>
#include "stadt.h"
#include "region.h"
int main(int argc, char *argv[])
{

    if (argc < 10)
    {

        printf("ya buddy, attention please, the list has less then 5 inputs, i need at least 5 \n");
    }
    StadtList *sl = newStadtList();
    Stadt *newStadt(StadtList * sl);

    readStadtList(sl, argv[1]);

    //printStadtWithId(sl, 22);

    //GetPopulationSize(sl, 22);

    RegionList *rl = newRegionList();
    Region *newRegion(RegionList * rl);
    StreetList *streetList = newStreetList();
    Street *newStreet(StreetList * streetList);
    readRegionList(rl, argv[2]);

    readStreetList(streetList, argv[3]);

    printR(rl, 21);

    // Be careful, this function is no joke.
    TheDestroyer(sl, rl, 3, streetList);
    //SortCitiesToRegion(rl, );
}