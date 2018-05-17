//
//  PartsSampleTableView.hpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#ifndef __rakuran__PartsSampleTableView__
#define __rakuran__PartsSampleTableView__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <extensions/cocos-ext.h>

USING_NS_CC;
using namespace ui;
using namespace extension;

struct SampleDTO;

class PartsSampleTableView
    : public Layout
    , public TableViewDataSource
    , public TableViewDelegate
{
  public:
    static PartsSampleTableView* create(const Size& size);

    void setSampleInfoList(const std::vector<SampleDTO>& list);

    using OnSelected = std::function<void(const int idx)>;
    CC_SYNTHESIZE(OnSelected, _onSelected, OnSelected);

  private:
    PartsSampleTableView();
    PartsSampleTableView(const Size& size);
    virtual ~PartsSampleTableView();
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

    void initUI();

  private:
    // TableViewDataSourceの抽象メソッド
    virtual Size           tableCellSizeForIndex(TableView* table, ssize_t idx) override;
    virtual TableViewCell* tableCellAtIndex(TableView* table, ssize_t idx) override;
    virtual ssize_t        numberOfCellsInTableView(TableView* table) override;

    // TableViewDelegateの抽象メソッド
    virtual void tableCellTouched(TableView* table, TableViewCell* cell) override;

  private:
    TableView*             _tableView;
    Size                   _tableViewContentSize;
    std::vector<SampleDTO> _sampleInfoList;
};

#endif /* defined(__rakuran__PartsSampleTableView__) */
