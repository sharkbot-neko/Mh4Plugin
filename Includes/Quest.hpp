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
}

#endif