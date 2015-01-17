/**
	Not Determinated Finite Auto Machine
							By YafaceX
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <map>
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

#define BadString ""
class UnitParser
{
public:
	UnitParser(){};
	~UnitParser(){};
	
	/**
		添加连接符部分
	*/
	bool isRepeat(char ch){
		return ch == '+' || ch == '*' || ch == '?' ;
	};
	bool isAlphbet(char ch){
		return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
	};
	bool isRepeat_Alphbet_BaracketR(char ch){
		 return isRepeat(ch) || isAlphbet(ch) || ch == ')';
	};
	bool isAlphbet_BracketL(char ch){
		return isAlphbet(ch) || ch == '(';	
	};
	string addConnection(string expression){
		//把链接符号~添加进去
		string processedExp = "";
		char lastChar = '\0';
		for_each(expression.begin(),expression.end(),[&](const char ch){
			if (isRepeat_Alphbet_BaracketR(lastChar) && isAlphbet_BracketL(ch)){
				processedExp.append(1,'~');
			}
			processedExp.append(1,ch);
			lastChar = ch;
		});
		cout << "[addConnection] : " << processedExp << endl;
		return processedExp;
	};

	/*
		转后缀表达式部分
	*/
	bool isBracket(char ch){
		return ch == '(' || ch == ')';
	};
	bool isAndOr(char ch){
		return ch == '~' || ch == '|';
	}
	bool isOp(char ch){
		return isRepeat(ch) || isBracket(ch) || isAndOr(ch);
	};
	bool isMiddleOp(char ch){
		return isAndOr(ch);
	};
	void pushChar(char ch) {
		charStack.push_back(ch);
	};
	void pushOp(char ch) {
		opStack.push_back(ch);
	};
	char charTop() {
		return charStack.back();
	}
	char popChar() {
		char tmp = charTop();
		charStack.pop_back();
		return tmp;
	};
	char opTop() {
		return opStack.back();
	}
	char popOp() {
		char tmp = opTop();
		opStack.pop_back();
		return tmp;
	};

	bool popUtilBracketL(){
		if(find(opStack.begin(),opStack.end(),'(') == opStack.end()){
			cout << "No Matched Left Baracket,Bad Expression!" << endl;
			return false;
		}else{
			char poped = '\0';
			while(poped == '('){
				charStack.push_back(opStack.back());
				opStack.pop_back();
			}
			return true;
		}
	};

	string toPostExpression(string expression){

		string passedStr = "";

		for_each(expression.begin(),expression.end(),[&](const char ch){
			passedStr.append(1,ch);
			if (isOp(ch)){
				if (isBracket(ch)){
					if (ch == '('){
						pushOp(ch);
					}else{
						bool popOK = popUtilBracketL();
						if(!popOK){
							cout << "Lack Of [(] before " << passedStr <<endl;
							return BadString;
						}
					}
				}else{
					if (isMiddleOp(ch)){
						pushOp(ch);
					}else {
						pushChar(ch);
					}
				} 
			}else if (isAlphbet(ch)){
				pushChar(ch);
				char top = opTop();
				if(isMiddleOp(ch)){
					pushChar(popOp());
				}
			}else{
				cout << "Not Support Fuck Expression !" << endl;
			}
		});
	};
	// return head of the unit tree
	// ((ab)+)*
	Unit* parse(string expression)
	{
		expression = addConnection(expression);
		string post = toPostExpression(expression);
		return NULL;
	};	

	vector<char> charStack;
	vector<char> opStack;
};


int main(int argc,char **argv)
{
	cout<<"YafaceX ..."<<endl;
	string regExp = "xyz(a|b|c)+x(a(bc)|(aa|a+))bb";
	UnitParser parser;
	parser.parse(regExp);
}

