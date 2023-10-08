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
    // food1 = get_node<Food>("../Food");
    // food2 = get_node<Food>("../Food2");
    // food3 = get_node<Food>("../Food3");
    // food4 = get_node<Food>("../Food4");

    initialize_sound();
    play_background();
}

void Ground::initialize_sound() {
    String background_path = "res://audio/background.mp3";
    Ref<FileAccess> file = FileAccess::open(background_path, FileAccess::ModeFlags::READ);
    FileAccess *background_ptr = Object::cast_to<FileAccess>(*file);
    background = memnew(AudioStreamMP3);
    background->set_data(background_ptr->get_file_as_bytes(background_path));
    background_player = get_node<AudioStreamPlayer>("../BackgroundPlayer");
}

// set normal
void Ground::set_normal(const Vector3 p_normal) {
    normal = p_normal;
}

// get normal
Vector3 Ground::get_normal() const {
    return normal;
}

void Ground::play_background() {
    if (background_player && !Engine::get_singleton()->is_editor_hint()) {
        background_player->set_stream(background);
        background_player->set_volume_db(-17.0);
        background_player->play(0.0);
    }
}

// void Ground::play_empty_interact() {
//     if (empty_interact_player && !Engine::get_singleton()->is_editor_hint()) {
//         empty_interact_player->set_stream(background);
//         empty_interact_player->set_volume_db(-17.0);
//         empty_interact_player->play(0.0);
//     }
// }