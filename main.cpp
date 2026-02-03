#include "raylib.h"
#include "raymath.h"

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "My RPG");

    Texture2D game_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.0, 0.0};
    float speed{4.0};

    Texture2D knight{};
    Texture2D knight_idle = LoadTexture("characters/knight_idle_spritesheet.png");
    Texture2D knight_run = LoadTexture("characters/knight_run_spritesheet.png");
    Vector2 knight_pos{
        (float)window_width/2.0f - 4.0f * (0.5f * (float)knight.width/6.0f),
        (float)window_height/2.0f - 4.0f * (0.5f * (float)knight.height)};
    
    // 1: facing right, -1: facing left
    float right_left{1.f};

    // animation variables
    float running_time{};
    int frame{};
    const int max_frames{6};
    const float update_time{1.f / 12.f};
    


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
            direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
            knight = knight_run;
        } else {
            knight = knight_idle;
        }

        DrawTextureEx(game_map, map_pos, 0.0, 4.0, WHITE);

        // update animation frame
        running_time += GetFrameTime();
        if (running_time >= update_time){
            frame++;
            running_time = 0.f;
            if (frame > max_frames) frame = 0;
        }
        
        //draw the character
        Rectangle source{
            frame * (float)knight.width / 6.f, 
            0.f, 
            right_left * (float)knight.width / 6.f, 
            (float)knight.height};
        Rectangle dest{knight_pos.x, knight_pos.y, 4.0f * (float)knight.width / 6.0f, 4.0f * (float)knight.height};
        DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

        EndDrawing();
    }
    UnloadTexture(game_map);
    CloseWindow();
}