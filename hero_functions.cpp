#include "headers.hpp"

Hero::Hero( int id, HEROES name, SIDE facing, float x, float y )
{
    this->id = id;
    this->name = name;
    this->facing = facing;
    status = Stand;
    health = 1000.0;
    energy = 200.0;
    position_x = x;
    position_y = y;
    move_speed = 8.0;
    bitmap_stand_counter = 1;
    bitmap_walk_counter = 1;
    bitmap_attack_counter = 'z';
    timer_click_animation = al_create_timer( 0.2 );
    jump_speed = 20.0;
    jump_up = true;
    //last_stick_position = 0;
}

int Hero::check_hero_and_load()
{
    switch( name )
    {
        case Panda:
        {
            stand_right = al_load_bitmap( "img_panda/panda_stand_right.png" );
            if( !stand_right ) return -1;
            stand_left = al_load_bitmap( "img_panda/panda_stand_left.png" );
            if( !stand_left ) return -1;
            walk_right = al_load_bitmap( "img_panda/panda_walk_right.png" );
            if( !walk_right ) return -1;
            walk_left = al_load_bitmap( "img_panda/panda_walk_left.png" );
            if( !walk_left ) return -1;
            jump_right = al_load_bitmap( "img_panda/panda_jump_right.png" );
            if( !jump_right ) return -1;
            jump_left = al_load_bitmap( "img_panda/panda_jump_left.png" );
            if( !jump_left ) return -1;
            attack_right = al_load_bitmap( "img_panda/panda_attack_right.png" );
            if( !attack_right ) return -1;
            attack_left = al_load_bitmap( "img_panda/panda_attack_left.png" );
            if( !attack_left ) return -1;
            additional1 = al_load_bitmap( "img_panda/panda_shield_right.png" );
            if( ! additional1 ) return -1;
            additional2 = al_load_bitmap( "img_panda/panda_shield_left.png" );
            if( !additional2 ) return -1;
            additional3 = al_load_bitmap( "img_panda/panda_missile.png" );
            if( !additional3 ) return -1;
            break;
        }
    }
    return 1;
}

int Hero::load_bitmap_numbers()
{
    switch( name ) //albo case panda open a wczytaj uniwersalne
    {
        case Panda:
        {
            file.open( "txt_data/panda_stand.txt" );
            if( !file.good() ) return -1;
            for( int i = 0; i < 4; i++ ) for( int j = 0; j < 4; j++ ) file >> stand_values[ i ][ j ];
            file.close();

            file.open( "txt_data/panda_walk.txt" );
            if( !file.good() ) return -1;
            for( int i = 0; i < 8; i++ ) for( int j = 0; j < 4; j++ ) file >> walk_values[ i ][ j ];
            file.close();

            file.open( "txt_data/panda_jump.txt" );
            if( !file.good() ) return -1;
            for( int i = 0; i < 1; i++ ) for( int j = 0; j < 4; j++ ) file >> jump_values[ i ][ j ];
            file.close();

            file.open( "txt_data/panda_attack.txt" );
            if( !file.good() ) return -1;
            for( int i = 0; i < 10; i++ ) for( int j = 0; j < 4; j++ ) file >> attack_values[ i ][ j ];
            file.close();

            file.open( "txt_data/panda_additional.txt" );
            if( !file.good() ) return -1;
            for( int i = 0; i < 2; i++ ) for( int j = 0; j < 4; j++ ) file >> additional_values[ i ][ j ];
            file.close();
        }
    }
    return 1;
}

void Hero::set_hero_status( ACTIVITIES stat ) { status = stat; }
ACTIVITIES Hero::get_hero_status() { return status; }

void Hero::change_bitmap_status( ACTIVITIES bit_stat )
{
    switch( bit_stat )
    {
        case Stand:
        {
            if( bitmap_stand_counter == 1 ) bitmap_stand_counter = 2;
            else bitmap_stand_counter = 1;
            break;
        }
        case Walk:
        {
            if( bitmap_walk_counter == 4 ) bitmap_walk_counter = 1;
            else bitmap_walk_counter++;
            break;
        }
    }
}

