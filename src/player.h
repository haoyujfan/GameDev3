#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/node3d.hpp>

using namespace godot;

class Player : public Node3D {
    GDCLASS(Player, Node3D)

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

