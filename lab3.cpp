﻿#include <iostream>
#include <vector>
#include <string>
#include "histogram.h"
#include "svg.h"
using namespace std;





int main()
{

    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    double BLOCK_WIDTH = 10;
    // Ввод данных
    const auto input = read_input(cin,true);
    
    
    
    while (check_block_weight(BLOCK_WIDTH)==true)
    {
        cerr << "Invalid block width!  " << "Enter Block width: ";
        cin >> BLOCK_WIDTH;
    }



    // Создание диаграммы
    


    const auto bins = make_histogram(input);

    // Вывод данных
    show_histogram_svg(bins);
    double top = 0;


    size_t max_bin = bins[0];
    for (size_t bin : bins)
    {
        if (bin > max_bin)
        {
            max_bin = bin;
        }
    }
    const bool scaling_needed = max_bin* BLOCK_WIDTH > IMAGE_WIDTH - TEXT_WIDTH;
    for (size_t bin : bins)
    {
        size_t height = bin;

        if (scaling_needed)   //Если масштабировать необходимо
        {
            const double scaling_factor = (double)(IMAGE_WIDTH - TEXT_WIDTH )/ (max_bin* BLOCK_WIDTH);
            height = bin * scaling_factor;
        }
        const double bin_width = BLOCK_WIDTH * height;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT, "MediumSlateBlue", "#E6E6FA");
        top += BIN_HEIGHT;

    }
    svg_end();
}
