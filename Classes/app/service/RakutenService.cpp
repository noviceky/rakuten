//
//  RakutenService.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/23.
//

#include "RakutenService.hpp"
#include "AppMacro.h"
#include "picojson.h"

using namespace cocos2d::network;
namespace
{
const char* ID_FILE_NAME = "id.txt";
std::string API_RANKING_URL =
    "https://app.rakuten.co.jp/services/api/IchibaItem/Ranking/20170628?format=json&applicationId=";
}  // namespace

RakutenService* RakutenService::_instance = nullptr;

RakutenService::RakutenService()
    : _rakutenAppID(nullptr)
{
    // constructor
    TRACE;
    loadRakutenAppID();
}

RakutenService* RakutenService::getInstance()
{
    TRACE;
    if (NULL == _instance)
    {
        _instance = new RakutenService();
    }
    return _instance;
}

void RakutenService::destroy()
{
    TRACE;
}

/**
 *
 * 楽天ランキング情報リスト取得
 */
void RakutenService::requestGetRakutenRanking(dtoCallback callback)
{
    TRACE;
    std::vector<RankInfoDTO> list;
    auto        request = new HttpRequest();
    std::string url     = API_RANKING_URL + _rakutenAppID;
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([=](HttpClient* client, HttpResponse* response) {
        log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
        if (response->isSucceed())
        {
            std::vector<char>* json = response->getResponseData();
            callback();
        }
    });

    auto client = HttpClient::getInstance();
    client->enableCookies(nullptr);
    client->send(request);

}

void RakutenService::loadRakutenAppID()
{
    TRACE;
    FileUtils* fileUtils = FileUtils::getInstance();
    auto       filePath  = fileUtils->fullPathForFilename(ID_FILE_NAME);
    _rakutenAppID        = fileUtils->getStringFromFile(filePath).c_str();
    LOG("_rakutenAppID = %s", _rakutenAppID);
}
