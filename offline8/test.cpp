#include <iostream>
#include "HashTable.h"
using namespace std;

string techniques[] = {"Seperate", "chaining", "Linear", "Probing", "Quadratic", "Double", "Hashing"};

int main()
{
    DoubleHash hl(17);
    for (int i = 0; i < 7; i++)
    {
        hl.insert(techniques[0], i + 1);
    }

    for (int i = 0; i < 7; i++)
    {
        cout << hl.search(techniques[0]) << ' ';
        hl.deleteElement("Seperate");
    }
}