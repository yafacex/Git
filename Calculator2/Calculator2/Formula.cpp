#include "Formula.h"
#include <assert.h>
using namespace FormulaNS;

#define DBG_FORMULA 0

void  FORMULA_ERR(const char * errlog){
	printf("Formula Parse Error:");
	printf("%s",errlog);
	printf("\n");
#if DBG_FORMULA
    assert(false);
#endif
}


#define TOKEN_MAX_LEN 10

#define IS_NUMBER(_V_) (_V_ <= '9' && _V_ >= '0')
#define IS_OP(_V_) (_V_ >= OP_MIN && _V_ <= OP_MAX) 

#define OP_TOP (opStack.at(opStack.size()-1))
#define V_TOP (vStack.at(vStack.size()-1))

static char splits[] = {'+','-','*','/','(',')','\n',';',' ','\t',EOF};
static TokenTypeMap tokenMaps[] = {
	{"+",TokenType_ADD},
	{"-",TokenType_SUB},
	{"*",TokenType_MUL},
	{"/",TokenType_DIV},
	{"=",TokenType_ASSIGN},
	{"(",TokenType_LEFT_BRACKET},
	{")",TokenType_RIGHT_BRACKET},
	{"result",TokenType_RESULT},
	{"prev",TokenType_PREV},
	{";",TokenType_END}
};

