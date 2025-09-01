#include "CallFuncWrapper.hpp"
#include "lib/libPlayer.hpp"

namespace CTRPluginFramework
{
    u32 get_player_offset() {
        u32 value;
        Process::Read32(0x00106A3C, value);
        return value;
    }

    u32 get_net_player_offset() {
        u32 value;
        Process::Read32(0x00106A3C, value);
        return value;
    }

    u32 get_money() {
        u32 value;
        Process::Read32(0x00C85378, value);
        return value;
    }

    void set_money(u32 ammont) {
        Process::Write32(0x0ECD5B4, ammont);
    }

    void set_player_name(std::string string) {
        Process::WriteString(0xECD580, string, StringFormat::Utf16);
    }

    std::string get_player_name() {
        std::string string;
        Process::ReadString(0xECD580, string, 15, StringFormat::Utf16);
        return string;
    }

    void set_player_comment(std::string string) {
        Process::WriteString(0x0F39DF0, string, StringFormat::Utf16);
    }

    std::string get_player_comment() {
        std::string string;
        Process::ReadString(0x0F39DF0, string, 26, StringFormat::Utf16);
        return string;
    }

    u32 get_cat_struct_addres() {
        u32 offset = get_player_offset();
        u32 addres = (CallFuncWrapper(0x00a814ec))(offset);
        return addres;
    }

    void edit_cat_color(u8 red, u8 green, u8 blue) {
        u32 address = get_cat_struct_addres();    
        u32 color_address = address + 0x20;

        Process::Write8(color_address + 0, blue);
        Process::Write8(color_address + 1, green);
        Process::Write8(color_address + 2, red);
    }

    void reload_guildcard() {
        u32 offset = get_player_offset();
        (CallFuncWrapper(0x00a81958))(offset);
    }

    void update_player() {
        u32 offset = get_net_player_offset();
        // 0x152 バイト以上確保
        unsigned char buffer[0x152];
        CallFuncWrapper func(0x00a8616c);
        func(offset, reinterpret_cast<u32>(buffer));
    }
}
