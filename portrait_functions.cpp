#include "headers.hpp"

Hero_Portrait::Hero_Portrait( HEROES name, SIDE looking )
{
    this->name = name;
    this->looking = looking;
    width = 140;
    height = 144;
    color_red = al_map_rgb( 255, 0, 0 );
    color_blue = al_map_rgb( 0, 0, 255 );
    border_red = false;
    border_blue = false;
    calibri = al_load_font( "fonts/calibri.ttf", 50, 0 );
    name_title = false;
}

int Hero_Portrait::choose_bitmap_and_load()
{
    if( looking == Right )
    {
        switch( name )
        {
        case Panda: { portrait_map = al_load_bitmap( "img_faces/panda_right.png" ); break; }
        case HolderH: { portrait_map = al_load_bitmap( "img_faces/holder.png" ); break; }
        case NoneH: break;
        }
    }
    else if( looking == Left )
    {
        switch( name )
        {
        case Panda: { portrait_map = al_load_bitmap( "img_faces/panda_left.png" ); break; }
        case HolderH: { portrait_map = al_load_bitmap( "img_faces/holder.png" ); break; }
        case NoneH: break;
        }
    }

    if( !portrait_map ) return -1;
    else return 1;
}

void Hero_Portrait::draw( float x, float y )
{
    position_x = x;
    position_y = y;
    al_draw_scaled_bitmap( portrait_map, 0, 0, 140, 144, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x()*width, Display_Monitor_Issues::get_scaling_factor_y()*height, 0 );
}

void Hero_Portrait::allow_red_border( bool a )
{
    border_red = a;
}

void Hero_Portrait::allow_blue_border( bool a )
{
    border_blue = a;
}

void Hero_Portrait::draw_red_border()
{
    if( border_red )
        al_draw_rectangle( position_x, position_y, position_x+Display_Monitor_Issues::get_scaling_factor_x()*width, position_y+Display_Monitor_Issues::get_scaling_factor_y()*height, color_red, 3 );
}

void Hero_Portrait::draw_blue_border()
{
    if( border_blue )
        al_draw_rectangle( position_x, position_y, position_x+Display_Monitor_Issues::get_scaling_factor_x()*width, position_y+Display_Monitor_Issues::get_scaling_factor_y()*height, color_blue, 3 );
}

void Hero_Portrait::allow_write_name( bool a )
{
    name_title = a;
}

void Hero_Portrait::write_name()
{
    if( name_title )
    {
        const char *c;
        float x;
        if( looking == Right ) x = 350.0;
        else if( looking == Left ) x = 1150.0;
        switch( name )
        {
            case Panda: c = "PANDA"; break;
            case HolderH: c = "/holder/"; break;
            case NoneH: break;
        }
        al_draw_text( calibri, al_map_rgb( 0, 0, 0 ), Display_Monitor_Issues::get_scaling_factor_x()*x, Display_Monitor_Issues::get_scaling_factor_y()*200.0, 0, c );
    }
}

/*float Hero_Portrait::get_x() { return position_x; }
float Hero_Portrait::get_y() { return position_y; }
float Hero_Portrait::get_w() { return width; }
float Hero_Portrait::get_h() { return height; }*/

Hero_Portrait::~Hero_Portrait()
{
    al_destroy_bitmap( portrait_map );
    al_destroy_font( calibri );
}