static bool bPriorInit = false;
static char tokenPrior[OP_MAX-OP_MIN+1][OP_MAX-OP_MIN+1];
void initPrior(){
	tokenPrior[TokenType_ADD][TokenType_ADD] = '>';
	tokenPrior[TokenType_ADD][TokenType_SUB] = '>';
	tokenPrior[TokenType_ADD][TokenType_MUL] = '<';
	tokenPrior[TokenType_ADD][TokenType_DIV] = '<';
	tokenPrior[TokenType_ADD][TokenType_LEFT_BRACKET] = '<';
	tokenPrior[TokenType_ADD][TokenType_RIGHT_BRACKET] = '>';
	tokenPrior[TokenType_ADD][TokenType_ASSIGN] = '<';
	tokenPrior[TokenType_ADD][TokenType_END] = '>';
    tokenPrior[TokenType_ADD][TokenType_BEGIN] = '?';
	
	tokenPrior[TokenType_SUB][TokenType_ADD] = '>';
	tokenPrior[TokenType_SUB][TokenType_SUB] = '>';
	tokenPrior[TokenType_SUB][TokenType_MUL] = '<';
	tokenPrior[TokenType_SUB][TokenType_DIV] = '<';
	tokenPrior[TokenType_SUB][TokenType_LEFT_BRACKET] = '<';
	tokenPrior[TokenType_SUB][TokenType_RIGHT_BRACKET] = '>';
	tokenPrior[TokenType_SUB][TokenType_ASSIGN] = '<';
	tokenPrior[TokenType_SUB][TokenType_END] = '>';
    tokenPrior[TokenType_SUB][TokenType_BEGIN] = '?';
	
	tokenPrior[TokenType_MUL][TokenType_ADD] = '>';
	tokenPrior[TokenType_MUL][TokenType_SUB] = '>';
	tokenPrior[TokenType_MUL][TokenType_MUL] = '>';
	tokenPrior[TokenType_MUL][TokenType_DIV] = '>';
	tokenPrior[TokenType_MUL][TokenType_LEFT_BRACKET] = '<';
	tokenPrior[TokenType_MUL][TokenType_RIGHT_BRACKET] = '>';
	tokenPrior[TokenType_MUL][TokenType_ASSIGN] = '<';
	tokenPrior[TokenType_MUL][TokenType_END] = '>';
    tokenPrior[TokenType_MUL][TokenType_BEGIN] = '?';

	tokenPrior[TokenType_DIV][TokenType_ADD] = '>';
	tokenPrior[TokenType_DIV][TokenType_SUB] = '>';
	tokenPrior[TokenType_DIV][TokenType_MUL] = '>';
	tokenPrior[TokenType_DIV][TokenType_DIV] = '>';
	tokenPrior[TokenType_DIV][TokenType_LEFT_BRACKET] = '<';
	tokenPrior[TokenType_DIV][TokenType_RIGHT_BRACKET] = '>';
	tokenPrior[TokenType_DIV][TokenType_ASSIGN] = '<';
	tokenPrior[TokenType_DIV][TokenType_END] = '>';
    tokenPrior[TokenType_DIV][TokenType_BEGIN] = '?';

	tokenPrior[TokenType_LEFT_BRACKET][TokenType_ADD] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_SUB] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_MUL] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_DIV] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_LEFT_BRACKET] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_RIGHT_BRACKET] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_ASSIGN] = '<';
	tokenPrior[TokenType_LEFT_BRACKET][TokenType_END] = '<';
    tokenPrior[TokenType_LEFT_BRACKET][TokenType_BEGIN] = '?';

	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_ADD] = '>';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_SUB] = '>';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_MUL] = '>';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_DIV] = '>';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_LEFT_BRACKET] = '>';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_RIGHT_BRACKET] = '<';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_ASSIGN] = '>';
	tokenPrior[TokenType_RIGHT_BRACKET][TokenType_END] = '>';
    tokenPrior[TokenType_RIGHT_BRACKET][TokenType_BEGIN] = '?';

	tokenPrior[TokenType_ASSIGN][TokenType_ADD] = '<';
	tokenPrior[TokenType_ASSIGN][TokenType_SUB] = '<';
	tokenPrior[TokenType_ASSIGN][TokenType_MUL] = '<';
	tokenPrior[TokenType_ASSIGN][TokenType_DIV] = '<';
	tokenPrior[TokenType_ASSIGN][TokenType_LEFT_BRACKET] = '<';
	tokenPrior[TokenType_ASSIGN][TokenType_RIGHT_BRACKET] = '<';
	tokenPrior[TokenType_ASSIGN][TokenType_ASSIGN] = '?';
	tokenPrior[TokenType_ASSIGN][TokenType_END] = '>';
    tokenPrior[TokenType_ASSIGN][TokenType_BEGIN] = '?';

	tokenPrior[TokenType_END][TokenType_ADD] = '?';
	tokenPrior[TokenType_END][TokenType_SUB] = '?';
	tokenPrior[TokenType_END][TokenType_MUL] = '?';
	tokenPrior[TokenType_END][TokenType_DIV] = '?';
	tokenPrior[TokenType_END][TokenType_LEFT_BRACKET] = '?';
	tokenPrior[TokenType_END][TokenType_RIGHT_BRACKET] = '?';
	tokenPrior[TokenType_END][TokenType_ASSIGN] = '?';
	tokenPrior[TokenType_END][TokenType_END] = '=';
    tokenPrior[TokenType_END][TokenType_BEGIN] = '?';
    
    tokenPrior[TokenType_BEGIN][TokenType_ADD] = '?';
	tokenPrior[TokenType_BEGIN][TokenType_SUB] = '?';
	tokenPrior[TokenType_BEGIN][TokenType_MUL] = '?';
	tokenPrior[TokenType_BEGIN][TokenType_DIV] = '?';
	tokenPrior[TokenType_BEGIN][TokenType_LEFT_BRACKET] = '?';
	tokenPrior[TokenType_BEGIN][TokenType_RIGHT_BRACKET] = '?';
	tokenPrior[TokenType_BEGIN][TokenType_ASSIGN] = '<';
	tokenPrior[TokenType_BEGIN][TokenType_END] = '=';
    tokenPrior[TokenType_BEGIN][TokenType_BEGIN] = '=';
};

const char* getTokenString(TokenType type){
    int size = sizeof(tokenMaps) / sizeof(TokenTypeMap);
    for(int i = 0;i < size ; ++i){
        if (tokenMaps[i].type == type) {
            return tokenMaps[i].str;
        }
    }
    return "NoneType";
}

bool isSplit(const char c){
	int size = sizeof(splits) / sizeof(char);
	for (int i = 0; i < size;++i)
	{
		if (splits[i] == c)
		{
			return true;
		}
	}
	return false;
}

void skipBlank(char* &str){
	int i = 0;
	while (*str == ' '|*str == '\t'|*str == EOF)
	{
		++i;
		str = str + 1;
		if (i > 10)
		{
			FORMULA_ERR("blank is too long");
			break;
		}
	}
}

