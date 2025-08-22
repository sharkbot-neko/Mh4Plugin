#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"
#include "items.h"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    ITEM_MAP* SelectItemWithPagination();
    void GetItemPocket(u16 itemid, u8 category, int count);

    void ItemGet(MenuEntry *entry);
    void InfStone(MenuEntry *entry);
}

#endif