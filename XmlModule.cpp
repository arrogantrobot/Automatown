#include "XmlModule.h"
#include "Structure.h"
XmlModule::XmlModule(const std::string& filename)
{
    file = filename;
}

XmlModule::~XmlModule()
{

}

std::vector<Structure *> * XmlModule::getStructs()
{
    xmlChar *xpath;
    xmlDocPtr doc = xmlParseFile(file.c_str());
    xmlXPathContextPtr context = xmlXPathNewContext(doc);
    char* types[] = {
        "/buildings/residential/*",
        "/buildings/commercial/*",
        "/buildings/industrial/*",
        "/buildings/farm/*",
        "/buildings/road/*",
        "/buildings/misc/*"};

    std::vector<Structure*> * buildings = new std::vector<Structure*>;

    for(int ii=0;ii<6;ii++)
    {
        xpath =(xmlChar *) types[ii];
        xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);

        if(xmlXPathNodeSetIsEmpty(result->nodesetval)){
            printf("No result\n");
        }
        xmlNodeSet *np = result->nodesetval;
        for(int i=0;i<np->nodeNr;i++)
        {
            xmlChar *answer = xmlNodeGetContent(np->nodeTab[i]);
            printf("content=%s\n",answer);
            std::ostringstream a;
            a << answer;
            std::string x1;
            x1 = a.str();
            /*for(int i=0;i<x1.length();i++)
              {
              std::cout << "x1[" << i << "]= " << x1[i] << std::endl;
              }*/
            //printf("x1 = %s\n",x1.c_str());
            //char c[50];
            //a.getline(c,50);
            //printf("\t\tc=%s\n",x1.c_str());
            //Structure *s1;
            //s1 = 
            buildings->push_back(getNums(x1));
            xmlFree(answer);
            //np = np->next;
            /*std::cout << "s1->tileIndex = " << s1->tileIndex << std::endl;
            std::cout << "s1->population = " << s1->population << std::endl;
            std::cout << "s1->jobs = " << s1->jobs << std::endl;
            std::cout << "s1->inDem = " << s1->industrialDemand << std::endl;
            std::cout << "s1->comDem = " << s1->commercialDemand << std::endl;
            std::cout << "s1->resDem = " << s1->residentialDemand << std::endl;
            std::cout << "s1->type = " << s1->type << std::endl;*/
        }
        xmlXPathFreeObject(result);
    }
    xmlFreeDoc(doc);
    xmlXPathFreeContext(context);

    return buildings;
}


Structure * XmlModule::getNums(std::string lines)
{
    Structure *ns = new Structure;
    int index = 0, beginD=0;
    int nums[8];
    for(int i=0;i<8;i++)
    {
        while(!isdigit(lines[index]))
        {
            index++;
        }
        beginD = index;
        while(isdigit(lines[index]))
        {
            index++;
        }
        nums[i] = atoi(lines.substr(beginD,index-beginD).c_str());
    }
    ns->tileIndex = nums[0];
    ns->population = nums[1];
    ns->jobs = nums[2];
    ns->industrialDemand = nums[3];
    ns->commercialDemand = nums[4];
    ns->residentialDemand = nums[5];
    ns->type = nums[6];
    ns->structureNum = nums[7];
    return ns;
}
