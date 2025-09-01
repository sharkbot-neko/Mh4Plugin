#ifndef _ACTION_LIB_HPP
#define _ACTION_LIB_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"
#include "lib/libQuest.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;
    
    // 肉焼き処理
    void excute_nikuyaki();
    // 釣り処理
    void excute_fish();

    // アクション実行
    void excute_action(int actionid);
}

#endif