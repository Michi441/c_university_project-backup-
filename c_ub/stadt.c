#include <stdio.h>
#include <stdlib.h>
#include "stadt.h"
#include "region.h"

// I guess this is the standard way of creating lists in c
// as i have found pretty much the exact same code when
// i did my own research. I hope its okay if i kinda 'reuse' this.
StadtList *newStadtList()
{
    //printf("executed newstadtlist");
    StadtList *sl = (StadtList *)malloc(sizeof(StadtList));
    sl->count = 0;
    sl->allocated = 10;
    sl->stadt = (Stadt **)calloc(sl->allocated, sizeof(Stadt *));
    return sl;
}

StreetList *newStreetList()
{

    StreetList *streetList = (StreetList *)malloc(sizeof(StreetList));
    streetList->count = 0;
    streetList->allocated = 10;
    streetList->street = (Street **)calloc(streetList->allocated, sizeof(Street *));
    return streetList;
}

Street *newStreet(StreetList *streetList)
{

    if (streetList->count >= streetList->allocated)
    {

        streetList->allocated *= 2;
        streetList->street = (Street **)realloc(streetList->street, streetList->allocated * sizeof(StreetList *));
    }

    Street *street = (Street *)malloc(sizeof(Street));
    streetList->street[streetList->count++] = street;
    return street;
}

// Same as above.
Stadt *newStadt(StadtList *sl)
{
    if (sl->count >= sl->allocated)
    {
        sl->allocated *= 2;
        sl->stadt = (Stadt **)realloc(sl->stadt, sl->allocated * sizeof(Stadt *));
    }
    Stadt *s = (Stadt *)malloc(sizeof(Stadt));
    sl->stadt[sl->count++] = s;
    return s;
}

// Reads the file stadt.dat and adds the data to our StadtList struct.
void readStadtList(StadtList *sl, char *fileName)
{

    FILE *file = fopen(fileName, "r");
    // If there isn't a file, we can't read anything. Return error.
    if (file == NULL)
    {
        perror(fileName);
        exit(1);
    }

    // Integer used for the iteration.
    int r = 0;

    // while r != EOF
    while (r != EOF)
    {

        Stadt *s = newStadt(sl);
        r = fscanf(file, "%d %100s %d %d %d",
                   &s->stadtId, s->name, &s->gebietId, &s->einwohner, &s->meeresHoehe);
        //printStadt(s);
    }

    fclose(file);
}

void readStreetList(StreetList *streetList, char *fileName)
{

    FILE *file = fopen(fileName, "r");
    // If there isn't a file, we can't read anything. Return error.
    if (file == NULL)
    {
        perror(fileName);
        exit(1);
    }

    // Integer used for the iteration.
    int x = 0;
    // while r != EOF

    while (x != EOF)
    {
        Street *street = newStreet(streetList);
        x = fscanf(file, "%d %d %d",
                   &street->stadtStart, &street->stadtEnd, &street->distance);
        //printf("%d %d %d \n", street->stadtStart, street->stadtEnd, street->distance);
    }

    fclose(file);
}

// Finds a city in a given CityList with an integer id.
Stadt *findStadt(StadtList *sl, int id)
{
    int i;

    // Needs to be declared because we want to return
    // a new city.
    Stadt *s = NULL;

    // For the length of our cityList, start an for loop.
    for (i = 0; i < sl->count; i++)
        // if inside our cityList the id of a city is equal
        // to the id that were injected as an argument
        if (sl->stadt[i]->stadtId == id)
        {
            // Set the Stadt *s (which points to NULL)
            // to the stadt that has the same id.
            s = sl->stadt[i];
        }
    // Return the new City with all data (name, gebietId etc.)
    return s;
}

// This function is called TheDestroyer, because it literally
// destroy an entire city. Accepts a CityList, RegionList and an
// integer id for the city you want to destroy

