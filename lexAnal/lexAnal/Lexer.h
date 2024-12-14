#pragma once
#include "HashTable.h"
#include <fstream>
#include <cctype>

class Lexer {
private:
    std::ifstream inputFile;
    std::ofstream outputFile;


    long long tabs;

    std::string filename;
    std::string filename2;
    HashTable hashTable;
    char currentChar;

    void advance(std::ifstream& inputFile) {
        currentChar = inputFile.get();
    }
public:
    long long getTab() {
        return tabs;
    }

    Token getNextLexem() {
        while (currentChar == '\n') {//		currentChar	10 '\n'	char
            ++tabs;
            advance(inputFile);
        }
        while (isspace(currentChar)) advance(inputFile);
        if (currentChar == '(' || currentChar == ')' || currentChar == '{' || currentChar == '}') {
            std::string bracket;

            bracket += currentChar;
            advance(inputFile);
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("bracket", bracket);
            }

            while (!isspace(currentChar) && currentChar != EOF) { ////////////////////////////////////////
                bracket += currentChar;
                advance(inputFile);
            }
            return Token("unknown", bracket);
        }

        if (currentChar == 'i') {
            std::string id_name;
            id_name += currentChar;
            advance(inputFile);
            if (currentChar == 'n') {
                id_name += currentChar;
                advance(inputFile);
                if (currentChar == 't') {
                    id_name += currentChar;
                    advance(inputFile);
                    if (isspace(currentChar) || currentChar == EOF) {
                        advance(inputFile);
                        return Token("Type", id_name);
                    }
                }
            }
            else if (currentChar == 'f') {
                id_name += currentChar;
                advance(inputFile);
                if (isspace(currentChar) || currentChar == EOF) {
                    advance(inputFile);
                    return Token("Cond", id_name);
                }
            }

            while (isalpha(currentChar) && currentChar != EOF) {
                id_name += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("id_name", id_name);
            }
            
            while (!isspace(currentChar) && currentChar != EOF) {
                id_name += currentChar;
                advance(inputFile);
            }
            return Token("unknown", id_name);
        }

        if (currentChar == '=') {
            std::string relop;
            relop += currentChar;
            advance(inputFile);
            
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }

