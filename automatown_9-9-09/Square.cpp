#include "Square.h"

Square::Square(const int& mapCoord,const int& setLand, const Structure& setStruct)
{
	mapCoordinate = mapCoord;
	land = setLand;
	building = setStruct;
	
}

Square::~Square()
{
}

int Square::setLand(const int& changeTo)
{
	int prev = land;
	if(changeTo>=0)
	{
		land = changeTo;
	}
	else
	{
		prev = -1;
	}
	return prev;
}

Structure Square::setStructure(const Structure& changeTo)
{
	Structure oldBuilding = building;
	building = changeTo;
	return oldBuilding;
}

int Square::getLand()
{
	return land;
}

Structure Square::getStructure()
{
	return building;
}

int Square::getPopulation()
{
	return population;
}

bool Square::getNeedsRedraw()
{
	return needsRedraw;
}

bool Square::getCanChange()
{
	return canChange;
}

void Square::setPopulation(const int& changeTo)
{
	if(changeTo>=0)
	{
		population = changeTo;
	}
}

void Square::setCanChange(const bool& changeTo)
{
	canChange = changeTo;
}

void Square::setNeedsRedraw(const bool& changeTo)
{
	needsRedraw = changeTo;
}
