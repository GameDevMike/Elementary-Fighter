#include "headers.hpp"

//TEXT MENU OPTIONS

Text::Text( std::string value, int id, float x, float y )
{
    this->value = value;
    this->id = id;
    position_x = x;
    position_y = y;
    color_white = al_map_rgb( 255, 255, 255 );
    color_grey = al_map_rgb( 227, 229, 230 );
    if( id == 0 ) color_current = color_grey;
    else color_current = color_white;
    font_calibri_bold = al_load_font( "fonts/calibrib.ttf", 72, 0 );
}

void Text::write()
{
    const char *c = value.c_str();
    al_draw_text( font_calibri_bold, color_current, position_x, position_y, 0, c );
}

void Text::change_color_to_white() { color_current = color_white; }
void Text::change_color_to_grey() { color_current = color_grey; }

Text::~Text()
{
    al_destroy_font( font_calibri_bold );
}

//TEXT HEADER

Text_Header::Text_Header( std::string value, float x, float y, int font_s, int ver )
{
    this->value = value;
    position_x = x;
    position_y = y;
    color_black = al_map_rgb( 0, 0, 0 );
    if( ver == 0 ) font_calibri = al_load_font( "fonts/calibri.ttf", font_s, 0 );
    else if( ver == 1 ) font_calibri = al_load_font( "fonts/calibrib.ttf", font_s, 0 );
}

void Text_Header::write()
{
    const char *c = value.c_str();
    al_draw_text( font_calibri, color_black, position_x, position_y, 0, c );
}

Text_Header::~Text_Header()
{
    al_destroy_font( font_calibri );
}
