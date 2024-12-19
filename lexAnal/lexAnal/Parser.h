#pragma once
#include "Lexer.h"
#include "Node.h"
#include <iostream>
#include <string>
using namespace std;
class Parser
{
private:
	bool def = 1;
	int mglobal = 0;



	string in;
	string out;


	Token lexeme;
	Lexer lexer;
	void getLexeme();

	void error(Token l, string s);
	void unierror(string s);


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

// 1. Все используемые во входном файле переменные должны быть объявлены, причем повторное объявление переменной не допускается.
// 
//
// 
// 9. Все обнаруженные ошибки должны быть указаны в выходном файле.
// 
// 10. В выходной файл записываем полный перевод исходного текста в его постфиксную запись.
