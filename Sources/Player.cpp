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

    void MoneyMaxUp(MenuEntry *entry) {
        const std::vector<std::string> enable_or_disable = {
            "有効",
            "無効"
        };

        Keyboard keyboard("財布に最大以上に入れられる", enable_or_disable);

        int index = keyboard.Open();
        if (index < 0)
            return;

        switch (index) {
            default: break;

            case 0: {
                Process::Patch(0x00A87584, 0xE320F000);
                break;
            }

            case 1: {
                Process::Patch(0x00A87584, 0xC1A00003);
                break;
            }
        }
    }

    void MoneyMinusNoReset(MenuEntry *entry) {
        const std::vector<std::string> enable_or_disable = {
            "有効",
            "無効"
        };

        Keyboard keyboard("財布がマイナスでもリセットされない", enable_or_disable);

		int index = keyboard.Open();
		if(index < 0)
			return;

		switch (index) {
			default: break;

            case 0: {
                Process::Patch(0x00A87590, 0xE320F000);
                break;
            }

            case 1: {
                Process::Patch(0x00A87590, 0xD3A00000);
                break;
            }
        };
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

    void CatColor(MenuEntry *entry) {
        u8 blue;
        u8 green;
        u8 red;

        if (Keyboard("アイルーの色を入力 (red)").Open(red) == 0) {}
        if (Keyboard("アイルーの色を入力 (green)").Open(green) == 0) {}
        if (Keyboard("アイルーの色を入力 (blue)").Open(blue) == 0) {}
        edit_cat_color(blue, green, red);
    }

    void RaibowCat(MenuEntry *entry) {
        u8 blue = Utils::Random(0x00, 0xFF);
        u8 green = Utils::Random(0x00, 0xFF);
        u8 red = Utils::Random(0x00, 0xFF);
        edit_cat_color(blue, green, red);
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