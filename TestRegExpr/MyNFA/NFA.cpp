/**
	Not Determinated Finite Auto Machine
							By YafaceX
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Edge;

class State{
public:
	State(){};
	~State(){};
	Edge* in;
	std::vector<Edge*> outs;
};

class Edge
{
public:
	Edge();
	~Edge();
	char ch;
	State* from;
	State* to;
};

/*
	support:
		 repeat	+ * ?
		 logic  | connection
		 prior	( )
	not support temporarily:
		 range	[xx-xx] {m,n}
	*/
class Unit
{
public:
	enum Type{
		Char,
		And,
		Or,
		ZeroOne, // ?
		OneMore, // +
		ZeroMore // *
	};
	Unit();
	~Unit();
};

class FormationConverter
{
public:
	FormationConverter();
	~FormationConverter();
	
	void middle2post(string expression,vector<Unit*>& result)
	{

	};	
};
int main(int argc,char **argv)
{
	cout<<"YafaceX ..."<<endl;
	string regExp = "ab+";
}

