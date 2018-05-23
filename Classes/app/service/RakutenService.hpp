//
//  RakutenService.hpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/23.
//

#ifndef __rakuran__RakutenService__
#define __rakuran__RakutenService__

#include "cocos2d.h"

using namespace cocos2d;

class RakutenService
{
  public:
    RakutenService(const RakutenService&) = delete;               //コピーコンストラクタを delete 指定
    RakutenService& operator=(const RakutenService&) = delete;    //コピー代入演算子も delete 指定
    RakutenService(RakutenService&&)                 = delete;    //ムーブコンストラクタを delete 指定
    RakutenService&        operator=(RakutenService&&) = delete;  //ムーブ代入演算子も delete 指定
    static RakutenService* getInstance();
    static void            destroy();
    static RakutenService* _instance;

  private:
    RakutenService();
    virtual ~RakutenService(){};
};

#endif /* defined(__rakuran__RakutenService__) */
