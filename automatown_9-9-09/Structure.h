#ifndef _STRUCTURE_H
#define _STRUCTURE_H

#define INDUSTRIAL 		0
#define COMMERCIAL 		1
#define RESIDENTIAL 	2

struct Structure
{
	int		tileIndex,
			population,
			jobs,
			industrialDemand,
			commercialDemand,
			residentialDemand,
			type;
};

#endif
