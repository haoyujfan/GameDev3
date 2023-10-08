#include "player.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>
#include <godot_cpp/variant/transform3d.hpp>


#include <cstdlib>

using namespace godot;

void Player::_bind_methods() {
    //ClassDB::bind_method(D_METHOD("_physics_process", "delta"), &Player::_physics_process);
}

Player::Player() {
    //input = Input::get_singleton();
    gravity = 1400.0;
    jump_velocity = 300.0;
    speed = 75;
    velocity = Vector3(0.0, 0.0, 0.0);
    position = Vector3(0.0, 10.0, 0.0);
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

    food1 = get_node<Food>("../Food");
    food2 = get_node<Food>("../Food2");
    food3 = get_node<Food>("../Food3");
    food4 = get_node<Food>("../Food4");
}

void Player::_process(double delta) {
    bool entered = food1->is_entered() || food2->is_entered() || 
        food3->is_entered() || food4->is_entered();
    if (entered && Input::get_singleton()->is_action_pressed("E")) {
        if (!interact_player->is_playing()) {
            UtilityFunctions::print("Interact");
            play_interact();
        }
    }
    if (!entered && Input::get_singleton()->is_action_pressed("E")) {
        if (!empty_interact_player->is_playing()) {
            UtilityFunctions::print("Empty Interact");
            play_empty_interact();
        }
    }
}

void Player::_physics_process(double delta) {
    // sets rotate mode or strafe mode
    if (Input::get_singleton()->is_action_just_pressed("R")) {
        AD_rotate = !AD_rotate;
    }
    // reset gravity 
    if (this->is_on_floor()) {
        gravity = 1400.0;
    }

    // gravity and jumping
    if (!this->is_on_floor()) {
        velocity.y -= gravity * delta;
        //position.y -= 1;
    }
    if (Input::get_singleton()->is_action_just_pressed("Jump") && this->is_on_floor()) {
        velocity.y = jump_velocity;
        jumped = true;
    }
    if (Input::get_singleton()->is_action_just_pressed("Jump") && !this->is_on_floor() && jumped) {
        velocity.y = jump_velocity;
        jumped = false;
    }

    // ledge stop (shift)
    if (Input::get_singleton()->is_action_pressed("Shift")) {
        if (ray1->is_colliding() || ray2->is_colliding() ||
        ray3->is_colliding() || ray4->is_colliding()) {
            // WASD movement
            if (AD_rotate) {
                rotate_wasd();
            }
            else {
                strafe_wasd();
            }
        } else {
            gravity = 0;
        }
    } else {
        // WASD movement
        if (AD_rotate) {
            rotate_wasd();
        }
        else {
            strafe_wasd();
        }
    }
    // gliding (g)
    if (Input::get_singleton()->is_action_pressed("G")) {
        gravity = 800.0;
    }
    if (Input::get_singleton()->is_action_just_released("G")) {
        gravity = 1400.0;
    }
    // gacky way to limit speed, fix later
    limit_speed(75);
    set_velocity(velocity);
    apply_friction(800 * delta);
    move_and_slide();
}

void Player::rotate_wasd() {
    if (!hanging) {
        if (Input::get_singleton()->is_action_pressed("W")) {
            translate_object_local(-transform.get_basis().get_column(2));
        }
        if (Input::get_singleton()->is_action_pressed("S")) {
            translate_object_local(transform.get_basis().get_column(2));
        }
        if (Input::get_singleton()->is_action_pressed("A")) {
            rotate_object_local(Vector3(0, 1, 0), 0.1);
        }
        if (Input::get_singleton()->is_action_pressed("D")) {
            rotate_object_local(Vector3(0, 1, 0), -0.1);
        }
    }
}

void Player::strafe_wasd() {
    if (!hanging) {
        if (Input::get_singleton()->is_action_pressed("W")) {
            translate_object_local(-transform.get_basis().get_column(2));
        }
        if (Input::get_singleton()->is_action_pressed("S")) {
            translate_object_local(transform.get_basis().get_column(2));
        }
        if (Input::get_singleton()->is_action_pressed("A")) {
            translate_object_local(-transform.get_basis().get_column(0));
        }
        if (Input::get_singleton()->is_action_pressed("D")) {
            translate_object_local(transform.get_basis().get_column(0));
        }
    }

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
    String squish_path = "res://audio/squish.mp3";
    Ref<FileAccess> squish_file = FileAccess::open(squish_path, FileAccess::ModeFlags::READ);
    FileAccess *squish_ptr = Object::cast_to<FileAccess>(*squish_file);
    interact = memnew(AudioStreamMP3);
    interact->set_data(squish_ptr->get_file_as_bytes(squish_path));
    interact_player = get_node<AudioStreamPlayer>("InteractPlayer");

    String clonk_path = "res://audio/clonk.mp3";
    Ref<FileAccess> clonk_file = FileAccess::open(clonk_path, FileAccess::ModeFlags::READ);
    FileAccess *clonk_ptr = Object::cast_to<FileAccess>(*clonk_file);
    empty_interact = memnew(AudioStreamMP3);
    empty_interact->set_data(clonk_ptr->get_file_as_bytes(clonk_path));
    empty_interact_player = get_node<AudioStreamPlayer>("EmptyInteractPlayer");
}

void Player::play_interact() {
    if (interact_player && !Engine::get_singleton()->is_editor_hint()) {
        interact_player->set_stream(interact);
        interact_player->set_volume_db(-12.0);
        interact_player->play(0.0);
    }
}

void Player::play_empty_interact() {
    if (empty_interact_player && !Engine::get_singleton()->is_editor_hint()) {
        empty_interact_player->set_stream(empty_interact);
        empty_interact_player->set_volume_db(-17.0);
        empty_interact_player->play(0.0);
    }
}

// void Player::apply_movement(double acceleration) {
//     velocity += acceleration;
// }

