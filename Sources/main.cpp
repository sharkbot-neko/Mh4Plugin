#include <3ds.h>
#include "csvc.h"
#include <CTRPluginFramework.hpp>
#include "cheats.hpp"
#include "ModMenu.hpp"

#include <vector>

namespace CTRPluginFramework
{
    // This patch the NFC disabling the touchscreen when scanning an amiibo, which prevents ctrpf to be used
    static void    ToggleTouchscreenForceOn(void)
    {
        static u32 original = 0;
        static u32 *patchAddress = nullptr;

        if (patchAddress && original)
        {
            *patchAddress = original;
            return;
        }

        static const std::vector<u32> pattern =
        {
            0xE59F10C0, 0xE5840004, 0xE5841000, 0xE5DD0000,
            0xE5C40008, 0xE28DD03C, 0xE8BD80F0, 0xE5D51001,
            0xE1D400D4, 0xE3510003, 0x159F0034, 0x1A000003
        };

        Result  res;
        Handle  processHandle;
        s64     textTotalSize = 0;
        s64     startAddress = 0;
        u32 *   found;

        if (R_FAILED(svcOpenProcess(&processHandle, 16)))
            return;

        svcGetProcessInfo(&textTotalSize, processHandle, 0x10002);
        svcGetProcessInfo(&startAddress, processHandle, 0x10005);
        if(R_FAILED(svcMapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, processHandle, (u32)startAddress, textTotalSize)))
            goto exit;

        found = (u32 *)Utils::Search<u32>(0x14000000, (u32)textTotalSize, pattern);

        if (found != nullptr)
        {
            original = found[13];
            patchAddress = (u32 *)PA_FROM_VA((found + 13));
            found[13] = 0xE1A00000;
        }

        svcUnmapProcessMemoryEx(CUR_PROCESS_HANDLE, 0x14000000, textTotalSize);
exit:
        svcCloseHandle(processHandle);
    }

    // This function is called before main and before the game starts
    // Useful to do code edits safely
    void    PatchProcess(FwkSettings &settings)
    {
        ToggleTouchscreenForceOn();
    }

    // This function is called when the process exits
    // Useful to save settings, undo patchs or clean up things
    void    OnProcessExit(void)
    {
        ToggleTouchscreenForceOn();
    }

    void    InitMenu(PluginMenu &menu)
    {
        MenuFolder *player = new MenuFolder("プレイヤー");
        *player += new MenuEntry("名前", nullptr, Name);
        *player += new MenuEntry("コメント", nullptr, Comment);
        *player += new MenuEntry("お金", nullptr, Money);
        *player += new MenuEntry("ハンターランク", nullptr, HunterRank);
        *player += new MenuEntry("スピード変更", Speed);
        menu += player;

        MenuFolder *movement = new MenuFolder("移動");
        // *movement += new MenuEntry("Z座標移動", Z_Up_Down, "L+UpとL+Downで移動します。");
        *movement += new MenuEntry("座標移動", CoordMove, "L+上下左右で移動します。");
        menu += movement;

        MenuFolder *Item = new MenuFolder("アイテム");
        *Item += new MenuEntry("アイテムを取得(関数)", nullptr, ItemGet);
        *Item += new MenuEntry("無限の砥石", InfStone);
        *Item += new MenuEntry("アイテム減らない", nullptr, ItemNoDelete);
        menu += Item;

        MenuFolder *quest = new MenuFolder("クエスト");
        *quest += new MenuEntry("クエスト中のプレイヤー名", nullptr, Quest_playerName, "クエスト中専用です");
        *quest += new MenuEntry("アイテムを釣る(関数)", fish_allitem, "上キーとAボタンでアイテム選択、\n下キーとAボタンで釣る。");
        *quest += new MenuEntry("クエストクリア", nullptr, quest_clear);
        *quest += new MenuEntry("クエスト即帰還", nullptr, quest_gohome);
        *quest += new MenuEntry("定型文編集画面", teikei_text, "YとLキーを押して定型文・チャットを開きます。");
        *quest += new MenuEntry("切れ味無限", kieraji_inf);
        *quest += new MenuEntry("集会所で装備変更(関数)", shukai_armor, "一度ステータスを開いてから実行すること。");
        // *quest += new MenuEntry("ステータスを開く", nullptr, open_status);
        menu += quest;

        MenuFolder *camera = new MenuFolder("カメラ");
        *camera += new MenuEntry("ズーム", Zoom);
        menu += camera;
    }

    void socInit_Plugin() {
        u32 *socBuffer = nullptr;
        constexpr u32 SOC_BUFFER_ADDR = 0x7500000;
        constexpr u32 SOC_BUFFER_SIZE = 0x100000;

        u8 *soundBuffer = nullptr;
        u8 *micBuffer = nullptr;

        Result ret = RL_SUCCESS;
        if (System::IsCitra()) {
            socBuffer = (u32 *)aligned_alloc(0x1000, SOC_BUFFER_SIZE);
            if (!socBuffer)
            ret = RL_FATAL;
        } else
            ret = svcControlMemoryUnsafe((u32 *)&socBuffer, SOC_BUFFER_ADDR, SOC_BUFFER_SIZE, MemOp(MEMOP_REGION_SYSTEM | MEMOP_ALLOC), MemPerm(MEMPERM_READ | MEMPERM_WRITE));

        if (R_FAILED(ret) || !socBuffer)
            OSD::Notify("alloc socBuffer failed");
        else {
            ret = socInit(socBuffer, SOC_BUFFER_SIZE);
            if (R_FAILED(ret)) {
            OSD::Notify(Utils::Format("socInit: 0x%lX failed", ret));
            socExit();
            } else
            OSD::Notify("socInit success");
        }
    }

    int     main(void)
    {
        PluginMenu *menu = new PluginMenu("CTRPF MonsterHunter 4 OLD", 1, 0, 0,
                                            "モンスターハンター4のOLD専用プラグイン。");
                                            
        

        // Synnchronize the menu with frame event
        menu->SynchronizeWithFrame(true);

        // Init our menu entries & folders
        InitMenu(*menu);

        // Launch menu and mainloop
        menu->Callback(ModMenu);
        menu->Run();

        delete menu;

        // Exit plugin
        return (0);
    }
}
