#include "raylib.h"
#include "raymath.h"

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "My RPG");

    Texture2D game_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.0, 0.0};

    float speed{4.0};


    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;

        if (Vector2Length(direction) != 0.0){
            map_pos = Vector2Subtract(map_pos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        DrawTextureEx(game_map, map_pos, 0.0, 4.0, WHITE);

        EndDrawing();
    }
    UnloadTexture(game_map);
    CloseWindow();
}