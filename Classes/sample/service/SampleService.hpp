//
//  SampleService.hpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#ifndef __rakuran__SampleService__
#define __rakuran__SampleService__

#include "cocos2d.h"

using namespace cocos2d;

struct SampleDTO;

class SampleService
{
  public:
    static SampleService* getInstance();
    static void           destory();

    const std::vector<SampleDTO> getSampleListInfo();
    const std::vector<SampleDTO> getSampleListInfoFromJson();

  private:
    static SampleService* _instance;
    SampleService();
    virtual ~SampleService(){};
};

#endif /* defined(__rakuran__SampleService__) */
