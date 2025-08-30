#include "CallFuncWrapper.hpp"
#include "lib/libPlayer.hpp"

namespace CTRPluginFramework
{
    u32 get_money() {
        u32 value;
        Process::Read32(0x0ECD5B4, value);
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
}
