#ifndef FOOD_H
#define FOOD_H

#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class Food : public Area3D {
    GDCLASS(Food, Area3D)

private:
    Vector3 position;
    int value;
    bool pickup;

protected:
    static void _bind_methods();

public:
    Food();
    ~Food();
    void _process(double delta) override;
    void _ready() override;

    void ball_area_entered(const Area3D* area);

    int get_value() const;
    void set_value(const int p_value);

};

}

#endif