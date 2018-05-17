//
//  AppMacro.h
//  rakuran
//
//  Created by 工藤陸 on 03/06/20
//
//

#include "PartsLoadingScene.hpp"
#include "AppMacro.h"

namespace
{
// 無名名前空間
// ここに宣言した内容は、このファイル内だけで有効

const char* CSB_NAME           = "loading_scene.csb";
const float ANIMATION_INTERVAL = 3.0f;
const char* LOADING_STRING[3]  = {"Loading.", "Loading..", "Loading..."};
}  // namespace

PartsLoadingScene::PartsLoadingScene()
    : _csb(nullptr)
    , _loadingText(nullptr)
    , _elapsed(0.f)
{
    // constructor
    TRACE;
}

PartsLoadingScene::~PartsLoadingScene()
{
    // destructor
    TRACE;
}

bool PartsLoadingScene::init()
{
    TRACE;
    auto ret = Node::init();
    if (ret)
    {
        initUI();
    }
    return true;
}

void PartsLoadingScene::onEnter()
{
    TRACE;
    Node::onEnter();
}

void PartsLoadingScene::onEnterTransitionDidFinish()
{
    TRACE;
    Node::onEnterTransitionDidFinish();
}

void PartsLoadingScene::onExit()
{
    TRACE;
    Node::onExit();

    this->unscheduleUpdate();
}

void PartsLoadingScene::onExitTransitionDidStart()
{
    TRACE;
    Node::onExitTransitionDidStart();
}

void PartsLoadingScene::update(float delta)
{
    // ここでTRACEログ出力すると、毎フレームログ出力されるのでコメントアウト
    //    TRACE;
    Node::update(delta);
    updateLoadingText(delta);
}

void PartsLoadingScene::initUI()
{
    TRACE;
    // csbファイルのロード処理
    _csb = CSLoader::getInstance()->createNodeWithFlatBuffersFile(CSB_NAME);
    this->addChild(_csb);

    // thisのコンテンツサイズを_csbに合わせる
    this->setContentSize(_csb->getContentSize());

    // "Loading..."表示するTextノード初期設定
    initLoadingTextNode();
}

void PartsLoadingScene::initLoadingTextNode()
{
    TRACE;
    // _csbから"Loading..."を表示するTextノードを取得
    _loadingText = _csb->getChildByName<Text*>("text");

    // 表示位置を変えずにテキストのアンカーポイントを左下基準に変える
    auto boundingBox = _loadingText->getBoundingBox();
    _loadingText->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _loadingText->setPosition(Vec2(boundingBox.getMinX(), boundingBox.getMidY()));

    // テキストのアライメントを左基準に変更
    _loadingText->setTextHorizontalAlignment(TextHAlignment::LEFT);
}

void PartsLoadingScene::startLoadingAnimation()
{
    TRACE;
    // 経過時間リセット
    _elapsed = 0.f;

    // Node::scheduleUpdateを呼び出すことで、毎フレーム毎にNode::update()が呼び出されるようになる
    this->scheduleUpdate();
}

void PartsLoadingScene::updateLoadingText(float delta)
{
    // ここでTRACEログ出力すると、毎フレームログ出力されるのでコメントアウト
    //    TRACE;
    CCASSERT(_loadingText, "_loadingText is nullptr");

    _elapsed += delta;

    if (ANIMATION_INTERVAL < _elapsed)
    {
        _elapsed = 0.f;
    }

    auto percent = _elapsed / ANIMATION_INTERVAL;

    if (percent <= 0.33f)
    {
        _loadingText->setString(LOADING_STRING[0]);
    }
    else if (percent <= 0.66f)
    {
        _loadingText->setString(LOADING_STRING[1]);
    }
    else
    {
        _loadingText->setString(LOADING_STRING[2]);
    }
}
