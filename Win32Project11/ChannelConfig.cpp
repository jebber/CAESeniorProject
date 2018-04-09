#include "stdafx.h"
#include "ChannelConfig.h"

//Constructor w/o config file for image generation
ChannelConfig::ChannelConfig() {
	set_number(0);
	set_fov_h(0);
	set_fov_v(0);
	set_location_h(0);
	set_location_v(0);
	set_resolution_h(0);
	set_resolution_v(0);
}

ChannelConfig::ChannelConfig(ifstream& in_file) {
	string in_string;
	int peek;
	int keep_reading = 1;

	while (keep_reading) {
		getline(in_file, in_string, ':');
		if (in_string == "number") {
			getline(in_file, in_string);
			this->set_number(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "fov_h") {
			getline(in_file, in_string);
			this->set_fov_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "fov_v") {
			getline(in_file, in_string);
			this->set_fov_v(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "location_h") {
			getline(in_file, in_string);
			this->set_location_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "location_v") {
			getline(in_file, in_string);
			this->set_location_v(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "resolution_h") {
			getline(in_file, in_string);
			this->set_resolution_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "resolution_v") {
			getline(in_file, in_string);
			this->set_resolution_v(stoi(in_string, nullptr, 0));
		}
		else {
			cout << "ChannelConfig type not recognized." << endl;
		}

		peek = in_file.peek();

		if (peek == '-' || peek == -1)
			keep_reading = 0;
	}
}

ChannelConfig::~ChannelConfig() {
}

//Setters
void ChannelConfig::set_number(int input) {
	this->number = input;
}
void ChannelConfig::set_fov_h(int input) {
	this->fov_h = input;
}
void ChannelConfig::set_fov_v(int input) {
	this->fov_v = input;
}
void ChannelConfig::set_location_h(int input) {
	this->location_h = input;
}
void ChannelConfig::set_location_v(int input) {
	this->location_v = input;
}

void ChannelConfig::set_resolution_h(int input)
{
	this->resolution_h = input;
}

void ChannelConfig::set_resolution_v(int input)
{
	this->resolution_v = input;
}

//Getters
int ChannelConfig::get_number() {
	return this->number;
}
int ChannelConfig::get_fov_h() {
	return this->fov_h;
}
int ChannelConfig::get_fov_v() {
	return this->fov_v;
}
int ChannelConfig::get_location_h() {
	return this->location_h;
}
int ChannelConfig::get_location_v() {
	return this->location_v;
}

int ChannelConfig::get_resolution_h()
{
	return this->resolution_h;
}

int ChannelConfig::get_resolution_v()
{
	return this->resolution_v;
}

//Output
void ChannelConfig::display_channel_console() {
	cout << "number:" << this->get_number() << endl;
	cout << "fov_h:" << this->get_fov_h() << endl;
	cout << "fov_v:" << this->get_fov_h() << endl;
	cout << "location_h:" << this->get_location_h() << endl;
	cout << "location_v:" << this->get_location_v() << endl;
	cout << "resolution_h:" << this->get_resolution_h() << endl;
	cout << "resolution_v:" << this->get_resolution_v() << endl;
}
void ChannelConfig::output_channel_file(ofstream& out_file) {
	out_file << "number:" << this->get_number() << endl;
	out_file << "fov_h:" << this->get_fov_h() << endl;
	out_file << "fov_v:" << this->get_fov_h() << endl;
	out_file << "location_h:" << this->get_location_h() << endl;
	out_file << "location_v:" << this->get_location_v() << endl;
	out_file << "resolution_h:" << this->get_resolution_h() << endl;
	out_file << "resolution_v:" << this->get_resolution_v() << endl;
}