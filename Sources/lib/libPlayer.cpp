#include "CallFuncWrapper.hpp"
#include "lib/libPlayer.hpp"

namespace CTRPluginFramework
{
    void set_money(u32 ammont) {
        Process::Write32(0x0ECD5B4, ammont);
    }
}
