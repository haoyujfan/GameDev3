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
    /*ClassDB::bind_method(D_METHOD("get_value"), &Food::get_value);
    ClassDB::bind_method(D_METHOD("set_value", "p_value"), &Food::set_value);
    ClassDB::add_property("Food", PropertyInfo(Variant::INT, "value", PROPERTY_HINT_RANGE, 
        "0, 3, 1"), "set_value", "get_value");
    
    ClassDB::bind_method(D_METHOD("ball_area_entered", "area"), &Food::ball_area_entered);*/
}

// constructor
Food::Food() {

}

// destructor
Food::~Food() {

}

// update the new position based on speed and trajectory
void Food::_process(double delta) {
    // Vector3 movement_update = (delta * speed) * trajectory;

    // Vector3 new_position = Vector3(position.x + movement_update.x, 
    //     position.y + movement_update.y, position.z + movement_update.z);

    // position = new_position;
    // set_position(new_position);
}

// initialize the food when its children are ready 
void Food::_ready() {
    // don't play until press play, not in editor
    String file_path = "res://audio/background.mp3";
    Ref<FileAccess> file = FileAccess::open(file_path, FileAccess::ModeFlags::READ);
    FileAccess *file_ptr = Object::cast_to<FileAccess>(*file);

    AudioStreamMP3 *stream = memnew(AudioStreamMP3);
    stream->set_data(file_ptr->get_file_as_bytes(file_path));
    AudioStreamPlayer *music = get_node<AudioStreamPlayer>("AudioStreamPlayer");
    // play this in different functions
    if (music && !Engine::get_singleton()->is_editor_hint()) {
        UtilityFunctions::print("music connected\n");
        music->set_stream(stream);
        music->play(0.0);
    }
}

// handle collisions with other objects
void Food::ball_area_entered(const Area3D* area) {

}

int Food::get_value() const{
    return value;
}

void Food::set_value(const int p_value) {
   // value = p_value;
}
