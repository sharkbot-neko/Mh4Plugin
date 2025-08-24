#ifndef _PLAYER_HPP
#define _PLAYER_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"
#include "lib/libQuest.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void Money(MenuEntry *entry);
    void Name(MenuEntry *entry);
    void Comment(MenuEntry *entry);
    void HunterRank(MenuEntry *entry);
    void Speed(MenuEntry *entry);
}

#endif