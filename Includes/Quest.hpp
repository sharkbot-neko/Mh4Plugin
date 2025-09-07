#ifndef _QUEST_HPP
#define _QUEST_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void quest_clear(MenuEntry *entry);
    void quest_gohome(MenuEntry *entry);
    void teikei_text(MenuEntry *entry);
    void kieraji_inf(MenuEntry *entry);
    void shukai_armor(MenuEntry *entry);
    void open_status(MenuEntry *entry);
    void Quest_playerName(MenuEntry *entry);
    void fish_allitem(MenuEntry *entry);
    void excute_act(MenuEntry *entry);
    void nikuyaku_every(MenuEntry *entry);
    void go_canpu(MenuEntry *entry);
    void fish_excute(MenuEntry *entry);
    void open_box_1(MenuEntry *entry);
    void open_box_2(MenuEntry *entry);
    void toishi_run(MenuEntry *entry);
}

#endif