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

void RakutenService::loadRakutenAppID()
{
    TRACE;
    FileUtils* fileUtils = FileUtils::getInstance();
    auto       filePath  = fileUtils->fullPathForFilename(ID_FILE_NAME);
    _rakutenAppID        = fileUtils->getStringFromFile(filePath).c_str();
    LOG("_rakutenAppID = %s", _rakutenAppID);
}
