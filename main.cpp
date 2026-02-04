#include "raylib.h"
#include "raymath.h"

class Character{
    public:
        Vector2 get_world_pos(){ return world_pos; }
        void set_screen_pos(int win_width, int win_height);
        void tick(float delta_time);

    private:
        Texture2D texture{};
        Texture2D idle{LoadTexture("characters/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("characters/knight_run_spritesheet.png")};
        Vector2 screen_pos{};
        Vector2 world_pos{};
        // 1: facing right, -1: facing left
        float right_left{1.f};
        // animation variables
        float running_time{};
        int frame{};
        const int max_frames{6};
        const float update_time{1.f / 12.f};
        const float speed{4.f};
};

void Character::set_screen_pos(int win_width, int win_height){
    screen_pos = {(float)win_width/2.0f - 4.0f * (0.5f * (float)texture.width/6.0f),
        (float)win_height/2.0f - 4.0f * (0.5f * (float)texture.height)};
}

void Character::tick(float delta_time){
    Vector2 direction{};
    // handle keyboard inputs
    if (IsKeyDown(KEY_A)) direction.x -= 1.0;
    if (IsKeyDown(KEY_D)) direction.x += 1.0;
    if (IsKeyDown(KEY_W)) direction.y -= 1.0;
    if (IsKeyDown(KEY_S)) direction.y += 1.0;

    // sprite movement check
    if (Vector2Length(direction) != 0.0){
        world_pos = Vector2Add(world_pos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? right_left = -1.f : right_left = 1.f;
        texture = run;
    } else {
        texture = idle;
    }

    // update animation frame
    running_time += delta_time;
    if (running_time >= update_time){
        frame++;
        running_time = 0.f;
        if (frame > max_frames) frame = 0;
    }

    //draw the character
    Rectangle source{
        frame * (float)texture.width / 6.f, 
        0.f, 
        right_left * (float)texture.width / 6.f, 
        (float)texture.height};
    Rectangle dest{
        screen_pos.x, 
        screen_pos.y, 
        4.0f * (float)texture.width / 6.0f, 
        4.0f * (float)texture.height};
    DrawTexturePro(texture, source, dest, Vector2{}, 0.f, WHITE);
}

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "My RPG");

    Texture2D game_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.0, 0.0};

    Character knight{};
    knight.set_screen_pos(window_width, window_height);

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        ClearBackground(WHITE);

        map_pos = Vector2Scale(knight.get_world_pos(), -1.f);
        
        // draw the map
        DrawTextureEx(game_map, map_pos, 0.0, 4.0, WHITE);

        knight.tick(GetFrameTime());

        EndDrawing();
    }
    UnloadTexture(game_map);
    CloseWindow();
}