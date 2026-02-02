#include "raylib.h"

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "My RPG");

    Texture2D game_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 map_pos{0.0, 0.0};
        DrawTextureEx(game_map, map_pos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(game_map);
    CloseWindow();
}