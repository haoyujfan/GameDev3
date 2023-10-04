#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input.hpp>
#include "raycast.h"

using namespace godot;

class Player : public CharacterBody3D {
    GDCLASS(Player, CharacterBody3D)

    private:
        /* data */
        Vector3 position;
        Vector3 velocity;
        Input *input;
        Raycast *ray1;
        Raycast *ray2;
        Raycast *ray3;
        Raycast *ray4;
        double gravity;
        double jump_velocity;
        double speed;
        bool jumped;
        bool hanging;

    protected:
        static void _bind_methods();

    public:
        Player();
        ~Player();

        void _process(double delta) override;
        void _physics_process(double delta) override;
        void _ready() override;
        void apply_friction(double p_friction);
        void apply_movement(double acceleration);
        void limit_speed(double limit);

};
    

#endif

