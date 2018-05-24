//
//  PartsTableViewCell.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/24.
//

#include "PartsTableViewCell.hpp"
#include "AppMacro.h"
#include "const.h"

namespace
{
    const float kFontSize = 24;
}  // namespace

PartsSampleTableViewCell::PartsSampleTableViewCell()
{
    // constructor
    TRACE;
}

PartsSampleTableViewCell::~PartsSampleTableViewCell()
{
    // destructor
    TRACE;
}

bool PartsSampleTableViewCell::init()
{
    TRACE;
    return Layout::init();
}

void PartsSampleTableViewCell::onEnter()
{
    TRACE;
    Layout::onEnter();
}

void PartsSampleTableViewCell::onEnterTransitionDidFinish()
{
    TRACE;
    Layout::onEnterTransitionDidFinish();
}

void PartsSampleTableViewCell::onExit()
{
    TRACE;
    Layout::onExit();
    
    this->unscheduleUpdate();
}

void PartsSampleTableViewCell::onExitTransitionDidStart()
{
    TRACE;
    Layout::onExitTransitionDidStart();
}

void PartsSampleTableViewCell::initWithViewCellInfo(const int idx, const Size& size, const std::string& title)
{
    // 背景サイズ設定
    this->setContentSize(size);
    // 背景色設定（偶数なら青、奇数なら緑）
    this->setBackGroundColorType(BackGroundColorType::SOLID);
    this->setBackGroundColor(idx % 2 ? Color3B::BLUE : Color3B::GREEN);
    this->setBackGroundColorOpacity(100);
    
    // タイトル文言設定
    auto text = Text::create(title, rakuran::fontName, kFontSize);
    text->setTextColor(Color4B::RED);
    text->setTextVerticalAlignment(TextVAlignment::CENTER);
    text->setTextHorizontalAlignment(TextHAlignment::CENTER);
    text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    text->setPosition(size / 2);
    this->addChild(text);
}
