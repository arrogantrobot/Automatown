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
        (char *) "/buildings/residential/*",
        (char *) "/buildings/commercial/*",
        (char *) "/buildings/industrial/*",
        (char *) "/buildings/farm/*",
        (char *) "/buildings/road/*",
        (char *) "/buildings/misc/*"};

    std::vector<Structure*> * buildings = new std::vector<Structure*>;

    for(int ii=0;ii<6;ii++)
    {
        xpath =(xmlChar *) types[ii];
        xmlXPathObjectPtr result = xmlXPathEvalExpression(xpath, context);
        xmlNodeSet *np = result->nodesetval;
        for(int i=0;i<np->nodeNr;i++)
        {
            xmlChar *answer = xmlNodeGetContent(np->nodeTab[i]);
            std::ostringstream a;
            a << answer;
            std::string x1;
            x1 = a.str();
            buildings->push_back(getNums(x1));
            xmlFree(answer);
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
