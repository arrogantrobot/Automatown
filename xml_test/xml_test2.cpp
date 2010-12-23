#include <gnome.h>
#include <stdio.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlmemory.h>
#include <libxml/xpath.h>
#include <string>
#include <iostream>
#include <sstream>
#include "Structure.h"

int main()
{
	std::string docname = "test.xml";
	xmlDocPtr doc;
	xmlNodePtr cur;
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
	//cur = cur->xmlChildrenNode;
	//xmlChar *num;
	Structure test;
	//std::ostringstream a;
	//std::string b;
	
	//cur = cur->next;
//	cur = cur->xmlChildrenNode;	
//	cur = cur->next;

//	cur = cur->xmlChildrenNode;	
//	cur = cur->next;
//	cur = cur->next;	cur = cur->next;
//	cur = cur->xmlChildrenNode;	
	//num = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
	//printf("content = %s\n",num);
	//a << num ;
	//test.tileIndex = atoi(a.str().c_str());
	//std::cout << test.tileIndex << std::endl;	
/*	while(cur != NULL)
	{
		//std::cout << "cur->name = " << cur->name << std::endl;
		//num = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
		//printf("content = %s\n",num);
		//xmlFree(num);
		cur = cur->next;
		std::cout << "cur->name = " << cur->name << std::endl;
		num = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
		printf("content = %s\n",num);
		a << num ;
		if(b.find("tileIndex",0)!=std::string::npos)
		{
			test.tileIndex = atoi(b.c_str());
			std::cout << test.tileIndex << std::endl;
			break;
		}
		xmlFree(num);
		b = a.str();
		cur = cur->xmlChildrenNode;
	}*/
	xmlChar *num,*keyword;	
		printf("Made it here...\n");
	//cur = cur->next;
		printf("Made it here...\n");
	//cur = cur->xmlChildrenNode;
		printf("Made it here...\n");

	/*while(cur != NULL)
	{
		std::cout << "cur->name = " << cur->name << std::endl;
		num = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
		printf("content = %s\n",num);
		xmlFree(num);
		cur = cur->next;
	}*/
//	xmlChar *xpath =(const xmlChar *) "child::node()";
	xmlXPathContextPtr context;
	xmlXPathObjectPtr result;
	context = xmlXPathNewContext(doc);
	result = xmlXPathEvalExpression((const xmlChar *)"/buildings/residential", context);
	if(xmlXPathNodeSetIsEmpty(result->nodesetval))
	{
		xmlXPathFreeObject(result);
        printf("No result\n");
		return NULL;
	}
	xmlNodeSet* nodeset = result->nodesetval;
	printf("Made it here...\n");
	for (int i=0; i < nodeset->nodeNr; i++) 
	{
		keyword = xmlNodeListGetString(doc, nodeset->nodeTab[i]->xmlChildrenNode, 1);
		printf("keyword: %s\n", keyword);
        xmlFree(keyword);
	}


	printf("hey!\n");
	return 0;
}
