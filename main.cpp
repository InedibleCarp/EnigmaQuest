#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

enum GameState { MAIN_MENU, PLAYING, GAME_OVER };

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "EnigmaQuest");
    InitAudioDevice();

    Music music = LoadMusicStream("audio/level_soundtrack.mp3");
    PlayMusicStream(music);

    Texture2D game_map = LoadTexture("nature_tileset/OpenWorldMap24x24.png");
    Vector2 map_pos{0.0, 0.0};
    const float map_scale{4.0f};

    Character knight{window_width, window_height};

    Prop props[2]{
        Prop{Vector2{600.f, 300.f}, LoadTexture("nature_tileset/Rock.png")},
        Prop{Vector2{400.f, 500.f}, LoadTexture("nature_tileset/Log.png")}};

    Enemy goblin{
        Vector2{800.f, 300.f},
        LoadTexture("characters/goblin_idle_spritesheet.png"),
        LoadTexture("characters/goblin_run_spritesheet.png"),
        60.f
    };

    Enemy slime{
        Vector2{500.f, 700.f},
        LoadTexture("characters/slime_idle_spritesheet.png"),
        LoadTexture("characters/slime_run_spritesheet.png"),
        40.f
    };

    Enemy* enemies[]{
        &goblin, &slime
    };
    constexpr int enemy_count = sizeof(enemies) / sizeof(enemies[0]);

    for (auto enemy: enemies){
        enemy->set_target(&knight);
    }

    GameState game_state{MAIN_MENU};

    auto reset_game = [&](){
        knight.reset();
        goblin.reset({800.f, 300.f});
        slime.reset({500.f, 700.f});
    };

    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        UpdateMusicStream(music);

        if (game_state == MAIN_MENU){
            ClearBackground(BLACK);

            // Title
            const char* title = "EnigmaQuest";
            int title_width = MeasureText(title, 52);
            DrawText(title, window_width/2 - title_width/2, 70, 52, GOLD);

            // Subtitle
            const char* subtitle = "A 2D Action RPG";
            int sub_width = MeasureText(subtitle, 18);
            DrawText(subtitle, window_width/2 - sub_width/2, 135, 18, LIGHTGRAY);

            // Divider
            DrawLine(60, 163, window_width - 60, 163, DARKGRAY);

            // Blinking "Press ENTER to Play"
            if ((int)(GetTime() * 2) % 2 == 0){
                const char* play_text = "Press ENTER to Play";
                int play_width = MeasureText(play_text, 22);
                DrawText(play_text, window_width/2 - play_width/2, 193, 22, WHITE);
            }

            // Controls section
            const char* ctrl_header = "Controls";
            int ctrl_header_w = MeasureText(ctrl_header, 17);
            DrawText(ctrl_header, window_width/2 - ctrl_header_w/2, 250, 17, GRAY);

            const char* ctrl1 = "WASD   -   Move";
            int ctrl1_w = MeasureText(ctrl1, 15);
            DrawText(ctrl1, window_width/2 - ctrl1_w/2, 273, 15, DARKGRAY);

            const char* ctrl2 = "LMB    -   Attack";
            int ctrl2_w = MeasureText(ctrl2, 15);
            DrawText(ctrl2, window_width/2 - ctrl2_w/2, 293, 15, DARKGRAY);

            // Quit hint
            const char* quit_text = "ESC to Quit";
            int quit_width = MeasureText(quit_text, 14);
            DrawText(quit_text, window_width/2 - quit_width/2, 355, 14, DARKGRAY);

            if (IsKeyPressed(KEY_ENTER)){
                reset_game();
                game_state = PLAYING;
            }

        } else if (game_state == PLAYING){
            ClearBackground(WHITE);

            map_pos = Vector2Scale(knight.get_world_pos(), -1.f);

            // draw the map
            DrawTextureEx(game_map, map_pos, 0.0, map_scale, WHITE);

            // draw the props
            for (auto prop : props){
                prop.Render(knight.get_world_pos());
            }

            // health display
            std::string knights_health = "Health: ";
            knights_health.append(std::to_string(knight.get_health()), 0, 5);
            DrawText(knights_health.c_str(), 55.f, 45.f, 40, RED);

            knight.tick(GetFrameTime());

            // check map bounds
            if (knight.get_world_pos().x < 0.f ||
                knight.get_world_pos().y < 0.f ||
                knight.get_world_pos().x + window_width > game_map.width * map_scale ||
                knight.get_world_pos().y + window_height > game_map.height * map_scale){

                    knight.undo_movement();
                }

            // check prop collision
            for (auto prop: props){
                if (CheckCollisionRecs(prop.get_collision_rec(knight.get_world_pos()), knight.get_collision_rec())){
                    knight.undo_movement();
                }
            }

            for (auto enemy : enemies){
                enemy->tick(GetFrameTime());
            }

            // enemy to enemy collisions
            for (int i = 0; i < enemy_count; i++){
                for (int j = i + 1; j < enemy_count; j++){
                    enemies[i]->resolve_overlap(*enemies[j]);
                }
            }

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                for (auto enemy : enemies){
                    if (CheckCollisionRecs(enemy->get_collision_rec(), knight.get_weapon_rec())){
                        enemy->take_damage(knight.get_damage());
                        Vector2 knockback_dir = Vector2Normalize(
                            Vector2Subtract(enemy->get_world_pos(), knight.get_world_pos()));
                        enemy->apply_knockback(knockback_dir, 250.f, 0.25f);
                    }
                }
            }

            if (!knight.get_alive()){
                game_state = GAME_OVER;
            }

        } else { // GAME_OVER
            ClearBackground(BLACK);

            const char* game_over = "Game Over!";
            int go_width = MeasureText(game_over, 52);
            DrawText(game_over, window_width/2 - go_width/2, 120, 52, RED);

            const char* menu_prompt = "Press ENTER for Main Menu";
            int mp_width = MeasureText(menu_prompt, 20);
            DrawText(menu_prompt, window_width/2 - mp_width/2, 210, 20, WHITE);

            if (IsKeyPressed(KEY_ENTER)){
                game_state = MAIN_MENU;
            }
        }

        EndDrawing();
    }
    UnloadTexture(game_map);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}