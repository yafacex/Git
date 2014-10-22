#include <iostream>
#include <string>
#include <spirit/Spirit.h>

/////////////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::cin;
using std::endl;
using std::string;

using Spirit::Rule;
using Spirit::Scanner;
using Spirit::Action;
using Spirit::Lexeme;
using Spirit::ch_p;
using Spirit::digit;
using Spirit::space;

namespace {

	void	doInt(char const* str, char const* end)
	{
		string	s(str, end);
		cout << s << endl;
	}

	void	doAdd(char const*, char const*) 	{ cout << "ADD\n"; }
	void	doSubt(char const*, char const*) 	{ cout << "SUBT\n"; }
	void	doMult(char const*, char const*) 	{ cout << "MULT\n"; }
	void	doDiv(char const*, char const*) 	{ cout << "DIV\n"; }
}

/////////////////////////////////////////////////////////////////////////////////////////
static void
Parse(Rule<> const& rule, char const* expr)
{
	cout << "/////////////////////////////////////////////////////////\n\n";

	Scanner<>	scan(expr, space);
	if (rule.Parse(scan) && !*scan)
	{
		cout << "\t\t" << expr << " Parses OK\n\n\n";
	}
	else
	{
		cout << "\t\t" << expr << " Fails Parsing\n";
		cout << "\t\t";
		for (int i = 0; i < (&*scan - expr); i++)
			cout << " ";
		cout << "^--Here\n\n\n";
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
int
main()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tInterpreter Test For Spirit...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";

	//	Start grammar definition

	Rule<>	expr;
	Rule<>	integer	= Lexeme[ (!(ch_p('+') | '-') >> +digit)[&doInt] ];
	Rule<>	group 	= '(' >> expr >> ')';
	Rule<>	expr1 	= integer | group;
	Rule<>	expr2 	= expr1 >> *(('*' >> expr1)[&doMult] | ('/' >> expr1)[&doDiv]);
	expr 			= expr2 >> *(('+' >> expr2)[&doAdd] | ('-' >> expr2)[&doSubt]);

	//	End grammar definition

	cout << "=================================================\n";
	cout << "The following expressions should fail to parse...\n";
	cout << "=================================================\n\n";
	Parse(expr, "- ");
	Parse(expr, "1 2 3 4 5");
	Parse(expr, "- 1234");
	Parse(expr, "1 ++ 1");
	Parse(expr, "1 ^ 1");
	Parse(expr, "(1 + 1) * 3)");
	Parse(expr, "(1 + 1) * 3 4");
	Parse(expr, "(1 + (2 + (3 + (4 + 5)))");
	Parse(expr, ")1 + 1)");

	cout << "=================================================\n";
	cout << "The following expressions should parse OK...\n";
	cout << "=================================================\n\n";
	Parse(expr, "12345");
	Parse(expr, "-12345");
	Parse(expr, "+12345");
	Parse(expr, "1 + 2");
	Parse(expr, "1 * 2");
	Parse(expr, "1/2 + 3/4");
	Parse(expr, "1 + 2 + 3 + 4");
	Parse(expr, "1 * 2 * 3 * 4");
	Parse(expr, "(1 + 2) * (3 + 4)");
	Parse(expr, "(-1 + 2) * (3 + -4)");
	Parse(expr, "1 + ((6 * 200) - 20) / 6");
	Parse(expr, "(1 + (2 + (3 + (4 + 5))))");

	return 0;
}


