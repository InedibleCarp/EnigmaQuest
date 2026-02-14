#include "Enemy.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture){

    world_pos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;


    width = texture.width / max_frames;
    height = texture.height;
}

void Enemy::tick(float delta_time){
    BaseCharacter::tick(delta_time);
}
