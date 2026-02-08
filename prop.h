#include "raylib.h"

class Prop{
    public:
        Prop(Vector2 pos, Texture2D tex);
        void Render(Vector2 knight_pos);
        Rectangle get_collision_rec(Vector2 knight_pos);

    private:
        Texture2D texture{};
        Vector2 world_pos{};
        float scale{4.f};
};