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
    
    TestRegex(){
        locMap res,searched;
        TestRegex::heuristicSearch2d(3, 4, res,searched, 4, cao);
    };
    ~TestRegex(){};
    void test(){
        boost::regex reg("\\d{3}([a-zA-Z]+).(\\d{2}|N/A)\\s\\1");
        std::string correct="123Hello N/A Hello";
        std::string incorrect="123Hello 12 hello";
        assert(boost::regex_match(correct,reg)==true);
        assert(boost::regex_match(incorrect,reg)==false);
        
    };
};

#endif