bool isConst(const char* token){
	if (!IS_NUMBER(token[0]))
	{
		return false;
	}
	int i = 1;
	int dotPos = 256;
	bool bDot = false;
	while(token[i] != '\0'){
		if (token[i] == '.')
		{
			dotPos = i;
			if (!bDot)
			{
				bDot = true;
			}else{
				FORMULA_ERR("DOT appear more than once");
			}
		}else{
			if (IS_NUMBER(token[i]))
			{
				return false;
			}
		}
		++i;
	};
	if (dotPos + 1 <= i)
	{
		FORMULA_ERR("number cant not end with DOT");
        return false;
	}else{
		return true;
	}
}

Formula::Formula(void)
{
    if (!bPriorInit) {
        initPrior();
        bPriorInit = true;
    }
}


Formula::~Formula(void)
{
}

float Formula::calcByString(char* formulaStr,bool convertToOPCODE){
    vStack.clear();
    opStack.clear();
    opCodes.clear();
    
	char current[TOKEN_MAX_LEN];
    TokenType curType;

    printf("Formula:%s\n",formulaStr);
    opStack.push_back(TokenType_BEGIN);
	do 
	{
        do{
            switch (OP_TOP) {
                case TokenType_END:{
                    curType = OP_TOP;
                    opStack.pop_back();
                }
                    break;
                default:{
                    nextToken(formulaStr,current);
            		printf("tokenCurr:%s\n",current);
                    curType = getTokenType(current);
                }
                    break;
            }
            if (TokenType_ERR == curType) {
                FORMULA_ERR("Invalid token type");
            }
            if (IS_OP(curType)) {
                switch (tokenPrior[OP_TOP][curType]) {
                    case '<':{
                        opStack.push_back(curType);
                    }
                        break;
                    case '=':{
                        opStack.pop_back();
                    }
                        break;
                    case '>':{
                        switch (curType) {
                            case TokenType_RIGHT_BRACKET:{
                                VAL v1 = V_TOP;
                                vStack.pop_back();
                                VAL v2 = V_TOP;
                                vStack.pop_back();
                                TokenType op = OP_TOP;
                                opStack.pop_back();
                                dealOp(op, v1, v2,convertToOPCODE);
                                opStack.pop_back();
                            }
                                break;
                            default:{
                                VAL v1 = V_TOP;
                                vStack.pop_back();
                                VAL v2 = V_TOP;
                                vStack.pop_back();
                                TokenType op = OP_TOP;
                                opStack.pop_back();
                                if(dealOp(op, v1, v2,convertToOPCODE)){
                                    return v2.value;
                                }
                                opStack.push_back(curType);
                                
                            }
                                break;
                        }
                        
                    }
                        break;
                    case '?':{
                        char err[100];
                        sprintf(err,"OP[%s] cant follow OP[%s]",getTokenString(curType),getTokenString(OP_TOP));
                        FORMULA_ERR(err);
                    }
                        break;
                    default:{
                        FORMULA_ERR("Invalid OP prior");
                    }
                        break;
                }
            }else{
                VAL val;
                val.type = curType;
                if (isConst(current)) {
                    val.value = atof(current);
                    vStack.push_back(val);
                    if (convertToOPCODE) {
                        OPCODE code;
                        code.op = OP_PUSH_CONST;
                        code.value = val.value;
                        opCodes.push_back(code);
                    }
                }else{
                    val.value = 0;
                    vStack.push_back(val);
                    if (convertToOPCODE && curType == TokenType_PREV) {
                        OPCODE code;
                        code.op = OP_PUSH_PREV;
                        opCodes.push_back(code);
                    }
                }
                
            }
        }while (true);
        
        
        
	} while (true);
}
bool Formula::dealOp(TokenType op,VAL& v1,VAL& v2,bool convertToOPCODE){
    switch (op) {
        case TokenType_ADD:{
            VAL res;
            res.type = TokenType_CONST;
            res.value = getValueByVAL(v1) + getValueByVAL(v2);
            vStack.push_back(res);
            if (convertToOPCODE) {
                OPCODE code;
                code.op = OP_ADD;
                opCodes.push_back(code);
            }
            return false;
        }
            break;
        case TokenType_SUB:{
            VAL res;
            res.type = TokenType_CONST;
            res.value = getValueByVAL(v2) - getValueByVAL(v1);
            vStack.push_back(res);
            if (convertToOPCODE) {
                OPCODE code;
                code.op = OP_SUB;
                opCodes.push_back(code);
            }
            return false;
        }
            break;
        case TokenType_MUL:{
            VAL res;
            res.type = TokenType_CONST;
            res.value = getValueByVAL(v1) * getValueByVAL(v2);
            vStack.push_back(res);
            if (convertToOPCODE) {
                OPCODE code;
                code.op = OP_MUL;
                opCodes.push_back(code);
            }
            return false;
        }
            break;
        case TokenType_DIV:{
            VAL res;
            res.type = TokenType_CONST;
            if (v1.type == TokenType_CONST) {
                if(v1.value == 0){
                    FORMULA_ERR("can not div zero");
                    return false;
                }
            }
            res.value = getValueByVAL(v2) / getValueByVAL(v1);
            vStack.push_back(res);
            if (convertToOPCODE) {
                OPCODE code;
                code.op = OP_DIV;
                opCodes.push_back(code);
            }
            return false;
        }
            break;
        case TokenType_ASSIGN:{
            v2.value = v1.value;
            if (convertToOPCODE) {
                OPCODE code;
                code.op = OP_ASSIGN_RES;
                opCodes.push_back(code);
            }
            return true;
        }
            break;
        default:{
            FORMULA_ERR("Invalid operator");
            return false;
        }
            break;
    }
}

