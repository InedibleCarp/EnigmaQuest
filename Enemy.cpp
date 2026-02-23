#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture, float max_hp){
    world_pos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;
    width = texture.width / max_frames;
    height = texture.height;
    speed = 3.5f;
    health = max_hp;
    max_health = max_hp;
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

void Enemy::reset(Vector2 start_pos){
    BaseCharacter::reset(start_pos);
}

void Enemy::resolve_overlap(Enemy& other){
    if (!get_alive() || !other.get_alive()) return;

    const float this_radius = (width * scale) * 0.5f;
    const float other_radius = (other.width * other.scale) * 0.5f;
    const float min_distance = this_radius + other_radius;

    const Vector2 this_center = Vector2Add(world_pos, Vector2{this_radius, this_radius});
    const Vector2 other_center = Vector2Add(other.world_pos, Vector2{other_radius, other_radius});
    Vector2 delta = Vector2Subtract(this_center, other_center);
    float distance = Vector2Length(delta);

    if (distance >= min_distance) return;

    if (distance == 0.f){
        delta = Vector2{1.f, 0.f};
        distance = 1.f;
    }

    const Vector2 separation_dir = Vector2Scale(delta, 1.f / distance);
    const float push_amount = (min_distance - distance) * 0.5f;

    world_pos = Vector2Add(world_pos, Vector2Scale(separation_dir, push_amount));
    other.world_pos = Vector2Add(other.world_pos, Vector2Scale(separation_dir, -push_amount));
}