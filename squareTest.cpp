#include "Square.h"
#include "Structure.h"
#include <iostream>
using namespace std;

int main()
{
    Square *ptr;
    Structure s;
    s.tileIndex = 4;
    ptr = new Square(1,0,s);
    ptr->setLand(2);
    cout << ptr->getLand() << endl;
    cout << "tileIndex = "<< ptr->getStructure()->tileIndex << endl;
    return 0;
}


