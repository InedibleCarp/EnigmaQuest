#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture){

    world_pos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / max_frames;
    height = texture.height;
    speed = 3.5f;
}

void Enemy::tick(float delta_time){
    Vector2 to_target = Vector2Subtract(target->get_screen_pos(), screen_pos);
    to_target = Vector2Scale(Vector2Normalize(to_target), speed);
    // move the enemy
    world_pos = Vector2Add(world_pos, to_target);

    screen_pos = Vector2Subtract(world_pos, target->get_world_pos());
    BaseCharacter::tick(delta_time);
}
