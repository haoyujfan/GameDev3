#include "camera.h"
#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <cstdlib>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Camera::_bind_methods() {}

Camera::Camera() {
    rotation = Vector3(0.0, 0.0, 0.0);
    transform = new Transform3D();
}

Camera::~Camera() {}

void Camera::_process(double delta) {
    Player* tgt = Object::cast_to<Player>(get_parent());//->get_transform().get_origin();
    //position += tgt;
    //set_position(position);
}

void Camera::_physics_process(double delta) {
}

void Camera::_input(const Ref<InputEvent> &event) {
	const InputEventMouseMotion *key_event = Object::cast_to<const InputEventMouseMotion>(*event);
	if (key_event) {
		UtilityFunctions::print(key_event);
        rotation += Vector3(-1 * key_event->get_relative()[1] / 2, -1 * key_event->get_relative()[0] / 2, 0.0);
        transform.rotated(Vector3(1.0, 0.0, 0.0), rotation.x / 180);
        //set_rotation_degrees(rotation);
        //rotate(Vector3(1.0,0.0,0.0), rotation.x/90);
        //rotate(Vector3(0.0,1.0,0.0), rotation.y/90);
	}
}
