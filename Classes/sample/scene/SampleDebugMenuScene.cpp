//
//  SampleDebugMenuScene.cpp
//  rakuran
//
//  Created by Choshi on 02/26/18.
//
//

#include "SampleDebugMenuScene.hpp"
#include "AppMacro.h"
#include "LoadingScene.hpp"
#include "PartsSampleDebugMenuList.hpp"
#include "SampleDTO.h"
#include "SampleTableViewScene.hpp"

SampleDebugMenuScene* SampleDebugMenuScene::createScene()
{
    TRACE;
    auto scene = new SampleDebugMenuScene();
    scene->autorelease();
    scene->init();
    return scene;
}

SampleDebugMenuScene::SampleDebugMenuScene()
    : _onSamlpleCalled(
          nullptr)  // メンバ変数としてコールバック関数を保存する変数を書いた場合は、コンストラクタでnullptrクリアすること（必須）
{
    // constructor
    TRACE;
}

SampleDebugMenuScene::~SampleDebugMenuScene()
{
    // destructor
    TRACE;
}

bool SampleDebugMenuScene::init()
{
    TRACE;
    auto ret = Scene::init();
    if (ret)
    {
        initUI();
    }
    return true;
}

void SampleDebugMenuScene::onEnter()
{
    TRACE;
    Scene::onEnter();
}

void SampleDebugMenuScene::onEnterTransitionDidFinish()
{
    TRACE;
    Scene::onEnterTransitionDidFinish();
}

void SampleDebugMenuScene::onExit()
{
    TRACE;
    Scene::onExit();
}

void SampleDebugMenuScene::onExitTransitionDidStart()
{
    TRACE;
    Scene::onExitTransitionDidStart();
}

void SampleDebugMenuScene::initUI()
{
    TRACE;
    auto panel = Layout::create();
    panel->setContentSize(MAIN_VIEW_SIZE);
    panel->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
    panel->setBackGroundColor(Color3B::BLUE);
    this->addChild(panel);

    if (auto ui = PartsSampleDebugMenuList::create())
    {
        this->addChild(ui);

        ui->addListItem("戻る", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedBack, this));

        ui->addListItem("MessageBoxサンプル", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedMessageBoxSample, this));

        ui->addListItem("TableViewサンプル", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedTableViewSample, this));

        ui->addListItem("関数を保存する１", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedSTDFunctionSample1, this));

        ui->addListItem("関数を保存する２", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedSTDFunctionSample2, this));

        ui->addListItem("関数を保存する３", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedSTDFunctionSample3, this));

        ui->addListItem("コールバック実装例１", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedCallbackSample1, this));

        ui->addListItem("コールバック実装例２", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedCallbackSample2, this));

        ui->addListItem("コールバック実装例３", CC_CALLBACK_0(SampleDebugMenuScene::onSelectedCallbackSample3, this));

        // 「コールバック実装例３」まで全て読み終わったら、addListItem処理の中を見てみよう
        // きっと何をやってるか読めるようになるはず
    }
}

#pragma mark - 各リストアイテム選択時の処理

void SampleDebugMenuScene::onSelectedBack()
{
    // LoadingSceneに遷移
    auto scene      = LoadingScene::createScene();
    auto transition = TransitionCrossFade::create(1.0f, scene);
    Director::getInstance()->replaceScene(transition);
}

void SampleDebugMenuScene::onSelectedMessageBoxSample()
{
    MessageBox("メッセージ", "タイトル");
}

void SampleDebugMenuScene::onSelectedTableViewSample()
{
    auto scene      = SampleTableViewScene::createScene();
    auto transition = TransitionCrossFade::create(1.0f, scene);
    Director::getInstance()->replaceScene(transition);
}

#pragma mark - 関数を保存する１
void SampleDebugMenuScene::onSelectedSTDFunctionSample1()
{
    TRACE;

    /*****************/
    /* 関数を保存する１ */
    /*****************/

    int val;  // これはint型の変数valを宣言している処理
    val = 5;  // これはint型変数valに5を格納している処理

    // 上記と同じように、関数もまた変数に格納することが出来る
    // （もう少し正確に書くと、関数を指すポインタ（＝アドレス）を保存する変数を書くことが出来る）

    // C++11では、std::functionを使うと関数を格納する変数を簡単に書ける

    // 先に具体例を書くと
    // 「戻り値なし＆引数なし」の関数を保存する変数func1は以下のように書く
    std::function<void()> func1;

    // --- ここからstd::functionの説明 ---

    // std::functionは、<>の中に
    // 戻り値の型名(引数)
    // を書くことで、同じ戻り値（引数）の関数を保存出来る

    // 例えば、以下のように書く
    std::function<int(float)>       func2;  // 戻り値がint型、引数がfloatの場合
    std::function<void(SampleDTO&)> func3;  // 戻り値なし、引数がSampleDTOの参照渡しの場合
    std::function<bool(int, const char*)> func4;  // 戻り値がbool型、第１引数がint、第２引数がconst char*の場合

    // 保存したい関数がラムダ式の場合、ラムダを格納する方法は直感的にわかる...かも

    func1 = []() {
        LOG("---");
        LOG("func1が呼ばれたよ");
    };

    func2 = [](float val) -> int {
        LOG("---");
        LOG("func2が呼ばれたよ");
        return 156.3f;
    };

    func3 = [](SampleDTO& dto) {
        LOG("---");
        LOG("func3が呼ばれたよ");
        LOG("dto.idx[%d] dto.title[%s]", dto.idx, dto.title.c_str());
    };

    func4 = [](int val, const char* str) -> bool {
        LOG("---");
        LOG("func4が呼ばれたよ");
        LOG("val=%d str=%s", val, str);
        return true;
    };

    // では、変数に保存した関数をどのように呼び出すか

    // それは、普通に関数を呼び出す時と同じように呼べば良い

    // func1を呼び出す処理
    func1();

    // func2を呼び出す処理
    int x = func2(3.2f);
    LOG("func2 x=%d", x);

    // func3を呼び出す処理
    SampleDTO dto;
    dto.idx   = 1;
    dto.title = "title1";
    func3(dto);

    // func4を呼び出す処理
    bool ret = func4(10, "abcde");
    LOG("func4 ret=%d", ret);
}

