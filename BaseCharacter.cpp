#include "BaseCharacter.h"
#include "raymath.h"

BaseCharacter::BaseCharacter(){

}

Rectangle BaseCharacter::get_collision_rec(){
    return Rectangle{
        get_screen_pos().x,
        get_screen_pos().y,
        width * scale,
        height * scale
    };
}

void BaseCharacter::take_damage(float damage){
    health -= damage;
    if (health <= 0.f){
        health = 0.f;
        set_alive(false);
    }
}

void BaseCharacter::apply_knockback(Vector2 direction, float force, float duration){
    knockback_vel = Vector2Scale(direction, force);
    knockback_duration = duration;
}

void BaseCharacter::reset(Vector2 start_pos){
    world_pos = start_pos;
    world_pos_last_frame = start_pos;
    health = max_health;
    set_alive(true);
    velocity = {};
    knockback_vel = {};
    knockback_duration = 0.f;
    running_time = 0.f;
    frame = 0;
    right_left = 1.f;
    tint = WHITE;
    texture = idle;
}

void BaseCharacter::tick(float delta_time){
    world_pos_last_frame = world_pos;

    // apply knockback
    if (knockback_duration > 0.f){
        world_pos = Vector2Add(world_pos, Vector2Scale(knockback_vel, delta_time));
        knockback_duration -= delta_time;
        if (knockback_duration < 0.f) knockback_duration = 0.f;
    }

    // update animation frame
    running_time += delta_time;
    if (running_time >= update_time){
        frame++;
        running_time = 0.f;
        if (frame > max_frames) frame = 0;
    }

    // sprite movement check
    if (Vector2Length(velocity) != 0.0){
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(velocity), speed));
        velocity.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    } else {
        texture = idle;
    }
    velocity = {};

    //draw the character
    Rectangle source{
        frame * width,
        0.f,
        right_left * width,
        height};
    Rectangle dest{
        get_screen_pos().x,
        get_screen_pos().y,
        scale * width,
        scale * height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, tint);
}