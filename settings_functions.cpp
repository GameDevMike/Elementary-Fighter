#include "headers.hpp"

int Display_Monitor_Issues::number_of_adapters;
ALLEGRO_MONITOR_INFO Display_Monitor_Issues::aminfo;
float Display_Monitor_Issues::desktop_width;
float Display_Monitor_Issues::desktop_height;
float Display_Monitor_Issues::aspect_ratio;
float Display_Monitor_Issues::scaling_factor_x;
float Display_Monitor_Issues::scaling_factor_y;

void Display_Monitor_Issues::learn_number_of_adapters()
{
    number_of_adapters = al_get_num_video_adapters();
}

int Display_Monitor_Issues::get_number_of_adapters()
{
    return number_of_adapters;
}

void Display_Monitor_Issues::choose_adapter( int adapter_no )
{
    al_set_new_display_adapter( adapter_no );
}

void Display_Monitor_Issues::monitor_info( int adapter_no )
{
    al_get_monitor_info( adapter_no, &aminfo );
}

void Display_Monitor_Issues::calculate_desktop_width()
{
    desktop_width = aminfo.x2 - aminfo.x1;
}

void Display_Monitor_Issues::calculate_desktop_height()
{
    desktop_height = aminfo.y2 - aminfo.y1;
}

float Display_Monitor_Issues::get_desktop_width()
{
    return desktop_width;
}

float Display_Monitor_Issues::get_desktop_height()
{
    return desktop_height;
}

void Display_Monitor_Issues::calculate_aspect_ratio()
{
    aspect_ratio = desktop_width / desktop_height;
}

float Display_Monitor_Issues::get_aspect_ratio()
{
    return aspect_ratio;
}

void Display_Monitor_Issues::calculate_scaling_factors()
{
    scaling_factor_x = desktop_width / 1600.0;
    scaling_factor_y = desktop_height / 900.0;
}

float Display_Monitor_Issues::get_scaling_factor_x()
{
    return scaling_factor_x;
}

float Display_Monitor_Issues::get_scaling_factor_y()
{
    return scaling_factor_y;
}

int Display_Monitor_Issues::determine_window_resolution()
{
    if( desktop_width >= 1600 ) { desktop_width = 1600; desktop_height = 900; }
    else if ( desktop_width >= 1366 ) { desktop_width = 1366; desktop_height = 768; }
    else if ( desktop_width >= 1280 ) { desktop_width = 1280; desktop_height = 720; }
    else if ( desktop_width >= 1024 ) { desktop_width = 1024; desktop_height = 576; }
    else if ( desktop_width >= 800 ) { desktop_width = 800; desktop_height = 450; }
    else return -1;
    return 1;
}

void Display_Monitor_Issues::print_to_console()
{
    std::cout << desktop_width << "\n"
    << desktop_height << "\n"
    << aspect_ratio << "\n"
    << aminfo.x1 << " " << aminfo.y1 << " " << aminfo.x2 << " " << aminfo.y2 << "\n\n";
}
