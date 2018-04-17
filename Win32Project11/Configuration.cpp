#include "Configuration.h"

//Constructors & Destructor
Configuration::Configuration(ifstream& in_file) {
	string in_string;
	channels = new vector<ChannelConfig>;

	while (getline(in_file, in_string, ':')) {
		if (in_string == "name") {
			getline(in_file, in_string);
			this->set_name(in_string);
		}
		else if (in_string == "total_fov_h") {
			getline(in_file, in_string);
			this->set_total_fov_h(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "total_fov_v") {
			getline(in_file, in_string);
			this->set_total_fov_v(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "viewer_distance") {
			getline(in_file, in_string);
			this->set_viewer_distance(stof(in_string, nullptr));
		}
		else if (in_string == "num_channels") {
			getline(in_file, in_string);
			this->set_num_channels(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "test_pattern") {
			getline(in_file, in_string);
			this->set_test_pattern(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "display_horizontal") {
 			getline(in_file, in_string);
			if (stoi(in_string, nullptr, 0) == false)
				this->set_display_horizontal(false);
			else
				this->set_display_horizontal(true);
		}
		else if (in_string == "full_pattern") {
			getline(in_file, in_string);
			if (stoi(in_string, nullptr, 0) == false)
				this->set_full_pattern(false);
			else
				this->set_full_pattern(true);
		}
		else if (in_string == "opacity") {
			getline(in_file, in_string);
			this->set_opacity(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "azimuth") {
			getline(in_file, in_string);
			this->set_azimuth(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "elevation") {
			getline(in_file, in_string);
			this->set_elevation(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "range") {
			getline(in_file, in_string);
			this->set_range(stoi(in_string, nullptr, 0));
		}
		else if (in_string == "-") {
			getline(in_file, in_string);
			ChannelConfig* temp = new ChannelConfig(in_file);
			channels->push_back(*temp);
		}
		else {
			cout << "Configuration type not recognized" << endl;
		}
	}
}
Configuration::Configuration() {
	this->set_name("Untitled Configuration");
	channels = new vector<ChannelConfig>;
	this->display_horizontal = true;
	this->full_pattern = false;
}

Configuration::~Configuration() {
	delete this;
}

//Setters
void Configuration::set_name(string input) {
	this->name = input;
}
void Configuration::set_total_fov_h(int input) {
	this->total_fov_h = input;
}
void Configuration::set_total_fov_v(int input) {
	this->total_fov_v = input;
}
void Configuration::set_viewer_distance(float input) {
	this->viewer_distance = input;
}
void Configuration::set_num_channels(int input) {
	this->num_channels = input;
}
void Configuration::set_test_pattern(int input) {
	this->test_pattern = input;
}

void Configuration::set_display_horizontal(bool input)
{
	this->display_horizontal = input;
}

void Configuration::set_full_pattern(bool input)
{
	this->full_pattern = input;
}

void Configuration::set_opacity(int input)
{
	this->opacity = input;
}

void Configuration::set_azimuth(int input)
{
	this->azimuth = input;
}

void Configuration::set_elevation(int input)
{
	this->elevation = input;
}

void Configuration::set_range(int input)
{
	this->range = input;
}

//Getters
string Configuration::get_name() {
	return this->name;
}
int Configuration::get_total_fov_h() {
	return this->total_fov_h;
}
int Configuration::get_total_fov_v() {
	return this->total_fov_v;
}
float Configuration::get_viewer_distance() {
	return this->viewer_distance;
}
int Configuration::get_num_channels() {
	return this->num_channels;
}
int Configuration::get_test_pattern() {
	return this->test_pattern;
}
vector<ChannelConfig>* Configuration::get_channels()
{
	return channels;
}

bool Configuration::get_display_horizontal()
{
	return display_horizontal;
}

bool Configuration::get_full_pattern()
{
	return full_pattern;
}

int Configuration::get_opacity()
{
	return opacity;
}

int Configuration::get_azimuth()
{
	return azimuth;
}

int Configuration::get_elevation()
{
	return elevation;
}

int Configuration::get_range()
{
	return range;
}

//Output
void Configuration::display_config_console() {
	cout << "name:" << this->get_name() << endl;
	cout << "total_fov_h:" << this->get_total_fov_h() << endl;
	cout << "total_fov_v:" << this->get_total_fov_v() << endl;
	cout << "viewer_distance:" << this->get_viewer_distance() << endl;
	cout << "num_channels:" << this->get_num_channels() << endl;
	cout << "test_pattern:" << this->get_test_pattern() << endl;
	for (vector<ChannelConfig>::iterator it = channels->begin(); it != channels->end(); ++it) {
		cout << "-:" << endl;
		it->display_channel_console();
	}
}

void Configuration::output_config_file(ofstream& out_file) {
	out_file << "name:" << this->get_name() << endl;
	out_file << "total_fov_h:" << this->get_total_fov_h() << endl;
	out_file << "total_fov_v:" << this->get_total_fov_v() << endl;
	out_file << "viewer_distance:" << this->get_viewer_distance() << endl;
	out_file << "num_channels:" << this->get_num_channels() << endl;
	out_file << "test_pattern:" << this->get_test_pattern() << endl;
	out_file << "display_horizontal:" << this->get_display_horizontal() << endl;
	out_file << "full_pattern:" << this->get_full_pattern() << endl;
	out_file << "opacity:" << this->get_opacity() << endl;
	out_file << "azimuth:" << this->get_azimuth() << endl;
	out_file << "elevation:" << this->get_elevation() << endl;
	out_file << "range:" << this->get_range() << endl;

	for (vector<ChannelConfig>::iterator it = channels->begin(); it != channels->end(); ++it) {
		out_file << "-:" << endl;
		it->output_channel_file(out_file);
	}
}
