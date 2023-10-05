#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>


#include <cstdlib>

using namespace godot;

void Player::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("player_area_entered", "area"), &Player::player_area_entered);
}

Player::Player() {
    input = Input::get_singleton();
    gravity = 1400.0;
    jump_velocity = 300.0;
    speed = 75;
    velocity = Vector3(0.0, 0.0, 0.0);
    position = Vector3(0.0, 10.0, 0.0);
    rotation = Vector3(0.0, 0.0, 0.0);
    hanging = false;
    AD_rotate = true;
}

Player::~Player() {}

void Player::_ready() {
    set_position(position);
    initialize_sound();
    //this->connect("area_entered", Callable(this, "player_area_entered"));
    ray1 = get_node<Raycast>("Raycast");
    ray2 = get_node<Raycast>("Raycast2");
    ray3 = get_node<Raycast>("Raycast3");
    ray4 = get_node<Raycast>("Raycast4");
}

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {
    //set_position(position);
    if (input->is_action_just_pressed("R")) {
        AD_rotate = !AD_rotate;
    }
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
    if (input->is_action_pressed("W") && !hanging) {
        //position += Vector3(0.0, 0.0, -1.0);
        velocity = -get_global_transform().basis.xform(Vector3(0.0, 0.0, 1.0)).normalized() * speed;
    }
    if (input->is_action_pressed("S") && !hanging) {
        //position += Vector3(0.0, 0.0, 1.0);
        velocity = get_global_transform().basis.xform(Vector3(0.0, 0.0, 1.0)).normalized() * speed;
    }
    if (AD_rotate) {
        if (input->is_action_pressed("A") && !hanging) {
            //position += Vector3(-1.0, 0.0, 0.0);
            rotation.y += 0.05;
        }
        if (input->is_action_pressed("D") && !hanging) {
            //position += Vector3(1.0, 0.0, 0.0);
            rotation.y += -0.05;
        }
    } else {
        if (input->is_action_pressed("A") && !hanging) {
            //position += Vector3(-1.0, 0.0, 0.0);
            velocity.x += -1 * speed;
        }
        if (input->is_action_pressed("D") && !hanging) {
            //position += Vector3(1.0, 0.0, 0.0);
            velocity.x += 1 * speed;
        }
    }
    // ledge stop
    if (input->is_action_pressed("Shift")) {
        if (!ray1->is_colliding() || !ray2->is_colliding() ||
        !ray3->is_colliding() || !ray4->is_colliding()) {
            velocity = Vector3(0, 0, 0);
        }
    }
    // ledge hang 
    if (input->is_action_pressed("H")) {
        if (!ray1->is_colliding() && !ray2->is_colliding() &&
        !ray3->is_colliding() && !ray4->is_colliding()) {
            gravity = 0;
            hanging = true;
        }
    }
    // ledge climb (jump)
    if (input->is_action_just_pressed("Jump") && hanging) {
        gravity = 1400.0;
        velocity.y = jump_velocity;
        hanging = false;
    }

    //set_position(position);

    // gacky way to limit speed, fix later
    limit_speed(75);
    set_velocity(velocity);
    set_rotation(rotation);
    apply_friction(800 * delta);
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

void Player::limit_speed(double limit) {
    if (velocity.x > limit) {
        velocity.x = limit;
    }
    if (velocity.z > limit) {
        velocity.z = limit;
    }
    if (velocity.x < -limit) {
        velocity.x = -limit;
    }
    if (velocity.z < -limit) {
        velocity.z = -limit;
    }
}

void Player::initialize_sound() {
    // String clonk_path = "res://audio/clonk.mp3";
    // Ref<FileAccess> clonk_file = FileAccess::open(clonk_path, FileAccess::ModeFlags::READ);
    // FileAccess *clonk_ptr = Object::cast_to<FileAccess>(*clonk_file);
    // empty_interact = memnew(AudioStreamMP3);
    // empty_interact->set_data(clonk_ptr->get_file_as_bytes(clonk_path));

    // String squish_path = "res://audio/squish.mp3";
    // Ref<FileAccess> squish_file = FileAccess::open(squish_path, FileAccess::ModeFlags::READ);
    // FileAccess *squish_ptr = Object::cast_to<FileAccess>(*squish_file);
    // interact = memnew(AudioStreamMP3);
    // interact->set_data(squish_ptr->get_file_as_bytes(squish_path));

    // String hurt_path = "res://audio/hurt.mp3";
    // Ref<FileAccess> hurt_file = FileAccess::open(hurt_path, FileAccess::ModeFlags::READ);
    // FileAccess *hurt_ptr = Object::cast_to<FileAccess>(*hurt_file);
    // hurt = memnew(AudioStreamMP3);
    // hurt->set_data(hurt_ptr->get_file_as_bytes(hurt_path));

    
    // sound_effects = get_node<AudioStreamPlayer>("AudioStreamPlayer");
    // // play this in different functions
}

// void Player::play_hurt() {
//     if (sound_effects && !Engine::get_singleton()->is_editor_hint()) {
//         sound_effects->set_stream(hurt);
//         sound_effects->set_volume_db(-12.0);
//         sound_effects->play(0.0);
//     }
// }

// void Player::play_empty() {
//     if (sound_effects && !Engine::get_singleton()->is_editor_hint()) {
//         sound_effects->set_stream(empty_interact);
//         sound_effects->set_volume_db(-12.0);
//         sound_effects->play(0.0);
//     }
// }

// void Player::play_interaction() {
//     if (sound_effects && !Engine::get_singleton()->is_editor_hint()) {
//         sound_effects->set_stream(interact);
//         sound_effects->set_volume_db(-12.0);
//         sound_effects->play(0.0);
//     }
// }

// void Player::player_area_entered(const Area3D* area) {
//     if (area->get_class() == "Cactus") {
//         play_hurt();
//     }
//     if (area->get_class() == "Food") {
//         play_interaction();
//     }
// }

// void Player::apply_movement(double acceleration) {
//     velocity += acceleration;
// }

