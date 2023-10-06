#include "food.h"
#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <iostream>
#include <stdlib.h>

using namespace godot;

// bind c++ methods to godot
void Food::_bind_methods() {
    // ClassDB::bind_method(D_METHOD("get_value"), &Food::get_value);
    // ClassDB::bind_method(D_METHOD("set_value", "p_value"), &Food::set_value);
    // ClassDB::add_property("Food", PropertyInfo(Variant::INT, "value", PROPERTY_HINT_RANGE, 
    //     "0, 3, 1"), "set_value", "get_value");
    ClassDB::bind_method(D_METHOD("food_body_entered", "node"), &Food::food_body_entered);
    ClassDB::bind_method(D_METHOD("food_body_exited", "node"), &Food::food_body_exited);
    
}

// constructor
Food::Food() {

}

// destructor
Food::~Food() {

}

// update the new position based on speed and trajectory
void Food::_process(double delta) {
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

// initialize the food when its children are ready 
void Food::_ready() {
    initialize_sound();
    entered = false;
    this->connect("body_entered", Callable(this, "food_body_entered"));
    this->connect("body_exited", Callable(this, "food_body_exited"));
}

int Food::get_value() const{
    return value;
}

void Food::set_value(const int p_value) {
   // value = p_value;
}

void Food::initialize_sound() {
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

void Food::play_interact() {
    if (interact_player && !Engine::get_singleton()->is_editor_hint()) {
        interact_player->set_stream(interact);
        interact_player->set_volume_db(-12.0);
        interact_player->play(0.0);
    }
}

void Food::play_empty_interact() {
    if (empty_interact_player && !Engine::get_singleton()->is_editor_hint()) {
        empty_interact_player->set_stream(empty_interact);
        empty_interact_player->set_volume_db(-17.0);
        empty_interact_player->play(0.0);
    }
}

void Food::food_body_entered(const Node3D* node) {
    if (node->get_class() == "Player") {
        entered = true;
    }
}

void Food:: food_body_exited(const Node3D* node) {
    if (node->get_class() == "Player") {
        entered = false;
    }
}
