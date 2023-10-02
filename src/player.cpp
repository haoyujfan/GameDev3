#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>

#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>

#include <cstdlib>

using namespace godot;

void Player::_bind_methods() {}

Player::Player() {
    input = Input::get_singleton();
    gravity = 1200.0;
    jump_velocity = 200.0;
    speed = 20;
    velocity = Vector3(0.0, 0.0, 0.0);
    position = Vector3(0.0, 10.0, 0.0);
    
    String file_path = "../Assignment2/audio/background.mp3";
    Ref<FileAccess> file = FileAccess::open(file_path, FileAccess::ModeFlags::READ);
    FileAccess *file_ptr = Object::cast_to<FileAccess>(*file);

    AudioStreamMP3 *stream = memnew(AudioStreamMP3);
    stream->set_data(file_ptr->get_file_as_bytes(file_path));
    AudioStreamPlayer *music = memnew(AudioStreamPlayer);
    music->set_stream(stream);
    music->play(0.0);
}

Player::~Player() {}

void Player::_ready() {
    set_position(position);
}

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {
    //set_position(position);

    if (!this->is_on_floor()) {
        velocity.y -= gravity * delta;
        //position.y -= 1;
    }
    if (input->is_action_just_pressed("Jump") && this->is_on_floor()) {
        velocity.y = jump_velocity;
        jumped = true;
    }
    if (input->is_action_just_pressed("Jump") && !this->is_on_floor() && jumped) {
        velocity.y = jump_velocity;
        jumped = false;
    }
    if (input->is_action_pressed("W")) {
        //position += Vector3(0.0, 0.0, -1.0);
        velocity.z += -1 * speed;
    }
    if (input->is_action_pressed("S")) {
        //position += Vector3(0.0, 0.0, 1.0);
        velocity.z += 1 * speed;
    }
    if (input->is_action_pressed("A")) {
        //position += Vector3(-1.0, 0.0, 0.0);
        velocity.x += -1 * speed;
    }
    if (input->is_action_pressed("D")) {
        //position += Vector3(1.0, 0.0, 0.0);
        velocity.x += 1 * speed;
    }
    //set_position(position);
    set_velocity(velocity);
    apply_friction(600 * delta);
    move_and_slide();
}

void Player::apply_friction(double p_friction) {
    if (velocity.length() > p_friction) {
        velocity -= velocity.normalized() * p_friction;
    }
    else {
        velocity = Vector3(0.0, 0.0, 0.0);
    }
}

// void Player::apply_movement(double acceleration) {
//     velocity += acceleration;
// }

