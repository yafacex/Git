//
//  FilterActNode.cpp
//  TestSpirit
//
//  Created by yafacex on 14-8-6.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#include "FilterActNode.h"
using namespace Skill;


//enum Feature{
//    nearest = add + 1,
//    farest,
//    in,
//    out,
//    leastHp,
//    mostHp,
//    
//    alien,
//    enemy,
//    soldier,
//    hero,
//    character,
//};

//void ArmManager::getSplashTargetBuildings(std::vector<CCGameObject*>& resArr,CCPoint centerIsoPt,float gridRange,GameObjectType gameObjectType,CharacterAttackOrDefence attackOrDefence,std::vector<CCGameObject*>* elseArr)
ACT_STATUS FilterActNode::execute(){
    if (mFeature && mResult) {
        vector<ClusterFeature::FeatureData*>* features = mFeature->getFeatures();
        for (vector<ClusterFeature::FeatureData*>::iterator itr = features->begin();
             itr != features->end(); ++itr) {
            switch ((*itr)->feature) {
                case nearest:
                    /*
                     [step-3]
                     copy BattleAI code
                     **/
                    break;
                case farest:
                    break;
                    /**
                     [step-2]
                     call ArmManager->getSplash....
                     in => resArr
                     out => elseArr
                     */
                case in:
                    break;
                case out:
                    break;
                case leastHp:
                    break;
                case mostHp:
                    break;
                    
                /**
                 [step-1]
                 define GameObjectType and CharacterAttackOrDefence and Relationship
                 determine CCCharacterVectorArray
                 **/
                case alien:
                    break;
                case enemy:
                    break;
                case soldier:
                    break;
                case hero:
                    break;
                case character:
                    break;
                case me:
                    mResult->push_back(mOwner);
                    break;
                default:
                    break;
            }
        }
    }
    return AS_Success;
}