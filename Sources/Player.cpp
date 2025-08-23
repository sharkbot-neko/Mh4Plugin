#include "Player.hpp"
#include "lib/libPlayer.hpp"
#include "lib/libQuest.hpp"
#include <string>

namespace CTRPluginFramework
{
    void Money(MenuEntry *entry) {
        u32 count;

        Keyboard keyboard("金額を入力");
        keyboard.IsHexadecimal(false);
    
        if (keyboard.Open(count) == 0) {
            set_money(count);
        }
    }

    void HunterRank(MenuEntry *entry) {
        u32 count;

        Keyboard keyboard("ハンターランクを入力");
        keyboard.IsHexadecimal(false);
    
        if (keyboard.Open(count) == 0) {
            Process::Write32(0x10ECD5AC, count);
        }
    }

    void Name(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        std::string string;

        Keyboard keyboard("名前を入力");

        if (keyboard.Open(string) == 0) {
            set_name(string);
        }
    }

    void Comment(MenuEntry *entry) {
        std::string string;

        Keyboard keyboard("コメントを入力");

        if (keyboard.Open(string) == 0) {
            Process::WriteString(0x0F39DF0, string, StringFormat::Utf16);
        }
    }

    void Speed(MenuEntry *entry) {
        u32 offset;
        u32 cmp32;
        
        if (Process::Read32(0x0E248F8, cmp32) && cmp32 != 0x00000000)
        {
            Process::Read32(0x0E248F8, offset);
            Process::Write32(offset + 0x000111C, 0x40E00000);
        }
    }
}