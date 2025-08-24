#ifndef _QUEST_LIB_HPP
#define _QUEST_LIB_HPP

#include <vector>
#include <string>
#include "CTRPluginFramework.hpp"

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    u32 get_quest_offset();
    bool is_the_quest();
    void set_player_name_during_quest(std::string string);
}

#endif