//
//  TestRegex.h
//  TestMacro
//
//  Created by yafacex on 14-6-30.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestMacro_TestRegex_h
#define TestMacro_TestRegex_h
#define BOOST_REGEX_STATIC_LINK
#include "boost/regex.hpp"
#include <string>
#include<map>
using namespace std;
using namespace boost;

typedef pair<int, int> loc;
typedef map<pair<int, int>, bool> locMap;


bool cao(int x,int y){
    printf("%d--%d\n",x,y);
    if(x < 10 && y<10 && x>0 && y>0){
        return true;
    }else{
        return false;
    }
};

class TestRegex {
public:
    typedef int loc;
    typedef map<loc, bool> locMap;
    template<typename _Function>
    static void heuristicSearch2d(int startX,int startY,locMap& res,locMap& searched,int _4or8,_Function _f){
        static int around[8][2] = {
            {-1,0},{0,-1},{0,1},{1,0},{-1,-1},{-1,1},{1,-1},{1,1}
        };
        int x = startX;
        int y = startY;
        int tmpX,tmpY;
#define KEY(_X,_Y) (_X + _Y * 100)
        do{
            //mark around
            bool bOver = false;
            for (int i =0; i < 8; ++i) {
                tmpX = x + around[i][0];
                tmpY = y + around[i][1];
                //if is searchable
                bool b = _f(tmpX,tmpY);
                if(searched.find(KEY(tmpX,tmpY)) == searched.end()){
                    bOver = true;
                    searched[KEY(tmpX,tmpY)] = true;
                }
                if ( b ) {
                    locMap::iterator itr = res.find(KEY(tmpX,tmpY));
                    locMap::iterator itrEnd = res.end();
                    if(itr == itrEnd){
                        res[KEY(tmpX,tmpY)] = true;
//                        res.insert(loc(tmpX,tmpY),true));
                        heuristicSearch2d(tmpX, tmpY, res,searched, _4or8, _f);
                    }
                }
            }
            if(!bOver)break;
        }while(true);
    }
    
    public:
    TestRegex(){
        testMatch();
        testSearch();
    };
    ~TestRegex(){};
    void testMatch(){
//        regex reg("([a-z]|[0-9])+");
        std::string regstr = "[a|b|c]+";
        boost::regex expression(regstr);
        string str = "aaabbbbcccc";
        bool b = regex_match(str.c_str(), expression,match_all);
        if (b){
            printf("find\n");
        }else{
            printf("not find\n");
        }
    };
    void testSearch(){
        regex reg("[0|2|5]+");
        string str = "wl is 250,use 502 to paste";
        smatch res;
        string::const_iterator itrBegin = str.begin();
        string::const_iterator itrEnd = str.end();
        while(regex_search(itrBegin, itrEnd, res, reg)){
            if(res[0].matched){
                string str1 = res[0].str();
                printf("search0:%s\n",str1.c_str());
            }
//            {
//                string first = &res[0].first.operator*();
//                string second = &res[0].first.operator*();
//                printf("[0]first is \n%s\n",first.c_str());
//                printf("[0]second is \n%s\n",second.c_str());
//            }
//            {
//                string first = &res[1].first.operator*();
//                string second = &res[1].first.operator*();
//                printf("[1]first is \n%s\n",first.c_str());
//                printf("[1]second is \n%s\n",second.c_str());
//            }
//            if(res[1].matched){
//                string str1 = res[0].str();
//                printf("search1:%s\n",str1.c_str());
//            }
//            if(res[2].matched){
//                string str1 = res[0].str();
//                printf("search2:%s\n",str1.c_str());
//            }
            itrBegin = res[0].second;
        };
    }
};

#endif
