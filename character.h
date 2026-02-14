#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter{
    public:
        Character(int win_width, int win_height);
        virtual void tick(float delta_time) override;

    private:
        
};