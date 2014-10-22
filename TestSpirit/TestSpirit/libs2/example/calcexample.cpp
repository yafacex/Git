#include <spirit/Spirit.h>
#include <iostream>
#include <stack>
#include <functional>

////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stack;

using Spirit::Rule;
using Spirit::Scanner;
using Spirit::Action;
using Spirit::Lexeme;
using Spirit::ch_p;
using Spirit::digit;
using Spirit::space;

stack<long>	evaluation_stack;

////////////////////////////////////////////////////////////////////////////
struct Integer {

	void operator()(char const* str, char const* /*end*/) const
	{
		long n = std::strtol(str, nil, 10);
		evaluation_stack.push(n);
		cout << "push\t" << long(n) << endl;
	}
	
};

template <class op>
struct doOp
{
	doOp(op const& theOp) : m_op(theOp) {}
	op m_op;

	void operator()(char const*, char const*) const
	{
		long rhs = evaluation_stack.top();
		evaluation_stack.pop();
		long lhs = evaluation_stack.top();
		evaluation_stack.pop();

		cout << "popped " << lhs << " and " << rhs << " from the stack. ";
		cout << "pushing " << m_op(lhs, rhs) << " onto the stack.\n";
		evaluation_stack.push(m_op(lhs, rhs));
	}
};

template <class op>
doOp<op> makeDoOp(op const& theOp)
{
	return doOp<op>(theOp);
}

struct doNegate
{
	void operator()(char const*, char const*) const
	{
		long lhs = evaluation_stack.top();
		evaluation_stack.pop();

		cout << "popped " << lhs << " from the stack. ";
		cout << "pushing " << -lhs << " onto the stack.\n";
		evaluation_stack.push(-lhs);
	}
};

////////////////////////////////////////////////////////////////////////////
int
main()
{
	//	Start grammar definition

	/* calc2.cpp way...
	Rule<>	expr, integer, group, expr1, expr2;

	integer	= Lexeme[ (!(ch_p('+') | '-') >> +digit)[Integer()] ];
	group 	= '(' >> expr >> ')';
	expr1 	= integer | group;
	expr2 	= expr1 >> *(('*' >> expr1)[makeDoOp(std::multiplies<long>())] 
								| ('/' >> expr1)[makeDoOp(std::divides<long>())]);
	expr		= expr2 >> *(('+' >> expr2)[makeDoOp(std::plus<long>())] 
								| ('-' >> expr2)[makeDoOp(std::minus<long>())]);
	*/

	/* ebnf grammar:
	 * <expression> ::= <term> ( ( '+' | '-' ) <term> )*
	 * <term> ::= <factor> ( ( '*' | '/' ) <factor> )*
	 * <factor> ::= <integer> | '-' <factor> | '(' <expression> ')'
	 */

	/* simplest grammar
	Rule<> expression, term, factor, integer;
	
	integer		= Lexeme[ (!ch_p('-') >> +digit) ];
	factor		= 	integer
						| '(' >> expression >> ')'
						| '-' >> factor;
	term			=	factor >> *( (ch_p('*') | '/') >> factor);
	expression	=	term >> *( (ch_p('+') | '-') >> term);
	*/

	Rule<> expression, term, factor, integer;
	
	integer		= Lexeme[ (!ch_p('-') >> +digit)[Integer()] ];
	factor		= 	integer
						| '(' >> expression >> ')'
						| ('-' >> factor)[doNegate()];
	term		= factor >> *( ('*' >> factor)[makeDoOp(std::multiplies<long>())]
									|('/' >> factor)[makeDoOp(std::divides<long>())]);
	expression	=term >> *( ('+' >> term)[makeDoOp(std::plus<long>())] 
									|('-' >> term)[makeDoOp(std::minus<long>())]);


	//	End grammar definition

	char str[256];
	cin.getline(str, 256);
	Scanner<> scan(str, space);
	if (expression.Parse(scan) && !*scan)
	{
		cout << "parsing succeeded\n";
		cout << "result = " << evaluation_stack.top() << "\n\n";
		evaluation_stack.pop();
	}
	else
	{
		cout << "parsing failed\n";
	}
}


