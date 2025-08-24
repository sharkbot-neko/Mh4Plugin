#include "Movement.hpp"
#include <string>

namespace CTRPluginFramework
{

    void Z_Up_Down(MenuEntry *entry) {
        u32 offset;
        u32 cmp32;
        u32 data32;

        if(Controller::IsKeysDown(DPadUp + L))
        {
            if(Process::Read32(offset + 0x00E248F8 , cmp32) && cmp32 != 0x00000000)
            {
                Process::Read32(offset + 0x00E248F8 , data32);
                offset = data32;
                Process::Read32(offset + 0x00000E3D, data32);
                data32 += 0x00001A80;
                Process::Write32(offset + 0x00000E3D, data32);
                offset += 0x4;
            }
        }
        offset = 0;
        data32 = 0;
        if(Controller::IsKeysDown(DPadDown + L))
        {
            Process::Read32(offset + 0x00E248F8 , data32);
            offset = data32;
            Process::Read32(offset + 0x0000E3D , data32);
            data32 += 0xFFF9E580;
            Process::Write32(offset + 0x0000E3D , data32);
        }
    }

    void CoordMove(MenuEntry *entry) {
        u32 offset;
        u32 data32;
        if(Controller::IsKeysDown(DPadRight + L))
        {
            Process::Read32(offset + 0x00E248F8 , data32);
            offset = data32;
            Process::Read32(offset + 0x00000E38, data32);
            data32 += 0x00070FFF;
            Process::Write32(offset + 0x00000E38, data32);
            offset += 0x4;
        }
        offset = 0;
        data32 = 0;
        if(Controller::IsKeysDown(DPadLeft + L))
        {
            Process::Read32(offset + 0x00E248F8 , data32);
            offset = data32;
            Process::Read32(offset + 0x00000E38, data32);
            data32 += 0xFFF8F000;
            Process::Write32(offset + 0x00000E38, data32);
            offset += 0x4;
        }
        offset = 0;
        data32 = 0;
        if(Controller::IsKeysDown(DPadUp + L))
        {
            Process::Read32(offset + 0x00E248F8 , data32);
            offset = data32;
            Process::Read32(offset + 0x00000E40, data32);
            data32 += 0x00070FFF;
            Process::Write32(offset + 0x00000E40, data32);
            offset += 0x4;
        }
        offset = 0;
        data32 = 0;
        if(Controller::IsKeysDown(DPadDown + L))
        {
            Process::Read32(offset + 0x00E248F8 , data32);
            offset = data32;
            Process::Read32(offset + 0x00000E40, data32);
            data32 += 0xFFF8F000;
            Process::Write32(offset + 0x00000E40, data32);
            offset += 0x4;
        }
    }
}