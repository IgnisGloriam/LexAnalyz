#pragma once
#include "Lexer.h"
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;
class Parser
{
private:
	Token lexeme;
	Lexer lexer;
	void getLexeme();

	void error(Token l, string s);

	void Function(Node& n);
	void Begin(Node& n);
	void Descriptions(Node& n);
	void Operators(Node& n);
	void Op(Node& n);
	void Operators1(Node& n);
	void Condition(Node& n);
	void End(Node& n);
	void Type(Node& n);
	void FunctionName(Node& n);
	void Descr(Node& n);
	void Descriptions1(Node& n);
	void Varlist(Node& n);
	void Varlist1(Node& n);
	void Expr(Node& n);
	void Expr1(Node& n);
	void SimpleExpr(Node& n);
	void Id(Node& n);
	void Const(Node& n);
	void RelationOperations(Node& n);

public:
	Parser(const std::string& filename, const std::string& filename2);
	Node parse();

};

