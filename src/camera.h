#ifndef CAMERA_H
#define CAMERA_H

#include <godot_cpp/classes/camera3d.hpp>

namespace godot {

class Camera : public Camera3D {
    GDCLASS(Camera, Camera3D)

private:
    Vector3 position;

protected:
    static void _bind_methods();

public:
    Camera();
    ~Camera();
    void _process(double delta) override;
};

}

#endif