//#pragma once
//Configuration Class file
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "stdafx.h"
#include "ChannelConfig.h"

using namespace std;

class Configuration {

private:
	string name;
	int total_fov_h;       //Measured in degrees
	int total_fov_v;       //Measured in degrees
	int viewer_distance; //Measured in inches
	int num_channels;
	int test_pattern;
	vector<ChannelConfig>* channels;

	//Test pattern parameters
	bool display_horizontal;
	bool full_pattern;
	int opacity;
	int azimuth;
	int elevation;
	int range;
	
public:
	//Constructors & Destructor
	Configuration(ifstream& in_file);
	Configuration();
	~Configuration();

	//Setters
	void set_name(string input);
	void set_total_fov_h(int input);
	void set_total_fov_v(int input);
	void set_viewer_distance(int input);
	void set_num_channels(int input);
	void set_test_pattern(int input);
	void set_display_horizontal(bool input);
	void set_full_pattern(bool input);
	void set_opacity(int input);
	void set_azimuth(int input);
	void set_elevation(int input);
	void set_range(int input);

	//Getters
	string get_name();
	int get_total_fov_h();
	int get_total_fov_v();
	int get_viewer_distance();
	int get_num_channels();
	int get_test_pattern();
	vector<ChannelConfig>* get_channels();
	bool get_display_horizontal();
	bool get_full_pattern();
	int get_opacity();
	int get_azimuth();
	int get_elevation();
	int get_range();

	//Output
	void display_config_console();
	void output_config_file(ofstream& out_file);
	void output_config_file(ofstream& out_file, int channel_number);

	//TODO: Error detection

};


#endif