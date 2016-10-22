#pragma once

#include "Box.h"
#include "game/components/HoldQueue.h"
#include "system/Color.h"


class AppContext;
class Font;
class Texture;

namespace Layout {
class LeftSidebarBox : public Layout::Box {
public:
    LeftSidebarBox(AppContext&, int height);

    void setPosition(int x, int y) override;

    void update();
    void updateGoalCounter(unsigned);
    void updateLevelCounter(unsigned);

    void draw(GraphicsContext&) const;

    HoldQueue& holdQueue() { return hold_queue; }

private:
    static constexpr int text_height = 30;
    static constexpr int text_padding = 10;
    static constexpr int item_padding = 10;
    const RGBAColor box_color = 0x0A0AFF80_rgba;

    std::shared_ptr<Font> font_label;
    std::shared_ptr<Font> font_content;

    std::unique_ptr<Texture> tex_hold;
    HoldQueue hold_queue;

    ::Rectangle rect_goal;
    std::unique_ptr<Texture> tex_goal;
    std::unique_ptr<Texture> tex_goal_counter;

    ::Rectangle rect_level;
    std::unique_ptr<Texture> tex_level;
    std::unique_ptr<Texture> tex_level_counter;
};
} // namespace Layout