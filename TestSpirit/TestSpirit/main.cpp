#include <spirit/Spirit.h>
#include <iostream>
#include <stack>
#include <functional>
#include <fstream>
#include "SkillCfg.h"
#include "boost/bind.hpp"
#include <VM.h>
#include "SkillParser.h"

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

//stack<long>	evaluation_stack;
//
//////////////////////////////////////////////////////////////////////////////
//struct Integer {
//    
//	void operator()(char const* l, char const* r/*end*/) const
//	{
//        std::string str(l,r);
//        std::cout << "Int:" << str << std::endl;
//		long n = std::strtol(l, nil, 10);
//		evaluation_stack.push(n);
//		cout << "push\t" << long(n) << endl;
//	}
//	
//};
//
//template <class op>
//struct doOp
//{
//	doOp(op const& theOp) : m_op(theOp) {}
//	op m_op;
//    
//	void operator()(char const*, char const*) const
//	{
//		long rhs = evaluation_stack.top();
//		evaluation_stack.pop();
//		long lhs = evaluation_stack.top();
//		evaluation_stack.pop();
//        
//		cout << "popped " << lhs << " and " << rhs << " from the stack. ";
//		cout << "pushing " << m_op(lhs, rhs) << " onto the stack.\n";
//		evaluation_stack.push(m_op(lhs, rhs));
//	}
//};
//
//template <class op>
//doOp<op> makeDoOp(op const& theOp)
//{
//	return doOp<op>(theOp);
//}
//
//struct doNegate
//{
//	void operator()(char const*, char const*) const
//	{
//		long lhs = evaluation_stack.top();
//		evaluation_stack.pop();
//        
//		cout << "popped " << lhs << " from the stack. ";
//		cout << "pushing " << -lhs << " onto the stack.\n";
//		evaluation_stack.push(-lhs);
//	}
//};
//
//struct doVariant{
//    void operator()(char const* l,char const* r) const{
//        std::string str(l,r);
//        std::cout << "doVariant:" << str << std::endl;
//    }
//};
//
//struct doExpr{
//    void operator()(char const* l,char const* r) const{
//        std::string str(l,r);
//        std::cout << "doExpr:" << str << std::endl;
//    }
//};
//
//struct doDigit{
//    void operator()(char const* l,char const* r) const{
//        std::string str(l,r);
//        std::cout << "doDigit:" << str << std::endl;
//    }
//};
//////////////////////////////////////////////////////////////////////////////
//
//void testMy(){
//    Spirit::Rule<> expression,variant,real,ch,assign;
//    ch = Spirit::Range<unsigned char>('\x41', '\x5A') | Spirit::Range<unsigned char>('\x61', '\x7A')
//    | Spirit::Range<unsigned char>('\xC0', '\xD6') | Spirit::Range<unsigned char>('\xD8', '\xF6')
//    | Spirit::Range<unsigned char>('\xF8', '\xFF');
//    variant =  Spirit::Lexeme[ (+ch)[doVariant()] ];
//    real = Lexeme[ (+Spirit::digit)[doDigit()] ];
//    expression = (variant >> assign >> real)[doExpr()];
//    assign = Spirit::ChLit<>('=');
//    char str[] = "haha = 6665";
//    Spirit::Scanner<> scan(str,Spirit::space);
//    if (expression.Parse(scan) && !*scan) {
//        std::cout<<"hahahahahah"<<std::endl;
//    }
//}
//
//
//void testExample(){
//    
//	Rule<> expression, term, factor, integer;
//	
//	expression	=term >> *( ('+' >> term)[makeDoOp(std::plus<long>())]
//                           |('-' >> term)[makeDoOp(std::minus<long>())]);
//	integer		= Lexeme[ (!ch_p('-') >> +digit)[Integer()] ];
//	factor		= 	integer
//    | '(' >> expression >> ')'
//    | ('-' >> factor)[doNegate()];
//	term		= factor >> *( ('*' >> factor)[makeDoOp(std::multiplies<long>())]
//                              |('/' >> factor)[makeDoOp(std::divides<long>())]);
//    
//    
//	//	End grammar definition
//    
//    char str[] = " 3000 * ( 255 + 166 ) - 589";
//	Scanner<> scan(str, space);
//	if (expression.Parse(scan) && !*scan)
//	{
//		cout << "parsing succeeded\n";
//		cout << "result = " << evaluation_stack.top() << "\n\n";
//		evaluation_stack.pop();
//	}
//	else
//	{
//		cout << "parsing failed\n";
//	}
//}
/**
 Relationship=["alian"|"enemy"];
 
 Set=["soldier"|"hero"|"building"];
 
 Range=["nearest"|"farest"|"in"(real)|"out"(real)];
 
 Attr=["hp"|"movespeed"|"attackspeed"];
 
 OP=["*","+"]
 
 RowTable=Attr : +(real)
 
 Table={
 +RowTable;
 }
 
 Target={
 "relationship":relationship
 "tarSet":+Set
 "tarRange":Range
 "tarAttr":+Attr
 }
 Trigger={
 "times":integer(delayFrm)
 "time":real
 //func 暂时不搞
 }
  
 Description =
 */
