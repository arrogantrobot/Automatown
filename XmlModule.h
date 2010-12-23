#ifndef _XML_MODULE_H
#define _XML_MODULE_H
#include <gnome.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Structure.h"

class XmlModule
{

	public:
	
	XmlModule(const std::string& filename);
	~XmlModule();
	
	std::vector<Structure *> * getStructs();

	private:
	Structure * getNums(std::string lines);
		
	std::string file;
	
	
};
#endif
