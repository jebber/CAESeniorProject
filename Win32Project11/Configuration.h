//#pragma once
//Configuration Class file
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "ChannelConfig.h"

using namespace std;

class Configuration {

private:
	string name;
	int total_fov_h;       //Measured in degrees
	int total_fov_v;       //Measured in degrees
	float viewer_distance; //Measured in inches
	int num_channels;
	int test_pattern;
	vector<ChannelConfig>* channels;
	

public:
	//Constructors & Destructor
	Configuration(ifstream& in_file);
	Configuration();
	~Configuration();
	
	

	//Setters
	void set_name(string input);
	void set_total_fov_h(int input);
	void set_total_fov_v(int input);
	void set_viewer_distance(float input);
	void set_num_channels(int input);
	void set_test_pattern(int input);

	//Getters
	string get_name();
	int get_total_fov_h();
	int get_total_fov_v();
	float get_viewer_distance();
	int get_num_channels();
	int get_test_pattern();
	vector<ChannelConfig>* get_channels();

	//Output
	void display_config_console();
	void output_config_file(ofstream& out_file);

	//TODO: Error detection

};


#endif