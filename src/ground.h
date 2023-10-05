#ifndef GROUND_H
#define GROUND_H

#include <godot_cpp/classes/static_body3d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/audio_stream_mp3.hpp>

namespace godot {

class Ground : public StaticBody3D {
    GDCLASS(Ground, StaticBody3D)

private:
    Vector3 normal;
    AudioStreamMP3 *stream;
    AudioStreamPlayer *music;

protected:
    static void _bind_methods();

public:

    Vector3 get_normal() const;
    void set_normal(const Vector3 p_normal);
    void _ready() override;

    Ground();
    ~Ground();
};

}

#endif