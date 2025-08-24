#include "CallFuncWrapper.hpp"
#include "lib/libPlayer.hpp"

namespace CTRPluginFramework
{
    void set_money(u32 ammont) {
        Process::Write32(0x0ECD5B4, ammont);
    }

    void set_player_name(std::string string) {
        Process::WriteString(0xECD580, string, StringFormat::Utf16);
    }
}
