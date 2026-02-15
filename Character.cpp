#include "Character.h"
#include "raymath.h"

Character::Character(int win_width, int win_height) : 
    window_width(win_width), window_height(win_height){
    width = texture.width / max_frames;
    height = texture.height;
}

Vector2 Character::get_screen_pos(){
    return Vector2{static_cast<float>(window_width)/2.0f - scale * (0.5f * width),
        static_cast<float>(window_height)/2.0f - scale * (0.5f * height)};
}

void Character::tick(float delta_time){
    // handle keyboard inputs
    if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
    if (IsKeyDown(KEY_S)) velocity.y += 1.0;

    BaseCharacter::tick(delta_time);
}
