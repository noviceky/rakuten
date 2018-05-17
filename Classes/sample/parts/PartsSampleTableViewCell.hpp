//
//  PartsSampleTableViewCell.hpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#ifndef __rakuran__PartsSampleTableViewCell__
#define __rakuran__PartsSampleTableViewCell__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PartsSampleTableViewCell : public Layout
{
  public:
    CREATE_FUNC(PartsSampleTableViewCell);

    void initWithViewCellInfo(const int idx, const Size& size, const std::string& title);

  private:
    PartsSampleTableViewCell();
    virtual ~PartsSampleTableViewCell();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;
};

#endif /* defined(__rakuran__PartsSampleTableViewCell__) */