#pragma mark - 関数を保存する２
void SampleDebugMenuScene::onSelectedSTDFunctionSample2()
{
    TRACE;

    /*****************/
    /* 関数を保存する２ */
    /*****************/

    // クラスのメンバ関数を受け渡す時はちょっと面倒
    // std::bindを使って、関数を呼ぶための情報をひとまとめにしてからstd::functionで宣言した変数に渡してあげる必要がある

    // std::bindに関しては後でぐぐってー

    // 引数なし関数を格納する場合
    // std::bindを使って、関数へのアドレス、その関数が所属するクラスのインスタンスへのポインタひとまとめにしてから、受け渡す
    std::function<void()> func1 = std::bind(&SampleDebugMenuScene::sample1, this);

    // 引数あり関数の場合は、同じようにstd::bindを使うが、
    // 引数１つであれば、std::placeholders::_1を３番めに指定する
    std::function<int(float)> func2 = std::bind(&SampleDebugMenuScene::sample2, this, std::placeholders::_1);

    std::function<void(SampleDTO&)> func3 = std::bind(&SampleDebugMenuScene::sample3, this, std::placeholders::_1);

    // 引数２であれば、４番めにstd::placeholders::_2を指定
    std::function<bool(int, const char*)> func4 =
        std::bind(&SampleDebugMenuScene::sample4, this, std::placeholders::_1, std::placeholders::_2);

    // ------------
    // 以下、関数を呼び出す例

    // func1を呼び出す処理
    func1();

    // func2を呼び出す処理
    int x = func2(5.0f);
    LOG("func2 x=%d", x);

    // func3を呼び出す処理
    SampleDTO dto;
    dto.idx   = 2;
    dto.title = "title2";
    func3(dto);

    // func4を呼び出す処理
    bool ret = func4(10, "fghijk");
    LOG("func4 ret=%d", ret);
}

#pragma mark - 関数を保存する３
void SampleDebugMenuScene::onSelectedSTDFunctionSample3()
{
    TRACE;

    /*****************/
    /* 関数を保存する３ */
    /*****************/

    // cocos2d-xではstd::bindを書きやすくするためのマクロが用意されている

    {
        std::function<void()> func1 = std::bind(&SampleDebugMenuScene::sample1, this);

        std::function<int(float)> func2 = std::bind(&SampleDebugMenuScene::sample2, this, std::placeholders::_1);

        std::function<void(SampleDTO&)> func3 = std::bind(&SampleDebugMenuScene::sample3, this, std::placeholders::_1);

        std::function<bool(int, const char*)> func4 =
            std::bind(&SampleDebugMenuScene::sample4, this, std::placeholders::_1, std::placeholders::_2);
    }

    // 上記は、cocos2d-xのマクロを使うと以下のように書ける
    std::function<void()>                 func1 = CC_CALLBACK_0(SampleDebugMenuScene::sample1, this);
    std::function<int(float)>             func2 = CC_CALLBACK_1(SampleDebugMenuScene::sample2, this);
    std::function<void(SampleDTO&)>       func3 = CC_CALLBACK_1(SampleDebugMenuScene::sample3, this);
    std::function<bool(int, const char*)> func4 = CC_CALLBACK_2(SampleDebugMenuScene::sample4, this);

    // ------------
    // 以下、関数を呼び出す例

    // func1を呼び出す処理
    func1();

    // func2を呼び出す処理
    int x = func2(2.0f);
    LOG("func2 x=%d", x);

    // func3を呼び出す処理
    SampleDTO dto;
    dto.idx   = 3;
    dto.title = "title3";
    func3(dto);

    // func4を呼び出す処理
    bool ret = sample4(20, "xyz");
    LOG("sample4 ret=%d", ret);
}

#pragma mark - 関数を保存する２、３から呼ばれる処理
void SampleDebugMenuScene::sample1()
{
    LOG("SampleDebugMenuScene::sample1が呼ばれたよ ");
}

