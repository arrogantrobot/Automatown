#include <gnome.h>
#include <stdio.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include "Structure.h"

int main()
{
	std::vector<Structure *> *structDefs = new std::vector<Structure *>;
	std::string docname = "test.xml";
	xmlDocPtr doc;
	xmlNodePtr cur, buildings,element;
	doc = xmlParseFile(docname.c_str());
	if (doc == NULL ) {
		fprintf(stderr,"Document not parsed successfully. \n");
		return 1;
	}
	cur = xmlDocGetRootElement(doc);
	
	if (cur == NULL) {
		fprintf(stderr,"empty document\n");
		xmlFreeDoc(doc);
		return 1;
	}
	if (xmlStrcmp(cur->name, (const xmlChar *) "buildings")) {
		fprintf(stderr,"document of the wrong type, root node != story");
		xmlFreeDoc(doc);
		return 1;
	}
	printf("cur->name=%s\n",cur->name);
	buildings = cur;
	while(buildings != NULL)
	{
		printf("Starting buildings loop\n");	
		cur = buildings;
		cur = cur->xmlChildrenNode;
		//xmlChar *num;
		Structure *newStruct = new Structure;
		newStruct->tileIndex = 1;
		structDefs->push_back(newStruct);
		//std::ostringstream a;
		//std::string b;
		//printf("cur->name=%s\n",cur->name);
		cur = cur->next;
		//printf("cur->name=%s\n",cur->name);
		cur = cur->xmlChildrenNode;
		//printf("cur->name=%s\n",cur->name);
		cur = cur->next;
		element = cur;
		while(element !=NULL)
		{
			printf("Starting element loop\n");
			//printf("cur->name=%s\n",cur->name);
			cur = element;
			//cur = cur->next;
			cur = cur->xmlChildrenNode;
			//printf("cur->name=%s\n",cur->name);
			cur = cur->next;
			//printf("cur->name=%s\n",cur->name);
			cur = cur->xmlChildrenNode;
			//printf("cur->name=%s\n",cur->name);
			//cur = cur->xmlChildrenNode;
			cur = cur->next;
			//printf("cur->name=%s\n",cur->next);

			xmlChar *answer = xmlNodeGetContent(cur);
			printf("content=%s\n",answer);
			printf("hey!\n");
			element = element->next;
			element = element->next;
		}
		buildings = buildings->next;
	}
	return 0;
}
