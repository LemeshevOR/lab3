#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "histogram.h"
#include "svg.h"
#define CURL_STATICLIB
#include <curl\curl.h>
using namespace std;

struct Input
{
    vector<double> numbers;
    size_t bin_count;
    double BLOCK_WIDTH=10;

};
Input read_input(istream& in, bool prompt);
size_t write_data(void* items, size_t item_size, size_t item_count, void* ctx);
Input download(const string& address);
void find_minmax(const vector<double>& numbers, double& min, double& max);
bool check_block_weight(double BLOCK_WIDTH);
vector<double> input_numbers(istream& in, size_t count);
vector<size_t> make_histogram(const Input input);
void show_histogram_text(vector<size_t> bins);
