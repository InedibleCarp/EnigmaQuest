#include "character.h"
#include "raymath.h"

Character::Character(){
    width = texture.width / max_frames;
    height = texture.height;
}

void Character::set_screen_pos(int win_width, int win_height){
    screen_pos = {(float)win_width/2.0f - 4.0f * (0.5f * width),
        (float)win_height/2.0f - 4.0f * (0.5f * height)};
}

void Character::tick(float delta_time){
    world_pos_last_frame = world_pos;
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

    // update animation frame
    running_time += delta_time;
    if (running_time >= update_time){
        frame++;
        running_time = 0.f;
        if (frame > max_frames) frame = 0;
    }

    //draw the character
    Rectangle source{
        frame * width, 
        0.f, 
        right_left * width, 
        height};
    Rectangle dest{
        screen_pos.x, 
        screen_pos.y, 
        4.0f * width, 
        4.0f * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}