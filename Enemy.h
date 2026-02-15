#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter{
    public:
        Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
        virtual void tick(float delta_time) override;
        void set_target(Character* character){ target = character; }
        virtual Vector2 get_screen_pos() override;

    private:
        Character* target{};
};