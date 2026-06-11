#pragma once
#include "gfx/drawable.hpp"

#include <memory>
#include <vector>

class Pane : public Drawable {
public:
    enum class Position {
        TopLeft,
        TopMiddle,
        TopRight,
        CenterLeft,
        CenterMiddle,
        CenterRight,
        BottomLeft,
        BottomMiddle,
        BottomRight
    };
private:
    int x, y;
    Position anchor;
    Position coordinate_origin;
    std::shared_ptr<Pane> parent;
    std::vector<std::shared_ptr<Pane>> children;

public:
    Pane(int ox, int oy, Position anchor);
    ~Pane();

    Pane(const Pane&) = delete;
    Pane(Pane&&) = delete;

    Pane& operator=(const Pane&) = delete;
    Pane& operator=(Pane&&) = delete;
};