//
//  LoadingScene.hpp
//  rakuran
//
//  Created by choshi on 02/18/18.
//
//

#ifndef __rakuran__LoadingScene__
#define __rakuran__LoadingScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PartsLoadingScene;

class LoadingScene : public Scene
{
  public:
    static LoadingScene* createScene();

    LoadingScene();
    virtual ~LoadingScene();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

  private:
    void initUI();

    PartsLoadingScene* _partsScene;
};

#endif /* defined(__rakuran__LoadingScene__) */
