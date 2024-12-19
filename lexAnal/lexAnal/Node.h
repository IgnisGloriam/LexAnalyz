#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;
class Node
{
private:
	string data;
	vector<Node> children;
	
public:
	string trace;
	int depth = 0;
	Node(string s);
	void addSon(string s);
	Node& getSon(int i);
	void print(int lvl, std::ofstream& outputFile);
	
};

