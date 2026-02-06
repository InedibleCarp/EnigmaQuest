#include "raylib.h"

class Character{
    public:
        Character();
        Vector2 get_world_pos(){ return world_pos; }
        void set_screen_pos(int win_width, int win_height);
        void tick(float delta_time);
        void undo_movement(){ world_pos = world_pos_last_frame; }

    private:
        Texture2D texture{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screen_pos{};
        Vector2 world_pos{};
        Vector2 world_pos_last_frame{};
        // 1: facing right, -1: facing left
        float right_left{1.f};
        // animation variables
        float running_time{};
        int frame{};
        int max_frames{6};
        float update_time{1.f / 12.f};
        float speed{4.f};
        float width{};
        float height{};
};