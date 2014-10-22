//
//  hash.h
//  TestOpenglView
//
//  Created by yafacex on 14-4-4.
//  Copyright (c) 2014年 yafacex. All rights reserved.
//

#ifndef TestOpenglView_hash_h
#define TestOpenglView_hash_h

#define HashMapVecLen 31

typedef struct hashList_{
    void * ptr;
    struct * next;
}hashList;

typedef struct hashMap_{
    hashList (*vec)[15];
}hashMap;

class HashMap{
public:
    inline int getStringKeyTimes33(char *str){
        int i = 0;
        int hashKey =0;
        while (*(str + i) != '\0') {
            hashKey += hashKey<<5 + *(str + i);
        }
        return hashKey;
    }
    
    inline void hashMapInsert(char *strKey,void* contentPtr){
        int key = getStringKeyTimes33(strKey) % 15;
        if (NULL == mMap.vec[key]) {
            mMap.vec[key] = contentPtr;
        }
    }
protected:
    hashMap mMap;
}



#endif
