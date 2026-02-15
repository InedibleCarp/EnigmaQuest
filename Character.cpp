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

    Vector2 origin{};
    Vector2 offset{};
    float rotation{};
    if (right_left > 0.f){
        origin = {0.f, weapon.height * scale};
        offset = {35.f, 55.f};
        weapon_collision_rec = {
            get_screen_pos().x + offset.x,
            get_screen_pos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = 35.f;
    } else {
        origin = {weapon.width * scale, weapon.height * scale};
        offset = {25.f, 55.f};
        weapon_collision_rec = {
            get_screen_pos().x + offset.x - weapon.width * scale,
            get_screen_pos().y + offset.y - weapon.height * scale,
            weapon.width * scale,
            weapon.height * scale
        };
        rotation = -35.f;
    }
    
    // draw the sword
    Rectangle source{
        0.f, 
        0.f, 
        static_cast<float>(weapon.width) * right_left, 
        static_cast<float>(weapon.height)};
    Rectangle dest{
        get_screen_pos().x + offset.x,
        get_screen_pos().y + offset.y,
        weapon.width * scale,
        weapon.height * scale
    };
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(
        weapon_collision_rec.x,
        weapon_collision_rec.y,
        weapon_collision_rec.width,
        weapon_collision_rec.height,
        RED
    );
}
