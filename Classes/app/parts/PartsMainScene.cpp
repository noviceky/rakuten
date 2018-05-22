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

const char* CSB_HEADER_NAME      = "header.csb";
const char* CSB_FOOTER_NAME      = "footer.csb";
std::string BOTTON_HEADLINE_NAME = "btn_headline";
std::string BOTTON_LIST_NAME     = "btn_list";
std::string BOTTON_MODULE_NAME   = "btn_module";
std::string BOTTON_ARRAY_NAME    = "btn_array";
std::string BOTTON_SETTING_NAME  = "btn_setting";
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

    listenHeaderButton();
    listenFooterList();
    listenFooterModule();
    listenFooterArray();
    listenFooterSetting();
}

/**
  * タッチイベント取得共通部分
  * @param {Node *} csb ヘッダかフッタの参照
  * @param {std::string} buttonName ボタン要素の名前
  */
void PartsMainScene::listenButton(Node* csb, std::string buttonName)
{
    //タッチイベント取得
    auto button = csb->getChildByName<ui::Button*>(buttonName);

    button->addTouchEventListener([=](Ref* ref, Widget::TouchEventType eventType) {
        if (eventType != Widget::TouchEventType::ENDED)
        {
            return;
        }
        //タッチが終わったら
        LOG("%s Pressed", buttonName.c_str());
    });
}

void PartsMainScene::listenHeaderButton()
{
    listenButton(_csbHeader, BOTTON_HEADLINE_NAME);
}

void PartsMainScene::listenFooterList()
{
    listenButton(_csbFooter, BOTTON_LIST_NAME);
}

void PartsMainScene::listenFooterModule()
{
    listenButton(_csbFooter, BOTTON_MODULE_NAME);
}

void PartsMainScene::listenFooterArray()
{
    listenButton(_csbFooter, BOTTON_ARRAY_NAME);
}

void PartsMainScene::listenFooterSetting()
{
    listenButton(_csbFooter, BOTTON_SETTING_NAME);
}
