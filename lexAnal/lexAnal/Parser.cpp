#include "Parser.h"


void Parser::getLexeme()
{
	lexeme = lexer.getNextLexem();
}

void Parser::error(Token l, string s)
{
	cout << "Error at " << lexer.getTab() << " line\n";
	cout << "Expected : " << s << " \n";
	cout << "Received : " << l.type << ' ' << l.lexem << "   - lexeme\n";

	

	fout << "Error at " << lexer.getTab() << " line\n";
	fout << "Expected : " << s << " \n";
	fout << "Received : " << l.type << ' ' << l.lexem << "   - lexeme\n";

	exit(0);
}

void Parser::unierror(string s)
{
	//std::ofstream fout;
	//fout.open(out);
	cout << s;
	fout << s;

	//exit(0);
}

void Parser::Function(Node& n)
{
	if (lexeme.type == "Type"){
		n.addSon("Begin");
		Begin(n.getSon(0));
		n.trace += n.getSon(0).trace + '\n';


		n.addSon("Descriptions");
		Descriptions(n.getSon(1));
		n.trace += n.getSon(1).trace + '\n';

		def = 0;
		n.addSon("Operators");
		Operators(n.getSon(2));
		n.trace += n.getSon(2).trace + '\n';

		//cout << n.trace;

		n.addSon("End");
		End(n.getSon(3));
		n.trace += n.getSon(3).trace;

		cout << n.trace;
		fout << n.trace;
	}
	else {
		error(lexeme, "Type");
	}
}

void Parser::Begin(Node& n)
{
	if (lexeme.type == "Type"){
		n.addSon("Type");
		Type(n.getSon(0));
		n.addSon("FunctionName");
		FunctionName(n.getSon(1));

		n.trace = n.getSon(0).trace + ' ' + n.getSon(1).trace + " DECL ";

		if (lexeme.lexem == "(")
		{
			n.addSon("(");
			getLexeme();
			if (lexeme.lexem == ")")
			{
				n.addSon(")");
				getLexeme();
				if (lexeme.lexem == "{")
				{
					n.addSon("{");
					getLexeme();
				}
				else {
					error(lexeme, "{");
				}
			}
			else {
				error(lexeme, ")");
			}
		}
		else {
			error(lexeme, "(");
		}
	}
	else {
		error(lexeme, "Type");
	}
}

void Parser::Descriptions(Node& n)
{
	if (lexeme.type == "Type") {
		n.addSon("Descr");
		Descr(n.getSon(0));
		n.addSon("Descriptions1");
		Descriptions1(n.getSon(1));

		n.trace = n.getSon(0).trace + ' ';
		n.trace += n.getSon(1).trace;

	}
	else {
		error(lexeme, "Type");
	}
}

void Parser::Operators(Node& n)
{
	if (lexeme.lexem == "if" || lexeme.type == "id_name") {
		n.addSon("Op");
		Op(n.getSon(0));
		n.addSon("Operators1");
		Operators1(n.getSon(1));

		
		n.trace = n.getSon(0).trace + ' ';
		n.trace += n.getSon(1).trace;
		
	}
	else error(lexeme, "if or id_name");
}

