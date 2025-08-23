#ifndef _ITEM_HPP
#define _ITEM_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"
#include "items.h"
#include "lib/libItem.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    ITEM_MAP* SelectItemWithPagination();
    // If you have another overload with the same parameters but different return type, rename it or change its parameters.
    // For example, if you have:
    // int SelectItemWithPagination();
    // Rename it to:
    // int SelectItemWithPaginationInt();
    void GetItemPocket(u16 itemid, u8 category, int count);

    void ItemGet(MenuEntry *entry);
    void InfStone(MenuEntry *entry);
    void ItemNoDelete(MenuEntry *entry);
}

#endif