using namespace Spirit;
using namespace Skill;
#define STR(_V_) StrLit<>(#_V_)

struct testFunc{
    void operator()(char const* l,char const* r) const {
        std::string _str(l,r);
        std::cout << "[[[[[[[[[["<<std::endl<<_str << std::endl << "]]]]]]" << std::endl;
    };
};

//#define TestFunc [testFunc()]
#define BindFunc(_V_)\
    [boost::bind(&VM::_V_,vm,_1,_2)]

void testSkill(VM* vm){
    //support
    Rule<> Real,Integer,String;
    Rule<> AnyChar,BChar,Enter;
    //comment & description
    Rule<> Table,Description,Comment,CommentN,Table_,Description_;
    //function & variant
    Rule<> FunctionCall,Param,Params,FunctionName,ParamName,FunctionBuildin;
    Rule<> VariantName,ConstName;
    Rule<> Expr;
    
    Rule<> DeclareVariant;
    
    Rule<> RowTable;
    Rule<> Skill;
    
    /**
     Support
     */
	AnyChar = ChLit<>('\x9') | ChLit<>('\xA') | ChLit<>('\xD') | Spirit::Range<unsigned char>('\x20', '\xFF');
    BChar = Spirit::Range<unsigned char>(65, 90) | Spirit::Range<unsigned char>(97, 122);
    Enter = ch_p('\r') | ch_p('\n');
    
    Integer = Lexeme[ (!ch_p('-') >> +digit)];
    Real = Lexeme[!ch_p('-') >> +digit >> '.' >> +digit];
    String =  +BChar;
    
    ConstName = (ch_p('@')>>+BChar);
    /**
     Table
     */
    RowTable = Lexeme[ch_p('"') >> String BindFunc(TableAttr)>> ch_p('"')] >> ch_p('=') >>
                (
                 (+Real BindFunc(TableDataReal)) |
                 (+Integer BindFunc(TableDataInt))
                 );
    Table_ = ch_p('{')>> (*RowTable) >> '}';
    Table = STR(Table) >> ch_p('=')>> Table_;
    
    /*
     Description
     */
    Description_ = ch_p('{') >>
                STR(Name)>> ':' >>Lexeme[(+BChar)BindFunc(DescriptionName) ]>>
                STR(Effect) >> ':'>>Lexeme[(+(AnyChar-'}')) ] >>
                '}';
    Description = STR(Description) >> '=' >> Description_;
    
    /*
     Comment
     just like c/c++
     */
    Comment = "/*" >> (*(AnyChar-'*'-'/')) >> "*/" ;
    CommentN = *Comment;
    
    /*
     Function & Declare & Expr
     */
    VariantName = +BChar;
    DeclareVariant = STR(var) >> STR(VariantName) >> ch_p('=') >> Expr;
    
    FunctionName =  (ch_p('$')>>(+BChar)) BindFunc(VmCallFuncBeginBuiltin);
    FunctionCall = FunctionName>>ch_p('(')>>Params>>ch_p(')') BindFunc(VmCallFuncEndBuiltin)>>+ch_p(';');
    
    ParamName = (+BChar) | ConstName BindFunc(VmParamConstBuildin);
    Param = ParamName |
            Real BindFunc(VmParamReal)|
            Integer BindFunc(VmParamInteger)|
            Lexeme[ch_p('"') >> String BindFunc(VmParamString)>> ch_p('"')];
    Params = !Param >> (*(ch_p(',')>>Param));
    
    Expr = Real | Integer | VariantName | FunctionCall |
        (VariantName>> ch_p('=') >> Real)|
        (VariantName>> ch_p('=') >> Integer) |
         (VariantName>> ch_p('=') >> FunctionCall);
    
    /**
     Skill
     */
    Skill = CommentN>>Description >>CommentN>> Table >>*(CommentN>> Expr)>>CommentN;
    
    
    FILE* fp = fopen("haha.skill", "r");
    fseek(fp,0L,SEEK_END);
    long size = ftell(fp);
    if (size > 1000) {
        std::cout << "Skill File is Too Long" << std::endl;
        return;
    }
    char * fc = new char[size];
    memset(fc, 0, size);
    fseek(fp,0L,SEEK_SET);
    fread(fc, sizeof(char), size, fp);
    string str(fc);
    std::cout << "File Content:" << std::endl << str <<std::endl;
    Spirit::Scanner<> scan(fc,Spirit::space);
    if (Skill.Parse(scan) && !*scan) {
        std::cout<<"hahahahahah"<<std::endl;
    }
}
int
main()
{
    assert(false);
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
 
//    testMy();
    
//    testSkill(VM::getInstance());
    VM::getInstance()->loadGrammar();
    VM::getInstance()->compile();
    VM::getInstance()->compile();
    VM::getInstance()->compile();
}