void Parser::Op(Node& n)
{
	if (lexeme.lexem == "if") { // Op -> if ( Condition ) { Operators } else { Operators }
		n.addSon(lexeme.lexem);
		getLexeme();

		if (lexeme.lexem == "(")
		{
			n.addSon("(");
			getLexeme();

			n.addSon("Condition");
			Condition(n.getSon(2));

			if (lexeme.lexem == ")")
			{
				n.addSon(")");
				getLexeme();

				if (lexeme.lexem == "{")
				{
					n.addSon("{");
					getLexeme();

					n.addSon("Operators");
					Operators(n.getSon(5));

					if (lexeme.lexem == "}")
					{
						n.addSon("}");
						getLexeme();

						if (lexeme.lexem == "else")
						{
							n.addSon("else");
							getLexeme();

							if (lexeme.lexem == "{")
							{
								n.addSon("{");
								getLexeme();

								n.addSon("Operators");
								Operators(n.getSon(9));

								if (lexeme.lexem == "}")
								{
									n.addSon("}");
									getLexeme();
								}
								else error(lexeme, "}");
							}
							else error(lexeme, "{");
						}
						else error(lexeme, "else");
					}
					else error(lexeme, "}");
				}
				else error(lexeme, "{");
			}
			else error(lexeme, ")");
		}
		else error(lexeme, "(");

		mglobal += 2;
		int mlocal = mglobal;
		n.trace += n.getSon(2).trace + ' ' + 'm' + to_string(mlocal-1) + " BF " + n.getSon(5).trace + ' ' + 'm' + to_string(mlocal) + " BRL " + 'm' + to_string(mlocal - 1) + " DEFL ";
		n.trace += n.getSon(9).trace + ' ' + 'm' + to_string(mlocal) + " DEFL ";


	}
	else if (lexeme.type == "id_name") {
		n.addSon("Id");
		Id(n.getSon(0));
		if (lexeme.lexem == "=")
		{
			n.addSon("=");
			getLexeme();

			n.addSon("Expr");
			Expr(n.getSon(2));

			if (lexeme.lexem == ";")
			{
				n.addSon(";");
				getLexeme();
			}
			else error(lexeme, ";");
		}
		else error(lexeme, "=");


		n.trace += n.getSon(0).trace + ' ';
		n.trace += n.getSon(2).trace;
		n.trace += '=';
	}
	else error(lexeme, "if or id_name");
}

void Parser::Operators1(Node& n)
{
	if (lexeme.lexem == "}" || lexeme.lexem == "return") {
		n.addSon("eps");
		//getLexeme();
	}
	else if (lexeme.type == "id_name" || lexeme.lexem == "if") {
		n.addSon("Operators");
		Operators(n.getSon(0));

		n.trace += n.getSon(0).trace;
	}
	else error(lexeme, "if or id_name or } or return");
}

void Parser::Condition(Node& n)
{
	if (lexeme.lexem == "(" || lexeme.type == "id_name" || lexeme.type == "Const") {
		n.addSon("Expr");
		Expr(n.getSon(0));

		n.addSon("RelationOperations");
		RelationOperations(n.getSon(1));

		n.addSon("Expr");
		Expr(n.getSon(2));


		n.trace += n.getSon(0).trace;
		n.trace += n.getSon(2).trace;
		n.trace += n.getSon(1).trace;
	}
	else error(lexeme, "( or id_name or Const");
}

void Parser::End(Node& n)
{
	if (lexeme.lexem == "return") {
		n.addSon("return");
		getLexeme();

		n.addSon("Id");
		Id(n.getSon(1));

		n.trace += n.getSon(1).trace + ' ' + "return";

		if (lexeme.lexem == ";")
		{
			n.addSon(";");
			getLexeme();

			if (lexeme.lexem == "}")
			{
				n.addSon("}");
				getLexeme();
			}
			else error(lexeme, "}");
		}
		else error(lexeme, ";");

	}
	else error(lexeme, "return");
}

void Parser::Type(Node& n)
{
	if (lexeme.type == "Type") {
		n.addSon(lexeme.lexem);
		n.trace = lexeme.lexem;

		getLexeme();
	}
	else error(lexeme, "Type");
}

void Parser::FunctionName(Node& n)
{
	if (lexeme.type == "id_name") {
		n.addSon(lexeme.lexem);
		n.trace = lexeme.lexem;


		getLexeme();

		
	}
	else error(lexeme, "id_name");
}

void Parser::Descr(Node& n)
{
	if (lexeme.type == "Type") {
		n.addSon("Type");
		Type(n.getSon(0));
		n.addSon("Varlist");
		Varlist(n.getSon(1));


		n.trace += n.getSon(0).trace + ' ' + n.getSon(1).trace;
		if (n.getSon(1).depth > 1) n.trace += to_string(n.getSon(1).depth + 1) + ' ';
		n.trace += "DECL";


		if (lexeme.lexem == ";")
		{
			n.addSon(";");
			getLexeme();
		}
		else error(lexeme, ";");

	}
	else error(lexeme, "Type");
}

void Parser::Descriptions1(Node& n)
{
	if (lexeme.type == "Type") {
		n.addSon("Descriptions");
		Descriptions(n.getSon(0));

		n.trace += n.getSon(0).trace;
	}
	else if (lexeme.lexem == "if" || lexeme.type == "id_name") {
		n.addSon("eps");
	}
	else error(lexeme, "Type or if or id_name");
}

