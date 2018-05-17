//
//  PartsSampleDebugMenuList.hpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#ifndef __rakuran__PartsSampleDebugMenuList__
#define __rakuran__PartsSampleDebugMenuList__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

class PartsSampleDebugMenuList : public Layout
{
  public:
    CREATE_FUNC(PartsSampleDebugMenuList);

    using OnSelectedCallback = std::function<void()>;
    void addListItem(const std::string& title, OnSelectedCallback cb);

  private:
    PartsSampleDebugMenuList();
    virtual ~PartsSampleDebugMenuList();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

    void      initUI();
    ListView* createListView();
    Layout*   createListItem(const std::string& title, OnSelectedCallback cb);

    ListView* _listView;
};

#endif /* defined(__rakuran__PartsSampleDebugMenuList__) */
