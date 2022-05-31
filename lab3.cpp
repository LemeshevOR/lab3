#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "histogram.h"
#include "svg.h"
#define CURL_STATICLIB
#include <curl\curl.h>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;






int main(int argc, char* argv[]) 
{
    DWORD mask = 0x0000ffff;
    DWORD info = GetVersion();
    DWORD version = info & mask;

    DWORD platform = info >> 16;
    DWORD mask_major = 0x0000ff;
    DWORD version_major = (version & mask_major);
    DWORD version_minor = version >> 8;
    if ((info & 0x80000000) == 0)
    {
        DWORD version_major = version & mask_major;
        DWORD version_minor = version >> 8;
        DWORD build = platform;
        printf("Windows v%u.%u (build %u)\n", version_major, version_minor, build);
    }
   
    char system_dir[MAX_PATH];
    char computer_name[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD size = MAX_COMPUTERNAME_LENGTH + 1;
    GetComputerNameA(computer_name, &size);
    printf("Computer name: %s\n", computer_name);

    return 0;
    Input input;
    if (argc > 1) {
        input = download(argv[1]);
    }
    else {
        input = read_input(cin, true);
    }
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    double BLOCK_WIDTH = 10;


 
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


        cerr << "CURL: " << curl_version_info(CURLVERSION_NOW)->version << "\n" << "SSL: " << curl_version_info(CURLVERSION_NOW)->ssl_version;
    }
    svg_end();
}