void Parser::Varlist(Node& n)
{
	if (lexeme.type == "id_name") {
		n.depth++;

		n.addSon("Id");
		Id(n.getSon(0));
		n.addSon("Varlist1");
		Varlist1(n.getSon(1));

		n.depth += n.getSon(1).depth;
		n.trace += n.getSon(0).trace + ' ' + n.getSon(1).trace;
		
	}
	else error(lexeme, "id_name");
}

void Parser::Varlist1(Node& n)
{
	if (lexeme.lexem == ";")
	{
		n.addSon("eps");
		//getLexeme();
	}

	else if (lexeme.lexem == ",") {
		n.addSon(",");
		getLexeme();
		
		n.addSon("Varlist");
		Varlist(n.getSon(1));

		n.depth += n.getSon(1).depth;
		n.trace += n.getSon(1).trace;
	}
	else error(lexeme, "; or ,");
}

void Parser::Expr(Node& n)
{
	if (lexeme.lexem == "(" || lexeme.type == "id_name" || lexeme.type == "Const")
	{
		n.addSon("SimpleExpr");
		SimpleExpr(n.getSon(0));

		n.addSon("Expr1");
		Expr1(n.getSon(1));

		n.trace += n.getSon(0).trace + ' ' + n.getSon(1).trace;
	}
	else error(lexeme, "( or id_name or Const");
}

void Parser::Expr1(Node& n)
{
	if (lexeme.lexem == ";" || lexeme.type == "RelOper" || lexeme.lexem == ")")
	{
		n.addSon("eps");
		//getLexeme();
	}
	else if (lexeme.type == "Sign") {
		n.addSon(lexeme.lexem);
		getLexeme();

		n.addSon("Expr");
		Expr(n.getSon(1));

		n.trace += n.getSon(1).trace + '+';
	}
	else error(lexeme, "; or Relation Operator or )");
}

void Parser::SimpleExpr(Node& n)
{
	if (lexeme.lexem == "(") {
		n.addSon(lexeme.lexem);
		getLexeme();

		n.addSon("Expr");
		Expr(n.getSon(1));

		n.trace += n.getSon(1).trace;

		if (lexeme.lexem == ")") {
			n.addSon(lexeme.lexem);
			getLexeme();
		}
		else error(lexeme, ")");
	}
	else if (lexeme.type == "id_name") {
		n.addSon("Id");
		Id(n.getSon(0));

		n.trace += n.getSon(0).trace;
	}
	else if (lexeme.type == "Const") {
		n.addSon("Const");
		Const(n.getSon(0));

		n.trace += n.getSon(0).trace;
	}
	else error(lexeme, "( or id_name or Const");
}

void Parser::Id(Node& n)
{
	if (lexeme.type == "id_name") {
		n.addSon(lexeme.lexem);
		n.trace = lexeme.lexem;


		if (def) {
			if (lexer.search(lexeme)) {
				unierror("The variable " + lexeme.lexem + " has already been declared\n");
			}
			else {
				lexer.insert(lexeme);
			}
		}
		else {
			if (!lexer.search(lexeme)) {
				unierror("The variable " + lexeme.lexem + " hasn't been declared\n");
			}
		}

		getLexeme();

		
	}
	else error(lexeme, "id_name");
}

void Parser::Const(Node& n)
{
	if (lexeme.type == "Const") {
		n.addSon(lexeme.lexem);
		n.trace = lexeme.lexem;


		getLexeme();
	}
	else error(lexeme, "Const");
}

void Parser::RelationOperations(Node& n)
{
	if (lexeme.type == "RelOper") {
		n.addSon(lexeme.lexem);
		n.trace = lexeme.lexem;

		getLexeme();

		
	}
	else error(lexeme, "Relation Operator");
}


Parser::Parser(const std::string& filename, const std::string& filename2) {
	lexer.set(filename, filename2);
	in = filename;
	out = filename2;

	fout.open(out);
}

Node Parser::parse()
{
	Node root("Function");

	lexer.advance();

	getLexeme();
	Function(root);

	
	return root;
}
