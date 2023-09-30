#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D)

    private:
        /* data */
        Vector3 position;
        Input *input;

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();

        void _process(double delta) override;
        void _physics_process(double delta) override;

};
    

#endif

