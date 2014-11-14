#include "hello.h"
void hello::funcA(){

};
int hello::funcC(string str){
	printf("%s\n", str.c_str());
}
void hello1::funcA(){

};
int hello1::funcC(string str){
	printf("%s\n", str.c_str());
}

int main(int argc,char ** argv){
	hello* h = new hello(); 
	h->funcA();
	h->funcC("i am 0");
	hello1* h1 = new hello1(); 
	h1->funcA();
	h1->funcC("i am 1");
}