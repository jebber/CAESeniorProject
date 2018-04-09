//#pragma once
#ifndef CHANNEL_H
#define CHANNEL_H


//Class file for the ChannelConfig class

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

class ChannelConfig {
private:
	int number;
	int fov_h;
	int fov_v;
	int location_h;
	int location_v;
	int resolution_h;
	int resolution_v;

public:
	//channel constructor from config file 
	ChannelConfig(ifstream& in_file);
	//channel constructor w/o config file for image generation
	ChannelConfig();
	//destructor
	~ChannelConfig();

	//Setters
	void set_number(int input);
	void set_fov_h(int input);
	void set_fov_v(int input);
	void set_location_h(int input);
	void set_location_v(int input);
	void set_resolution_h(int input);
	void set_resolution_v(int input);

	//Getters
	int get_number();
	int get_fov_h();
	int get_fov_v();
	int get_location_h();
	int get_location_v();
	int get_resolution_h();
	int get_resolution_v();

	//Output
	void display_channel_console();
	void output_channel_file(ofstream& out_file);

};



#endif