#include "Player.hpp"
#include "lib/libPlayer.hpp"
#include "lib/libQuest.hpp"
#include <string>

namespace CTRPluginFramework
{
    void Money(MenuEntry *entry) {
        u32 count;

        std::string now_money = Utils::Format("金額を入力 (現在: %dz)", get_money());

        Keyboard keyboard(now_money);
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
            Process::Write32(0x00ECD5B0, count);
        }
    }

    void Name(MenuEntry *entry) {
        std::string string;

        std::string now_name = Utils::Format("名前を入力 (現在: %s)", get_player_name());

        Keyboard keyboard(now_name);

        if (keyboard.Open(string) == 0) {
            set_player_name(string);
        }
    }

    void Comment(MenuEntry *entry) {
        std::string string;

        Keyboard keyboard("コメントを入力");

        if (keyboard.Open(string) == 0) {
            set_player_comment(string);
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