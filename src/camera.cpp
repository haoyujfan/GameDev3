#include "camera.h"
#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <cstdlib>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

void Camera::_bind_methods() {}

Camera::Camera() {
    rotation = Vector3(0.0, 0.0, 0.0);
}

Camera::~Camera() {}

void Camera::_input(const Ref<InputEvent> &event) {
	const InputEventMouseMotion *key_event = Object::cast_to<const InputEventMouseMotion>(*event);
	if (key_event) {
        rotation += Vector3(-1 * key_event->get_relative()[1] / 200, -1 * key_event->get_relative()[0] / 200, 0.0);
        Node3D* tgt = Object::cast_to<Node3D>(get_parent());
        tgt->set_rotation(rotation);
	}
}
