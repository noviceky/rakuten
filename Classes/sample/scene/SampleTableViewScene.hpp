//
//  SampleTableViewScene.hpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#ifndef __rakuran__SampleTableViewScene__
#define __rakuran__SampleTableViewScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class SampleTableViewScene : public Scene
{
  public:
    static SampleTableViewScene* createScene();

    SampleTableViewScene();
    virtual ~SampleTableViewScene();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

  private:
    void initUI();
};

#endif /* defined(__rakuran__SampleTableViewScene__) */
