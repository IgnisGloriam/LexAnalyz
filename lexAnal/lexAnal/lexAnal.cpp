#include "Lexer.h"

int main() {
    Lexer lexer("input.txt", "output.txt");
    lexer.analyze();
    lexer.printTokens("output.txt");
    return 0;
}