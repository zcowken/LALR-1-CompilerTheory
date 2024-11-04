#if !defined(MY_ALGOR_H)
#define MY_ALGOR_H

#include <iostream>

using namespace std;

#include <string>

#include "lalr.h"
#include "production.h"

class algor {
public:
    void process(string fileName, string matchFilePath = "../match.txt");

    // ProductionUtil ProductionUtil1;
    LALR lalrUtil1;
};

#endif // MY_ALGOR_H
