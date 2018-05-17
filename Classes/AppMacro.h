//
//  AppMacro.h
//  rakuran
//
//  Created by choshi on 02/18/18.
//
//

#ifndef __rakuran__AppMacro__
#define __rakuran__AppMacro__

#include "cocos2d.h"

#define WINSIZE Director::getInstance()->getWinSize()
#define WINCENTER Point(WINSIZE.width * 0.5, WINSIZE.height * 0.5)
#define WIN_WIDTH Director::getInstance()->getWinSize().width
#define WIN_HEIGHT Director::getInstance()->getWinSize().height
#define MAIN_VIEW_WIDTH 640
#define MAIN_VIEW_HEIGHT 1136
#define MAIN_VIEW_SIZE Size(MAIN_VIEW_WIDTH, MAIN_VIEW_HEIGHT)
#define HEADER_HEIGHT 64.0
#define FOOTER_HEIGHT 100.0

// デバック機能
#if DEBUG
#define DEBUG_MENU_ENABLE (1)
#else
#define DEBUG_MENU_ENABLE (0)
#endif

// ログ
#if DEBUG
#define LOG(format, ...) cocos2d::log(format, ##__VA_ARGS__)
#else
#define LOG(format, ...)
#endif

// トレースログ
#define TRACE LOG("TRACE[%s][L:%d]", __PRETTY_FUNCTION__, __LINE__)

// デバックトレースログ（処理速度計測用）
#define DEBUG_TRACE DEBUG_TRACE_LOG trace(__PRETTY_FUNCTION__);

class DEBUG_TRACE_LOG
{
  public:
    DEBUG_TRACE_LOG(const std::string& msg)
    {
        _msg        = msg;
        _startClock = std::chrono::system_clock::now();
        LOG("DEBUG_TRACE[%s] --->", _msg.c_str());
    };

    virtual ~DEBUG_TRACE_LOG()
    {
        _endClock      = std::chrono::system_clock::now();
        double elapsed = std::chrono::duration_cast<std::chrono::microseconds>(_endClock - _startClock).count();
        elapsed *= 0.001;
        LOG("DEBUG_TRACE[%s][%.3fmsec] <---", _msg.c_str(), elapsed);
    };

  private:
    std::string                           _msg;
    std::chrono::system_clock::time_point _startClock;
    std::chrono::system_clock::time_point _endClock;
    DEBUG_TRACE_LOG(){};
};

#endif /* defined(__rakuran__AppMacro__) */
