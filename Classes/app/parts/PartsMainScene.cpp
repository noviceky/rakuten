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
// ここに宣言した内容は、このファイル内だけで有効

const char* CSB_HEADER_NAME = "header.csb";
//const char* CSB_BODY_NAME           = "body.csb";
const char* CSB_FOOTER_NAME    = "footer.csb";
const float ANIMATION_INTERVAL = 3.0f;
//const char* LOADING_STRING[3]  = {"Loading.", "Loading..", "Loading..."};
}  // namespace

PartsMainScene::PartsMainScene()
    : _csbHeader(nullptr)
    , _csbFooter(nullptr)
    , _csbBody(nullptr)
    , _loadingText(nullptr)
    , _elapsed(0.f)
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
    updateLoadingText(delta);
}

void PartsMainScene::initUI()
{
    TRACE;
    // csbファイルのロード処理
    _csbHeader = CSLoader::getInstance()->createNodeWithFlatBuffersFile(CSB_HEADER_NAME);
    _csbFooter = CSLoader::getInstance()->createNodeWithFlatBuffersFile(CSB_FOOTER_NAME);

    this->setContentSize(Size(MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT));
    this->setPosition(Vec2::ANCHOR_BOTTOM_LEFT);

    this->addChild(_csbHeader);
    this->addChild(_csbFooter);

    _csbHeader->setPosition(Vec2::ANCHOR_TOP_LEFT);
    _csbFooter->setPosition(Vec2::ANCHOR_BOTTOM_LEFT);
    // thisのコンテンツサイズを_csbに合わせる
    this->setContentSize(_csbHeader->getContentSize());
    this->setContentSize(_csbFooter->getContentSize());

    // "Loading..."表示するTextノード初期設定
    //initLoadingTextNode();
}

void PartsMainScene::initLoadingTextNode()
{
    TRACE;
    // _csbから"Loading..."を表示するTextノードを取得
    //    _loadingText = _csb->getChildByName<Text*>("text");
    //
    //    // 表示位置を変えずにテキストのアンカーポイントを左下基準に変える
    //    auto boundingBox = _loadingText->getBoundingBox();
    //    _loadingText->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    //    _loadingText->setPosition(Vec2(boundingBox.getMinX(), boundingBox.getMidY()));
    //
    //    // テキストのアライメントを左基準に変更
    //    _loadingText->setTextHorizontalAlignment(TextHAlignment::LEFT);
}

void PartsMainScene::startLoadingAnimation()
{
    TRACE;
    // 経過時間リセット
    _elapsed = 0.f;

    // Node::scheduleUpdateを呼び出すことで、毎フレーム毎にNode::update()が呼び出されるようになる
    this->scheduleUpdate();
}

void PartsMainScene::updateLoadingText(float delta)
{
    // ここでTRACEログ出力すると、毎フレームログ出力されるのでコメントアウト
    //    TRACE;
    //    CCASSERT(_loadingText, "_loadingText is nullptr");
    //
    //    _elapsed += delta;
    //
    //    if (ANIMATION_INTERVAL < _elapsed)
    //    {
    //        _elapsed = 0.f;
    //    }
    //
    //    auto percent = _elapsed / ANIMATION_INTERVAL;
    //
    //    if (percent <= 0.33f)
    //    {
    //        _loadingText->setString(LOADING_STRING[0]);
    //    }
    //    else if (percent <= 0.66f)
    //    {
    //        _loadingText->setString(LOADING_STRING[1]);
    //    }
    //    else
    //    {
    //        _loadingText->setString(LOADING_STRING[2]);
    //    }
}
