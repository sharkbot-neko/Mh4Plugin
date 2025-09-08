#ifndef _PLAYER_LIB_HPP
#define _PLAYER_LIB_HPP

#include <vector>
#include <string>

namespace CTRPluginFramework
{
    using StringVector = std::vector<std::string>;

    u32 get_player_offset();
    u32 get_net_player_offset();
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
    void edit_cat_name(std::string catname);
    std::string get_cat_name();
    void edit_cat_soubi(u8 head, u8 body, u8 buki);

    // 通信系？
    void update_player();
}

#endif