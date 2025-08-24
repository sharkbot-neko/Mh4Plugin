#include "lib/libItem.hpp"
#include "CallFuncWrapper.hpp"

namespace CTRPluginFramework
{
    void add_item(int itemid, int count) {
        u32 OffCheck = get_quest_offset();
        (CallFuncWrapper(0x009de864))(OffCheck, itemid, count);
    }

    void set_item(u16 itemid, u8 count, int basho) {
        u32 offset = 0x00000000;
        Process::Read32(offset + 0x0E1CFE4, offset);
        u16 i = 4 * (basho - 1);
        Process::Write32(offset + 0x000100C + i, itemid * 0x10000);
        Process::Write8(offset + 0x0001010 + i, count);
    }

    void fished_item(u16 itemid, int count, int message) {
        u32 OffCheck = get_quest_offset();
        (CallFuncWrapper(0x009fc944))(OffCheck, itemid, 0, message, count, OffCheck);
    }
}
