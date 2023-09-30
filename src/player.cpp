#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <cstdlib>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() {
    position = Vector3(0.0, 5.0, 0.0);
}

Player::~Player() {}

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {

}

void Player::_input(const Ref<InputEvent> &event) {
    const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);
    if (key_event) {
        UtilityFunctions::print(key_event);
        if (key_event->as_text_key_label() == "W") {
            position += Vector3(0.0, 0.0, 1.0);
            set_position(position);
        }
    }
}
