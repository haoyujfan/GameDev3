#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_key.hpp>
#include <cstdlib>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() {}

Player::~Player() {}

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {

}

void Player::_input(const Ref<InputEvent> &event) {
    const InputEventKey key_event = Object::cast_to<const InputEventMouseMotion>(event);
    if (key_event) {
        UtilityFunctions::print(key_event);
        set_rotation(key_event->get_relative());
    }
}
