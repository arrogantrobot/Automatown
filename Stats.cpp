#include "Stats.h"
#include <iostream>
using namespace std;


Stats::Stats()
{


}

Stats::~Stats()
{


}


int Stats::getTotalPop()
{
    return totalPop;
}

int Stats::getTotalJobs()
{
    return totalJobs;
}

int Stats::getTotalIDem()
{
    return totalIDem;
}

int Stats::getTotalCDem()
{
    return totalCDem;
}

int Stats::getTotalRDem()
{
    return totalRDem;
}

void Stats::updateStats(std::vector<Square *> *tiles)
{

    totalPop = 0;
    totalJobs = 0;
    totalIDem = 0;
    totalCDem = 0;
    totalRDem = 0;
    
    for(unsigned int i=0;i<tiles->size();i++)
    {
        Structure *strPtr;
        strPtr = (*tiles)[i]->getStructure();
        totalPop += strPtr->population;
        totalJobs += strPtr->jobs;
        totalIDem += strPtr->industrialDemand;
        totalCDem += strPtr->commercialDemand;
        totalRDem += strPtr->residentialDemand;
    }
}

void Stats::showStats()
{
	cout << "totalPop= " << totalPop << endl;
	cout << "totalJobs= " << totalJobs << endl;
	cout << "totalIDem= " << totalIDem << endl;
	cout << "totalCDem= " << totalCDem << endl;
	cout << "totalRDem= " << totalRDem << endl;
}
