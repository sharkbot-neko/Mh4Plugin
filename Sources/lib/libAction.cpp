#include "lib/libAction.hpp"
#include "CallFuncWrapper.hpp"

namespace CTRPluginFramework
{
    void excute_nikuyaki() {
        u32 OffCheck = get_quest_offset();
        (CallFuncWrapper(0x009a0fb4))(OffCheck,0,0x47,2);
    }

    void excute_fish() {
        u32 OffCheck = get_quest_offset();
        (CallFuncWrapper(0x009a0fb4))(OffCheck,0,0x5b);
    }

    void excute_action(int actionid) {
        u32 OffCheck = get_quest_offset();
        (CallFuncWrapper(0x009a0fb4))(OffCheck,0,actionid);
    }
}