            if (currentChar == '=') {
                relop += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }
            while (!isspace(currentChar) && currentChar != EOF) {
                relop += currentChar;
                advance(inputFile);
            }
            return Token("unknown", relop);
        }

        if (currentChar == '!') {
            std::string relop;
            relop += currentChar;
            advance(inputFile);

            if (isspace(currentChar) || currentChar == EOF) {
                return Token("unknown", relop);
            }

            if (currentChar == '=') {
                relop += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }
            while (!isspace(currentChar) && currentChar != EOF) {
                relop += currentChar;
                advance(inputFile);
            }
            return Token("unknown", relop);
        }

        if (currentChar == '>') {
            std::string relop;
            relop += currentChar;
            advance(inputFile);

            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }

            if (currentChar == '=') {
                relop += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }
            while (!isspace(currentChar) && currentChar != EOF) {
                relop += currentChar;
                advance(inputFile);
            }
            return Token("unknown", relop);
        }

        if (currentChar == '<') {
            std::string relop;
            relop += currentChar;
            advance(inputFile);

            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }

            if (currentChar == '=') {
                relop += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("RelOper", relop);
            }
            while (!isspace(currentChar) && currentChar != EOF) {
                relop += currentChar;
                advance(inputFile);
            }
            return Token("unknown", relop);
        }

        if (currentChar == 'e') {
            std::string id_name;
            id_name += currentChar;
            advance(inputFile);

            if (currentChar == 'l') {
                id_name += currentChar;
                advance(inputFile);
                if (currentChar == 's') {
                    id_name += currentChar;
                    advance(inputFile);
                    if (currentChar == 'e') {
                        id_name += currentChar;
                        advance(inputFile);
                        if (isspace(currentChar) || currentChar == EOF) {
                            advance(inputFile);
                            return Token("Cond", id_name);
                        }
                    }
                }
            }

            while (isalpha(currentChar) && currentChar != EOF) {
                id_name += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("id_name", id_name);
            }

            while (!isspace(currentChar) && currentChar != EOF) {
                id_name += currentChar;
                advance(inputFile);
            }
            return Token("unknown", id_name);
        }

        if (currentChar == ';' || currentChar == ',') {
            std::string str;
            str += currentChar;
            advance(inputFile);

            if (isspace(currentChar) || currentChar == EOF) {
                return Token("Comma", str);
            }
            
            while (!isspace(currentChar) && currentChar != EOF) {
                str += currentChar;
                advance(inputFile);
            }
            return Token("unknown", str);
        }

        if (currentChar == '+' || currentChar == '-') {
            std::string str;
            str += currentChar;
            advance(inputFile);

            if (isspace(currentChar) || currentChar == EOF) {
                return Token("Sign", str);
            }

            while (!isspace(currentChar) && currentChar != EOF) {
                str += currentChar;
                advance(inputFile);
            }
            return Token("unknown", str);
        }

        if (isalpha(currentChar)) {
            std::string id_name;
            while (isalpha(currentChar)) {
                id_name += currentChar;
                advance(inputFile);
            }
            if (!isalpha(currentChar) && !isspace(currentChar) && currentChar != EOF) {
                while (!isspace(currentChar) && currentChar != EOF) {
                    id_name += currentChar;
                    advance(inputFile);
                }
                return Token("unknown", id_name);
            }

            return Token("id_name", id_name);
        }

        if (isdigit(currentChar)) {
            std::string int_num;
            while (isdigit(currentChar)) {
                int_num += currentChar;
                advance(inputFile);
            }
            if (!isdigit(currentChar) && !isspace(currentChar) && currentChar != EOF) {
                while (!isspace(currentChar) && currentChar != EOF) {
                    int_num += currentChar;
                    advance(inputFile);
                }
                return Token("unknown", int_num);
            }

            return Token("Const", int_num);
        }

        if (currentChar == 'r') {
            std::string id_name;
            id_name += currentChar;
            advance(inputFile);
            if (currentChar == 'e') {
                id_name += currentChar;
                advance(inputFile);
                if (currentChar == 't') {
                    id_name += currentChar;
                    advance(inputFile);
                    if (currentChar == 'u') {
                        id_name += currentChar;
                        advance(inputFile);
                        if (currentChar == 'r') {
                            id_name += currentChar;
                            advance(inputFile);
                            if (currentChar == 'n') {
                                id_name += currentChar;
                                advance(inputFile);
                                if (isspace(currentChar) || currentChar == EOF) {
                                    advance(inputFile);
                                    return Token("Key", id_name);
                                }
                            }
                        }
                    }
                }
            }

            while (isalpha(currentChar) && currentChar != EOF) {
                id_name += currentChar;
                advance(inputFile);
            }
            if (isspace(currentChar) || currentChar == EOF) {
                return Token("id_name", id_name);
            }

            while (!isspace(currentChar) && currentChar != EOF) {
                id_name += currentChar;
                advance(inputFile);
            }
            return Token("unknown", id_name);
        }


        if (currentChar == EOF) {
            return Token("EOF", "EOF");
        }
        std::string unknown = "";
        while (!isspace(currentChar) && currentChar != EOF) {
            unknown += currentChar;
            advance(inputFile);
        }
        return Token("unknown", unknown);
        
    }

    void advance() {
        currentChar = inputFile.get();
    }

    Lexer(const std::string& f="", const std::string& f2 = "") {
        filename = f;
        filename2 = f2;

        tabs = 1;

        if (filename != "") {
            inputFile.open(filename);
            outputFile.open(filename2);
        }
    }


    void set(const std::string& f, const std::string& f2)
    {
        filename = f;
        filename2 = f2;

        if (filename != "") {
            inputFile.open(filename);
            outputFile.open(filename2);
        }
    }

    void analyze() {
        
        advance(inputFile);

        Token token;

        while (currentChar != EOF) {
            token = getNextLexem();
            if (token.type == "unknown") {
                outputFile << "Error: Unrecognized token, ";
                outputFile << token.lexem;
                outputFile << '\n';
            }
            else if (token.type != "EOF") {
                hashTable.insert(token);
            }
            else
                break;
        }
        


        outputFile.close();
        inputFile.close();
    }

    void printTokens(const std::string& filename) {
        hashTable.print(filename);
    }
};
