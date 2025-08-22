#include "Camera.hpp"

namespace CTRPluginFramework
{
    void Zoom(MenuEntry *entry) {
        u32 offset = 0x08000000;
        Process::Write32(offset + 0x0167B44, 0x406ED9EA);
        Process::Write32(offset + 0x0167B30, 0x400F4F8D);
    }
}
