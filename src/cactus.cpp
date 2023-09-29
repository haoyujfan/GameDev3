#include "cactus.h"
#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <stdlib.h>

using namespace godot;

// bind c++ methods to godot
void Cactus::_bind_methods() {
    ClassDB::bind_method(D_METHOD("ball_area_entered", "area"), &Cactus::ball_area_entered);
}

// constructor
Cactus::Cactus() {

}

// destructor
Cactus::~Cactus() {

}

// update the new position based on speed and trajectory
void Cactus::_process(double delta) {
}

// initialize the ball when its children are ready 
void Cactus::_ready() {
    // connect the signal to area_entered
    this->connect("area_entered", Callable(this, "ball_area_entered"));
}

// handle collisions with other objects
void Cactus::ball_area_entered(const Area3D* area) {
    // handle cactus collision
    if (area->get_class() == "Cactus") {
        const Cactus* cactus_collide = Object::cast_to<Cactus>(area);
    }
}