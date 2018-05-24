//
//  PartsTableViewCell.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/24.
//

#include "PartsTableViewCell.hpp"
#include "AppMacro.h"
#include "const.h"
#include <string.h>

namespace
{
const float kFontSize         = 24;
const char* CSB_ITEM_NAME     = "list_item_s.csb";
const char* LAYOUT_PANEL_NAME = "panel";
const char* TEXT_RANK_NAME    = "rank";
const char* TEXT_TITLE_NAME   = "title";
}  // namespace

PartsTableViewCell::PartsTableViewCell()
    : _csbItem(nullptr)
{
    // constructor
    TRACE;
}

PartsTableViewCell::~PartsTableViewCell()
{
    // destructor
    TRACE;
}

bool PartsTableViewCell::init()
{
    TRACE;
    return Layout::init();
}

void PartsTableViewCell::onEnter()
{
    TRACE;
    Layout::onEnter();
}

void PartsTableViewCell::onEnterTransitionDidFinish()
{
    TRACE;
    Layout::onEnterTransitionDidFinish();
}

void PartsTableViewCell::onExit()
{
    TRACE;
    Layout::onExit();

    this->unscheduleUpdate();
}

void PartsTableViewCell::onExitTransitionDidStart()
{
    TRACE;
    Layout::onExitTransitionDidStart();
}

void PartsTableViewCell::initWithViewCellInfo(const int idx, const Size& size, const int rank, const std::string& title)
{
    // csbファイルのロード処理
    _csbItem = CSLoader::getInstance()->createNodeWithFlatBuffersFile(CSB_ITEM_NAME);
    _csbItem->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    // 背景サイズ設定
    this->setContentSize(size);

    // タイトル文言設定 labelだがText*型
    auto panel     = _csbItem->getChildByName<Layout*>(LAYOUT_PANEL_NAME);
    auto rankText  = panel->getChildByName<ui::Text*>(TEXT_RANK_NAME);
    auto titleText = panel->getChildByName<ui::Text*>(TEXT_TITLE_NAME);

    rankText->setString(std::to_string(rank));
    titleText->setString(title);

    this->addChild(_csbItem);
}
