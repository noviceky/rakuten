//
//  SampleDebugMenuScene.hpp
//  rakuran
//
//  Created by Choshi on 02/26/18.
//
//

#ifndef __rakuran__SampleDebugMenuScene__
#define __rakuran__SampleDebugMenuScene__

#include "cocos2d.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
using namespace ui;

struct SampleDTO;

class SampleDebugMenuScene : public Scene
{
  public:
    static SampleDebugMenuScene* createScene();

    SampleDebugMenuScene();
    virtual ~SampleDebugMenuScene();

    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onEnterTransitionDidFinish() override;
    virtual void onExit() override;
    virtual void onExitTransitionDidStart() override;

  private:
    void initUI();

    void onSelectedBack();
    void onSelectedMessageBoxSample();
    void onSelectedTableViewSample();

    // 「関数を保存する１」を選択したときに呼ばれるコールバック関数
    void onSelectedSTDFunctionSample1();

    // 「関数を保存する２」を選択したときに呼ばれるコールバック関数
    void onSelectedSTDFunctionSample2();

    // 「関数を保存する３」を選択したときに呼ばれるコールバック関数
    void onSelectedSTDFunctionSample3();

    // 「コールバック実装例１」を選択したときに呼ばれるコールバック関数
    void onSelectedCallbackSample1();

    // 「コールバック実装例２」を選択したときに呼ばれるコールバック関数
    void onSelectedCallbackSample2();

    // 「コールバック実装例３」を選択したときに呼ばれるコールバック関数
    void onSelectedCallbackSample3();

    // ----------------------------------------------
    // 以下、「関数を保存する２」，「関数を保存する３」の説明用
    // ----------------------------------------------

    // 以下、std::function説明用に追加した関数
    void sample1();
    int  sample2(float val);
    void sample3(SampleDTO& dto);
    bool sample4(int val, const char* str);

    // ----------------------------------------------------
    // 以下、「コールバック実装例１」、「コールバック実装例２」の説明用
    // ----------------------------------------------------

    // usingを使うと、型に別名を付けることが出来る
    // ここでは、std::function<void(bool)>という型にOnSampleCalledという名前を付けている
    using OnSampleCalled = std::function<void(bool)>;

    // OnSampleCalled型（std::function<(void(bool)>型）のメンバ変数を宣言
    OnSampleCalled _onSamlpleCalled;

    void onSampleCalledFunc(bool isSucceeded);

    // -----------------------------
    // 以下、コールバック実装例３の説明用
    // -----------------------------
    // OnSampleCalledのsetter（OnSampleCalled型のコールバック関数を保存する関数）
    void setOnSampleCallback(OnSampleCalled cb);
    // OnSampleCalledのgetter（保存したOnSampleCalled型のコールバック関数を取得する関数）
    OnSampleCalled getOnSampleCallback();

    // ３秒後にレスポンスを返す（OnSampleCalled型の関数でコールバックする）関数
    void delayRespnse(OnSampleCalled cb);
};

#endif /* defined(__rakuran__SampleDebugMenuScene__) */
