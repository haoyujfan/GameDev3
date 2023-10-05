#include "food.h"
#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/engine.hpp>
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
    
}

// constructor
Food::Food() {

}

// destructor
Food::~Food() {

}

// update the new position based on speed and trajectory
void Food::_process(double delta) {

}

// initialize the food when its children are ready 
void Food::_ready() {
    initialize_sound();
    this->connect("body_entered", Callable(this, "food_body_entered"));
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


    sound_effects = get_node<AudioStreamPlayer>("../AudioStreamPlayer");
    // play this in different functions
}

void Food::play_interact() {
    if (sound_effects && !Engine::get_singleton()->is_editor_hint()) {
        sound_effects->set_stream(interact);
        sound_effects->set_volume_db(-12.0);
        sound_effects->play(0.0);
    }
}

void Food::food_body_entered(const Node3D* node) {
    UtilityFunctions::print("entered\n");
    if (node->get_class() == "Player") {
        UtilityFunctions::print("Player\n");
        play_interact();
    }
}
