#include "cactus.h"
#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <stdlib.h>

using namespace godot;

// bind c++ methods to godot
void Cactus::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_value"), &Cactus::get_value);
    ClassDB::bind_method(D_METHOD("set_value", "p_value"), &Cactus::set_value);
    ClassDB::add_property("Cactus", PropertyInfo(Variant::INT, "value", PROPERTY_HINT_RANGE, 
        "0, 3, 1"), "set_value", "get_value");

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

// initialize the cactus when its children are ready 
void Cactus::_ready() {
    // get the name of the Ball and apply set position based on the name
    String name = this->get_name();
    if (name == "Cactus") {
        position = Vector3(20.0, 3.0, -24.0);
        set_position(position);
    }
    else if (name == "Cactus2") {
        position = Vector3(-4.0, 3.0, 40.0);
        set_position(position);
    }
    else if (name == "Cactus3") {
        position = Vector3(5.0, 3.0, -35.0);
        set_position(position);
    } else if (name == "Cactus4") {
        position = Vector3(-16.0, 3.0, -20.0);
        set_position(position);
    }

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

int Cactus::get_value() const{
    return value;
}

void Cactus::set_value(const int p_value) {
    value = p_value;
}
