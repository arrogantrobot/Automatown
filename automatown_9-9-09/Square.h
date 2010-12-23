#ifndef _SQUARE_H
#define _SQUARE_H

//#include <gnome.h>

#include "Structure.h"

class Square
{
	public:
	
	Square(const int& mapCoord,const int& setLand, const Structure& setStruct);

	~Square();

	int setLand(const int& changeTo);
	Structure setStructure(const Structure& changeTo);
	int getLand();
	Structure getStructure();
	int getPopulation();
	bool getNeedsRedraw();
	bool getCanChange();
	
	void setPopulation(const int& changeTo);
	void setCanChange(const bool& changeTo);
	void setNeedsRedraw(const bool& changeTo);
	
	private:
	
	int 		land,
				population,
				mapCoordinate;
	bool		canChange,
				needsRedraw;
	Structure 	building;
	
};

#endif
