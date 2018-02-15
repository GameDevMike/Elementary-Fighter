#include "headers.hpp"

Location_Miniature::Location_Miniature( PLACES name )
{
    this->name = name;
    width = 400.0;
    height = 225.0;
    color_red = al_map_rgb( 255, 0, 0 );
    color_blue = al_map_rgb( 0, 0, 255 );
    border_red = false;
    border_blue = false;
}

int Location_Miniature::check_location_and_load()
{
    switch( name )
    {
    case Planets: { location_map = al_load_bitmap( "img_locations/planets.png" ); break; }
    case Tree: { location_map = al_load_bitmap( "img_locations/tree.png" ); break; }
    case HolderP: { location_map = al_load_bitmap( "img_locations/holder.png" ); break; }
    }

    if( !location_map ) return -1;
    else return 1;
}

void Location_Miniature::draw_location( float pos_x, float pos_y )
{
    al_draw_scaled_bitmap( location_map, 0, 0, 1600, 900, pos_x, pos_y, Display_Monitor_Issues::get_scaling_factor_x()*width, Display_Monitor_Issues::get_scaling_factor_y()*height, 0 );
    position_x = pos_x;
    position_y = pos_y;
}

void Location_Miniature::allow_red_border( bool a )
{
    border_red = a;
}

void Location_Miniature::allow_blue_border( bool a )
{
    border_blue = a;
}

void Location_Miniature::draw_red_border()
{
    if( border_red )
        al_draw_rectangle( position_x, position_y, position_x+Display_Monitor_Issues::get_scaling_factor_x()*width, position_y+Display_Monitor_Issues::get_scaling_factor_y()*height, color_red, 3 );
}

void Location_Miniature::draw_blue_border()
{
    if( border_blue )
        al_draw_rectangle( position_x, position_y, position_x+Display_Monitor_Issues::get_scaling_factor_x()*width, position_y+Display_Monitor_Issues::get_scaling_factor_y()*height, color_blue, 3 );
}

/*void Location_Miniature::set_border_thickness( float bth ) { border_thickness = bth; }
float Location_Miniature::get_x() { return position_x; }
float Location_Miniature::get_y() { return position_y; }
float Location_Miniature::get_w() { return width; }
float Location_Miniature::get_h() { return height; }*/

Location_Miniature::~Location_Miniature()
{
    al_destroy_bitmap( location_map );
}

Location_Background::Location_Background( PLACES name )
{
    this->name = name;
    width = Display_Monitor_Issues::get_desktop_width();
    height = Display_Monitor_Issues::get_desktop_height();
}

int Location_Background::check_location_and_load()
{
    switch( name )
    {
    case Planets: { location_map = al_load_bitmap( "img_locations/planets.png" ); break; }
    case Tree: { location_map = al_load_bitmap( "img_locations/tree.png" ); break; }
    case HolderP: { location_map = al_load_bitmap( "img_locations/holder.png" ); break; }
    }

    if( !location_map ) return -1;
    else return 1;
}

void Location_Background::draw_location( float pos_x, float pos_y )
{
    al_draw_scaled_bitmap( location_map, 0, 0, 1600, 900, pos_x, pos_y, width, height, 0 );
}

Location_Background::~Location_Background()
{
    al_destroy_bitmap( location_map );
}