void Hero::make_keyboard_hold_move( ALLEGRO_KEYBOARD_STATE ks, ALLEGRO_TIMER *t )
{
    al_get_keyboard_state( &ks );

    if( al_key_down( &ks, ALLEGRO_KEY_LEFT ) && status != Attack && status != Block && status != Jump )
    {
        status = Walk;
        if( position_x > Display_Monitor_Issues::get_scaling_factor_x() * 50.0 ) position_x -= move_speed;
        if( al_get_timer_count( t ) % 5 == 0 ) change_bitmap_status( Walk );
    }
    else if( al_key_down( &ks, ALLEGRO_KEY_RIGHT ) && status != Attack && status != Block && status != Jump )
    {
        status = Walk;
        if( position_x < Display_Monitor_Issues::get_scaling_factor_x() * 1330.0 ) position_x += move_speed;
        if( al_get_timer_count( t ) % 5 == 0 ) change_bitmap_status( Walk );
    }
    else if( al_key_down( &ks, ALLEGRO_KEY_DOWN ) && status != Attack && status != Jump ) status = Block;
    else
    {
        if( status == Walk ) status = Stand;
        if( status == Block ) status = Stand;
        if( status == Attack && al_get_timer_count( timer_click_animation ) >= 1 )
        {
            status = Stand;
            al_stop_timer( timer_click_animation );
            al_set_timer_count( timer_click_animation, 0 );
        }
        if( status == Jump )
        {
            if( jump_up )
            {
                if( position_y <= 70 ) { jump_speed = -6; jump_up = false; }
                else if( position_y <= 110 ) jump_speed = 6;
                else if( position_y <= 100 ) jump_speed = 14;
                else if( position_y <= 320 ) jump_speed = 18;
            }
            else
            {
                if( position_y >= 310 )
                {
                    position_y = Display_Monitor_Issues::get_scaling_factor_y() * 400.0;
                    status = Stand;
                    jump_speed = 10;
                    jump_up = true;
                }
                else if( position_y >= 190 ) jump_speed = -14;
                else if( position_y >= 110 ) jump_speed = -18;
            }
            position_y -= jump_speed;
        }
        if( al_get_timer_count( t ) % 14 == 0 ) change_bitmap_status( Stand );
    }
}

void Hero::make_gamepad_hold_move( ALLEGRO_JOYSTICK_STATE js, ALLEGRO_EVENT event, ALLEGRO_TIMER *t )
{
    if( js.stick[ 0 ].axis[ 0 ] < -0.7 && status != Attack && status != Block && status != Jump )
    {
        status = Walk;
        if( position_x > Display_Monitor_Issues::get_scaling_factor_x() * 50.0 ) position_x -= move_speed;
        if( al_get_timer_count( t ) % 5 == 0 ) change_bitmap_status( Walk );
    }
    else if( js.stick[ 0 ].axis[ 0 ] > 0.7 && status != Attack && status != Block && status != Jump )
    {
        status = Walk;
        if( position_x < Display_Monitor_Issues::get_scaling_factor_x() * 1350.0 ) position_x += move_speed;
        if( al_get_timer_count( t ) % 5 == 0 ) change_bitmap_status( Walk );
    }
    else if( js.stick[ 0 ].axis[ 1 ] > 0.9 && status != Attack && status != Jump ) status = Block;
    else
    {
        if( status == Walk ) status = Stand;
        if( status == Block ) status = Stand;
        if( status == Attack && al_get_timer_count( timer_click_animation ) >= 1 )
        {
            status = Stand;
            al_stop_timer( timer_click_animation );
            al_set_timer_count( timer_click_animation, 0 );
        }
        if( status == Jump )
        {
            if( jump_up )
            {
                if( position_y <= 70 ) { jump_speed = -6; jump_up = false; }
                else if( position_y <= 110 ) jump_speed = 6;
                else if( position_y <= 100 ) jump_speed = 14;
                else if( position_y <= 320 ) jump_speed = 18;
            }
            else
            {
                if( position_y >= 310 )
                {
                    position_y = Display_Monitor_Issues::get_scaling_factor_y() * 400.0;
                    status = Stand;
                    jump_speed = 10;
                    jump_up = true;
                }
                else if( position_y >= 190 ) jump_speed = -14;
                else if( position_y >= 110 ) jump_speed = -18;
            }
            position_y -= jump_speed;
        }
        if( al_get_timer_count( t ) % 14 == 0 ) change_bitmap_status( Stand );
    }
}

