#include "prop.h"
#include "raymath.h"

Prop::Prop(Vector2 pos, Texture2D tex):
     texture(tex), 
     world_pos(pos){

}

void Prop::Render(Vector2 knight_pos){
     Vector2 screen_pos{ Vector2Subtract(world_pos, knight_pos) };
     DrawTextureEx(texture, screen_pos, 0.f, scale, WHITE);
}

Rectangle Prop::get_collision_rec(Vector2 knight_pos){
     Vector2 screen_pos{ Vector2Subtract(world_pos, knight_pos) };
     return Rectangle{
          screen_pos.x,
          screen_pos.y,
          texture.width * scale,
          texture.height * scale
     };
}