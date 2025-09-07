#include "Test.hpp"
#include "CallFuncWrapper.hpp"
#include "lib/libPlayer.hpp"
#include "lib/libArm.hpp"
#include "lib/libQuest.hpp"

namespace CTRPluginFramework
{
    void UpdatePlayer(MenuEntry *entry) {
        update_player();
    }

    void TestingArm(MenuEntry *entry) {
        arm11::Arm caller(0x009DE864);
        caller.Write([&](arm11::Arm& a) {
            a.Bx(arm11::LR);
        });
        caller.Flush();

    }
}
