#ifndef _ITEM_LIB_HPP
#define _ITEM_LIB_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"
#include "lib/libQuest.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void add_item(int itemid, int count);
    void set_item(u16 itemid, u8 count, int basho);
    void fished_item(u16 itemid, int count, int message);
}

#endif