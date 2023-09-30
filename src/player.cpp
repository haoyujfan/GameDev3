#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <cstdlib>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() {
    input = Input::get_singleton();
}

Player::~Player() {}

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {
    if (input->is_key_label_pressed(KEY_W)) {
        position += Vector3(0.0, 0.0, -1.0);
    }
    if (input->is_key_label_pressed(KEY_S)) {
        position += Vector3(0.0, 0.0, 1.0);
    }
    if (input->is_key_label_pressed(KEY_A)) {
        position += Vector3(-1.0, 0.0, 0.0);
    }
    if (input->is_key_label_pressed(KEY_D)) {
        position += Vector3(1.0, 0.0, 0.0);
    }
    set_position(position);
}

// void Player::_input(const Ref<InputEvent> &event) {
//     const InputEventKey *key_event = Object::cast_to<const InputEventKey>(*event);
//     if (key_event) {
//         UtilityFunctions::print(key_event);
//         if (key_event->as_text_key_label() == "W") {
//             position += Vector3(0.0, 0.0, -1.0);
//         }
//         if (key_event->as_text_key_label() == "S") {
//             position += Vector3(0.0, 0.0, 1.0);
//         }
//         if (key_event->as_text_key_label() == "A") {
//             position += Vector3(-1.0, 0.0, 0.0);
//         }
//         if (key_event->as_text_key_label() == "D") {
//             position += Vector3(1.0, 0.0, 0.0);
//         }
//         set_position(position);
//     }
// }

