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
    : _rakutenAppID("")
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
void RakutenService::requestGetRakutenRanking(getRankingResultCallback callback)
{
    TRACE;
    auto        request = new HttpRequest();
    std::string url     = API_RANKING_URL + _rakutenAppID;
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([=](HttpClient* client, HttpResponse* response) {
        log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
        if (response->isSucceed())
        {
            std::vector<RankInfoDTO> list;
            for (int i = 1; i <= 20; ++i)
            {
                RankInfoDTO dto;
                dto.idx   = i;
                dto.rank  = i + 1;
                dto.title = cocos2d::StringUtils::format("idx[%d]", dto.idx);
                list.push_back(dto);
            }
            callback(list);
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
    _rakutenAppID        = fileUtils->getStringFromFile(filePath);
    LOG("_rakutenAppID = %s", _rakutenAppID.c_str());
}
