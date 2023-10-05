#ifndef FOOD_H
#define FOOD_H

#include <godot_cpp/classes/area3d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>

namespace godot {

class Food : public Area3D {
    GDCLASS(Food, Area3D)

private:
    Vector3 position;
    int value;
    bool pickup;
    AudioStreamPlayer *sound_effects;
    AudioStreamMP3 *interact;

protected:
    static void _bind_methods();

public:
    Food();
    ~Food();
    void _process(double delta) override;
    void _ready() override;

    int get_value() const;
    void set_value(const int p_value);
    void initialize_sound();
    void play_interact();
    void food_body_entered(const Node3D *node);

};

}

#endif