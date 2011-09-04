#ifndef _STATS_H
#define _STATS_H
#include <vector>
#include "Square.h"

class Stats
{
    public:
        Stats();
        ~Stats();
        int getTotalPop();
        int getTotalJobs();
        int getTotalIDem();
        int getTotalCDem();
        int getTotalRDem();

        void updateStats(std::vector<Square *> *tiles);
        void showStats();

    private:
        int     totalPop,
                totalJobs,
                totalIDem,
                totalCDem,
                totalRDem;



};


#endif
