#include <string>
#include <stdio.h>
using namespace std;
enum enum1{
	TYPE1 = 1 << 1,
	TYPE2 = 1 << 2,
	TYPE3 = 1 << 3,
};
class hello
{
public:
	hello(){};
	~hello(){};
	
//tolua_begin
	void funcA();
	int funcC(string str);
	void funcB(){

	};
//tolua_end
};

class hello1 : public hello{
public:
	hello1(){};
	~hello1(){};
	void funcA();
	virtual int funcC(string str);
	void funcB(){

	};
};