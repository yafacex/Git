#include <spirit/Spirit.h>
#include <iostream>
#include <vector>
#include <cstdlib>

/////////////////////////////////////////////////////////////////////////////////////////
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

using Spirit::Rule;
using Spirit::Scanner;
using Spirit::Action;
using Spirit::Lexeme;
using Spirit::ch_p;
using Spirit::digit;
using Spirit::space;

/////////////////////////////////////////////////////////////////////////////////////////
//
//	The VMachine
//
/////////////////////////////////////////////////////////////////////////////////////////
enum ByteCodes {

	OP_ADD,		//	add top two stack entries
	OP_SUB,		//	subtract top two stack entries
	OP_MUL,		//	multiply top two stack entries
	OP_DIV,		//	divide top two stack entries
	OP_INT,		//	push constant integer into the stack
	OP_RET, 	//	return from the interpreter
};

/////////////////////////////////////////////////////////////////////////////////////////
class VMachine {

public:
				VMachine(unsigned stackSize = 1024)
				:	stack(new int[stackSize]),
					stackPtr(stack) {}
				~VMachine() { delete [] stack; }
	int			Top() const { return stackPtr[-1]; };
	void		Execute(unsigned code[]);

private:

	int*		stack;
	int*		stackPtr;
};

/////////////////////////////////////////////////////////////////////////////////////////
void
VMachine::Execute(unsigned code[])
{
	unsigned const*	pc = code;
	bool			running = true;
	
	while (running) {

		switch (*pc++) {
		
			case OP_ADD:
				stackPtr--;
				stackPtr[-1] += stackPtr[0];
				break;
				
			case OP_SUB:
				stackPtr--;
				stackPtr[-1] -= stackPtr[0];
				break;
				
			case OP_MUL:
				stackPtr--;
				stackPtr[-1] *= stackPtr[0];
				break;
				
			case OP_DIV:
				stackPtr--;
				stackPtr[-1] /= stackPtr[0];
				break;
				
			case OP_INT:
				//	Check stack overflow here
				*stackPtr++ = *pc++;
				break;

			case OP_RET:
				running = false;
				break;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
//
//	The Compiler
//
/////////////////////////////////////////////////////////////////////////////////////////
vector<unsigned>	code;

/////////////////////////////////////////////////////////////////////////////////////////
struct Integer {

	void operator()(char const* str, char const* /*end*/) const
	{
		unsigned	n = std::strtol(str, nil, 10);
		code.push_back(OP_INT);
		code.push_back(n);
		cout << "push\t" << int(n) << endl;
	}
	
};

/////////////////////////////////////////////////////////////////////////////////////////
struct PushOp {

	PushOp(unsigned op_)
	: op(op_) {}

	void operator()(char const*, char const*) const
	{
		code.push_back(op);

		switch (op) {
		
			case OP_ADD:
				cout << "add\n";
				break;
				
			case OP_SUB:
				cout << "sub\n";
				break;
				
			case OP_MUL:
				cout << "mul\n";
				break;
				
			case OP_DIV:
				cout << "div\n";
				break;
		}		
	}
	
	unsigned op;
};

/////////////////////////////////////////////////////////////////////////////////////////
static bool
Compile(Rule<> const& rule, char const* expr)
{
	cout << "\n/////////////////////////////////////////////////////////\n\n";

	Scanner<>	scan(expr, space);
	if (rule.Parse(scan) && !*scan)
	{
		cout << "\t\t" << expr << " Parses OK\n\n\n";
		code.push_back(OP_RET);
		return true;
	}
	else
	{
		cout << "\t\t" << expr << " Fails Parsing\n";
		cout << "\t\t";
		for (int i = 0; i < (&*scan - expr); i++)
			cout << " ";
		cout << "^--Here\n\n\n";
		return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////
int
main()
{
	cout << "/////////////////////////////////////////////////////////\n\n";
	cout << "\t\tA Simple VMachine Test For Spirit...\n\n";
	cout << "/////////////////////////////////////////////////////////\n\n";

	//	Start grammar definition

	Rule<>	expr, integer, group, expr1, expr2;

	integer	= Lexeme[ (!(ch_p('+') | '-') >> +digit)[Integer()] ];
	group 	= '(' >> expr >> ')';
	expr1 	= integer | group;
	expr2 	= expr1 >> *(('*' >> expr1)[PushOp(OP_MUL)] | ('/' >> expr1)[PushOp(OP_DIV)]);
	expr 	= expr2 >> *(('+' >> expr2)[PushOp(OP_ADD)] | ('-' >> expr2)[PushOp(OP_SUB)]);

	//	End grammar definition

	cout << "Type an expression...or [q or Q] to quit\n\n";

	VMachine	mach;

	while (true)
	{
		char str[256];
		code.clear();
		cin.getline(str, 256);
		if (str[0] == 'q' || str[0] == 'Q')
			break;

		if (Compile(expr, &str[0]))
		{
			mach.Execute(&code[0]);
			cout << "result = " << mach.Top() << "\n\n";
		}
	}
	
	cout << "Bye... :-) \n\n";

	return 0;
}


