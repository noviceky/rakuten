//
//  PartsMainScene.hpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/17.
//

#ifndef __rakuran__PartsMainScene__
#define __rakuran__PartsMainScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <stdio.h>

USING_NS_CC;
using namespace ui;

class PartsMainScene : public Node
{
  public:
    CREATE_FUNC(PartsMainScene);

    PartsMainScene();
    virtual ~PartsMainScene();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

    virtual void update(float delta) override;

  private:
    void initUI();

    Node *_csbHeader, *_csbFooter;
};

#endif /* defined(__rakuran__PartsMainScene__) */