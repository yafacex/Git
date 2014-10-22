//
//  ProgData.h
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__ProgData__
#define __TestSpirit__ProgData__

#include <iostream>
#include <boost/unordered_map.hpp>
using namespace std;
using namespace boost;

class Description{
public:
    string name;
    string effect;
};
class Table{
public:
    Table():curAttr(""),bRecording(false){
    }
    void startRecord(string attr){
        bRecording = true;
        curAttr = attr;
    }
    void endRecord(){
        bRecording = false;
    }
    void record(float data){
        if(m_tableData.find(curAttr) == m_tableData.end()){
            m_tableData[curAttr] = new vector<float>();
        }
        m_tableData[curAttr]->push_back(data);
    }
    vector<float>* getDatasByAttr(string attrName){
        if(m_tableData.find(attrName) == m_tableData.end()){
            cout << "Table Item Not Exist=> "<<attrName<<endl;
            assert(false);
        }
        return m_tableData[attrName];
    };
protected:
    bool bRecording;
    string curAttr;
    unordered_map<string, vector<float>* > m_tableData;
};
#endif /* defined(__TestSpirit__ProgData__) */
