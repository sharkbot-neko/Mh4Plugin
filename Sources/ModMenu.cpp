#include "ModMenu.hpp"
#include <string>
#include <CTRPluginFramework.hpp>
#include "modmenu_items.hpp"

namespace CTRPluginFramework
{
    bool opend_modmenu = false;
    bool initd_modmenu = false;
    std::vector<const std::vector<ModMenuItems>*> menu_stack;
    std::vector<int> select_stack;

    void ModMenu_test(void) {
        OSD::Notify("test");
        return;
    }

    void run_cheat(void) {
        if (zoom) {
            u32 offset = 0x08000000;
            Process::Write32(offset + 0x0167B44, 0x406ED9EA);
            Process::Write32(offset + 0x0167B30, 0x400F4F8D);
        }
    }

    void InitModMenu() {
        menu_stack.clear();
        select_stack.clear();
        static const std::vector<ModMenuItems> root_items(AllModMenuItems,
            AllModMenuItems + sizeof(AllModMenuItems)/sizeof(AllModMenuItems[0]));
        menu_stack.push_back(&root_items);
        select_stack.push_back(0);
    }

    void ModMenu(void) {
        if (!initd_modmenu) {
            InitModMenu();
            initd_modmenu = true;
        }

        OSD::Run([](const Screen &screen)
        {
            if (!screen.IsTop) return false;
            if (!opend_modmenu) return false;

            screen.DrawRect(0, 0, 200, 240, Color::White);

            const auto& items = *menu_stack.back();
            int now_select = select_stack.back();

            for (size_t i = 0; i < items.size(); i++) {
                const auto& m = items[i];
                std::string prefix = (i == (size_t)now_select ? ">" : " ");

                if (m.type == ItemType::Folder) {
                    screen.DrawSysfont(prefix + m.name, 0, i * 15, Color::Red);
                } else if (m.type == ItemType::Function) {
                    screen.DrawSysfont(prefix + m.name, 0, i * 15, Color::Black);
                } else if (m.type == ItemType::Toggle) {
                    if (m.toggle && *m.toggle) {
                        screen.DrawSysfont(prefix + m.name + " [ON]", 0, i * 15, Color::Green);
                    } else if (m.toggle) {
                        screen.DrawSysfont(prefix + m.name + " [OFF]", 0, i * 15, Color::Red);
                    }
                }
            }

            return true;
        });

        if (Controller::IsKeysPressed(R + DPadLeft)) {
            opend_modmenu = !opend_modmenu;
        }

        if (!opend_modmenu) return;

        auto& now_select = select_stack.back();
        const auto& items = *menu_stack.back();

        if (Controller::IsKeysPressed(DPadDown)) {
            now_select++;
            if (now_select >= (int)items.size()) now_select = 0;
        }
        if (Controller::IsKeysPressed(DPadUp)) {
            now_select--;
            if (now_select < 0) now_select = items.size() - 1;
        }

        if (Controller::IsKeysPressed(A)) {
            const auto& m = items[now_select];
            if (m.type == ItemType::Folder) {
                menu_stack.push_back(&m.folder.items);
                select_stack.push_back(0);
            } else if (m.type == ItemType::Function && m.function != nullptr) {
                m.function();
            } else if (m.type == ItemType::Toggle) {
                if (m.toggle) *m.toggle = !*m.toggle; 
            }
        }

        if (Controller::IsKeysPressed(B)) {
            if (menu_stack.size() > 1) {
                menu_stack.pop_back();
                select_stack.pop_back();
            }
        }

        run_cheat();
    }


}