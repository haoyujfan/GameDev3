#ifndef CACTUS_H
#define CACTUS_H

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>
#include "player.h"

namespace godot {

class Cactus : public Area3D {
    GDCLASS(Cactus, Area3D)

private:
    Vector3 position;
    int value;
    bool pickup;
    AudioStreamPlayer *sound_effects;
    AudioStreamMP3 *hurt;
<<<<<<< HEAD
    bool mute_sound_effects;
=======
    Player *player;
>>>>>>> 8667acef62e4e0aa0edc9a781710fc7f0ea9e4ac

protected:
    static void _bind_methods();

public:
    Cactus();
    ~Cactus();
    void _process(double delta) override;
    void _ready() override;

    int get_value() const;
    void set_value(const int p_value);
    void initialize_sound();
    void play_interact();
    void cactus_body_entered(const Node3D *node);


};

}

#endif