#pragma once
#include "CTRPluginFramework.hpp"
#include <functional>

using namespace CTRPluginFramework;

class TouchButton {
public:
    TouchButton(UIntVector pos, UIntVector size, std::string label, std::function<void()> onClick);

    void Draw(Screen &screen);

    void Update();

private:
    UIntVector _pos;
    UIntVector _size;
    std::string _label;
    std::function<void()> _onClick;
};
