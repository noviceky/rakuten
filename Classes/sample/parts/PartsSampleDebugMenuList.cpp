//
//  PartsSampleDebugMenuList.cpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#include "PartsSampleDebugMenuList.hpp"
#include "AppMacro.h"
#include "const.h"

namespace
{
const float   kListTopBottomMergin            = 20.f;
const float   kListItemsMergin                = 10.f;
const float   kListItemMinHeight              = 100.f;
const float   kListItemFontSize               = 24;
const GLubyte kListItemBackGroundColorOpacity = 200;
}  // namespace

PartsSampleDebugMenuList::PartsSampleDebugMenuList()
    : _listView(nullptr)
{
    // constructor
    TRACE;
}

PartsSampleDebugMenuList::~PartsSampleDebugMenuList()
{
    // destructor
    TRACE;
}

bool PartsSampleDebugMenuList::init()
{
    TRACE;
    auto ret = Layout::init();
    if (ret)
    {
        initUI();
    }
    return true;
}

void PartsSampleDebugMenuList::onEnter()
{
    TRACE;
    Layout::onEnter();
}

void PartsSampleDebugMenuList::onEnterTransitionDidFinish()
{
    TRACE;
    Layout::onEnterTransitionDidFinish();
}

void PartsSampleDebugMenuList::onExit()
{
    TRACE;
    Layout::onExit();

    this->unscheduleUpdate();
}

void PartsSampleDebugMenuList::onExitTransitionDidStart()
{
    TRACE;
    Layout::onExitTransitionDidStart();
}

void PartsSampleDebugMenuList::initUI()
{
    TRACE;

    this->setContentSize(MAIN_VIEW_SIZE);

    _listView = createListView();
    this->addChild(_listView);
}

ListView* PartsSampleDebugMenuList::createListView()
{
    auto view = ListView::create();
    view->setContentSize(this->getContentSize() - Size(0.f, kListTopBottomMergin * 2));
    view->setItemsMargin(kListItemsMergin);
    view->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    view->setPosition(MAIN_VIEW_SIZE / 2);
    return view;
}

void PartsSampleDebugMenuList::addListItem(const std::string& title, OnSelectedCallback cb)
{
    CCASSERT(_listView != nullptr, "_listView is nullptr");

    // if (_listView != nullptr)の省略した書き方
    if (_listView)
    {
        // リストビューにリストアイテムを追加
        _listView->pushBackCustomItem(createListItem(title, cb));
    }
}

Layout* PartsSampleDebugMenuList::createListItem(const std::string& title, OnSelectedCallback cb)
{
    auto text = Text::create(title, rakuran::fontName, kListItemFontSize);
    text->setTextVerticalAlignment(TextVAlignment::CENTER);
    text->setTextHorizontalAlignment(TextHAlignment::CENTER);

    auto panelHeight = std::max(kListItemMinHeight, text->getContentSize().height);

    auto panel = Layout::create();
    panel->setContentSize(Size(MAIN_VIEW_WIDTH, panelHeight));
    panel->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    panel->setBackGroundColor(Color3B::GRAY);
    panel->setBackGroundColorOpacity(kListItemBackGroundColorOpacity);

    text->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    text->setPosition(panel->getContentSize() / 2);
    panel->addChild(text);

    panel->setTouchEnabled(true);
    panel->addTouchEventListener([=](Ref* ref, Widget::TouchEventType eventType) {
        if (eventType != Widget::TouchEventType::ENDED)
        {
            return;
        }

        // リストスクロールとタッチ判定が競合するため
        // 5.0pix以上移動したらリストアイテムを選択されたとは判定しない
        if (auto widget = dynamic_cast<Widget*>(ref))
        {
            if (5.0f < widget->getTouchEndPosition().distance(widget->getTouchBeganPosition()))
            {
                return;
            }
        }

        // リストアイテム選択されたことをリストアイテム生成元にコールバック
        if (cb)
        {
            // cbはラムダの[=]でキャプチャしているので、ここで呼べる
            cb();
        }
    });

    return panel;
}
