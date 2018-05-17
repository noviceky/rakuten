//
//  PartsSampleTableView.cpp
//  rakuran
//
//  Created by Choshi on 02/28/18.
//
//

#include "PartsSampleTableView.hpp"
#include "AppMacro.h"
#include "PartsSampleTableViewCell.hpp"
#include "SampleDTO.h"
#include "const.h"

PartsSampleTableView* PartsSampleTableView::create(const Size& size)
{
    auto instance = new PartsSampleTableView(size);
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

PartsSampleTableView::PartsSampleTableView()
    : _tableView(nullptr)
    , _onSelected(nullptr)
    , _tableViewContentSize(Size::ZERO)
{
    // constructor
    TRACE;
}

PartsSampleTableView::PartsSampleTableView(const Size& size)
    : _tableView(nullptr)
    , _onSelected(nullptr)
    , _tableViewContentSize(size)
{
    // constructor
    TRACE;
}

PartsSampleTableView::~PartsSampleTableView()
{
    // destructor
    TRACE;
}

bool PartsSampleTableView::init()
{
    TRACE;
    auto ret = Layout::init();
    if (ret)
    {
        initUI();
    }
    return ret;
}

void PartsSampleTableView::onEnter()
{
    TRACE;
    Layout::onEnter();
}

void PartsSampleTableView::onEnterTransitionDidFinish()
{
    TRACE;
    Layout::onEnterTransitionDidFinish();
}

void PartsSampleTableView::onExit()
{
    TRACE;
    Layout::onExit();
}

void PartsSampleTableView::onExitTransitionDidStart()
{
    TRACE;
    Layout::onExitTransitionDidStart();
}

void PartsSampleTableView::initUI()
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

void PartsSampleTableView::setSampleInfoList(const std::vector<SampleDTO>& list)
{
    _sampleInfoList = list;

    if (_tableView)
    {
        // reloadDataを呼ぶと、TableView先頭セル（idx=0）から順に画面内に収まるセルの数だけセルが生成される
        _tableView->reloadData();
    }
}

#pragma mark - TableViewDataSource
Size PartsSampleTableView::tableCellSizeForIndex(TableView* table, ssize_t idx)
{
    // このメソッドはTableViewから呼ばれる
    // このメソッドでidx番目のセルのコンテンツサイズ（縦横幅）を返す

    if (_sampleInfoList.empty())
    {
        return Size::ZERO;
    }

    return Size(_tableViewContentSize.width, _sampleInfoList.at(idx).listItemHeight);
}

TableViewCell* PartsSampleTableView::tableCellAtIndex(TableView* table, ssize_t idx)
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

    auto info = _sampleInfoList.at(idx);

    cell->setTag(info.idx);

    // 実際に表示させたいパーツを生成してセルにaddChild
    auto panel = PartsSampleTableViewCell::create();
    panel->initWithViewCellInfo(info.idx, Size(_tableViewContentSize.width, info.listItemHeight), info.title);
    cell->addChild(panel);

    return cell;
}

ssize_t PartsSampleTableView::numberOfCellsInTableView(TableView* table)
{
    // このメソッドはTableViewから呼ばれる
    // TableView全体のセル数を返す
    return _sampleInfoList.size();
}

#pragma mark - TableViewDelegate
void PartsSampleTableView::tableCellTouched(TableView* table, TableViewCell* cell)
{
    // このメソッドはTableViewから呼ばれる
    // TableViewの各セルをタップしたときにTableViewから呼ばれる

    if (_onSelected)
    {
        // TableViewのセルをタップされたことをTableView生成元にコールバック
        _onSelected(static_cast<int>(cell->getTag()));
    }
}
