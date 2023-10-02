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
    gravity = 1000.0;
    jump_velocity = -800.0;
    speed = 1;
    
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

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {

    Vector3 velocity = Vector3(0.0, 0.0, 0.0);
    if (!this->is_on_floor()) {
        velocity.y += gravity * delta;
    }
    if (this->is_on_floor()) {
        UtilityFunctions::print("on floor");
    }
    if (input->is_key_label_pressed(KEY_SPACE) && this->is_on_floor()) {
        UtilityFunctions::print("space");
        velocity.y = jump_velocity;
    }
    if (input->is_key_label_pressed(KEY_W)) {
        position += Vector3(0.0, 0.0, -1.0);
        //velocity.z += -1;;
    }
    if (input->is_key_label_pressed(KEY_S)) {
        position += Vector3(0.0, 0.0, 1.0);
        //velocity.z += 1;
    }
    if (input->is_key_label_pressed(KEY_A)) {
        position += Vector3(-1.0, 0.0, 0.0);
        //velocity.x += -1;
    }
    if (input->is_key_label_pressed(KEY_D)) {
        position += Vector3(1.0, 0.0, 0.0);
        //velocity.x += 1;
    }
    set_position(position);
    //velocity = velocity;
    move_and_slide();
}


