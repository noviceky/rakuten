//
//  MainScene.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/18.
//

#include "MainScene.hpp"
#include "AppMacro.h"
#include "PartsMainScene.hpp"

MainScene* MainScene::createScene()
{
    TRACE;
    auto scene = new MainScene();
    scene->autorelease();
    scene->init();
    return scene;
}

MainScene::MainScene()
    : _partsScene(nullptr)
{
    // constructor
    TRACE;
}

MainScene::~MainScene()
{
    // destructor
    TRACE;
}

bool MainScene::init()
{
    TRACE;
    auto ret = Scene::init();
    if (ret)
    {
        initUI();
    }
    return true;
}

void MainScene::onEnter()
{
    TRACE;
    Scene::onEnter();
}

void MainScene::onEnterTransitionDidFinish()
{
    TRACE;
    Scene::onEnterTransitionDidFinish();

    //    if (_partsScene)
    //    {
    //        _partsScene->startLoadingAnimation();
    //    }
    //    this->scheduleOnce(
    //                       [=](float delta) {
    //                           // TODO: ここに次画面への遷移処理を実装する
    //                       },
    //                       3.0f, "delay_replace_scene");
}

void MainScene::onExit()
{
    TRACE;
    Scene::onExit();
}

void MainScene::onExitTransitionDidStart()
{
    TRACE;
    Scene::onExitTransitionDidStart();
}

void MainScene::initUI()
{
    TRACE;
    this->setContentSize(MAIN_VIEW_SIZE);
    _partsScene = PartsMainScene::create();
    this->addChild(_partsScene);

    this->cocos2d::Node::setPosition(Vec2::ANCHOR_TOP_LEFT);
#if DEBUG_MENU_ENABLE
    // サンプルメニューへの導線表示追加
    {
        //        auto panel = Layout::create();
        //        panel->setContentSize(Size(200.f, 100.f));
        //        panel->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
        //        panel->setBackGroundColorOpacity(100);
        //        panel->setBackGroundColor(Color3B::GRAY);
        //        panel->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
        //        panel->cocos2d::Node::setPosition(Vec2(MAIN_VIEW_WIDTH - 20.f, 20.f));
        //        panel->setTouchEnabled(true);
        //        panel->addTouchEventListener([=](Ref* ref, Widget::TouchEventType eventType) {
        //            if (eventType != Widget::TouchEventType::ENDED)
        //            {
        //                return;
        //            }
        //
        //            //            // サンプルのメニュー画面へ遷移
        //            //            auto scene      = SampleDebugMenuScene::createScene();
        //            //            auto transition = TransitionFade::create(1.0f, scene, Color3B::WHITE);
        //            //            Director::getInstance()->replaceScene(transition);
        //        });
        //        this->addChild(panel);

        //        auto label = Label::createWithSystemFont("Sample", "Helvetica-Bold", 24);
        //        label->setTextColor(Color4B::WHITE);
        //        label->setVerticalAlignment(TextVAlignment::CENTER);
        //        label->setHorizontalAlignment(TextHAlignment::CENTER);
        //        label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        //        label->setPosition(panel->getContentSize() / 2);
        //        panel->addChild(label);
    }
#endif
}
