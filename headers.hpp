#ifndef headers_hpp
#define headers_hpp

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>

enum GAME_STATE { Menu1, Menu2, Select_Opponent, Select_Hero, Select_Location, Fight };
enum OPPONENT { Both, Real, Computer };
enum DEVICES { NoneD, Keyboard, Gamepad1, Gamepad2 };
enum SIDE { Right, Left };
enum PLACES { NoneP, Planets, Tree, HolderP };
enum HEROES { NoneH, Panda, HolderH };
enum ACTIVITIES { Stand, Walk, Jump, Attack, Block, Disabled };

class Display_Monitor_Issues
{
private:
    static int number_of_adapters;
    static ALLEGRO_MONITOR_INFO aminfo;
    static float desktop_width;
    static float desktop_height;
    static float aspect_ratio;
    static float scaling_factor_x;
    static float scaling_factor_y;

public:
    static void learn_number_of_adapters();
    static int get_number_of_adapters();
    static void choose_adapter( int adapter_no );
    static void monitor_info( int adapter_no );
    static void convert_to_float();
    static void calculate_desktop_width();
    static void calculate_desktop_height();
    static float get_desktop_width();
    static float get_desktop_height();
    static void calculate_aspect_ratio();
    static float get_aspect_ratio();
    static void calculate_scaling_factors();
    static float get_scaling_factor_x();
    static float get_scaling_factor_y();
    static int determine_window_resolution();
    static void print_to_console();
};

class Text
{
private:
    int id;
    std::string value;
    ALLEGRO_FONT *font_calibri_bold;
    float position_x;
    float position_y;
    float text_length;
    float text_height;
    ALLEGRO_COLOR color_white;
    ALLEGRO_COLOR color_grey;
    ALLEGRO_COLOR color_current;

public:
    Text( std::string value, int id, float x, float y );
    ~Text();
    void write();
    void change_color_to_white();
    void change_color_to_grey();
};

class Text_Header
{
private:
    std::string value;
    ALLEGRO_FONT *font_calibri;
    float position_x;
    float position_y;
    ALLEGRO_COLOR color_black;

public:
    Text_Header( std::string value, float x, float y, int font_s, int ver );
    ~Text_Header();
    void write();
};

class Hero_Portrait
{
private:
    HEROES name;
    SIDE looking;
    ALLEGRO_BITMAP *portrait_map;
    float position_x;
    float position_y;
    float width;
    float height;
    ALLEGRO_COLOR color_red;
    ALLEGRO_COLOR color_blue;
    bool border_red;
    bool border_blue;
    ALLEGRO_FONT *calibri;
    bool name_title;

public:
    Hero_Portrait( HEROES name, SIDE looking );
    ~Hero_Portrait();
    int choose_bitmap_and_load();
    void draw( float x, float y );
    void allow_red_border( bool a );
    void allow_blue_border( bool a );
    void draw_red_border();
    void draw_blue_border();
    void allow_write_name( bool a );
    void write_name();
};

class Location_Miniature
{
private:
    PLACES name;
    ALLEGRO_BITMAP *location_map;
    float position_x;
    float position_y;
    float width;
    float height;
    ALLEGRO_COLOR color_red;
    ALLEGRO_COLOR color_blue;
    bool border_red;
    bool border_blue;

public:
    Location_Miniature( PLACES name );
    ~Location_Miniature();
    int check_location_and_load();
    void allow_red_border( bool a );
    void allow_blue_border( bool a );
    void draw_red_border();
    void draw_blue_border();
    void draw_location( float pos_x, float pos_y );
};

class Location_Background
{
private:
    PLACES name;
    ALLEGRO_BITMAP *location_map;
    float width;
    float height;

public:
    Location_Background( PLACES name );
    ~Location_Background();
    int check_location_and_load();
    void draw_location( float pos_x, float pos_y );
};

class Hero
{
private:
    int id;
    HEROES name;
    SIDE facing;
    ACTIVITIES status;
    float health;
    float energy;
    float position_x;
    float position_y;
    float move_speed;
    ALLEGRO_BITMAP *stand_right;
    ALLEGRO_BITMAP *stand_left;
    ALLEGRO_BITMAP *walk_right;
    ALLEGRO_BITMAP *walk_left;
    ALLEGRO_BITMAP *jump_right;
    ALLEGRO_BITMAP *jump_left;
    ALLEGRO_BITMAP *attack_right;
    ALLEGRO_BITMAP *attack_left;
    ALLEGRO_BITMAP *additional1;
    ALLEGRO_BITMAP *additional2;
    ALLEGRO_BITMAP *additional3;
    std::ifstream file;
    int stand_values[ 4 ][ 4 ];
    int walk_values[ 8 ][ 4 ];
    int jump_values[ 1 ][ 4 ];
    int attack_values[ 10 ][ 4 ];
    int additional_values[ 2 ][ 4 ];
    int bitmap_stand_counter;
    int bitmap_walk_counter;
    char bitmap_attack_counter;
    int draw;
    ALLEGRO_TIMER *timer_click_animation;
    float jump_speed;
    bool jump_up;

public:
    Hero( int id, HEROES name, SIDE facing, float x, float y );
    ~Hero();
    int check_hero_and_load();
    int load_bitmap_numbers();
    void set_hero_status( ACTIVITIES stat );
    ACTIVITIES get_hero_status();
    void change_bitmap_status( ACTIVITIES bit_stat );
    void make_keyboard_hold_move( ALLEGRO_KEYBOARD_STATE ks, ALLEGRO_TIMER *t );
    void make_gamepad_hold_move( ALLEGRO_JOYSTICK_STATE js, ALLEGRO_EVENT event, ALLEGRO_TIMER *t );
    void make_keyboard_click_move( char move_type );
    void make_gamepad_click_move();
    float get_jump_position();
    void draw_hero();
    void draw_hud();
    float get_hero_pos_x() { return position_x; }
    float get_health() { return health; }
    void receive_damage( float dmg );
    float deal_basic_damage();
};

class Various_Procedures
{
public:
    static void menu_go_down( int &marked_menu, Text *menu_text1, Text *menu_text2, Text *menu_text3, Text *menu_text4 );
    static void menu_go_up( int &marked_menu, Text *menu_text1, Text *menu_text2, Text *menu_text3, Text *menu_text4 );
    static void hero_go_right( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 );
    static void hero_go_left( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 );
    static void hero_go_down( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 );
    static void hero_go_up( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 );
    static void hero_enter( SIDE half, HEROES &chosen_hero, int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 );
    static void loc_go_right( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 );
    static void loc_go_left( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 );
    static void loc_go_down( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 );
    static void loc_go_up( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 );
    static void loc_enter( PLACES &chosen_loc, int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 );
};

#endif
