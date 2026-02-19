#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
#include <string>

int main(){
    const int window_width{384};
    const int window_height{384};

    InitWindow(window_width, window_height, "My RPG");
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

    for (auto enemy: enemies){
        enemy->set_target(&knight);
    }

    bool paused{false};
    SetTargetFPS(60);
    while(!WindowShouldClose()){
        BeginDrawing();
        UpdateMusicStream(music);
        ClearBackground(WHITE);

        // toggle pause (only while alive)
        if (IsKeyPressed(KEY_ESCAPE) && knight.get_alive()){
            paused = !paused;
            paused ? PauseMusicStream(music) : ResumeMusicStream(music);
        }

        map_pos = Vector2Scale(knight.get_world_pos(), -1.f);

        // draw the map
        DrawTextureEx(game_map, map_pos, 0.0, map_scale, WHITE);

        // draw the props
        for (auto prop : props){
            prop.Render(knight.get_world_pos());
        }

        if (!knight.get_alive()){
            DrawText("Game Over!", 55.f, 45.f, 40, RED);
            EndDrawing();
            continue;
        } else if (paused){
            // dim overlay
            DrawRectangle(0, 0, window_width, window_height, Fade(BLACK, 0.5f));

            // title
            const char* pause_title = "PAUSED";
            int title_size{40};
            DrawText(pause_title,
                (window_width - MeasureText(pause_title, title_size)) / 2,
                130, title_size, WHITE);

            // options
            const char* resume_text = "ESC - Resume";
            const char* quit_text   = "Q   - Quit";
            int opt_size{20};
            DrawText(resume_text,
                (window_width - MeasureText(resume_text, opt_size)) / 2,
                200, opt_size, LIGHTGRAY);
            DrawText(quit_text,
                (window_width - MeasureText(quit_text, opt_size)) / 2,
                230, opt_size, LIGHTGRAY);

            if (IsKeyPressed(KEY_Q)) break;
        } else { // character is alive and playing
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
        }

        EndDrawing();
    }
    UnloadTexture(game_map);
    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();
}