void TheDestroyer(StadtList *sl, RegionList *rl, int id, StreetList *streetList)
{
    // Used for an loop down below.
    int z;
    // Probably needs to be removed.
    int count = 0;
    // First, lets find the City we want to destroy by using the
    // findStadt function (add sl cityList and the id from the city.)
    Stadt *s = findStadt(sl, id);

    // Used to generate a second cityList that holds only neighbor
    // cities from the city that should be destroyed.
    // I think its good to seperate them as i don't want to
    // mess around with the original cityList.
    StadtList *sl2 = newStadtList();

    // Looks like some spaghetti code, but its at the end of the day
    // just the region where the city is in (i use findRegion with
    // the regionList and the city's gebietId we want to destroy) to find
    // the region. For some reason, einwoher and gebietId are switched
    // and i couldn't figure out why, which is why i use s->einwohner
    // for s->gebietId everywhere and the opposite when i need the population
    // size.
    // This also finds all overtypes (if there are any)
    // and even the continent.
    Region *r = findRegion(rl, s->einwohner);
    printf("%s %s %d\n", "Region of the City: ", r->name, r->regionId);
    Region *bundesLand = findRegion(rl, r->overRegion);
    printf("%s %s %d\n", "State of the Citys Region: ", bundesLand->name, bundesLand->regionId);
    Region *Land = findRegion(rl, bundesLand->overRegion);
    printf("%s %s %d\n \n", "Country of the City:", Land->name, Land->regionId);
    printf("%s\n", "Neighbor Cities:");

    // Where the fun begins
    for (int i = 0; i < rl->count; i++)
    {
        if (rl->region[i]->overRegion == bundesLand->regionId)
        {

            //printf("%s", rl->region[i]->name);
            for (int z = 0; z < sl->count; z++)
            {
                if (sl->stadt[z]->einwohner == rl->region[i]->regionId)
                {

                    count++;
                    printf("%s %d %s %s %d\n", "ID: ", sl->stadt[z]->stadtId, sl->stadt[z]->name, " Population Size: ", sl->stadt[z]->gebietId);

                    sl2->stadt[sl2->count++] = sl->stadt[z];
                }
            }
        }
    }

    printf("%101s %s %s %d %d \n",
           "the city we want to destroy is: ",
           s->name, " Population Size: ", s->gebietId, s->stadtId);

    printf("%s \n", "initiaizing BFG 10000 ...... waiting");

    printf("%s %d \n", "Counter is...", count);
    printf("%s \n", "trying to find the closest city. Standby.");
    printf("%s \n \n", "this indeed rocket science...");

    GetAllDistancesFromCity(sl2, s, streetList);
    // LEFT OFF. Basically we need to somehow get the distance between each city
    // and iterate the population size to it
    // either with a new list?
    // and then we need to print it out. so yeah, almost finished.
}

void GetAllDistancesFromCity(StadtList *sl2, Stadt *s, StreetList *streetList)
{

    //Stadt *stadtToDestroy = findStadt(sl2, s);
    for (int i = 0; i < sl2->count; i++)
    {
        for (int z = 0; z < streetList->count; z++)
        {

            if (streetList->street[z]->stadtStart == sl2->stadt[i]->stadtId)
            {
                printf("%s %d %s %s %s %s %s %d %s %d \n", "Start ID:", streetList->street[z]->stadtStart, "City Name:", sl2->stadt[i]->name, "End ID", streetList->street[z]->stadtEnd, "City Name:", streetList->street[z]->name, streetList->street[z]->distance "Distance: ", streetList->street[z]->distance);
            }
        }
    }

    // for (int i = 0; i < streetList->count; i++)
    // {

    //     if (streetList->street[i]->stadtStart == s->stadtId)
    //     {

    //         printf("%d", streetList->street[i]->stadtEnd);
    //     }
    // }
}

void printStadt(Stadt *s)
{
    printf("%d %101s %d %d %d \n", s->stadtId, s->name, s->einwohner, s->gebietId, s->meeresHoehe);

    //findStadt(StadtList *sl, 1);
}

void printStadtWithId(StadtList *sl, int id)
{

    //Stadt *s = findStadt(sl, id);

    //printStadt(s);
}

void GetPopulationSize(StadtList *sl, int id)
{

    Stadt *s = findStadt(sl, id);

    printf("%100s, %d", "You requested the population size, here is it:", s->gebietId);
}

void stringSubst(char *s, char old, char new)
{
    while (*s)
    {
        if (*s == old)
            *s = new;
        s++;
    }
}