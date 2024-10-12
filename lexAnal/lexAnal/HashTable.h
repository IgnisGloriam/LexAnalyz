#include "Token.h"
#include <iostream>
#include <fstream>
#include <string>



int hashToken(const Token& token, int capacity) {
    int hashValue = 0;

    for (char ch : token.lexem) {
        hashValue = (hashValue * 31 + ch) % capacity;
    }

    return hashValue;
}


class HashTable {
private:
    Token* table;
    int capacity;
    int size;


    void rehash() {
        int oldCapacity = capacity;
        capacity *= 2;
        Token* newTable = new Token[capacity];



        for (int i = 0; i < oldCapacity; ++i) {
            if (!table[i].type.empty()) {
                int newIndex = hashToken(table[i], capacity);
                while (!newTable[newIndex].type.empty()) {
                    newIndex = (newIndex + 1) % capacity;
                }
                newTable[newIndex] = table[i];
            }
        }

        delete[] table;
        table = newTable;
    }

public:
    HashTable(int initialCapacity = 4) : capacity(initialCapacity), size(0) {
        table = new Token[capacity];
    }

    ~HashTable() {
        delete[] table;
    }


    void insert(const Token& token) {
        if (size * 2 >= capacity) {
            rehash();
        }

        int index = hashToken(token, capacity);

        while (!table[index].type.empty()) {
            if (table[index] == token) {
                return;
            }
            index = (index + 1) % capacity;
        }

        table[index] = token;
        size++;
        return;
    }

    bool search(const Token& token) const {
        int index = hashToken(token, capacity);

        for (int i = 0; i < capacity; ++i) {
            if (table[index] == token) {
                return true;
            }
            if (table[index].type.empty()) {
                return false;
            }
            index = (index + 1) % capacity;
        }
        return false;
    }

    void remove(const Token& token) {
        int index = hashToken(token, capacity);


        for (int i = 0; i < capacity; ++i) {
            if (table[index] == token) {
                table[index] = Token();
                size--;
                return;
            }
            if (table[index].type.empty()) {
                return;
            }
            index = (index + 1) % capacity;
        }
    }


    void print(const std::string& filename) const {
        std::ofstream outputFile(filename, std::ios_base::in | std::ios_base::app);
        for (int i = 0; i < capacity; ++i) {
            if (!table[i].type.empty()) {
                outputFile << i << ":  " << table[i].type << ", " << table[i].lexem << '\n';
            }
        }
    }
};
