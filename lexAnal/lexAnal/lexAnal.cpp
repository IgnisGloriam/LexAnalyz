#include "Parser.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;




int main() {
    Parser p("input.txt", "output.txt");
    Node root = p.parse();

    
    std::ofstream outputFile;
    outputFile.open("output.txt");

    root.print(0, outputFile);
    return 0;
}
