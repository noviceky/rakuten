//
//  RakutenService.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/23.
//

#include "RakutenService.hpp"
#include "AppMacro.h"

RakutenService* RakutenService::_instance = nullptr;

RakutenService::RakutenService()
{
}

RakutenService* RakutenService::getInstance()
{
    if (NULL == _instance)
    {
        _instance = new RakutenService();
    }
    return _instance;
}

void RakutenService::destroy()
{
}
