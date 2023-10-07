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
    //ClassDB::bind_method(D_METHOD("player_area_entered", "area"), &Player::player_area_entered);
    //ClassDB::bind_method(D_METHOD("_physics_process", "delta"), &Player::_physics_process);
}

Player::Player() {
    //input = Input::get_singleton();
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
    //this->connect("area_entered", Callable(this, "player_area_entered"));
    ray1 = get_node<Raycast>("Raycast");
    ray2 = get_node<Raycast>("Raycast2");
    ray3 = get_node<Raycast>("Raycast3");
    ray4 = get_node<Raycast>("Raycast4");
}

void Player::_process(double delta) {}

void Player::_physics_process(double delta) {
    //set_position(position);
    if (Input::get_singleton()->is_action_just_pressed("R")) {
        AD_rotate = !AD_rotate;
    }
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
    if (AD_rotate) {
        rotate_wasd();
    }
    else {
        strafe_wasd();
    }
    // ledge climb (jump)
    if (Input::get_singleton()->is_action_just_pressed("Jump") && hanging) {
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

void Player::rotate_wasd() {
    if (Input::get_singleton()->is_action_pressed("W") && !hanging) {
        //position += Vector3(0.0, 0.0, -1.0);
        // velocity = -get_global_transform().basis.xform(Vector3(0.0, 0.0, 1.0)).normalized() * speed;
        translate_object_local(-transform.get_basis().get_column(2));
    }
    if (Input::get_singleton()->is_action_pressed("S") && !hanging) {
        //position += Vector3(0.0, 0.0, 1.0);
        // velocity = get_global_transform().basis.xform(Vector3(0.0, 0.0, 1.0)).normalized() * speed;
        translate_object_local(transform.get_basis().get_column(2));
    }
    if (Input::get_singleton()->is_action_pressed("A") && !hanging) {
        //position += Vector3(-1.0, 0.0, 0.0);
        // rotation.y += 0.05;
        rotate_object_local(Vector3(0, 0, 1), 1);
    }
    if (Input::get_singleton()->is_action_pressed("D") && !hanging) {
        //position += Vector3(1.0, 0.0, 0.0);
        // rotation.y += -0.05;
        rotate_object_local(Vector3(0, 0, 1), -1);
    }
}

void Player::strafe_wasd() {
    if (Input::get_singleton()->is_action_pressed("W") && !hanging) {
        //position += Vector3(0.0, 0.0, -1.0);
        // velocity += get_global_transform().basis.xform(Vector3(0.0, 0.0, -1.0)).normalized() * speed;
        translate_object_local(-transform.get_basis().get_column(2));
    }
    if (Input::get_singleton()->is_action_pressed("S") && !hanging) {
        //position += Vector3(0.0, 0.0, 1.0);
        // velocity += get_global_transform().basis.xform(Vector3(0.0, 0.0, 1.0)).normalized() * speed;
        translate_object_local(transform.get_basis().get_column(2));
    }
    if (Input::get_singleton()->is_action_pressed("A") && !hanging) {
        //position += Vector3(-1.0, 0.0, 0.0);
        // velocity += get_global_transform().basis.xform(Vector3(-1.0, 0.0, 0.0)).normalized() * speed;
        translate_object_local(-transform.get_basis().get_column(0));
    }
    if (Input::get_singleton()->is_action_pressed("D") && !hanging) {
        //position += Vector3(1.0, 0.0, 0.0);
        // velocity += get_global_transform().basis.xform(Vector3(1.0, 0.0, 0.0)).normalized() * speed;
        translate_object_local(transform.get_basis().get_column(0));
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

// void Player::apply_movement(double acceleration) {
//     velocity += acceleration;
// }

