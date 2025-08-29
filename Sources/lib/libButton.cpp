#include "lib/libButton.hpp"

TouchButton::TouchButton(UIntVector pos, UIntVector size, std::string label, std::function<void()> onClick)
    : _pos(pos), _size(size), _label(label), _onClick(onClick) {}

void TouchButton::Draw(Screen &screen) {
    screen.DrawRect(_pos.x, _pos.y, _size.x, _size.y, Color::White);
    screen.DrawRect(_pos.x, _pos.y, _size.x, _size.y, Color::Black, false);
    screen.DrawSysfont(_label, _pos.x + 5, _pos.y + 5, Color::Black);
}

void TouchButton::Update() {
    if (!Controller::IsKeysDown(Touchpad)) return;

    UIntVector t = Touch::GetPosition();
    UIntVector touchPos(t.x, t.y);

    if (touchPos.x >= _pos.x && touchPos.x <= _pos.x + _size.x &&
        touchPos.y >= _pos.y && touchPos.y <= _pos.y + _size.y) {
        if (_onClick) _onClick();
    }
}