//
//  PartsMainScene.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/17.
//

#include "PartsMainScene.hpp"
#include "AppMacro.h"

namespace
{
// 無名名前空間

const char* CSB_HEADER_NAME    = "header.csb";
const char* CSB_FOOTER_NAME    = "footer.csb";
const float ANIMATION_INTERVAL = 3.0f;
}  // namespace

PartsMainScene::PartsMainScene()
    : _csbHeader(nullptr)
    , _csbFooter(nullptr)
{
    // constructor
    TRACE;
}

PartsMainScene::~PartsMainScene()
{
    // destructor
    TRACE;
}

bool PartsMainScene::init()
{
    TRACE;
    auto ret = Node::init();
    if (ret)
    {
        initUI();
    }
    return true;
}

void PartsMainScene::onEnter()
{
    TRACE;
    Node::onEnter();
}

void PartsMainScene::onEnterTransitionDidFinish()
{
    TRACE;
    Node::onEnterTransitionDidFinish();
}

void PartsMainScene::onExit()
{
    TRACE;
    Node::onExit();

    this->unscheduleUpdate();
}

void PartsMainScene::onExitTransitionDidStart()
{
    TRACE;
    Node::onExitTransitionDidStart();
}

void PartsMainScene::update(float delta)
{
    // ここでTRACEログ出力すると、毎フレームログ出力されるのでコメントアウト
    //    TRACE;
    Node::update(delta);
}

void PartsMainScene::initUI()
{
    TRACE;
    // csbファイルのロード処理
    _csbHeader = CSLoader::getInstance()->createNodeWithFlatBuffersFile(CSB_HEADER_NAME);
    _csbFooter = CSLoader::getInstance()->createNodeWithFlatBuffersFile(CSB_FOOTER_NAME);

    this->addChild(_csbHeader);
    this->addChild(_csbFooter);

    _csbHeader->setAnchorPoint(Vec2::ANCHOR_TOP_LEFT);
    _csbFooter->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _csbHeader->setPosition(Size(0, MAIN_VIEW_HEIGHT));
    _csbFooter->setPosition(Size(0, 0));
    // thisのコンテンツサイズを_MAIN_VIEW_SIZEに合わせる
    this->setContentSize(MAIN_VIEW_SIZE);
}
