#include "Character.h"
#include "raymath.h"

Character::Character(int win_width, int win_height){
    width = texture.width / max_frames;
    height = texture.height;
    screen_pos = {static_cast<float>(win_width)/2.0f - scale * (0.5f * width),
        static_cast<float>(win_height)/2.0f - scale * (0.5f * height)};
}

void Character::tick(float delta_time){
    BaseCharacter::tick(delta_time);

    Vector2 direction{};
    // handle keyboard inputs
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;

    // sprite movement check
    if (Vector2Length(direction) != 0.0){
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    } else {
        texture = idle;
    }
}
