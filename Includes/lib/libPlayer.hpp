#ifndef _PLAYER_LIB_HPP
#define _PLAYER_LIB_HPP

#include <vector>
#include <string>

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    void set_money(u32 ammont);
    void set_player_name(std::string string);
    std::string get_player_name();
}

#endif