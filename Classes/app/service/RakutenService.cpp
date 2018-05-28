//
//  RakutenService.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/23.
//

#include "RakutenService.hpp"
#include "AppMacro.h"

#include "picojson.h"

namespace
{
const char* ID_FILE_NAME = "id.txt";
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
 * TODO
 * 一旦ダミー実装
 */
const std::vector<RankInfoDTO> RakutenService::getRankInfoDTOList()
{
    TRACE;
    // min,maxの範囲の乱数を取得するラムダ
    auto getRandomReal = [](const float min, const float max) {
        std::random_device rnd;        // 非決定的な乱数生成器でシード生成機を生成
        std::mt19937       mt(rnd());  //  メルセンヌツイスターの32ビット版、引数は初期シード
        std::uniform_real_distribution<float> randFactor(std::min<float>(min, max), std::max<float>(min, max));
        return randFactor(mt);
    };

    std::vector<RankInfoDTO> list;

    for (int i = 1; i <= 30; ++i)
    {
        RankInfoDTO dto;
        dto.idx   = i;
        dto.rank  = getRandomReal(1, 30);
        dto.title = cocos2d::StringUtils::format("idx[%d] rank[%d]", dto.idx, dto.rank);
        list.push_back(dto);
    }

    return list;
}

const std::vector<RankInfoDTO> RakutenService::getRankInfoDTOListFromJSON()
{
    std::vector<RankInfoDTO> list;

    // sample.jsonファイル読み出し
    auto        data = FileUtils::getInstance()->getDataFromFile("sample.json");
    const char* json = (const char*)(data.getBytes());
    ssize_t     size = data.getSize();

    picojson::value v;
    std::string     err;

    // picojsonでパース
    picojson::parse(v, json, json + size, &err);

    if (!err.empty())
    {
        // パース失敗した場合は、空リストデータを返す
        return list;
    }

    // ルート階層のオブジェクトを取得
    picojson::object& root = v.get<picojson::object>();

    picojson::array& array = root["array"].get<picojson::array>();

    for (auto o : array)
    {
        picojson::object& info = o.get<picojson::object>();
        picojson::object& data = info["data"].get<picojson::object>();

        RankInfoDTO dto;
        dto.idx   = static_cast<int>(info["idx"].get<double>());
        dto.rank  = static_cast<float>(data["listItemHeight"].get<double>());
        dto.title = data["title"].get<std::string>();

        list.push_back(dto);
    }

    return list;
}

void RakutenService::rakutenAPIRequest()
{
    auto request = new HttpRequest();
    std::string url = "https://qiita-image-store.s3.amazonaws.com/0/7063/2903f4b7-a428-2105-574e-f6f6b0e041db.jpeg";
    request->setUrl(url.c_str());
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback([this](HttpClient* client, HttpResponse* response){
        
        log("responseCode:%ld %s", response->getResponseCode(), response->getHttpRequest()->getUrl());
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        
        auto fileUtils = FileUtils::getInstance();
        std::string filename = fileUtils->getWritablePath() + "hoge.jpg";
        
        if (fileUtils->isFileExist(filename)) {
            
            auto sprite = Sprite::create(filename.c_str());
            sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
            this->addChild(sprite, 0);
            
        } else if (response->isSucceed()) {
            
            std::vector<char>* buffer = response->getResponseData();
            auto* img = new Image();
            img->initWithImageData(reinterpret_cast<unsigned char*>(&(buffer->front())), buffer->size());
            img->saveToFile(filename.c_str());
            auto* texture = new Texture2D();
            texture->initWithImage(img);
            auto sprite = Sprite::createWithTexture(texture);
            sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
            this->addChild(sprite, 0);
            
        }
        
    });
    
    auto client = HttpClient::getInstance();
    client->enableCookies(NULL);
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
