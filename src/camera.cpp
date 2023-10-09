#include "camera.h"
#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <cstdlib>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Camera::_bind_methods() {}

Camera::Camera() {
    rotation = Vector3(0.0, 0.0, 0.0);
}

Camera::~Camera() {}

void Camera::_input(const Ref<InputEvent> &event) {
    if(Engine::get_singleton()->is_editor_hint()) {
        return;
    }
	const InputEventMouseMotion *key_event = Object::cast_to<const InputEventMouseMotion>(*event);
	if (key_event) {
        
        Node3D* tgt = Object::cast_to<Node3D>(get_parent());
        Player* player = get_node<Player>("../../../Player");
        if (!player->get_ad_rotate()) {
            rotation[0] = 0.0;
            rotation += Vector3(0.0, -1 * key_event->get_relative()[0] / 200, 0.0);
            player->set_rotation(rotation);
        } else {
            rotation += Vector3(-1 * key_event->get_relative()[1] / 200, -1 * key_event->get_relative()[0] / 200, 0.0);
            if (rotation[0] > 0) {
                rotation[0] = 0;
            } else if (rotation[0] < -2.8) {
                rotation[0] = -2.8;
            }        
            tgt->set_rotation(rotation);
        }
	}
}


