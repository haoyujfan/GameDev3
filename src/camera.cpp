#include "camera.h"
#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <cstdlib>

using namespace godot;

void Camera::_bind_methods() {}

Camera::Camera() {
    position = Vector3(0.0, 0.0, 0.0);
}

Camera::~Camera() {}

void Camera::_process(double delta) {
    Vector3 tgt = Object::cast_to<Player>(get_parent())->get_transform().get_origin();
    position += tgt;
    set_position(position);
}
