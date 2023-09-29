#include "food.h"
#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <stdlib.h>

using namespace godot;

// bind c++ methods to godot
void Ball::_bind_methods() {
    ClassDB::bind_method(D_METHOD("get_speed"), &Ball::get_speed);
    ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &Ball::set_speed);
    ClassDB::add_property("Ball", PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, 
        "0.0,200.0,0.01"), "set_speed", "get_speed");
    
    ClassDB::bind_method(D_METHOD("ball_area_entered", "area"), &Ball::ball_area_entered);
}

// constructor
Ball::Ball() {

}

// destructor
Ball::~Ball() {

}

// update the new position based on speed and trajectory
void Ball::_process(double delta) {
    Vector3 movement_update = (delta * speed) * trajectory;

    Vector3 new_position = Vector3(position.x + movement_update.x, 
        position.y + movement_update.y, position.z + movement_update.z);

    position = new_position;
    set_position(new_position);
}

// initialize the ball when its children are ready 
void Ball::_ready() {
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
void Ball::ball_area_entered(const Area3D* area) {
    Vector3 total_trajectory;

    // handle wall collision
    if (area->get_class() == "Wall") {
        Vector3 wall_normal = area->get_global_transform().basis.xform(Vector3(0.0, 0.0, 1.0));;
        trajectory = trajectory - 2 * wall_normal * (wall_normal.dot(trajectory));
        trajectory.normalize();

        total_trajectory += trajectory;
    }
    // handle ball collision
    if (area->get_class() == "Ball") {
        const Ball* ball_collide = Object::cast_to<Ball>(area);
        Vector3 ball_pos = ball_collide->get_position();
        Vector3 ball_normal = Vector3(ball_pos.x - position.x, ball_pos.y - position.y, 
                ball_pos.z - position.z);
        ball_normal.normalize();
        trajectory = trajectory - 2 * ball_normal * (ball_normal.dot(trajectory));
        trajectory.normalize();

        total_trajectory += trajectory;
    }

    // set trajectory to total_trajectory in case there are multiple collisions happening at once
    trajectory = total_trajectory;
}

// set the speed (to stop the ball when in the editor)
void Ball::set_speed(const double p_speed) {
    speed = p_speed;
}

// get the speed of the ball
double Ball::get_speed() const {
    return speed;
}

// set the trajectory
void Ball::set_trajectory(const Vector3 p_trajectory) {
    trajectory = p_trajectory;
}

// get the trajectory
Vector3 Ball::get_trajectory() const {
    return trajectory;
}