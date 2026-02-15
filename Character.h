#ifndef CHARACTER_H
#define CHARACTER_H

#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter{
    public:
        Character(int win_width, int win_height);
        virtual void tick(float delta_time) override;
        virtual Vector2 get_screen_pos() override;
        Rectangle get_weapon_rec() { return weapon_collision_rec; }
        float get_health() const { return health; }
        void take_damage(float damage);

    private:
        int window_width{};
        int window_height{};
        Texture2D weapon{LoadTexture("characters/weapon_sword.png")};
        Rectangle weapon_collision_rec{};
        float health{100.f};
        
};

#endif