#include "ground.h"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

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

// set normal
void Ground::set_normal(const Vector3 p_normal) {
    normal = p_normal;
}

// get normal
Vector3 Ground::get_normal() const {
    return normal;
}
