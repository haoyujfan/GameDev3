#ifndef GROUND_H
#define GROUND_H

#include <godot_cpp/classes/area3d.hpp>

namespace godot {

class Ground : public Area3D {
    GDCLASS(Ground, Area3D)

private:
    Vector3 normal;

protected:
    static void _bind_methods();

public:

    Vector3 get_normal() const;
    void set_normal(const Vector3 p_normal);

    Ground();
    ~Ground();
};

}

#endif