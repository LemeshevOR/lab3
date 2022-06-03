#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "histogram.h"
#include "svg.h"
#define CURL_STATICLIB
#include <curl\curl.h>
#include <sstream>
#include <windows.h>
using namespace std;

void svg_begin(double width, double height);

void svg_end();

void svg_text(double left, double baseline, string text);

void show_histogram_svg(const vector<size_t>& bins);

void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black");

string make_info_text(double param);
