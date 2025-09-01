#ifndef _PLAYER_LIB_HPP
#define _PLAYER_LIB_HPP

#include <vector>
#include <string>

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    u32 get_player_offset();
    void set_money(u32 ammont);
    u32 get_money();
    void set_player_name(std::string string);
    std::string get_player_name();
    void set_player_comment(std::string string);
    std::string get_player_comment();
    void reload_guildcard();

    // アイルー系
    u32 get_cat_struct_addres();
    void edit_cat_color(u8 blue, u8 green, u8 red);
}

#endif