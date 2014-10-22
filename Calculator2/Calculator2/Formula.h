#pragma once
#include <iostream>
#include <vector>
using namespace std;
namespace FormulaNS{

enum TokenType
{
	TokenType_ADD = 0,
	TokenType_SUB,
	TokenType_MUL,
	TokenType_DIV,
	TokenType_ASSIGN,
    TokenType_BEGIN,
	TokenType_END,
	TokenType_LEFT_BRACKET,
	TokenType_RIGHT_BRACKET,

	TokenType_RESULT,
	TokenType_PREV,
	TokenType_CONST,

	TokenType_ERR,
	 
	OP_MIN = TokenType_ADD,
	OP_MAX = TokenType_RIGHT_BRACKET
};
typedef struct TokenTypeMap_
{
	const char* str;
	TokenType type;
}TokenTypeMap;


typedef struct VAL_{
	TokenType type;
	float value;
}VAL;

typedef struct OP_VAL_{
	TokenType type;
	VAL value;
}OP_VAL;
    
class Formula
{
public:
/**
 effience runtime data structure
 */
    enum OP{
        OP_PUSH_PREV,
        OP_PUSH_CONST,
        OP_ADD,
        OP_SUB,
        OP_MUL,
        OP_DIV,
        OP_ASSIGN_RES,
    };
    typedef struct OPCODE_{
        OP op;
        float value;
    }OPCODE;
    typedef vector<OPCODE> OPCODES;
    typedef vector<float> OP_RUNTIME_STACK;
    typedef vector<OPCODE>::iterator OPCODES_ITERATOR;
    OP_RUNTIME_STACK rtStack;
    
    float getPrevAtRunTime();
/*
 end
 */
    
    
	typedef vector<TokenType> OP_STACK;
	typedef vector<VAL> VALUE_STACK;
	typedef vector<OP_VAL> CAL_STACK;
	
    Formula(void);
	~Formula(void);
    
	float calcByString(char* formulaStr,bool convertToOPCODE);
    bool dealOp(TokenType op,VAL& v1,VAL& v2,bool convertToOPCODE);
    float getValueByVAL(VAL& val);
	void nextToken(char* &src,char* token);
	TokenType getTokenType(const char* token);
    
    float calcByOP();
	
	OP_STACK opStack;
	VALUE_STACK vStack;
	CAL_STACK calStack;
    
    OPCODES opCodes;
};

}
