//
//  PartsTableView.cpp
//  rakuran-mobile
//
//  Created by kyagi on 2018/05/24.
//

#include "PartsTableView.hpp"
#include "AppMacro.h"
#include "PartsTableViewCell.hpp"
#include "const.h"

PartsTableView* PartsTableView::create(const Size& size)
{
    auto instance = new PartsTableView(size);
    if (instance)
    {
        instance->init();
        instance->autorelease();
        return instance;
    }
    else
    {
        delete instance;
        instance = nullptr;
        return nullptr;
    }
}

PartsTableView::PartsTableView()
: _tableView(nullptr)
, _onSelected(nullptr)
, _tableViewContentSize(Size::ZERO)
{
    // constructor
    TRACE;
}

PartsTableView::PartsTableView(const Size& size)
: _tableView(nullptr)
, _onSelected(nullptr)
, _tableViewContentSize(size)
{
    // constructor
    TRACE;
}

PartsTableView::~PartsTableView()
{
    // destructor
    TRACE;
}

bool PartsTableView::init()
{
    TRACE;
    auto ret = Layout::init();
    if (ret)
    {
        initUI();
    }
    return ret;
}

void PartsTableView::onEnter()
{
    TRACE;
    Layout::onEnter();
}

void PartsTableView::onEnterTransitionDidFinish()
{
    TRACE;
    Layout::onEnterTransitionDidFinish();
}

void PartsTableView::onExit()
{
    TRACE;
    Layout::onExit();
}

void PartsTableView::onExitTransitionDidStart()
{
    TRACE;
    Layout::onExitTransitionDidStart();
}

void PartsTableView::initUI()
{
    this->setContentSize(MAIN_VIEW_SIZE);
    this->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    this->setBackGroundColor(Color3B::WHITE);
    
    _tableView = TableView::create(this, _tableViewContentSize);
    _tableView->setDelegate(this);
    _tableView->setDirection(TableView::Direction::VERTICAL);
    _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    _tableView->setBounceable(true);
    _tableView->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    _tableView->setPosition(Vec2((MAIN_VIEW_SIZE - _tableViewContentSize) / 2));
    this->addChild(_tableView);
}

void PartsTableView::setRankInfoDTOList(const std::vector<RankInfoDTO>& list)
{
    _rankInfoDTOList = list;
    
    if (_tableView)
    {
        // reloadDataを呼ぶと、TableView先頭セル（idx=0）から順に画面内に収まるセルの数だけセルが生成される
        _tableView->reloadData();
    }
}

#pragma mark - TableViewDataSource
Size PartsTableView::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
    // このメソッドはTableViewから呼ばれる
    // このメソッドでidx番目のセルのコンテンツサイズ（縦横幅）を返す
    
    if (_rankInfoDTOList.empty())
    {
        return Size::ZERO;
    }
    //TODO 高さどうするか
    return Size(_tableViewContentSize.width, _rankInfoDTOList.at(idx).listItemHeight);
}

TableViewCell* PartsTableView::tableCellAtIndex(TableView* table, ssize_t idx)
{
    // このメソッドはTableViewから呼ばれる
    // このメソッドでセルを生成して返す
    
    TableViewCell* cell;
    {
        // 再利用出来る（生成済み）セルを取得
        cell = table->dequeueCell();
        if (cell)
        {
            // 生成済みセルが存在した場合は、セルにaddChildされた子ノードを全て取り除く
            cell->removeAllChildren();
        }
        else
        {
            // 再利用出来るセルが無い場合は新規にセルを生成
            cell = new TableViewCell();
            cell->autorelease();
        }
    }
    
    auto info = _rankInfoDTOList.at(idx);
    
    cell->setTag(info.idx);
    
    // 実際に表示させたいパーツを生成してセルにaddChild
    auto panel = PartsTableViewCell::create();
    panel->initWithViewCellInfo(info.idx, Size(_tableViewContentSize.width, info.listItemHeight), info.title);
    cell->addChild(panel);
    
    return cell;
}

ssize_t PartsTableView::numberOfCellsInTableView(TableView* table)
{
    // このメソッドはTableViewから呼ばれる
    // TableView全体のセル数を返す
    return _rankInfoDTOList.size();
}

#pragma mark - TableViewDelegate
void PartsTableView::tableCellTouched(TableView* table, TableViewCell* cell)
{
    // このメソッドはTableViewから呼ばれる
    // TableViewの各セルをタップしたときにTableViewから呼ばれる
    
    if (_onSelected)
    {
        // TableViewのセルをタップされたことをTableView生成元にコールバック
        _onSelected(static_cast<int>(cell->getTag()));
    }
}
