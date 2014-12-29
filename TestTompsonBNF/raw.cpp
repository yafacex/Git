#include<stdio.h>
#include<string.h>
#include<set>
#include<string>
#include<vector>
#include<stdexcept>
#include<iostream>
#include<tuple>
#include<memory>
#include<regex>
#include<cstdlib>
using namespace std;

struct FA;
#define epsilon '_'

bool _w_category(char x)
{
	if(!(x<='z'&&x>='a'))
		if(!(x<='Z'&&x>='A'))
			return false;
	return true;
}

void JoinCharset(set<char>& ch1,const set<char>& ch2)
{
	for(const auto & _param : ch2)
	{
		ch1.insert(_param);
	}
	return ;
}

typedef struct FA
{
	FA()
	{
		ch.insert(epsilon);
		s0 = 0;
	}
	FA& operator + (const FA& other)
	{
		if(acc.size() > 1)
		{
			JoinAcceptSet();
		}
		int stOffset = st.size();
		printf("Offset : %d\n",stOffset);
		stran.insert(tuple<int,char,int>(st.size()-1,epsilon,other.s0+stOffset));
		for(int i=0;i<other.st.size();i++)
		{
			st.push_back(st.size());
		}
		JoinCharset(ch,other.ch);
		for(auto & _param : other.stran)
		{
			stran.insert(tuple<int,char,int>(get<0>(_param) + stOffset ,
												get<1>(_param),
												get<2>(_param) + stOffset ) );
		}
		acc = other.acc;
		for(auto& _param : acc)
			_param += stOffset;
		return *this;
	}
	FA& operator | (const FA& other)
	{
		FA temp = other;
		JoinCharset(ch,other.ch);
		st.push_back(st.size());
		int st_bnd = st.size() - 1;
		stran.insert(tuple<int,char,int>(st_bnd,epsilon,s0));
		s0 = st_bnd;
		int stOffset = st.size();
		for(int i=0;i<other.st.size();i++)
		{
			st.push_back(other.st[i] + stOffset);
		}
		for(const auto & _param : other.stran)
		{
			stran.insert(tuple<int,char,int>(get<0>(_param) + stOffset,
												get<1>(_param),
												get<2>(_param) + stOffset));
		}
		stran.insert(tuple<int,char,int>(st_bnd,epsilon,other.s0 + stOffset));
		acc.push_back(other.acc[0] + st_bnd + 1);
		printf("%d %d\n",acc[0],acc[1]);
		JoinAcceptSet();
		return *this;
	}
	FA& operator = (const FA& rval)
	{
		st = rval.st;
		ch = rval.ch;
		stran = rval.stran;
		s0 = rval.s0;
		acc = rval.acc;
		return *this;
	}
	void Print()
	{
		printf("states: ");
		for(const auto& _param:st)
		{
			printf("%d ",_param);
		}
		printf("\ncharset: ");
		for(const auto& _param:ch)
		{
			printf("%c ",_param);
		}
		printf("\ntransition: \n");
		for(const auto& _param:stran)
		{
			printf("\t{%d %c %d}\n",get<0>(_param),
					get<1>(_param),
					get<2>(_param));
		}
		printf("start: %d\naccept: ",s0);
		for(const auto& _param:acc)
		{
			printf("%d ",_param);
		}
		printf("\n");
	}
	vector<int>st;
	set<char>ch;
	set<tuple<int,char,int> >stran;
	int s0;
	vector<int>acc;
private:
	void JoinAcceptSet()
	{
		st.push_back(st.size());
		for(const auto& _param : acc)
		{
			stran.insert(tuple<int,char,int>(	_param,
												epsilon,
												st.back()));
		}
		acc = {st.back()};
		return ;
	}
}FA;

FA* simple_make_FA(string& tokens,int s,int e,bool init)
{
	FA* inst = new FA;
	bool has_subFA = false;
	int subFAst,subFAed;
	if(init)
	{
		for(int i=0;i<tokens.length() - 1;i++)
		{
			if(tokens[i] == '(' && !has_subFA)
			{
				has_subFA = true;
				subFAst = i;
			}
		}
		if(has_subFA)
		{
			for(int i=tokens.length()-1; i >= 0 ; i--)
			{
				if(tokens[i] == ')')
				{
					subFAed = i;
					break;
				}
			}
		}
	}
	if(has_subFA)
	{
		FA* temp = simple_make_FA(tokens,subFAst,subFAed,true);
		(*inst) + (*temp);
		delete temp;
		inst->Print();
		system("pause");
	}
	cout<<tokens<<endl;
	return inst;
}

int main()
{
	FA a,b;
	FA c;
	a.s0 = 0;
	b.s0 = 0;
	c.s0 = 0;
	a.st = {0,1};
	b.st = {0,1};
	c.st = {0,1};
	a.stran .insert(tuple<int,char,int>(0,'a',1));
	b.stran .insert(tuple<int,char,int>(0,'b',1));
	c.stran .insert(tuple<int,char,int>(0,'c',1));
	a.acc = {1};
	b.acc = {1};
	c.acc = {1};
	a.ch = {'a'};
	b.ch = {'b'};
	c.ch = {'c'};
	(a|b).Print();
	(c+a).Print();
	return 0;
}
