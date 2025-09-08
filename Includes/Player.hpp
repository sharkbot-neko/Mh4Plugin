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

    // コード系
    void MoneyMaxUp(MenuEntry *entry);
    void MoneyMinusNoReset(MenuEntry *entry);

    // アイルー系
    void CatColor(MenuEntry *entry);
    void RaibowCat(MenuEntry *entry);
    void CatName(MenuEntry *entry);
    void CatBuki(MenuEntry *entry);
}

#endif