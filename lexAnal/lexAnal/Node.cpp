#include "Node.h"

Node::Node(string s)
{
	data = s;
}

void Node::addSon(string s)
{
	Node n(s);
	children.push_back(n);
}

Node& Node::getSon(int i)
{
	return children[i];
}

void Node::print(int lvl, std::ofstream& outputFile)
{
	for (int i = 0; i < lvl; ++i)
		outputFile << "  ";
	outputFile << data << endl;
	for (Node n : children)
		n.print(lvl + 1, outputFile);
}


