//
//  PartsTableViewCell.hpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/24.
//

#ifndef __rakuran__PartsTableViewCell__
#define __rakuran__PartsTableViewCell__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PartsTableViewCell : public Layout
{
  public:
    CREATE_FUNC(PartsTableViewCell);

    void initWithViewCellInfo(const int idx, const Size& size, const int rank, const std::string& title);

  private:
    PartsTableViewCell();
    virtual ~PartsTableViewCell();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;
    Node*        _csbItem;
};

#endif /* defined(__rakuran__PartsTableViewCell__) */
