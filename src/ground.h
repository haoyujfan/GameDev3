#ifndef GROUND_H
#define GROUND_H

#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>
#include "food.h"

namespace godot {

class Ground : public StaticBody3D {
    GDCLASS(Ground, StaticBody3D)

private:

    Vector3 normal;
    AudioStreamMP3 *background;
    AudioStreamMP3 *empty_interact;
    AudioStreamPlayer *background_player;
    AudioStreamPlayer *empty_interact_player;
    bool mute_music;
    float volume;

protected:
    static void _bind_methods();

public:
    Ground();
    ~Ground();

    Vector3 get_normal() const;
    void set_normal(const Vector3 p_normal);
    void _ready() override;
    void initialize_sound();
    void play_background();
    void _process(double delta) override;


};

}

#endif