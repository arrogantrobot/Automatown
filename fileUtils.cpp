#include <fstream>
#include <vector>

void createFile()
{
	std::vector<int> *tiles;
	tiles = new std::vector<int>;
	for(int i=0;i<200;i++)
	{
		tiles->push_back(TREE);
	}
	for(int i=0;i<20;i++)
	{
		tiles->push_back(ROAD_1);
	}	
	for(int i=0;i<180;i++)
	{
		tiles->push_back(BLANK);
	}
	std::ofstream tileFile;
	tileFile.open("tileFile.dat");
	for(uint i=0;i<tiles->size();i++)
	{
		tileFile << (*tiles)[i] << std::endl;
	}
	tileFile.close();
}

void createMapping()
{
	std::vector<int> *tiles;
	tiles = new std::vector<int>;
	for(int i=0;i<200;i++)
	{
		tiles->push_back(TREE);
	}
	for(int i=0;i<20;i++)
	{
		tiles->push_back(ROAD_1);
	}	
	for(int i=0;i<180;i++)
	{
		tiles->push_back(BLANK);
	}
	std::ofstream tileFile;
	tileFile.open("tileFile.dat");
	for(uint i=0;i<tiles->size();i++)
	{
		tileFile << (*tiles)[i] << std::endl;
	}
	tileFile.close();
}
