#include "car.h"

car::car() {
	this->car_name = nullptr;
}
car::car(int wheel_number, int max_speed) {
	this->wheel_number = wheel_number;
	this->max_speed = max_speed;
}
car::car(int wheel_number, int max_speed, char* car_name) {
	this->wheel_number = wheel_number;
	this->max_speed = max_speed;
	this->car_name = car_name;
}
car::car(int wheel_number, int max_speed, char* car_name, bool has_name) {
	this->wheel_number = wheel_number;
	this->max_speed = max_speed;
	this->car_name = car_name;
	this->has_name = has_name;
}

char* car::get_car_name() {
	return this->car_name;
}
void car::set_car_name(char* new_car_name) {
	this->car_name = new_car_name;
}
const char* car::get_class_name() {
	return "car";
}
