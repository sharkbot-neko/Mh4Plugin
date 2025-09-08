#include "Test.hpp"
#include "CallFuncWrapper.hpp"
#include "lib/libPlayer.hpp"
#include "lib/libArm.hpp"
#include "lib/libQuest.hpp"

#define DAT_00d0e018_ADDR 0x00d0e018

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

    void drawText(MenuEntry *entry) {
        u32 param_1;

        Process::Read32(0x001052BC, param_1);

        // 文字列描画用バッファ
        char buf[24] = {0};
        int tmp = 0;

        // 文字列生成関数
        typedef void (*Func1Type)(char*, u32, const char*, int*);
        Func1Type func = reinterpret_cast<Func1Type>(0x00100098 | 1); // Thumb関数なので +1
        func(buf, 0xF, "Hello World", &tmp);

        // 文字列変換関数
        typedef void (*Func2Type)(char*);
        Func2Type func2 = reinterpret_cast<Func2Type>(0x00302db0 | 1); // Thumb
        func2(buf);

        // 描画用バッファ生成
        char buffer[32] = {0};
        char aux[4] = {0};
        typedef u32 (*Func3Type)(char*, u32, char*, u32, char*);
        Func3Type func3 = reinterpret_cast<Func3Type>(0x00a45b88 | 1); // Thumb
        func3(buf, 0xFFFFFFFF, buffer, 0x20, aux);

        // オブジェクトに描画バッファをセット
        typedef void (*Func4Type)(u32, u32, u32, char*);
        Func4Type func4 = reinterpret_cast<Func4Type>(0x005530a4 | 1); // Thumb

        uint32_t DAT_00d0e018_val;
        Process::Read32(0x00D0E018, DAT_00d0e018_val);

        uint32_t dat_val = 0;
        Process::Read32(0x00D0E018, dat_val);
        OSD::Notify(Utils::Format("DAT_00d0e018 = %08X", dat_val));

        uint32_t test_val = 0;
        Process::Read32(dat_val, test_val);
        OSD::Notify(Utils::Format("*(DAT_00d0e018) = %08X", test_val));

        // func4(param_1, DAT_00d0e018_val, 0x70055e9d, buffer);

        // 描画オブジェクトのフラグやサイズを設定
        int obj = *(int*)(param_1 + 0x32d20);
        if (obj != 0) {
            *(uint32_t*)(obj + 0x30) = 0x41b00000; // 描画サイズやスケール
            *(uint8_t*)(obj + 0x42) = 3;           // 描画モード
        }
    }

}
