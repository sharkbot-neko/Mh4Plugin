#include "lib/libQuest.hpp"
#include "CallFuncWrapper.hpp"

namespace CTRPluginFramework
{
    u32 get_quest_offset() {
        u32 OffCheck;
        Process::Read32(0x00000000 + 0x00E1CFE4 , OffCheck);
        return OffCheck;
    }

    bool is_the_quest() {
        u32 OffCheck = get_quest_offset();
        if (OffCheck != 0x00000000) {
            return true;
        } else {
            return false;
        }
    }

    void set_name(std::string string) {
        Process::WriteString(get_quest_offset() + 0x0000E80, string, StringFormat::Utf16);

    }
}
