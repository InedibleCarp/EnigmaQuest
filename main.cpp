#include "raylib.h"
#include "raymath.h"
#include "character.h"

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "My RPG");

    Texture2D game_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.0, 0.0};
    const float map_scale{4.0f};

    Character knight{};
    knight.set_screen_pos(window_width, window_height);

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        map_pos = Vector2Scale(knight.get_world_pos(), -1.f);
        
        // draw the map
        DrawTextureEx(game_map, map_pos, 0.0, map_scale, WHITE);

        // check map bounds
        knight.tick(GetFrameTime());
        if (knight.get_world_pos().x < 0.f ||
            knight.get_world_pos().y < 0.f ||
            knight.get_world_pos().x + window_width > game_map.width * map_scale ||
            knight.get_world_pos().y + window_height > game_map.height * map_scale){
                
                knight.undo_movement();
            }

        EndDrawing();
    }
    UnloadTexture(game_map);
    CloseWindow();
}