void Hero::make_keyboard_click_move( char move_type )
{
    if( move_type == 'j' )
    {
        status = Jump;
    }
    else if( move_type == 'v' )
    {
        status = Attack;
        bitmap_attack_counter = move_type;
        al_set_timer_speed( timer_click_animation, 1.0 );
        al_start_timer( timer_click_animation );
    }
    else
    {
        status = Attack;
        bitmap_attack_counter = move_type;
        draw = ( std::rand() % 2 ) + 1;
        al_set_timer_speed( timer_click_animation, 0.2 );
        al_start_timer( timer_click_animation );
    }
}

void Hero::make_gamepad_click_move() { status = Jump; }

void Hero::draw_hero()
{
    switch( status )
    {
        case Disabled:
        {
            if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( stand_right, stand_values[ 0 ][ 0 ], stand_values[ 0 ][ 1 ], stand_values[ 0 ][ 2 ], stand_values[ 0 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
            else al_draw_tinted_scaled_rotated_bitmap_region( stand_left, stand_values[ 2 ][ 0 ], stand_values[ 2 ][ 1 ], stand_values[ 2 ][ 2 ], stand_values[ 2 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
            break;
        }
        case Stand:
        {
            switch( bitmap_stand_counter )
            {
                case 1:
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( stand_right, stand_values[ 0 ][ 0 ], stand_values[ 0 ][ 1 ], stand_values[ 0 ][ 2 ], stand_values[ 0 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( stand_left, stand_values[ 2 ][ 0 ], stand_values[ 2 ][ 1 ], stand_values[ 2 ][ 2 ], stand_values[ 2 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
                case 2:
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( stand_right, stand_values[ 1 ][ 0 ], stand_values[ 1 ][ 1 ], stand_values[ 1 ][ 2 ], stand_values[ 1 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( stand_left, stand_values[ 3 ][ 0 ], stand_values[ 3 ][ 1 ], stand_values[ 3 ][ 2 ], stand_values[ 3 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
            }
            break;
        }
        case Walk:
        {
            switch( bitmap_walk_counter )
            {
                case 1:
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( walk_right, walk_values[ 0 ][ 0 ], walk_values[ 0 ][ 1 ], walk_values[ 0 ][ 2 ], walk_values[ 0 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( walk_left, walk_values[ 4 ][ 0 ], walk_values[ 4 ][ 1 ], walk_values[ 4 ][ 2 ], walk_values[ 4 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
                case 2:
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( walk_right, walk_values[ 1 ][ 0 ], walk_values[ 1 ][ 1 ], walk_values[ 1 ][ 2 ], walk_values[ 1 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( walk_left, walk_values[ 5 ][ 0 ], walk_values[ 5 ][ 1 ], walk_values[ 5 ][ 2 ], walk_values[ 5 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
                case 3:
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( walk_right, walk_values[ 2 ][ 0 ], walk_values[ 2 ][ 1 ], walk_values[ 2 ][ 2 ], walk_values[ 2 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( walk_left, walk_values[ 6 ][ 0 ], walk_values[ 6 ][ 1 ], walk_values[ 6 ][ 2 ], walk_values[ 6 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
                case 4:
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( walk_right, walk_values[ 3 ][ 0 ], walk_values[ 3 ][ 1 ], walk_values[ 3 ][ 2 ], walk_values[ 3 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( walk_left, walk_values[ 7 ][ 0 ], walk_values[ 7 ][ 1 ], walk_values[ 7 ][ 2 ], walk_values[ 7 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
            }
            break;
        }
        case Jump:
        {
            if( facing == Right ) al_draw_scaled_bitmap( jump_right, jump_values[ 0 ][ 0 ], jump_values[ 0 ][ 1 ], jump_values[ 0 ][ 2 ], jump_values[ 0 ][ 3 ], position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x()*jump_values[ 0 ][ 2 ], Display_Monitor_Issues::get_scaling_factor_y()*jump_values[ 0 ][ 3 ], 0 );
            else al_draw_scaled_bitmap( jump_left, jump_values[ 0 ][ 0 ], jump_values[ 0 ][ 1 ], jump_values[ 0 ][ 2 ], jump_values[ 0 ][ 3 ], position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x()*jump_values[ 0 ][ 2 ], Display_Monitor_Issues::get_scaling_factor_y()*jump_values[ 0 ][ 3 ], 0 );
            break;
        }
        case Attack:
        {
            switch( bitmap_attack_counter )
            {
                case 'z':
                {
                    if( draw == 1 )
                    {
                        if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( attack_right, attack_values[ 0 ][ 0 ], attack_values[ 0 ][ 1 ], attack_values[ 0 ][ 2 ], attack_values[ 0 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                        else al_draw_tinted_scaled_rotated_bitmap_region( attack_left, attack_values[ 5 ][ 0 ], attack_values[ 5 ][ 1 ], attack_values[ 5 ][ 2 ], attack_values[ 5 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x - 40, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    }
                    else
                    {
                        if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( attack_right, attack_values[ 1 ][ 0 ], attack_values[ 1 ][ 1 ], attack_values[ 1 ][ 2 ], attack_values[ 1 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                        else al_draw_tinted_scaled_rotated_bitmap_region( attack_left, attack_values[ 6 ][ 0 ], attack_values[ 6 ][ 1 ], attack_values[ 6 ][ 2 ], attack_values[ 6 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x - 40, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    }
                    break;
                }
                case 'x':
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( attack_right, attack_values[ 2 ][ 0 ], attack_values[ 2 ][ 1 ], attack_values[ 2 ][ 2 ], attack_values[ 2 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( attack_left, attack_values[ 7 ][ 0 ], attack_values[ 7 ][ 1 ], attack_values[ 7 ][ 2 ], attack_values[ 7 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x + 40, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
                case 'c':
                {
                    if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( attack_right, attack_values[ 3 ][ 0 ], attack_values[ 3 ][ 1 ], attack_values[ 3 ][ 2 ], attack_values[ 3 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    else al_draw_tinted_scaled_rotated_bitmap_region( attack_left, attack_values[ 8 ][ 0 ], attack_values[ 8 ][ 1 ], attack_values[ 8 ][ 2 ], attack_values[ 8 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x - 30, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                    break;
                }
                case 'v':
                {
                    if( facing == Right )
                    {
                        al_draw_tinted_scaled_rotated_bitmap_region( stand_right, stand_values[ 0 ][ 0 ], stand_values[ 0 ][ 1 ], stand_values[ 0 ][ 2 ], stand_values[ 0 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                        al_draw_scaled_bitmap( additional1, additional_values[ 0 ][ 0 ], additional_values[ 0 ][ 1 ], additional_values[ 0 ][ 2 ], additional_values[ 0 ][ 3 ], position_x + 140, position_y - 8, Display_Monitor_Issues::get_scaling_factor_x()*additional_values[ 0 ][ 2 ], Display_Monitor_Issues::get_scaling_factor_y()*additional_values[ 0 ][ 3 ], 0 );
                    }
                    else
                    {
                        al_draw_tinted_scaled_rotated_bitmap_region( stand_left, stand_values[ 2 ][ 0 ], stand_values[ 2 ][ 1 ], stand_values[ 2 ][ 2 ], stand_values[ 2 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
                        al_draw_scaled_bitmap( additional2, additional_values[ 0 ][ 0 ], additional_values[ 0 ][ 1 ], additional_values[ 0 ][ 2 ], additional_values[ 0 ][ 3 ], position_x - 40, position_y - 8, Display_Monitor_Issues::get_scaling_factor_x()*additional_values[ 0 ][ 2 ], Display_Monitor_Issues::get_scaling_factor_y()*additional_values[ 0 ][ 3 ], 0 );
                    }
                    break;
                }
            }
            break;
        }
        case Block:
        {
            if( facing == Right ) al_draw_tinted_scaled_rotated_bitmap_region( attack_right, attack_values[ 4 ][ 0 ], attack_values[ 4 ][ 1 ], attack_values[ 4 ][ 2 ], attack_values[ 4 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
            else al_draw_tinted_scaled_rotated_bitmap_region( attack_left, attack_values[ 9 ][ 0 ], attack_values[ 9 ][ 1 ], attack_values[ 9 ][ 2 ], attack_values[ 9 ][ 3 ], al_map_rgb( 255, 255, 255 ), 0, 0, position_x, position_y, Display_Monitor_Issues::get_scaling_factor_x(), Display_Monitor_Issues::get_scaling_factor_y(), 0, 0 );
            break;
        }
    }
}

void Hero::draw_hud()
{
    float sfx = Display_Monitor_Issues::get_scaling_factor_x();
    float sfy = Display_Monitor_Issues::get_scaling_factor_y();
    float basic_length = 500.0;
    float basic_health = 1000.0;
    float current_health_factor = health / basic_health;
    float current_length = current_health_factor * basic_length;
    if( id == 1 )
    {
        al_draw_filled_rectangle( sfx*50.0, sfy*30.0, sfx*50.0+sfx*current_length, sfy*30.0+sfy*30.0, al_map_rgb( 232, 0, 0 ) );
        al_draw_rectangle( sfx*50.0, sfy*30.0, sfx*50.0+sfx*500.0, sfy*30.0+sfy*30.0, al_map_rgb( 0, 0, 0 ), 1 );
        al_draw_filled_rectangle( sfx*50.0, sfy*70.0, sfx*50.0+sfx*500.0, sfy*70.0+sfy*30.0, al_map_rgb( 242, 234, 3 ) );
        al_draw_rectangle( sfx*50.0, sfy*70.0, sfx*50.0+sfx*500.0, sfy*70.0+sfy*30.0, al_map_rgb( 0, 0, 0 ), 1 );
        al_draw_circle( sfx*610.0, sfy*65.0, 20.0, al_map_rgb( 0, 0, 0 ), 1 );
        al_draw_circle( sfx*670.0, sfy*65.0, 20.0, al_map_rgb( 0, 0, 0 ), 1 );
    }
    else
    {
        al_draw_filled_rectangle( sfx*1550.0-sfx*current_length, sfy*30.0, sfx*1550.0, sfy*30.0+sfy*30.0, al_map_rgb( 232, 0, 0 ) );
        al_draw_rectangle( sfx*1550.0-sfx*500.0, sfy*30.0, sfx*1550.0, sfy*30.0+sfy*30.0, al_map_rgb( 0, 0, 0 ), 1 );
        al_draw_filled_rectangle( sfx*1550.0-sfx*500.0, sfy*70.0, sfx*1550.0, sfy*70.0+sfy*30.0, al_map_rgb( 242, 234, 3 ) );
        al_draw_rectangle( sfx*1550.0-sfx*500.0, sfy*70.0, sfx*1550.0, sfy*70.0+sfy*30.0, al_map_rgb( 0, 0, 0 ), 1 );
        al_draw_circle( sfx*990.0, sfy*65.0, 20.0, al_map_rgb( 0, 0, 0 ), 1 );
        al_draw_circle( sfx*930.0, sfy*65.0, 20.0, al_map_rgb( 0, 0, 0 ), 1 );
    }
}

void Hero::receive_damage( float dmg )
{
    if( health - dmg > 0 ) health -= dmg;
    else health = 0;
}

float Hero::deal_basic_damage()
{
    if( name == Panda ) return 30.0;
    else return 0; //not rly necessary
}

Hero::~Hero()
{
    al_destroy_bitmap( stand_right );
    al_destroy_bitmap( stand_left );
    al_destroy_bitmap( walk_right );
    al_destroy_bitmap( walk_left );
    al_destroy_bitmap( jump_right );
    al_destroy_bitmap( jump_left );
    al_destroy_bitmap( attack_right );
    al_destroy_bitmap( attack_left );
    al_destroy_bitmap( additional1 );
    al_destroy_bitmap( additional2 );
    al_destroy_bitmap( additional3 );
    al_destroy_timer( timer_click_animation );
}
