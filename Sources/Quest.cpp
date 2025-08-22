#include "Player.hpp"
#include <string>
#include "CallFuncWrapper.hpp"

namespace CTRPluginFramework
{
    void quest_clear(MenuEntry *entry)
    {
        Process::Write32(0x82EC464, 0x0000002A);
        Process::Write32(0x82EC470, 0x0000002A);
    }

    void quest_gohome(MenuEntry *entry)
    {
        u32 offset;
        Process::Read32(0x8171B44, offset);
        Process::Write32(offset + 0x000003C, 0x00000000);
    }

    void teikei_text(MenuEntry *entry)
    {
        if (Controller::IsKeysDown(Y + L)) {
            Process::Write32(0x0E24CCC, 0x01000000);
            Process::Write32(0x0E26504, 0x01000000);
        }
    }

    void kieraji_inf(MenuEntry *entry)
    {
        Process::Write32(0x09DC7D8, 0xE1A00000);
    }

    void shukai_armor(MenuEntry *entry)
    {
        u32 offset;
        Process::Read32(0x0DF95F0, offset);
        Process::Write8(offset + 0x000C132, 0x00000007);
    }

    void open_status(MenuEntry *entry)
    {
        (CallFuncWrapper(0x0025b07c))(0);
    }

}