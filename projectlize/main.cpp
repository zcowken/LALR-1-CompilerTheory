#include <iostream>
#include "myalgor.h"

using namespace std;

void testWithA() {
    algor alg;
    alg.process("../matchTestFiles/match(A)_prod.txt",
                "../matchTestFiles/match(A)_content.txt");
}

void testWith_A_Re() {
    algor alg;
    alg.process("../matchTestFiles/matchRe(A)_prod.txt",
                "../matchTestFiles/matchRe(A)_cont.txt");
}


void testWith_tiny() {
    algor alg;
    alg.process("../matchTestFiles/tiny_prod.txt",
                "../matchTestFiles/tiny_cont.txt");
}

void testWith_tiny_re() {
    algor alg;
    alg.process("../matchTestFiles/tinyRe_prod.txt",
                "../matchTestFiles/tinyRe_cont.txt");
}



void testWith_temp() {
    algor alg;
    alg.process("../file.txt",
                "../match.txt");
}


int main(int argc, char const *argv[]) {
//    testWith_temp();
    testWith_tiny_re();
    return 0;
}