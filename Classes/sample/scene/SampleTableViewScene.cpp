//
//  SampleTableViewScene.cpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#include "SampleTableViewScene.hpp"
#include "AppMacro.h"
#include "LoadingScene.hpp"
#include "PartsSampleTableView.hpp"
#include "SampleDTO.h"
#include "SampleService.hpp"

namespace
{
const Size kTableViewContentSize = MAIN_VIEW_SIZE - Size(20.f, 40.f);
}

SampleTableViewScene* SampleTableViewScene::createScene()
{
    TRACE;
    auto scene = new SampleTableViewScene();
    scene->autorelease();
    scene->init();
    return scene;
}

SampleTableViewScene::SampleTableViewScene()
{
    // constructor
    TRACE;
}

SampleTableViewScene::~SampleTableViewScene()
{
    // destructor
    TRACE;
}

bool SampleTableViewScene::init()
{
    TRACE;
    auto ret = Scene::init();
    if (ret)
    {
        initUI();
    }
    return true;
}

void SampleTableViewScene::onEnter()
{
    TRACE;
    Scene::onEnter();
}

void SampleTableViewScene::onEnterTransitionDidFinish()
{
    TRACE;
    Scene::onEnterTransitionDidFinish();
}

void SampleTableViewScene::onExit()
{
    TRACE;
    Scene::onExit();
}

void SampleTableViewScene::onExitTransitionDidStart()
{
    TRACE;
    Scene::onExitTransitionDidStart();
}

void SampleTableViewScene::initUI()
{
    TRACE;

    auto ui = PartsSampleTableView::create(kTableViewContentSize);
    ui->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    ui->setPosition(MAIN_VIEW_SIZE / 2);
    ui->setOnSelected([=](const int idx) { MessageBox(("idx[" + std::to_string(idx) + "]").c_str(), "onSelected"); });
    this->addChild(ui);

//    auto sampleInfoList = SampleService::getInstance()->getSampleListInfo();
    auto sampleInfoList = SampleService::getInstance()->getSampleListInfoFromJson();
    ui->setSampleInfoList(sampleInfoList);
}
