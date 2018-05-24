//
//  PartsMainScene.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/17.
//

#include "PartsMainScene.hpp"
#include "AppMacro.h"
#include "RakutenService.hpp"
#include "PartsTableView.hpp"

namespace
{
// 無名名前空間

const char* CSB_HEADER_NAME      = "header.csb";
const char* CSB_FOOTER_NAME      = "footer.csb";
const char* BUTTON_HEADLINE_NAME = "btn_headline";
const char* BUTTON_LIST_NAME     = "btn_list";
const char* BUTTON_MODULE_NAME   = "btn_module";
const char* BUTTON_ARRAY_NAME    = "btn_array";
const char* BUTTON_SETTING_NAME  = "btn_setting";
const Size kTableViewContentSize = MAIN_VIEW_SIZE - Size(20.f, 300.f);
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
    
    //TableViewの配置
    auto ui = PartsTableView::create(kTableViewContentSize);
    ui->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    ui->setPosition(MAIN_VIEW_SIZE / 2);
    ui->setOnSelected([=](const int idx) { MessageBox(("idx[" + std::to_string(idx) + "]").c_str(), "onSelected"); });
    this->addChild(ui);
    
    auto RankInfoDTOList = RakutenService::getInstance()->getRankInfoDTOList();
    ui->setRankInfoDTOList(RankInfoDTOList);
    
    this->addChild(_csbHeader);
    this->addChild(_csbFooter);
}

/**
  * タッチイベント取得共通部分
  * @param {Node *} csb ヘッダかフッタの参照
  * @param {const char*} buttonName ボタン要素の名前
  */
void PartsMainScene::listenButton(Node* csb, const char* buttonName)
{
    //タッチイベント取得
    auto button = csb->getChildByName<ui::Button*>(buttonName);

    button->addTouchEventListener([=](Ref* ref, Widget::TouchEventType eventType) {
        if (eventType != Widget::TouchEventType::ENDED)
        {
            return;
        }
        //タッチが終わったら
        LOG("%s Pressed", buttonName);
    });
}

void PartsMainScene::listenHeaderButton()
{
    listenButton(_csbHeader, BUTTON_HEADLINE_NAME);
}

void PartsMainScene::listenFooterList()
{
    listenButton(_csbFooter, BUTTON_LIST_NAME);
}

void PartsMainScene::listenFooterModule()
{
    listenButton(_csbFooter, BUTTON_MODULE_NAME);
}

void PartsMainScene::listenFooterArray()
{
    listenButton(_csbFooter, BUTTON_ARRAY_NAME);
}

void PartsMainScene::listenFooterSetting()
{
    listenButton(_csbFooter, BUTTON_SETTING_NAME);
}
