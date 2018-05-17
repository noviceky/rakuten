//
//  SampleService.cpp
//  rakuran
//
//  Created by Choshi on 02/26/18.
//
//

#include "SampleService.hpp"
#include "AppMacro.h"
#include "SampleDTO.h"

#include "picojson.h"

SampleService* SampleService::_instance = NULL;

SampleService::SampleService()
{
}

SampleService* SampleService::getInstance()
{
    if (NULL == _instance)
    {
        _instance = new SampleService();
    }
    return _instance;
}

void SampleService::destory()
{
    delete _instance;
    _instance = nullptr;
}

const std::vector<SampleDTO> SampleService::getSampleListInfo()
{
    // min,maxの範囲の乱数を取得するラムダ
    auto getRandomReal = [](const float min, const float max) {
        std::random_device rnd;        // 非決定的な乱数生成器でシード生成機を生成
        std::mt19937       mt(rnd());  //  メルセンヌツイスターの32ビット版、引数は初期シード
        std::uniform_real_distribution<float> randFactor(std::min<float>(min, max), std::max<float>(min, max));
        return randFactor(mt);
    };

    std::vector<SampleDTO> list;

    for (int i = 1; i <= 20; ++i)
    {
        SampleDTO dto;
        dto.idx            = i;
        dto.listItemHeight = getRandomReal(50, 200);
        dto.title          = cocos2d::StringUtils::format("idx[%d] height[%.2f]", dto.idx, dto.listItemHeight);
        list.push_back(dto);
    }

    return list;
}

const std::vector<SampleDTO> SampleService::getSampleListInfoFromJson()
{
    std::vector<SampleDTO> list;

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

        SampleDTO dto;
        dto.idx            = static_cast<int>(info["idx"].get<double>());
        dto.listItemHeight = static_cast<float>(data["listItemHeight"].get<double>());
        dto.title          = data["title"].get<std::string>();

        list.push_back(dto);
    }

    return list;
}
