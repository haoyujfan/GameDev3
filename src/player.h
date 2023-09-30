#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>

using namespace godot;

class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D)

    private:
        /* data */

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();

        void _process(double delta) override;
};
    

#endif

