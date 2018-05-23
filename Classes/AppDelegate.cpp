#include "AppDelegate.h"
#include "AppMacro.h"
#include "LoadingScene.hpp"
#include "RakutenService.hpp"// ダミー実装入っているか確認 TODO 消す

USING_NS_CC;

AppDelegate::AppDelegate()
{
    TRACE;
}

AppDelegate::~AppDelegate()
{
    TRACE;
}

// if you want a different context,just modify the value of glContextAttrs
// it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributions,now can only set six attributions:
    // red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    TRACE;

    // initialize director
    auto director = Director::getInstance();
    auto glview   = director->getOpenGLView();
    if (!glview)
    {
        glview = GLViewImpl::create("rakuran");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT, ResolutionPolicy::FIXED_HEIGHT);

    // add resource search path
    auto fileUtiles = FileUtils::getInstance();
    fileUtiles->addSearchPath("res");
    fileUtiles->addSearchPath("res/rakuranUI/Resources/res");
    fileUtiles->addSearchPath("res/rakuranUI/Resources/res/fonts");
    fileUtiles->addSearchPath("res/rakuranUI/Resources/res/images");
    
    // ダミー実装入っているか確認 TODO 消す
    auto rakutenService = RakutenService::getInstance();
    auto list = rakutenService->getSampleListInfo();
    
    for (int i = 0; i < 30; i++)
    {
        LOG("idx %d = rank %d title: %s", list[i].idx,list[i].rank,list[i].title.c_str());
    } //TODO ここまで消す
    
    // create a scene. it's an autorelease object
    auto scene = LoadingScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone
// call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    TRACE;
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    TRACE;
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
