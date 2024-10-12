#pragma once
#include <string>


struct Token {
    std::string type;
    std::string lexem;

    Token() : type(""), lexem("") {}
    Token(std::string n, std::string w) : type(n), lexem(w) {}


    bool operator==(const Token& other) const {
        return type == other.type && lexem == other.lexem;
    }

    Token& operator=(const Token& other) {
        type = other.type;
        lexem = other.lexem;
        return *this;
    }
};
