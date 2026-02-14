#include "BaseCharacter.h"

BaseCharacter::BaseCharacter(){

}

Rectangle BaseCharacter::get_collision_rec(){
    return Rectangle{
        screen_pos.x,
        screen_pos.y,
        width * scale,
        height * scale
    };
}