int SampleDebugMenuScene::sample2(float val)
{
    LOG("SampleDebugMenuScene::sample2が呼ばれたよ ");
    return static_cast<int>(val * 5);
}

void SampleDebugMenuScene::sample3(SampleDTO& dto)
{
    LOG("SampleDebugMenuScene::sample3が呼ばれたよ ");
    LOG("dto.idx[%d] dto.title[%s]", dto.idx, dto.title.c_str());
}

bool SampleDebugMenuScene::sample4(int val, const char* str)
{
    LOG("SampleDebugMenuScene::sample4が呼ばれたよ ");
    LOG("val=%d str=%s", val, str);
    return false;
}

#pragma mark - コールバック実装例１
void SampleDebugMenuScene::onSelectedCallbackSample1()
{
    TRACE;

    /********************/
    /* コールバック実装例１ */
    /********************/

    // OnSampleCalled型（このクラスのヘッダを見てね）のメンバ変数にラムダ式を格納
    _onSamlpleCalled = [=](bool isSucceeded) {
        LOG("_onSamlpleCalledに保存された関数が呼ばれたよー!!! isSucceeded[%d]", isSucceeded);
    };

    // 3.0f秒後に実行されるように処理をスケジューリング
    // scheduleOnceを呼んだ後に
    this->scheduleOnce(
        [=](float delta) {
            // ここが3.0f秒後に実行される処理
            LOG("3秒経過したので、コールバック関数を呼び出すよー");
            _onSamlpleCalled(true);

            // このように非同期処理が終わったことを、呼び元に通知してあげるような関数
            // （ここでは_onSamlpleCalledに保存したラムダ式）をコールバック関数と呼ぶ
        },
        3.0f, "delay_callback1");

    // 実は上でscheduleOnceに渡しているラムダそのものがコールバック関数だったり...
    LOG("SampleDebugMenuScene::onSelectedCallbackSample1の処理を抜けるよ");
}

#pragma mark - コールバック実装例２
void SampleDebugMenuScene::onSelectedCallbackSample2()
{
    TRACE;

    /********************/
    /* コールバック実装例２ */
    /********************/

    // OnSampleCalled型のメンバ変数にこのクラスのメンバ関数を格納
    _onSamlpleCalled = CC_CALLBACK_1(SampleDebugMenuScene::onSampleCalledFunc, this);

    // 3.0f秒後に実行されるように処理をスケジューリング
    // scheduleOnceを呼んだ後に
    this->scheduleOnce(
        [=](float delta) {
            // ここが3.0f秒後に実行される処理
            LOG("3秒経過したので、コールバック関数を呼び出すよー");
            _onSamlpleCalled(true);
        },
        3.0f, "delay_callback2");
    
    LOG("SampleDebugMenuScene::onSelectedCallbackSample2の処理を抜けるよ");
}

#pragma mark - コールバック実装例３
void SampleDebugMenuScene::onSelectedCallbackSample3()
{
    TRACE;

    /********************/
    /* コールバック実装例３ */
    /********************/

    // 引数としてコールバック関数を直接受け渡すことも出来る
    // ここではdelayRespnse関数にラムダ式を直接受け渡している
    delayRespnse([=](bool isSucceeded) {
        LOG("delayRespnseの応答が返って来たよ− isSucceeded=%d",isSucceeded);
    });

    // もちろん、クラスのメンバ変数を直接渡すことも可能
    // delayRespnse(CC_CALLBACK_1(SampleDebugMenuScene::onSampleCalledFunc, this));
    LOG("SampleDebugMenuScene::onSelectedCallbackSample3の処理を抜けるよ");
}

void SampleDebugMenuScene::onSampleCalledFunc(bool isSucceeded)
{
    LOG("SampleDebugMenuScene::onSampleCalledFuncが呼ばれたよー!!! isSucceeded[%d]", isSucceeded);
}

void SampleDebugMenuScene::setOnSampleCallback(OnSampleCalled cb)
{
    LOG("SampleDebugMenuScene::setOnSampleCallback _onSamlpleCalledにコールバック関数を保存");
    _onSamlpleCalled = cb;
}

SampleDebugMenuScene::OnSampleCalled SampleDebugMenuScene::getOnSampleCallback()
{
    LOG("SampleDebugMenuScene::getOnSampleCallback _onSamlpleCalledを戻り値として返す");
    return _onSamlpleCalled;
}

void SampleDebugMenuScene::delayRespnse(OnSampleCalled cb)
{
    LOG("SampleDebugMenuScene::delayRespnseが呼ばれた");

    setOnSampleCallback(cb);

    this->scheduleOnce(
        [=](float delta) {
            LOG("３秒後にスケジュールされた処理が呼び出された");

            // 3秒後にコールバック関数を呼び出す
            auto callback = getOnSampleCallback();
            if (callback != nullptr)
            {
                LOG("コールバックを返す");
                callback(true);
            }
            else
            {
                LOG("コールバックを返す");
                callback(false);  // コールバック関数がnullptrの場合は異常終了する
            }
        },
        3.0f, "delay_respnse");
    
    LOG("SampleDebugMenuScene::delayRespnseを抜ける");
}
