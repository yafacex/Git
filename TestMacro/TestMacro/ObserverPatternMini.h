//
//  ObserverPatternMini.h
//  DragonEmpire
//
//  Created by yafacex on 14-3-14.
//
//

#ifndef __DragonEmpire__ObserverPatternMini__
#define __DragonEmpire__ObserverPatternMini__

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

namespace ObserverNS {
    
    /**
     * def observer
     */
    template <typename MSG_TYPE>
    class IObserver{
    public:
        IObserver(){};
        ~IObserver(){};
        
        virtual void onMsgSend(MSG_TYPE& msg){};
    };
    /**
     * type finder
     */
//    template<typename U,typename...Ts>
//    struct find_convertible{};
//    template<typename U,typename V,typename... Ts>
//    struct find_convertible<U, V,Ts...>:
//    std::conditional<
//    std::is_constructible<U, V>::value,
//    std::common_type<V>,
//    find_convertible<U, Ts...>>::type{};

    /**
     * list observer
     */
    template <typename... Msgs>
    class IObserverList:public IObserver<Msgs>...{
//        template <typename OneMsg>
//         void onGetMsg(const OneMsg& msg){
//            typedef typename find_convertible<OneMsg,Msgs...>::type ResMsg;
//            IObserver<ResMsg>::onMsgSend(msg);
//        }
    };
    /**
     * def subject
     */
    template <typename MSG_TYPE>
    class Subject{
    public:
        virtual ~Subject(){};
        typedef list<ObserverNS::IObserver<MSG_TYPE> * > Observer_List;
    public:
        void attach(IObserver<MSG_TYPE>& observer){
            typename Observer_List::iterator itr =
            find(mObservers.begin(), mObservers.end(), &observer);
            
            if (mObservers.end() == itr) {
                mObservers.push_back(&observer);
            }
        };
        void detach(IObserver<MSG_TYPE>& observer){
            typename Observer_List::iterator itr =
            find(mObservers.begin(), mObservers.end(), &observer);
            
            if (mObservers.end() != itr) {
                mObservers.erase(itr);
            }
        };
        
        void notify(MSG_TYPE& msg){
            
            typename Observer_List::iterator itr = mObservers.begin();
            for( ; mObservers.end() != itr ; ++itr){
                (*itr)->onMsgSend((msg));
            }
        };
    private:
        Observer_List mObservers;
    };
    /**
     * list subject
     */
    template <typename... Msgs>
    class SubjectList:public Subject<Msgs>...{
    public:
        SubjectList(){};
        virtual ~SubjectList(){};
        template <typename OneMsg>
        void attach(IObserver<OneMsg>& observer){
            Subject<OneMsg>::attach(observer);
        }
        template <typename OneMsg>
        void detach(IObserver<OneMsg>& observer){
            Subject<OneMsg>::detach(observer);
        }
        template <typename OneMsg>
        void notify(OneMsg& msg){
            Subject<OneMsg>::notify(msg);
        }
    };
}

#endif /* defined(__DragonEmpire__ObserverPatternMini__) */
