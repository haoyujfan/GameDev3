#ifndef FOOD_H
#define FOOD_H

#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class Food : public Area3D {
    GDCLASS(Food, Area3D)

private:
    Vector3 trajectory;
    Vector3 position;
    double speed;

protected:
    static void _bind_methods();

public:
    Food();
    ~Food();
    void _process(double delta) override;
    void _ready() override;

    void set_trajectory(const Vector3 p_trajectory);
    Vector3 get_trajectory() const;
    
    void set_speed(const double p_speed);
    double get_speed() const;

    void ball_area_entered(const Area3D* area);


};

}

#endif