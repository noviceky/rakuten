//
//  AppMacro.h
//  rakuran
//
//  Created by 工藤陸 on 03/06/20
//
//

#ifndef __rakuran__PartsLoadingScene__
#define __rakuran__PartsLoadingScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PartsLoadingScene : public Node
{
  public:
    CREATE_FUNC(PartsLoadingScene);

    PartsLoadingScene();
    virtual ~PartsLoadingScene();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

    virtual void update(float delta) override;

    /**
     *  @brief ローディングアニメーション開始
     */
    void startLoadingAnimation();

  private:
    void initUI();
    void initLoadingTextNode();
    void updateLoadingText(float delta);

    float _elapsed;
    Node* _csb;
    Text* _loadingText;
};

#endif /* defined(__rakuran__PartsLoadingScene__) */
