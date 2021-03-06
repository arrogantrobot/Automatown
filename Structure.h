#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#define INDUSTRIAL  2
#define COMMERCIAL  1
#define RESIDENTIAL 0
#define FARM        3
#define ROAD        4
#define MISC        5

struct Structure
{
    int         tileIndex,
                population,
                jobs,
                industrialDemand,
                commercialDemand,
                residentialDemand,
                type,
                structureNum;

    Structure():tileIndex(6){}
    Structure(Structure& arg) : tileIndex(arg.tileIndex),
    population(arg.population),
    jobs(arg.jobs),
    industrialDemand(arg.industrialDemand),
    commercialDemand(arg.commercialDemand),
    residentialDemand(arg.residentialDemand),
    type(arg.type),
    structureNum(arg.structureNum)

    {
    }
};

#endif
