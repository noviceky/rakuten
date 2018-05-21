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
    _partsScene = PartsMainScene::create();
    this->addChild(_partsScene);
}
