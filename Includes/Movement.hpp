#ifndef _MOVEMENT_HPP
#define _MOVEMENT_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void Z_Up_Down(MenuEntry *entry);
    void CoordMove(MenuEntry *entry);
}

#endif