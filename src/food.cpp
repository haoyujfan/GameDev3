#include "food.h"
#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <stdlib.h>

using namespace godot;

// bind c++ methods to godot
void Food::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Food::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Food::set_speed);
    ClassDB::add_property("Food", PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, 
        "0.0,200.0,0.01"), "set_speed", "get_speed");
    
    ClassDB::bind_method(D_METHOD("ball_area_entered", "area"), &Food::ball_area_entered);
}

// constructor
Food::Food() {

}

// destructor
Food::~Food() {

}

// update the new position based on speed and trajectory
void Food::_process(double delta) {
    Vector3 movement_update = (delta * speed) * trajectory;

    Vector3 new_position = Vector3(position.x + movement_update.x, 
        position.y + movement_update.y, position.z + movement_update.z);

    position = new_position;
    set_position(new_position);
}

// initialize the ball when its children are ready 
void Food::_ready() {
    // randomize speed and trajectory
    RandomNumberGenerator rng;
    trajectory = Vector3(rng.randf_range(-10.0, 10.0), rng.randf_range(-10.0, 10.0), 
        rng.randf_range(-10.0, 10.0));
    trajectory.normalize();
    speed = rng.randf_range(150.0, 200.0);

    // get the name of the Ball and apply set position based on the name
    String name = this->get_name();
    if (name == "Ball") {
        position = Vector3(-50.0, 100.0, 0.0);
        set_position(position);
    }
    else if (name == "Ball2") {
        position = Vector3(0.0, 100.0, 0.0);
        set_position(position);
    }
    else if (name == "Ball3") {
        position = Vector3(50.0, 100.0, 0.0);
        set_position(position);
    }

    // connect the signal to area_entered
    this->connect("area_entered", Callable(this, "ball_area_entered"));
}

// handle collisions with other objects
void Food::ball_area_entered(const Area3D* area) {

    // set trajectory to total_trajectory in case there are multiple collisions happening at once

}
// set the speed (to stop the ball when in the editor)
void Food::set_speed(const double p_speed) {
    speed = p_speed;
}

// get the speed of the ball
double Food::get_speed() const {
    return speed;
}

// set the trajectory
void Food::set_trajectory(const Vector3 p_trajectory) {
    trajectory = p_trajectory;
}

// get the trajectory
Vector3 Food::get_trajectory() const {
    return trajectory;
}