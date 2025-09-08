#include "Player.hpp"
#include <string>
#include "CallFuncWrapper.hpp"
#include "Quest.hpp"
#include "Item.hpp"
#include "lib/libItem.hpp"
#include "lib/libAction.hpp"

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

    u16 itemid = 0x0001;
    int count_item = 1;

    void fish_allitem(MenuEntry *entry) {
        if (!is_the_quest()) {
            return;
        }

        if (Controller::IsKeysPressed(A + DPadUp)) {
            u8 count;
            const ITEM_MAP *selectedItem = SelectItemWithPagination();
            
            if (selectedItem == nullptr) {
                OSD::Notify("No item selected.");
                return;
            }
        
            Keyboard keyboard("個数を入力");
            keyboard.IsHexadecimal(false);

            if (keyboard.Open(count) == 0) {
                itemid = selectedItem->code;
                count_item = count;
            }
        }

        if (Controller::IsKeysPressed(A + DPadDown)) {
            fished_item(itemid, count_item, 7);
        }
    }

    void Quest_playerName(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        std::string string;

        Keyboard keyboard("名前を入力");

        if (keyboard.Open(string) == 0) {
            set_player_name_during_quest(string);
        }
    }

    void nikuyaku_every(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        excute_nikuyaki();
    }

    void go_canpu(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        excute_action(17);
    }

    void open_box_1(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        excute_action(0x70);
    }

    void open_box_2(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        excute_action(0x71);
    }

    void toishi_run(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }

        excute_action(0x5a);
    }

    void fish_excute(MenuEntry *entry) {
        if (!is_the_quest()) {
            return;
        }

        if (Controller::IsKeysPressed(Y)) {
            excute_fish();
        }
    }

    u16 actionid = 0;

    void excute_act(MenuEntry *entry) {
        if (!is_the_quest()) {
            return;
        }

        if (Controller::IsKeysPressed(L + DPadUp)) {
        
            u16 _actionid;

            Keyboard keyboard("アクションidを入力");

            if (keyboard.Open(_actionid) == 0) {
                actionid = _actionid;
            }
        }

        if (Controller::IsKeysPressed(L + DPadDown)) {
            excute_action(actionid);
        }
    }

    void FreeQuest(MenuEntry *entry) {
        const std::vector<std::string> enable_or_disable = {
            "有効",
            "無効"
        };

        Keyboard keyboard("無料のクエスト", enable_or_disable);

		int index = keyboard.Open();
		if(index < 0)
			return;

		switch (index) {
			default: break;

            case 0: {
                Process::Patch(0x0086EED0, 0xE320F000);
                break;
            }

            case 1: {
                Process::Patch(0x0086EED0, 0xEB0861A5);
                break;
            }
        };
    }
}