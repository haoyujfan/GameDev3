#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>
#include <godot_cpp/classes/file_access.hpp>
#include <godot_cpp/classes/engine.hpp>

using namespace godot;

void Ground::_bind_methods() {

    ClassDB::bind_method(D_METHOD("get_normal"), &Ground::get_normal);
    ClassDB::bind_method(D_METHOD("set_normal", "p_normal"), &Ground::set_normal);
    ClassDB::add_property("Ground", PropertyInfo(Variant::VECTOR3, "normal"), "set_normal", "get_normal");

}

// constructor
Ground::Ground() {
}

// destructor
Ground::~Ground() {
}

void Ground::_ready() {
    String file_path = "res://audio/background.mp3";
    Ref<FileAccess> file = FileAccess::open(file_path, FileAccess::ModeFlags::READ);
    FileAccess *file_ptr = Object::cast_to<FileAccess>(*file);

    stream = memnew(AudioStreamMP3);
    stream->set_data(file_ptr->get_file_as_bytes(file_path));
    music = get_node<AudioStreamPlayer>("AudioStreamPlayer");
    // play this in different functions
    if (music && !Engine::get_singleton()->is_editor_hint()) {
        UtilityFunctions::print("music connected\n");
        music->set_stream(stream);
        music->set_volume_db(-12.0);
        music->play(0.0);
    }
}

// set normal
void Ground::set_normal(const Vector3 p_normal) {
    normal = p_normal;
}

// get normal
Vector3 Ground::get_normal() const {
    return normal;
}
