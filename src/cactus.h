#ifndef CACTUS_H
#define CACTUS_H

#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class Cactus : public Area3D {
    GDCLASS(Cactus, Area3D)

private:

protected:
    static void _bind_methods();

public:
    Cactus();
    ~Cactus();
    void _process(double delta) override;
    void _ready() override;

    void ball_area_entered(const Area3D* area);


};

}

#endif