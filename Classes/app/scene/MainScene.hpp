//
//  MainScene.hpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/18.
//

#ifndef __rakuran__MainScene__
#define __rakuran__MainScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <stdio.h>

USING_NS_CC;
using namespace ui;

class PartsMainScene;

class MainScene : public Scene
{
  public:
    static MainScene* createScene();

    MainScene();
    virtual ~MainScene();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

  private:
    void initUI();

    PartsMainScene* _partsScene;
};

#endif /* defined(__rakuran__MainScene__) */
