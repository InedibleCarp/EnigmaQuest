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
    if (!get_alive()) return;
    velocity = Vector2Subtract(target->get_screen_pos(), get_screen_pos());
    if (Vector2Length(velocity) < radius) velocity = {};
    BaseCharacter::tick(delta_time);
    
    if (CheckCollisionRecs(target->get_collision_rec(), get_collision_rec())){
        target->take_damage(damange_per_sec * delta_time);
    }
}

Vector2 Enemy::get_screen_pos(){
    return Vector2Subtract(world_pos, target->get_world_pos());
}
