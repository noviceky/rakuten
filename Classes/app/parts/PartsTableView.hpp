//
//  PartsTableView.hpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/24.
//

#ifndef __rakuran__PartsTableView__
#define __rakuran__PartsTableView__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include <extensions/cocos-ext.h>
#include "RankInfoDTO.h"

USING_NS_CC;
using namespace ui;
using namespace extension;

struct RankInfoDTO;

class PartsTableView
: public Layout
, public TableViewDataSource
, public TableViewDelegate
{
public:
    static PartsTableView* create(const Size& size);
    
    void setRankInfoDTOList(const std::vector<RankInfoDTO>& list);
    
    using OnSelected = std::function<void(const int idx)>;
    CC_SYNTHESIZE(OnSelected, _onSelected, OnSelected);
    
private:
    PartsTableView();
    PartsTableView(const Size& size);
    virtual ~PartsTableView();
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
    Size                    _tableViewCellSize; //幅は_tableViewContentSizeと同じ
    std::vector<RankInfoDTO> _rankInfoDTOList;
};

#endif /* defined(__rakuran__PartsTableView__) */
