#include "lib/libItem.hpp"
#include "lib/libQuest.hpp"
#include "Item.hpp"
#include "items.h"

namespace CTRPluginFramework
{
    bool enabled_noitemdelete = false;

    void ItemGet(MenuEntry *entry) {
        if (!is_the_quest()) {
            MessageBox("クエストに参加していないため、\n使用できません。")();
            return;
        }
    
        u8 count;
        const ITEM_MAP *selectedItem = SelectItemWithPagination();
        
        if (selectedItem == nullptr) {
            OSD::Notify("No item selected.");
            return;
        }
    
        Keyboard keyboard("個数を入力");
        keyboard.IsHexadecimal(false);
    
        if (keyboard.Open(count) == 0) {
            add_item(selectedItem->code, count);
            // GetItemPocket(selectedItem->code, count, 1);
        }
    }    

    void InfStone(MenuEntry *entry) {
        u32 OffCheck;
        Process::Read32(0x00000000 + 0x00E1CFE4 , OffCheck);
        if (OffCheck != 0x00000000) {
            // u32 Off;
            // Process::Read32(0x00000000 + 0x00E1CFE4 , Off);
            // Process::Write32(Off + 0x0000100C , 0x00A80000);
            // Process::Write32(Off + 0x00001010 , 0x000000FF);
            set_item(0x00A8, 0xFF, 1);
        }
    }

    void ItemNoDelete(MenuEntry *entry) {
        if (!enabled_noitemdelete) {
            Process::Patch(0x009DE864, 0xE12FFF1E);
            enabled_noitemdelete = !enabled_noitemdelete;
            MessageBox("アイテム減らないコードをOnにしました。")();
        } else {
            Process::Patch(0x009DE864, 0xE92D4FF7);
            enabled_noitemdelete = !enabled_noitemdelete;
            MessageBox("アイテム減らないコードをOffにしました。")();
        }
        
    }
}