float Formula::getValueByVAL(VAL& val){
    switch (val.type) {
        case TokenType_CONST:
            return val.value;
            break;
        case TokenType_PREV:
            return 2.0;
            break;
        case TokenType_RESULT:
            return 3.0;
            break;
        default:
            FORMULA_ERR("Invalid value type[const/prev/result]");
            return 0;
            break;
    }
}
TokenType Formula::getTokenType(const char* token){
	int size = sizeof(tokenMaps) / sizeof(TokenTypeMap);
	for (int i = 0 ; i<size ; ++i)
	{
		if (0 == strcmp(token,tokenMaps[i].str))
		{
			return tokenMaps[i].type;
		}
	}
	if (isConst(token))
	{
		return TokenType_CONST;
	}else{
		return TokenType_ERR;
	}
}
void Formula::nextToken(char* &src,char* token){
	int i = 0;
	skipBlank(src);
	if(isSplit(*src)){
		token[0] = src[0];
		token[1] = '\0';
		src = src + 1;
		return;
	}
	do{
		*(token + i) = *src;
		++i;
		src = src + 1;
		if (i > TOKEN_MAX_LEN)
		{
			FORMULA_ERR("token is too long!");
			break;
		}
	}while (!isSplit(*src));
	*(token + i) = '\0';
}

float Formula::calcByOP(){
    float v1,v2;
    for (OPCODES_ITERATOR itr = opCodes.begin(); itr != opCodes.end(); ++itr) {
        switch ((*itr).op) {
            case OP_ADD:{
                v1 = rtStack.back();rtStack.pop_back();
                v2 = rtStack.back();rtStack.pop_back();
                rtStack.push_back(v1+v2);
            }
                break;
            case OP_SUB:{
                v1 = rtStack.back();rtStack.pop_back();
                v2 = rtStack.back();rtStack.pop_back();
                rtStack.push_back(v2-v1);
            }
                break;
            case OP_MUL:{
                v1 = rtStack.back();rtStack.pop_back();
                v2 = rtStack.back();rtStack.pop_back();
                rtStack.push_back(v1*v2);
            }
                break;
            case OP_DIV:{
                v1 = rtStack.back();rtStack.pop_back();
                v2 = rtStack.back();rtStack.pop_back();
                rtStack.push_back(v1/v2);
            }
                break;
            case OP_ASSIGN_RES:{
                return rtStack.at(0);
            }
                break;
            case OP_PUSH_CONST:{
                rtStack.push_back((*itr).value);
            }
                break;
            case OP_PUSH_PREV:{
                rtStack.push_back(getPrevAtRunTime());
            }
                break;
            default:
                break;
        }
    }
    return rtStack[0];
}
float Formula::getPrevAtRunTime(){
    return 1.0;
}