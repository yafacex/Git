/**
	Not Determinated Finite Auto Machine
							By YafaceX
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include<stdlib.h>
#include<stdio.h>
#include <string.h>
using namespace std;

class Edge;
class Unit;

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
	Edge(){};
	~Edge(){};
	Unit* unit;
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
	enum OpType{
		And,
		Or,
		ZeroOne, // ?
		OneMore, // +
		ZeroMore, // *
		BracketLeft, // (
		BracketRight // )
	};
	Unit(char ch){this->ch = ch;};
	~Unit(){};
	char ch;
};

class UnitParser
{
public:
	UnitParser(){};
	~UnitParser(){};
	
	bool isRepeat_Or_BaracketR(char ch){
		return ch == '+' || ch == '*' || ch == '?' || ch == '|' || ch == ')';
	}
	bool isAlpha_BracketR(char ch){
		return ch == ')' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
	}
	// return head of the unit tree
	// ((ab)+)*
	//因为repeat和|和)一定在字母或)后面，所以字母或)后面不是repeat和|和)的就是与了
	Unit* parse(string expression)
	{
		string processedExp = "";
		char lastChar = '|';//任意repeat和|均可
		for_each(expression.begin(),expression.end(),[&](const char ch){
			if (isAlpha_BracketR(lastChar) && !isRepeat_Or_BaracketR(ch)){
				processedExp.append(1,'~');
			}
			processedExp.append(1,ch);
			lastChar = ch;
		});
		cout << processedExp << endl;
	};	
};


int main(int argc,char **argv)
{
	cout<<"YafaceX ..."<<endl;
	string regExp = "xyz(a|b|c)+x(a(bc)|(aa|a+))bb";
	UnitParser parser;
	parser.parse(regExp);
}

