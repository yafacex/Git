//
//  SkillCfg.h
//  TestSpirit
//
//  Created by yafacex on 14-8-5.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef __TestSpirit__SkillCfg__
#define __TestSpirit__SkillCfg__

#include <iostream>
#include <boost/unordered_map.hpp>
using namespace std;
using namespace boost;


namespace Skill {

    enum Attr{
        hp = 0,
        movespd,
        attackspd
    };
    
    enum OP{
        mul = attackspd + 1,
        add
    };
    
    enum Feature{
        nearest = add + 1,
        farest,
        in,
        out,
        leastHp,
        mostHp,
        
        alien,
        enemy,
        soldier,
        hero,
        character,
        me,
    };
    
    enum Timer{
        every_n_sec_delay =me +1,
        rightnow
    };
    
    class TimerRule{
    public:
        Timer timer;
        float sec;
        int times;
    };
    
    class DataRule{
    public:
        Attr attr;
        OP op;
        vector<float>* dataSet;
    };
    
    class ClusterFeature{
    public:
        typedef struct FeatureData_{
            Feature feature;
            float data;
        }FeatureData;
        void addFeature(Feature feature,float data){
            FeatureData* fd = new FeatureData();
            fd->feature = feature;
            fd->data = data;
            m_features.push_back(fd);
        };
        vector<FeatureData*>* getFeatures(){
            return &m_features;
        };
    protected:
        vector<FeatureData*> m_features;
    };
   
#define COMMON_ARGS char const* l,char const* r
#define DBG_CONTENT\
    std::string _str(l,r);\
    std::cout << "Content:"<<std::endl<<_str << std::endl << "End" << std::endl;
    
    class SkillCfg{
    public:
        typedef struct SkillDb_{
            ClusterFeature* clusterFeature;
            TimerRule* timerRule;
            DataRule* dataRule;
            float waitForSec;
        }SkillDb;
    public:
        SkillCfg():mCurCluster(NULL),mCurDataRule(NULL),mCurTimerRule(NULL),mWaitForSec(0){
        };
        void createCluster();
        void setClusterRelationShip(int alienOrEnemy);
        void setClusterHeroBuilingSoldier(int whatKind);
        void setClusterRange(int range,float grid);
        void setClusterHpRange(int range);
        
        void createDataRule();
        void setDataRuleTarget(int attr);
        void setDataRuleOp(int op);
        void setDataRuleDatas(string key);
        
        void createTimerRule();
        void setTimerRuleRightNow();
        
        void setTimerRuleCycle(int times,float sec);
        void setWaitForSec(float sec);
        
        void skillCombine();
        
        void skillParse();
    protected:
        ClusterFeature* mCurCluster;
        DataRule* mCurDataRule;
        TimerRule* mCurTimerRule;
        float mWaitForSec;
        
        vector<SkillDb*> mSkillDbs;
    };
}

#endif /* defined(__TestSpirit__SkillCfg__) */
