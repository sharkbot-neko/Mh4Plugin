#include "Item.hpp"
#include "items.h"

namespace CTRPluginFramework
{
    void ItemGet(MenuEntry *entry) {
        u32 OffCheck;
        constexpr u32 QUEST_OFFSET = 0x00E1CFE4;
        constexpr u32 BASE_ADDRESS = 0x00000000;
    
        Process::Read32(BASE_ADDRESS + QUEST_OFFSET, OffCheck);
    
        if (OffCheck == 0x00000000) {
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
            GetItemPocket(selectedItem->code, count, 1);
        }
    }    

    void InfStone(MenuEntry *entry) {
        u32 OffCheck;
        Process::Read32(0x00000000 + 0x00E1CFE4 , OffCheck);
        if (OffCheck != 0x00000000) {
            u32 Off;
            Process::Read32(0x00000000 + 0x00E1CFE4 , Off);
            Process::Write32(Off + 0x0000100C , 0x00A80000);
            Process::Write32(Off + 0x00001010 , 0x000000FF);
        }
    }
}
