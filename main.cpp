#include "headers.hpp"

int main()
{
//ALLEGRO INITIALIZATION
    if( !al_init() )
    {
        al_show_native_message_box( NULL, "Warning", "ERROR", "Initialization failed, something went wrong, contact the dev", NULL, 0 );
        return -1;
    }

//DISPLAY CREATION AND DISPLAY/MONITOR SETTINGS
    int error_checker = 1;
    ALLEGRO_DISPLAY *main_display = NULL;
    Display_Monitor_Issues::choose_adapter( 0 );
    Display_Monitor_Issues::monitor_info( 1 );
    Display_Monitor_Issues::calculate_desktop_width();
    Display_Monitor_Issues::calculate_desktop_height();
    Display_Monitor_Issues::calculate_aspect_ratio();
    if( Display_Monitor_Issues::get_aspect_ratio() > 1.7 && Display_Monitor_Issues::get_aspect_ratio() < 1.8 )
        al_set_new_display_flags( ALLEGRO_FULLSCREEN );
    else error_checker = Display_Monitor_Issues::determine_window_resolution();
    if( error_checker < 0 )
    {
        al_show_native_message_box( NULL, "Warning", "ERROR", "Your display is too small", NULL, 0 );
        return -1;
    }
    Display_Monitor_Issues::calculate_scaling_factors();
    //Display_Monitor_Issues::print_to_console();
    main_display = al_create_display( Display_Monitor_Issues::get_desktop_width(), Display_Monitor_Issues::get_desktop_height() );
    if( !main_display )
    {
        al_show_native_message_box( main_display, "Warning", "ERROR", "Display could not be created", NULL, 0 );
        return -1;
    }
    al_set_window_title( main_display, "Elementary Fighter 2D" );

//INSTALLATIONS AND INITIALIZATIONS
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();
    al_install_joystick();
    srand( time( NULL ) );

//JOYSTICK GAMEPAD ROUTINES
    ALLEGRO_JOYSTICK *joy1;
    ALLEGRO_JOYSTICK *joy2;
    const char* j1name_c;
    const char* j2name_c;
    std::string j1name_s;
    std::string j2name_s;
    int j_num = al_get_num_joysticks();
    //std::cout << "j: " << j_num << "\n";
    if( j_num == 1 || j_num == 2 )
    {
        joy1 = al_get_joystick( 0 );
        j1name_c = al_get_joystick_name( joy1 );
        j1name_s = j1name_c;
        if( j1name_s.size() >= 21 ) j1name_s = j1name_s.substr( 0, 20 );
        //std::cout << j1name_s << "\n";
        if( j_num == 2 )
        {
            joy2 = al_get_joystick( 1 );
            j2name_c = al_get_joystick_name( joy2 );
            j2name_s = j2name_c;
            if( j2name_s.size() >= 21 ) j2name_s = j2name_s.substr( 0, 20 );
            //std::cout << j2name_s << "\n\n";
        }
    }
    else if( j_num > 2 )
    {
        al_show_native_message_box( NULL, "Warning", "ERROR", "You have to many joysticks/gamepads plugged in (the maximum is 2)", NULL, 0 );
        return -1;
    }

    /*std::cout << al_get_joystick_num_buttons( joy1 ) << "\n";
    std::cout << al_get_joystick_num_sticks( joy1 ) << "\n";
    std::cout << al_get_joystick_num_axes( joy1, 0 ) << "\n";
    std::cout << al_get_joystick_num_axes( joy1, 1 ) << "\n";
    std::cout << al_get_joystick_num_axes( joy1, 2 ) << "\n\n";

    std::cout << al_get_joystick_button_name( joy1, 0 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 1 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 2 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 3 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 4 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 5 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 6 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 6 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 7 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 8 ) << "\n";
    std::cout << al_get_joystick_button_name( joy1, 9 ) << "\n\n";

    std::cout << al_get_joystick_stick_name( joy1, 0 ) << "\n";
    std::cout << al_get_joystick_stick_name( joy1, 1 ) << "\n";
    std::cout << al_get_joystick_stick_name( joy1, 2 ) << "\n\n";

    std::cout << al_get_joystick_axis_name( joy1, 0, 0 ) << "\n";
    std::cout << al_get_joystick_axis_name( joy1, 0, 1 ) << "\n";
    std::cout << al_get_joystick_axis_name( joy1, 0, 2 ) << "\n\n";
    std::cout << al_get_joystick_axis_name( joy1, 1, 0 ) << "\n";
    std::cout << al_get_joystick_axis_name( joy1, 1, 1 ) << "\n\n";
    std::cout << al_get_joystick_axis_name( joy1, 2, 0 ) << "\n";
    std::cout << al_get_joystick_axis_name( joy1, 2, 1 ) << "\n\n";*/

//GAMELOOP VARIABLES, EVENT QUEUE, EVENT SOURCES, MAIN TIMER
    float sfx = Display_Monitor_Issues::get_scaling_factor_x();
    float sfy = Display_Monitor_Issues::get_scaling_factor_y();
    bool game_is_running = true;
    ALLEGRO_TIMER *timer_1_gameloop = al_create_timer( 1.0 / 60.0 );
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source( event_queue, al_get_timer_event_source( timer_1_gameloop ) );
    al_register_event_source( event_queue, al_get_mouse_event_source() );
    al_register_event_source( event_queue, al_get_keyboard_event_source() );
    al_register_event_source( event_queue, al_get_joystick_event_source() );
    ALLEGRO_EVENT event;
    ALLEGRO_JOYSTICK_STATE joystate1;
    ALLEGRO_JOYSTICK_STATE joystate2;
    ALLEGRO_JOYSTICK_STATE joystate_fight_g1;
    ALLEGRO_JOYSTICK_STATE joystate_fight_g2;
    ALLEGRO_KEYBOARD_STATE keyboard_state;

//OBJECTS, POINTERS, NON-CLASS VARIABLES AND RESOURCES
    //bitmaps
    ALLEGRO_BITMAP *bitmap_menu1 = al_load_bitmap( "img_menu/menu.png" );
    if( !bitmap_menu1 ) { al_show_native_message_box( NULL, "Warning", "ERROR", "Could not load menu", NULL, 0 ); return -1; }
    ALLEGRO_BITMAP *bitmap_loading1 = al_load_bitmap( "img_menu/loading.png" );
    if( !bitmap_loading1 ) { al_show_native_message_box( NULL, "Warning", "ERROR", "Could not load some graphics", NULL, 0 ); return -1; }
    ALLEGRO_BITMAP *bitmap_keys1 = al_load_bitmap( "img_menu/buttons.png" );
    if( !bitmap_keys1 ) { al_show_native_message_box( NULL, "Warning", "ERROR", "Could not load some graphics", NULL, 0 ); return -1; }
    ALLEGRO_BITMAP *bitmap_keys2 = al_load_bitmap( "img_menu/buttons_hero.png" );
    if( !bitmap_keys2 ) { al_show_native_message_box( NULL, "Warning", "ERROR", "Could not load some graphics", NULL, 0 ); return -1; }
    ALLEGRO_BITMAP *bitmap_round_1;
    ALLEGRO_BITMAP *bitmap_round_2;
    ALLEGRO_BITMAP *bitmap_round_3;
    //text menu options
    Text *menu1_text1 = new Text( "PLAY", 0, sfx*28, sfy*136 );
    Text *menu1_text2 = new Text( "LEARN", 1, sfx*28, sfy*280 );
    Text *menu1_text3 = new Text( "ABOUT", 2, sfx*28, sfy*430 );
    Text *menu1_text4 = new Text( "QUIT", 3, sfx*28, sfy*590 );
    Text *menu2_text1 = new Text( "STORY", 0, sfx*28, sfy*136 );
    Text *menu2_text2 = new Text( "QUICK", 1, sfx*28, sfy*280 );
    Text *menu2_text3 = new Text( "TRAIN", 2, sfx*28, sfy*430 );
    Text *menu2_text4 = new Text( "BACK", 3, sfx*28, sfy*590 );
    //other text objects
    Text_Header *title_location = new Text_Header( "SELECT LOCATION", sfx*460, sfy*50, 80, 1 );
    Text_Header *title_opponent = new Text_Header( "SELECT OPPONENT", sfx*460, sfy*50, 72, 1 );
    Text_Header *rp_opponent = new Text_Header( "Real player", sfx*300, sfy*260, 50, 0 );
    Text_Header *ai_opponent = new Text_Header( "AI player", sfx*1050, sfy*260, 50, 0 );
    Text_Header *p1_controller = new Text_Header( "Player 1 controller:", sfx*160.0, sfy*460.0, 60, 0 );
    Text_Header *p2_controller = new Text_Header( "Player 2 controller:", sfx*160.0, sfy*620.0, 60, 0 );
    Text_Header *kb1_controller = new Text_Header( "Keyboard", sfx*800.0, sfy*460.0, 60, 0 );
    Text_Header *kb2_controller = new Text_Header( "Keyboard", sfx*800.0, sfy*620.0, 60, 0 );
    Text_Header *c11_controller;
    Text_Header *c21_controller;
    Text_Header *c12_controller;
    Text_Header *c22_controller;
    if( j_num == 1 || j_num == 2 )
    {
        c11_controller = new Text_Header( j1name_s, sfx*800.0, sfy*460.0, 60, 0 );
        c12_controller = new Text_Header( j1name_s, sfx*800.0, sfy*620.0, 60, 0 );
        std::cout << "here1\n";
        if( j_num == 2 )
        {
            c21_controller = new Text_Header( j2name_s, sfx*800.0, sfy*460.0, 60, 0 );
            c22_controller = new Text_Header( j2name_s, sfx*800.0, sfy*620.0, 60, 0 );
            std::cout << "here2\n";
            std::cout << j1name_s << "\n";
            std::cout << j2name_s << "\n\n";
        }
    }
    Text_Header *title_hero;
    Text_Header *p1_hero_txt;
    Text_Header *p2_hero_txt;
    Text_Header *ai_hero_txt;
    //locations
    Location_Miniature *location1;
    Location_Miniature *location2;
    Location_Miniature *loc_placeholder1;
    Location_Miniature *loc_placeholder2;
    Location_Miniature *loc_placeholder3;
    Location_Miniature *loc_placeholder4;
    Location_Background *the_location;
    //portraits
    Hero_Portrait *panda_right;
    Hero_Portrait *panda_left;
    Hero_Portrait *hero_placeholder01;
    Hero_Portrait *hero_placeholder02;
    Hero_Portrait *hero_placeholder03;
    Hero_Portrait *hero_placeholder04;
    Hero_Portrait *hero_placeholder05;
    Hero_Portrait *hero_placeholder06;
    Hero_Portrait *hero_placeholder07;
    Hero_Portrait *hero_placeholder08;
    Hero_Portrait *hero_placeholder09;
    Hero_Portrait *hero_placeholder10;
    Hero_Portrait *hero_placeholder11;
    Hero_Portrait *hero_placeholder12;
    Hero_Portrait *hero_placeholder13;
    Hero_Portrait *hero_placeholder14;
    //flags
    bool select_hero_still_loading = true;
    bool free_hero_loading_memory = false;
    bool select_location_still_loading = true;
    bool free_location_loading_memory = false;
    bool fight_still_loading = true;
    bool free_fight_loading_memory = false;
    //other
    GAME_STATE STATE = Menu1;
    int marked_menu1 = 0;
    int marked_menu2 = 0;
    int select_controller_phase = 1;
    OPPONENT opponent_choice = Both;
    DEVICES p1_device = NoneD;
    DEVICES p2_device = NoneD;
    int select_hero_phase = 1;
    int marked_hero_left_half = 0;
    int marked_hero_right_half = 0;
    int select_location_phase = 1;
    int marked_location = 0;
    //bool marking_hero_left_allowed = true;
    //bool marking_hero_right_allowed = true;
    int timer_count1;
    int timer_count2;
    HEROES p1_hero = NoneH;
    HEROES p2_hero = NoneH;
    PLACES f_location = NoneP;
    Hero *hero1;
    Hero *hero2;

//MAIN GAME LOOP
    al_start_timer( timer_1_gameloop );
    while( game_is_running )
    {
        al_wait_for_event( event_queue, &event );

    //STATE: MENU1
        if( STATE == Menu1 )
        {
        //EVENTS & LOGIC
            if( event.type == ALLEGRO_EVENT_KEY_DOWN )
            {
                switch( event.keyboard.keycode )
                {
                    case ALLEGRO_KEY_ESCAPE: { game_is_running = false; break; }
                    case ALLEGRO_KEY_DOWN: { Various_Procedures::menu_go_down( marked_menu1, menu1_text1, menu1_text2, menu1_text3, menu1_text4 ); break; }
                    case ALLEGRO_KEY_UP: { Various_Procedures::menu_go_up( marked_menu1, menu1_text1, menu1_text2, menu1_text3, menu1_text4 ); break; }
                    case ALLEGRO_KEY_ENTER:
                    {
                        if( marked_menu1 == 0 ) STATE = Menu2;
                        else if( marked_menu1 == 3 ) game_is_running = false;
                        break;
                    }
                }
            }

            if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
            {
                if( ( event.joystick.stick == 2 || event.joystick.stick == 0 ) && event.joystick.axis == 1 )
                {
                    if( event.joystick.pos == 1.0 ) Various_Procedures::menu_go_down( marked_menu1, menu1_text1, menu1_text2, menu1_text3, menu1_text4 );
                    else if( event.joystick.pos == -1.0 ) Various_Procedures::menu_go_up( marked_menu1, menu1_text1, menu1_text2, menu1_text3, menu1_text4 );
                }
            }

            if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
            {
                if( event.joystick.button == 3 )
                {
                    if( marked_menu1 == 0 ) STATE = Menu2;
                    else if( marked_menu1 == 3 ) game_is_running = false;
                }
            }

        //DRAWING
            al_draw_scaled_bitmap( bitmap_menu1, 0, 0, 1600, 900, 0, 0, Display_Monitor_Issues::get_desktop_width(), Display_Monitor_Issues::get_desktop_height(), 0 );
            menu1_text1->write();
            menu1_text2->write();
            menu1_text3->write();
            menu1_text4->write();
            al_flip_display();
        }

    //STATE: MENU2
        else if( STATE == Menu2 )
        {
        //EVENTS & LOGIC
            if( event.type == ALLEGRO_EVENT_KEY_DOWN )
            {
                switch( event.keyboard.keycode )
                {
                    case ALLEGRO_KEY_ESCAPE: { STATE = Menu1; break; }
                    case ALLEGRO_KEY_DOWN: { Various_Procedures::menu_go_down( marked_menu2, menu2_text1, menu2_text2, menu2_text3, menu2_text4 ); break; }
                    case ALLEGRO_KEY_UP: { Various_Procedures::menu_go_up( marked_menu2, menu2_text1, menu2_text2, menu2_text3, menu2_text4 ); break; }
                    case ALLEGRO_KEY_ENTER:
                    {
                        if( marked_menu2 == 1 )
                        {
                            STATE = Select_Opponent;
                            if( j_num == 0 ) opponent_choice = Computer;
                            else opponent_choice = Both;
                            p1_device = NoneD;
                            p2_device = NoneD;
                            select_controller_phase = 1;
                        }
                        else if( marked_menu2 == 3 ) STATE = Menu1;
                        break;
                    }
                }
            }

            if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
            {
                if( ( event.joystick.stick == 2 || event.joystick.stick == 0 ) && event.joystick.axis == 1 )
                {
                    if( event.joystick.pos == 1.0 ) Various_Procedures::menu_go_down( marked_menu2, menu2_text1, menu2_text2, menu2_text3, menu2_text4 );
                    else if( event.joystick.pos == -1.0 ) Various_Procedures::menu_go_up( marked_menu2, menu2_text1, menu2_text2, menu2_text3, menu2_text4 );
                }
            }

            if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
            {
                if( event.joystick.button == 3 )
                {
                    if( marked_menu2 == 1 )
                    {
                        STATE = Select_Opponent;
                        if( j_num == 0 ) opponent_choice = Computer;
                        else opponent_choice = Both;
                        p1_device = NoneD;
                        p2_device = NoneD;
                        select_controller_phase = 1;
                    }
                    else if( marked_menu2 == 3 ) STATE = Menu1;
                }
                else if( event.joystick.button == 1 ) STATE = Menu1;
            }

        //DRAWING
            al_draw_scaled_bitmap( bitmap_menu1, 0, 0, 1600, 900, 0, 0, Display_Monitor_Issues::get_desktop_width(), Display_Monitor_Issues::get_desktop_height(), 0 );
            menu2_text1->write();
            menu2_text2->write();
            menu2_text3->write();
            menu2_text4->write();
            al_flip_display();
        }

    //STATE: SELECT OPPONENT AND CONTROLLER
        else if( STATE == Select_Opponent )
        {
        //PHASE 1
            if( select_controller_phase == 1 )
            { //std::cout << "phase 1\n";
            //EVENTS & LOGIC
                if( event.type == ALLEGRO_EVENT_KEY_DOWN )
                {
                    switch( event.keyboard.keycode )
                    {
                        case ALLEGRO_KEY_ESCAPE: { STATE = Menu2; break; }
                        case ALLEGRO_KEY_LEFT: { if( j_num > 0 ) opponent_choice = Real; break; }
                        case ALLEGRO_KEY_RIGHT: { opponent_choice = Computer; break; }
                        case ALLEGRO_KEY_ENTER: { if( opponent_choice != Both ) select_controller_phase = 2; break; }
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
                {
                    if( ( event.joystick.stick == 2 || event.joystick.stick == 0 ) && event.joystick.axis == 0 )
                    {
                        if( event.joystick.pos == -1.0 && j_num > 0 ) opponent_choice = Real;
                        else if( event.joystick.pos == 1.0 ) opponent_choice = Computer;
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
                {
                    if( event.joystick.button == 3 ) { if( opponent_choice != Both ) select_controller_phase = 2; }
                    else if( event.joystick.button == 1 ) STATE = Menu2;
                }
            }

        //PHASE 2
            else if( select_controller_phase == 2 )
            { //std::cout << "phase 2\n";

            //EVENTS & LOGIC
                if( event.type == ALLEGRO_EVENT_KEY_DOWN )
                {
                    if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
                    {
                        select_controller_phase = 1;
                        opponent_choice = Both;
                        p1_device = NoneD;
                    }
                    else if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_LEFT )
                    {
                        p1_device = Keyboard;
                    }
                    else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER && p1_device == Keyboard )
                    {
                        if( opponent_choice == Real ) select_controller_phase = 3;
                        else select_controller_phase = 4;
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
                {
                    if( event.joystick.button == 1 )
                    {
                        select_controller_phase = 1;
                        opponent_choice = Both;
                        p1_device = NoneD;
                    }
                    else if( event.joystick.button == 3 && ( p1_device == Gamepad1 || p1_device == Gamepad2 ) )
                    {
                        if( opponent_choice == Real ) select_controller_phase = 3;
                        else select_controller_phase = 4;
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
                {
                    if( j_num == 1 || j_num == 2 )
                    {
                        for( short i = 0; i < al_get_joystick_num_sticks( joy1 ); i++ )
                        {
                            al_get_joystick_state( joy1, &joystate1 );
                            if( joystate1.stick[ i ].axis[ 0 ] ) p1_device = Gamepad1;
                        }
                    }
                    if( j_num == 2 )
                    {
                        for( short i = 0; i < al_get_joystick_num_sticks( joy2 ); i++ )
                        {
                            al_get_joystick_state( joy2, &joystate2 );
                            if( joystate2.stick[ i ].axis[ 0 ] == -1.0 || joystate2.stick[ i ].axis[ 0 ] == 1.0 ) p1_device = Gamepad2;
                        }
                    }
                }
            }

        //PHASE 3
            if( select_controller_phase == 3 )
            { //std::cout << "phase 3\n";
            //EVENTS & LOGIC
                if( event.type == ALLEGRO_EVENT_KEY_DOWN )
                {
                    if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
                    {
                        select_controller_phase = 2;
                        p2_device = NoneD;
                    }
                    else if( event.keyboard.keycode == ALLEGRO_KEY_RIGHT || event.keyboard.keycode == ALLEGRO_KEY_LEFT )
                    {
                        if( p1_device != Keyboard ) p2_device = Keyboard;
                    }
                    else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER && p2_device == Keyboard ) select_controller_phase = 4;
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
                {
                    if( event.joystick.button == 1 )
                    {
                        select_controller_phase = 2;
                        p2_device = NoneD;
                    }
                    else if( event.joystick.button == 3 && p2_device != NoneD ) select_controller_phase = 4;
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
                {
                    if( j_num == 1 || j_num == 2 )
                    {
                        for( short i = 0; i < al_get_joystick_num_sticks( joy1 ); i++ )
                        {
                            al_get_joystick_state( joy1, &joystate1 );
                            if( joystate1.stick[ i ].axis[ 0 ] ) { if( p1_device != Gamepad1 ) p2_device = Gamepad1; }
                        }
                    }
                    if( j_num == 2 )
                    {
                        for( short i = 0; i < al_get_joystick_num_sticks( joy2 ); i++ )
                        {
                            al_get_joystick_state( joy2, &joystate2 );
                            if( joystate2.stick[ i ].axis[ 0 ] ) { if( p1_device != Gamepad2 ) p2_device = Gamepad2; }
                        }
                    }
                }
            }

        //PHASE 4
            if( select_controller_phase == 4 )
            { //std::cout << "phase 4\n";
            //EVENTS & LOGIC
                if( event.type == ALLEGRO_EVENT_KEY_DOWN )
                {
                    if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) select_controller_phase = 1;
                    else { STATE = Select_Hero; select_hero_phase = 1; marked_hero_left_half = 0; marked_hero_right_half = 0; }
                }
                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
                {
                    if( event.joystick.button == 1 ) select_controller_phase = 1;
                    else { STATE = Select_Hero; select_hero_phase = 1; marked_hero_left_half = 0; marked_hero_right_half = 0; }
                }
            }

        //DRAWING
            al_clear_to_color( al_map_rgb( 196, 196, 196 ) );
            title_opponent->write();
            if( opponent_choice == Both || opponent_choice == Real )
            {
                rp_opponent->write();
                al_draw_filled_triangle( sfx*740.0, sfy*280.0, sfx*780.0, sfy*240.0, sfx*780.0, sfy*320.0, al_map_rgb( 0, 0, 0 ) );
            }
            if( opponent_choice == Both || opponent_choice == Computer )
            {
                ai_opponent->write();
                al_draw_filled_triangle( sfx*820.0, sfy*320.0, sfx*820.0, sfy*240.0, sfx*860.0, sfy*280.0, al_map_rgb( 0, 0, 0 ) );
            }
            if( select_controller_phase == 2 || select_controller_phase == 3 || select_controller_phase == 4 )
            {
                p1_controller->write();
                if( p1_device == Keyboard ) kb1_controller->write();
                else if( p1_device == Gamepad1 ) c11_controller->write();
                else if( p1_device == Gamepad2 ) c21_controller->write();
            }
            if( select_controller_phase == 3 || select_controller_phase == 4 )
            {
                if( opponent_choice == Real ) p2_controller->write();
                if( p2_device == Keyboard ) kb2_controller->write();
                else if( p2_device == Gamepad1 ) c12_controller->write();
                else if( p2_device == Gamepad2 ) c22_controller->write();
            }
            al_draw_scaled_bitmap( bitmap_keys1, 0, 0, 1600, 70, 0, sfy*830, sfx*1600, sfy*70, 0 );
            al_flip_display();
        }

    //STATE: SELECT HERO
        else if( STATE == Select_Hero )
        {
        //LOADING
            if( select_hero_still_loading )
            {
                al_draw_scaled_bitmap( bitmap_loading1, 0, 0, 1600, 900, 0, 0, Display_Monitor_Issues::get_desktop_width(), Display_Monitor_Issues::get_desktop_height(), 0 );
                al_flip_display();
                title_hero = new Text_Header( "SELECT HERO", sfx*520.0, sfy*50.0, 80, 1 );
                p1_hero_txt = new Text_Header( "PLAYER 1:", sfx*70.0, sfy*200.0, 50, 0 );
                p2_hero_txt = new Text_Header( "PLAYER 2:", sfx*870.0, sfy*200.0, 50, 0 );
                ai_hero_txt = new Text_Header( "AI:", sfx*870.0, sfy*200.0, 50, 0 );
                panda_right = new Hero_Portrait( Panda, Right );
                if( panda_right->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                panda_left = new Hero_Portrait( Panda, Left );
                if( panda_left->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder01 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder01->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder02 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder02->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder03 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder03->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder04 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder04->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder05 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder05->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder06 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder06->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder07 = new Hero_Portrait( HolderH, Right );
                if( hero_placeholder07->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder08 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder08->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder09 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder09->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder10 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder10->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder11 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder11->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder12 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder12->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder13 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder13->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero_placeholder14 = new Hero_Portrait( HolderH, Left );
                if( hero_placeholder14->choose_bitmap_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                select_hero_still_loading = false;
                free_hero_loading_memory = false;
                panda_right->allow_red_border( true );
                panda_right->allow_write_name( true );
            }

        //PHASE 1
            if( select_hero_phase == 1 )
            {
            //EVENTS & LOGIC
                if( event.type == ALLEGRO_EVENT_KEY_DOWN && p1_device == Keyboard )
                {
                    switch( event.keyboard.keycode )
                    {
                        case ALLEGRO_KEY_ESCAPE: { free_hero_loading_memory = true; STATE = Menu2; break; }
                        case ALLEGRO_KEY_RIGHT: { Various_Procedures::hero_go_right( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 ); break; }
                        case ALLEGRO_KEY_LEFT: { Various_Procedures::hero_go_left( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 ); break; }
                        case ALLEGRO_KEY_DOWN: { Various_Procedures::hero_go_down( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 ); break; }
                        case ALLEGRO_KEY_UP: { Various_Procedures::hero_go_up( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 ); break; }
                        case ALLEGRO_KEY_ENTER:
                        {
                            Various_Procedures::hero_enter( Left, p1_hero, marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 );
                            select_hero_phase = 2;
                            marked_hero_right_half = 0;
                            hero_placeholder08->allow_red_border( true );
                            hero_placeholder08->allow_write_name( true );
                            timer_count1 = al_get_timer_count( timer_1_gameloop );
                            break;
                        }
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS && p1_device != Keyboard )
                {
                    if( p1_device == Gamepad1 ) al_get_joystick_state( joy1, &joystate1 );
                    else if( p1_device == Gamepad2 ) al_get_joystick_state( joy2, &joystate1 );

                    if( ( joystate1.stick[ 0 ].axis[ 0 ] || joystate1.stick[ 2 ].axis[ 0 ] ) && event.joystick.pos == 1.0 )
                        Various_Procedures::hero_go_right( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 );
                    else if( ( joystate1.stick[ 0 ].axis[ 0 ] || joystate1.stick[ 2 ].axis[ 0 ] ) && event.joystick.pos == -1.0 )
                        Various_Procedures::hero_go_left( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 );
                    else if( ( joystate1.stick[ 0 ].axis[ 1 ] || joystate1.stick[ 2 ].axis[ 1 ] ) && event.joystick.pos == 1.0 )
                        Various_Procedures::hero_go_down( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 );
                    else if( ( joystate1.stick[ 0 ].axis[ 1 ] || joystate1.stick[ 2 ].axis[ 1 ] ) && event.joystick.pos == -1.0 )
                        Various_Procedures::hero_go_up( marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 );
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
                {
                    if( p1_device == Gamepad1 ) al_get_joystick_state( joy1, &joystate1 );
                    else if( p1_device == Gamepad2 ) al_get_joystick_state( joy2, &joystate1 );

                    if( joystate1.button[ 1 ] )
                    {
                        free_hero_loading_memory = true;
                        STATE = Menu2;
                    }
                    else if( joystate1.button[ 3 ] )
                    {
                        Various_Procedures::hero_enter( Left, p1_hero, marked_hero_left_half, panda_right, hero_placeholder01, hero_placeholder02, hero_placeholder03, hero_placeholder04, hero_placeholder05, hero_placeholder06, hero_placeholder07 );
                        select_hero_phase = 2;
                        marked_hero_right_half = 0;
                        hero_placeholder08->allow_red_border( true );
                        hero_placeholder08->allow_write_name( true );
                        timer_count1 = al_get_timer_count( timer_1_gameloop );
                    }
                }
            }

        //PHASE 2
            if( select_hero_phase == 2 )
            {
            //EVENTS & LOGIC
                timer_count2 = al_get_timer_count( timer_1_gameloop );
                if( event.type == ALLEGRO_EVENT_KEY_DOWN && timer_count1 != timer_count2 && ( ( opponent_choice == Computer && p1_device == Keyboard ) || ( opponent_choice == Real && p2_device == Keyboard ) ) )
                {
                    switch( event.keyboard.keycode )
                    {
                        case ALLEGRO_KEY_ESCAPE: { free_hero_loading_memory = true; STATE = Menu2; break; }
                        case ALLEGRO_KEY_RIGHT: { Various_Procedures::hero_go_right( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 ); break; }
                        case ALLEGRO_KEY_LEFT: { Various_Procedures::hero_go_left( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 ); break; }
                        case ALLEGRO_KEY_DOWN: { Various_Procedures::hero_go_down( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 ); break; }
                        case ALLEGRO_KEY_UP: { Various_Procedures::hero_go_up( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 ); break; }
                        case ALLEGRO_KEY_ENTER:
                        {
                            Various_Procedures::hero_enter( Right, p2_hero, marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 );
                            select_hero_phase = 3;
                            marked_location = 0;
                            timer_count1 = al_get_timer_count( timer_1_gameloop );
                            break;
                        }
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS && timer_count1 != timer_count2 && ( ( opponent_choice == Computer && p1_device != Keyboard ) || ( opponent_choice == Real && p2_device != Keyboard ) ) ) //&& p1_device != Keyboard || ( p1_device != Keyboard && p2_device == NoneD )  )
                {
                    if( p2_device == Gamepad1 || ( p1_device == Gamepad1 && p2_device == NoneD ) )
                        al_get_joystick_state( joy1, &joystate2 );
                    else if( p2_device == Gamepad2 || ( p1_device == Gamepad2 && p2_device == NoneD ) )
                        al_get_joystick_state( joy2, &joystate2 );

                    if( ( joystate2.stick[ 0 ].axis[ 0 ] || joystate2.stick[ 2 ].axis[ 0 ] ) && event.joystick.pos == 1.0 )
                        Various_Procedures::hero_go_right( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 );
                    else if( ( joystate2.stick[ 0 ].axis[ 0 ] || joystate2.stick[ 2 ].axis[ 0 ] ) && event.joystick.pos == -1.0 )
                        Various_Procedures::hero_go_left( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 );
                    else if( ( joystate2.stick[ 0 ].axis[ 1 ] || joystate2.stick[ 2 ].axis[ 1 ] ) && event.joystick.pos == 1.0 )
                        Various_Procedures::hero_go_down( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 );
                    else if( ( joystate2.stick[ 0 ].axis[ 1 ] || joystate2.stick[ 2 ].axis[ 1 ] ) && event.joystick.pos == -1.0 )
                        Various_Procedures::hero_go_up( marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 );
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && timer_count1 != timer_count2 )
                {
                    if( p2_device == Gamepad1 || ( p1_device == Gamepad1 && p2_device == NoneD ) )
                        al_get_joystick_state( joy1, &joystate2 );
                    else if( p2_device == Gamepad2 || ( p1_device == Gamepad2 && p2_device == NoneD ) )
                        al_get_joystick_state( joy2, &joystate2 );

                    if( joystate2.button[ 1 ] )
                    {
                        free_hero_loading_memory = true;
                        STATE = Menu2;
                    }
                    else if( joystate2.button[ 3 ] )
                    {
                        Various_Procedures::hero_enter( Right, p2_hero, marked_hero_right_half, hero_placeholder08, hero_placeholder09, hero_placeholder10, panda_left, hero_placeholder11, hero_placeholder12, hero_placeholder13, hero_placeholder14 );
                        select_hero_phase = 3;
                        marked_location = 0;
                        timer_count1 = al_get_timer_count( timer_1_gameloop );
                    }
                }
            }

        //PHASE 3
            if( select_hero_phase == 3 )
            {
            //EVENTS & LOGIC
                timer_count2 = al_get_timer_count( timer_1_gameloop );
                if( event.type == ALLEGRO_EVENT_KEY_DOWN && timer_count1 != timer_count2 )
                {
                    if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE ) { free_hero_loading_memory = true; STATE = Menu2; }
                    else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ) { free_hero_loading_memory = true; STATE = Select_Location; }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && timer_count1 != timer_count2 )
                {
                    if( event.joystick.button == 1 ) { free_hero_loading_memory = true; STATE = Menu2; }
                    else if( event.joystick.button == 3 ) { free_hero_loading_memory = true; STATE = Select_Location; }
                }
            }

        //DRAWING
            al_clear_to_color( al_map_rgb( 196, 196, 196 ) );
            title_hero->write();
            p1_hero_txt->write();
            p2_hero_txt->write();
            al_draw_line( sfx*800.0, sfy*300.0, sfx*800.0, sfy*640.0, al_map_rgb( 0, 0, 0 ), 1 );
            panda_right->draw( sfx*50.0, sfy*300.0 );
            hero_placeholder01->draw( sfx*240.0, sfy*300.0 );
            hero_placeholder02->draw( sfx*430.0, sfy*300.0 );
            hero_placeholder03->draw( sfx*620.0, sfy*300.0 );
            hero_placeholder04->draw( sfx*50.0, sfy*500.0 );
            hero_placeholder05->draw( sfx*240.0, sfy*500.0 );
            hero_placeholder06->draw( sfx*430.0, sfy*500.0 );
            hero_placeholder07->draw( sfx*620.0, sfy*500.0 );
            hero_placeholder08->draw( sfx*836.0, sfy*300.0 );
            hero_placeholder09->draw( sfx*1026.0, sfy*300.0 );
            hero_placeholder10->draw( sfx*1216.0, sfy*300.0 );
            panda_left->draw( sfx*1406.0, sfy*300.0 );
            hero_placeholder11->draw( sfx*836.0, sfy*500.0 );
            hero_placeholder12->draw( sfx*1026.0, sfy*500.0 );
            hero_placeholder13->draw( sfx*1216.0, sfy*500.0 );
            hero_placeholder14->draw( sfx*1406.0, sfy*500.0 );

            panda_right->draw_red_border();
            panda_left->draw_red_border();
            hero_placeholder01->draw_red_border();
            hero_placeholder02->draw_red_border();
            hero_placeholder03->draw_red_border();
            hero_placeholder04->draw_red_border();
            hero_placeholder05->draw_red_border();
            hero_placeholder06->draw_red_border();
            hero_placeholder07->draw_red_border();
            hero_placeholder08->draw_red_border();
            hero_placeholder09->draw_red_border();
            hero_placeholder10->draw_red_border();
            hero_placeholder11->draw_red_border();
            hero_placeholder12->draw_red_border();
            hero_placeholder13->draw_red_border();
            hero_placeholder14->draw_red_border();
            panda_right->draw_blue_border();
            panda_left->draw_blue_border();
            hero_placeholder01->draw_blue_border();
            hero_placeholder02->draw_blue_border();
            hero_placeholder03->draw_blue_border();
            hero_placeholder04->draw_blue_border();
            hero_placeholder05->draw_blue_border();
            hero_placeholder06->draw_blue_border();
            hero_placeholder07->draw_blue_border();
            hero_placeholder08->draw_blue_border();
            hero_placeholder09->draw_blue_border();
            hero_placeholder10->draw_blue_border();
            hero_placeholder11->draw_blue_border();
            hero_placeholder12->draw_blue_border();
            hero_placeholder13->draw_blue_border();
            hero_placeholder14->draw_blue_border();
            panda_right->write_name();
            panda_left->write_name();
            hero_placeholder01->write_name();
            hero_placeholder02->write_name();
            hero_placeholder03->write_name();
            hero_placeholder04->write_name();
            hero_placeholder05->write_name();
            hero_placeholder06->write_name();
            hero_placeholder07->write_name();
            hero_placeholder08->write_name();
            hero_placeholder09->write_name();
            hero_placeholder10->write_name();
            hero_placeholder11->write_name();
            hero_placeholder12->write_name();
            hero_placeholder13->write_name();
            hero_placeholder14->write_name();
            al_draw_scaled_bitmap( bitmap_keys2, 0, 0, 1600, 70, 0, sfy*830, sfx*1600, sfy*70, 0 );
            al_flip_display();

        //FREEING MEMORY
            if( free_hero_loading_memory )
            {
                delete title_hero;
                delete p1_hero_txt;
                delete p2_hero_txt;
                delete ai_hero_txt;
                delete panda_left;
                delete panda_right;
                delete hero_placeholder01;
                delete hero_placeholder02;
                delete hero_placeholder03;
                delete hero_placeholder04;
                delete hero_placeholder05;
                delete hero_placeholder06;
                delete hero_placeholder07;
                delete hero_placeholder08;
                delete hero_placeholder09;
                delete hero_placeholder10;
                delete hero_placeholder11;
                delete hero_placeholder12;
                delete hero_placeholder13;
                delete hero_placeholder14;
                select_hero_still_loading = true;
            }
        }

    //STATE: SELECT_LOCATION
        else if( STATE == Select_Location )
        {
        //LOADING
            if( select_location_still_loading )
            {
                al_draw_scaled_bitmap( bitmap_loading1, 0, 0, 1600, 900, 0, 0, Display_Monitor_Issues::get_desktop_width(), Display_Monitor_Issues::get_desktop_height(), 0 );
                al_flip_display();
                location1 = new Location_Miniature( Planets );
                if( location1->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                location2 = new Location_Miniature( Tree );
                if( location2->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                loc_placeholder1 = new Location_Miniature( HolderP );
                if( loc_placeholder1->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                loc_placeholder2 = new Location_Miniature( HolderP );
                if( loc_placeholder2->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                loc_placeholder3 = new Location_Miniature( HolderP );
                if( loc_placeholder3->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                loc_placeholder4 = new Location_Miniature( HolderP );
                if( loc_placeholder4->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                select_location_still_loading = false;
                free_location_loading_memory = false;
                location1->allow_red_border( true );
            }

        //PHASE 1
            if( select_location_phase == 1 )
            {
            //EVENTS & LOGIC
                if( event.type == ALLEGRO_EVENT_KEY_DOWN )
                {
                    switch( event.keyboard.keycode )
                    {
                        case ALLEGRO_KEY_ESCAPE:
                        {
                            free_location_loading_memory = true;
                            p1_hero = NoneH;
                            p2_hero = NoneH;
                            STATE = Menu2;
                            break;
                        }
                        case ALLEGRO_KEY_RIGHT: { Various_Procedures::loc_go_right( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 ); break; }
                        case ALLEGRO_KEY_LEFT: { Various_Procedures::loc_go_left( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 ); break; }
                        case ALLEGRO_KEY_DOWN: { Various_Procedures::loc_go_down( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 ); break; }
                        case ALLEGRO_KEY_UP: { Various_Procedures::loc_go_up( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 ); break; }
                        case ALLEGRO_KEY_ENTER:
                        {
                            Various_Procedures::loc_enter( f_location, marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 );
                            select_location_phase = 2;
                            timer_count1 = al_get_timer_count( timer_1_gameloop );
                            break;
                        }
                    }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
                {
                    al_get_joystick_state( joy1, &joystate1 );
                    if( j_num == 2 ) al_get_joystick_state( joy2, &joystate2 );

                    if( ( ( joystate1.stick[ 0 ].axis[ 0 ] || joystate1.stick[ 2 ].axis[ 0 ] ) || ( joystate2.stick[ 0 ].axis[ 0 ] || joystate2.stick[ 2 ].axis[ 0 ] ) ) && event.joystick.pos == 1.0 )
                        Various_Procedures::loc_go_right( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 );
                    else if( ( ( joystate1.stick[ 0 ].axis[ 0 ] || joystate1.stick[ 2 ].axis[ 0 ] ) || ( joystate2.stick[ 0 ].axis[ 0 ] || joystate2.stick[ 2 ].axis[ 0 ] ) ) && event.joystick.pos == -1.0 )
                        Various_Procedures::loc_go_left( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 );
                    else if( ( ( joystate1.stick[ 0 ].axis[ 1 ] || joystate1.stick[ 2 ].axis[ 1 ] ) || ( joystate2.stick[ 0 ].axis[ 1 ] || joystate2.stick[ 2 ].axis[ 1 ] ) ) && event.joystick.pos == 1.0 )
                        Various_Procedures::loc_go_down( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 );
                    else if( ( ( joystate1.stick[ 0 ].axis[ 1 ] || joystate1.stick[ 2 ].axis[ 1 ] ) || ( joystate2.stick[ 0 ].axis[ 1 ] || joystate2.stick[ 2 ].axis[ 1 ] ) ) && event.joystick.pos == -1.0 )
                        Various_Procedures::loc_go_up( marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 );
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
                {
                    al_get_joystick_state( joy1, &joystate1 );
                    if( j_num == 2 ) al_get_joystick_state( joy2, &joystate2 );

                    if( joystate1.button[ 1 ] || joystate2.button[ 1 ] )
                    {
                        free_location_loading_memory = true;
                        p1_hero = NoneH;
                        p2_hero = NoneH;
                        STATE = Menu2;
                    }
                    else if( joystate1.button[ 3 ] || joystate2.button[ 3 ] )
                    {
                        Various_Procedures::loc_enter( f_location, marked_location, location1, location2, loc_placeholder1, loc_placeholder2, loc_placeholder3, loc_placeholder4 );
                        select_location_phase = 2;
                        timer_count1 = al_get_timer_count( timer_1_gameloop );
                    }
                }
            }

        //PHASE 2
            if( select_location_phase == 2 )
            {
            //EVENTS & LOGIC
                timer_count2 = al_get_timer_count( timer_1_gameloop );
                if( event.type == ALLEGRO_EVENT_KEY_DOWN && timer_count1 != timer_count2 )
                {
                    if( event.keyboard.keycode == ALLEGRO_KEY_ESCAPE )
                    {
                        if( marked_location == 0 ) { location1->allow_red_border( true ); location1->allow_blue_border( false ); }
                        else if( marked_location == 1 ) { location2->allow_red_border( true ); location2->allow_blue_border( false ); }
                        else if( marked_location == 2 ) { loc_placeholder1->allow_red_border( true ); loc_placeholder1->allow_blue_border( false ); }
                        else if( marked_location == 3 ) { loc_placeholder2->allow_red_border( true ); loc_placeholder2->allow_blue_border( false ); }
                        else if( marked_location == 4 ) { loc_placeholder3->allow_red_border( true ); loc_placeholder3->allow_blue_border( false ); }
                        else if( marked_location == 5 ) { loc_placeholder4->allow_red_border( true ); loc_placeholder4->allow_blue_border( false ); }
                        select_location_phase = 1;
                    }
                    else if( event.keyboard.keycode == ALLEGRO_KEY_ENTER ) { free_location_loading_memory = true; STATE = Fight; /*std::cout << "w enterze wszystko ok\n"*/; }
                }

                if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN && timer_count1 != timer_count2 )
                {
                    if( event.joystick.button == 1 )
                    {
                        if( marked_location == 0 ) { location1->allow_red_border( true ); location1->allow_blue_border( false ); }
                        else if( marked_location == 1 ) { location2->allow_red_border( true ); location2->allow_blue_border( false ); }
                        else if( marked_location == 2 ) { loc_placeholder1->allow_red_border( true ); loc_placeholder1->allow_blue_border( false ); }
                        else if( marked_location == 3 ) { loc_placeholder2->allow_red_border( true ); loc_placeholder2->allow_blue_border( false ); }
                        else if( marked_location == 4 ) { loc_placeholder3->allow_red_border( true ); loc_placeholder3->allow_blue_border( false ); }
                        else if( marked_location == 5 ) { loc_placeholder4->allow_red_border( true ); loc_placeholder4->allow_blue_border( false ); }
                        select_location_phase = 1;
                    }
                    else if( event.joystick.button == 3 ) { free_location_loading_memory = true; STATE = Fight; }
                }
            }

        //DRAWING
            al_clear_to_color( al_map_rgb( 196, 196, 196 ) );
            title_location->write();
            location1->draw_location( sfx*100.0, sfx*200.0 );
            location2->draw_location( sfx*600.0, sfx*200.0 );
            loc_placeholder1->draw_location( sfx*1100.0, sfx*200.0 );
            loc_placeholder2->draw_location( sfx*100.0, sfx*500.0 );
            loc_placeholder3->draw_location( sfx*600.0, sfx*500.0 );
            loc_placeholder4->draw_location( sfx*1100.0, sfx*500.0 );
            location1->draw_red_border();
            location2->draw_red_border();
            loc_placeholder1->draw_red_border();
            loc_placeholder2->draw_red_border();
            loc_placeholder3->draw_red_border();
            loc_placeholder4->draw_red_border();
            location1->draw_blue_border();
            location2->draw_blue_border();
            loc_placeholder1->draw_blue_border();
            loc_placeholder2->draw_blue_border();
            loc_placeholder3->draw_blue_border();
            loc_placeholder4->draw_blue_border();
            al_flip_display();

        //FREEING MEMORY
            if( free_location_loading_memory )
            {
                select_location_phase = 1;
                panda_right->allow_red_border( true );
                panda_right->allow_blue_border( false );
                panda_left->allow_blue_border( false );
                hero_placeholder01->allow_blue_border( false );
                hero_placeholder02->allow_blue_border( false );
                hero_placeholder03->allow_blue_border( false );
                hero_placeholder04->allow_blue_border( false );
                hero_placeholder05->allow_blue_border( false );
                hero_placeholder06->allow_blue_border( false );
                hero_placeholder07->allow_blue_border( false );
                hero_placeholder08->allow_blue_border( false );
                hero_placeholder09->allow_blue_border( false );
                hero_placeholder10->allow_blue_border( false );
                hero_placeholder11->allow_blue_border( false );
                hero_placeholder12->allow_blue_border( false );
                hero_placeholder13->allow_blue_border( false );
                hero_placeholder14->allow_blue_border( false );
                panda_right->allow_write_name( true );
                panda_left->allow_write_name( false );
                hero_placeholder01->allow_write_name( false );
                hero_placeholder02->allow_write_name( false );
                hero_placeholder03->allow_write_name( false );
                hero_placeholder04->allow_write_name( false );
                hero_placeholder05->allow_write_name( false );
                hero_placeholder06->allow_write_name( false );
                hero_placeholder07->allow_write_name( false );
                hero_placeholder08->allow_write_name( false );
                hero_placeholder09->allow_write_name( false );
                hero_placeholder10->allow_write_name( false );
                hero_placeholder11->allow_write_name( false );
                hero_placeholder12->allow_write_name( false );
                hero_placeholder13->allow_write_name( false );
                hero_placeholder14->allow_write_name( false );
                /*location1->allow_red_border( true );
                location1->allow_blue_border( false );
                location2->allow_blue_border( false );
                loc_placeholder1->allow_blue_border( false );
                loc_placeholder2->allow_blue_border( false );
                loc_placeholder3->allow_blue_border( false );
                loc_placeholder4->allow_blue_border( false );
                marked_location == 0;*/
                delete location1;
                delete location2;
                delete loc_placeholder1;
                delete loc_placeholder2;
                delete loc_placeholder3;
                delete loc_placeholder4;
                select_location_still_loading = true;
                //std::cout << "poprawna kasacja pamieci select location\n";
            }
        }

    //STATE: FIGHT
        else if( STATE == Fight )
        {
        //LOADING
            if( fight_still_loading )
            {
                //std::cout << "poczatek\n";
                al_draw_scaled_bitmap( bitmap_loading1, 0, 0, 1600, 900, 0, 0, Display_Monitor_Issues::get_desktop_width(), Display_Monitor_Issues::get_desktop_height(), 0 );
                //std::cout << "mapa tlo\n";
                al_flip_display();
                the_location = new Location_Background( f_location );
                if( the_location->check_location_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                hero1 = new Hero( 1, p1_hero, Right, sfx*100, sfy*390 );
                hero2 = new Hero( 2, p2_hero, Left, sfx*1280, sfy*390 );
                if( hero1->check_hero_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                if( hero2->check_hero_and_load() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                if( hero1->load_bitmap_numbers() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                if( hero2->load_bitmap_numbers() == -1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                //std::cout << "przed mapami ok\n";
                bitmap_round_1 = al_load_bitmap( "img_menu/round1.png" );
                if( !bitmap_round_1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                //std::cout << "pierwsza\n";
                bitmap_round_2 = al_load_bitmap( "img_menu/round2.png" );
                if( !bitmap_round_1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                //std::cout << "druga\n";
                bitmap_round_3 = al_load_bitmap( "img_menu/round3.png" );
                if( !bitmap_round_1 ) { al_show_native_message_box( main_display, "Warning", "ERROR", "Loading issue, you may be missing some resources", NULL, 0 ); return -1; }
                //std::cout << "trzecia\n";
                fight_still_loading = false;
                //std::cout << "czwarta\n";
                free_fight_loading_memory = false;
                //std::cout << "piata\n";
            }

        //EVENTS & LOGIC
            if( hero1->get_health() <= 0 || hero2->get_health() <= 0 )
            {
                f_location = NoneP;
                STATE = Menu2;
                free_fight_loading_memory = true;
            }
            if( event.type == ALLEGRO_EVENT_KEY_DOWN )
            {
                switch( event.keyboard.keycode )
                {
                    case ALLEGRO_KEY_ESCAPE:
                    {
                        f_location = NoneP;
                        STATE = Menu2;
                        free_fight_loading_memory = true;
                        break;
                    }
                    case ALLEGRO_KEY_Z:
                    {
                        if( p1_device == Keyboard && hero1->get_hero_status() == Stand )
                        {
                            hero1->make_keyboard_click_move( 'z' ); //hero1->set_hero_status( Attack ); cntr = 8;
                            if( hero1->get_hero_pos_x() > hero2->get_hero_pos_x() - 180 && hero1->get_hero_pos_x() < hero2->get_hero_pos_x() )
                                hero2->receive_damage( hero1->deal_basic_damage() );
                        }
                        if( p2_device == Keyboard && hero2->get_hero_status() == Stand )
                        {
                            hero2->make_keyboard_click_move( 'z' );
                            if( hero2->get_hero_pos_x() > hero1->get_hero_pos_x() && hero2->get_hero_pos_x() < hero1->get_hero_pos_x() + 220 )
                                hero1->receive_damage( hero2->deal_basic_damage() );
                        }
                        break;
                    }
                    case ALLEGRO_KEY_X:
                    {
                        if( p1_device == Keyboard && hero1->get_hero_status() == Stand ) hero1->make_keyboard_click_move( 'x' );
                        if( p2_device == Keyboard && hero2->get_hero_status() == Stand ) hero2->make_keyboard_click_move( 'x' );
                        break;
                    }
                    case ALLEGRO_KEY_C:
                    {
                        if( p1_device == Keyboard && hero1->get_hero_status() == Stand ) hero1->make_keyboard_click_move( 'c' );
                        if( p2_device == Keyboard && hero2->get_hero_status() == Stand ) hero2->make_keyboard_click_move( 'c' );
                        break;
                    }
                    case ALLEGRO_KEY_V:
                    {
                        if( p1_device == Keyboard && hero1->get_hero_status() == Stand ) hero1->make_keyboard_click_move( 'v' );
                        if( p2_device == Keyboard && hero2->get_hero_status() == Stand ) hero2->make_keyboard_click_move( 'v' );
                        break;
                    }
                    case ALLEGRO_KEY_UP:
                    {
                        if( p1_device == Keyboard && hero1->get_hero_status() == Stand ) hero1->make_keyboard_click_move( 'j' );
                        if( p2_device == Keyboard && hero2->get_hero_status() == Stand ) hero2->make_keyboard_click_move( 'j' );
                        break;
                    }
                }
            }

            if( event.type == ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN )
            {
                if( p1_device == Gamepad1 || p2_device == Gamepad1 ) al_get_joystick_state( joy1, &joystate_fight_g1 );
                if( p1_device == Gamepad2 || p2_device == Gamepad2 ) al_get_joystick_state( joy2, &joystate_fight_g2 );

                if( p1_device == Gamepad1 && hero1->get_hero_status() == Stand && joystate_fight_g1.button[ 1 ] ) hero1->make_keyboard_click_move( 'z' );
                if( p1_device == Gamepad1 && hero1->get_hero_status() == Stand && joystate_fight_g1.button[ 0 ] ) hero1->make_keyboard_click_move( 'x' );
                if( p1_device == Gamepad1 && hero1->get_hero_status() == Stand && joystate_fight_g1.button[ 2 ] ) hero1->make_keyboard_click_move( 'c' );
                if( p1_device == Gamepad1 && hero1->get_hero_status() == Stand && joystate_fight_g1.button[ 3 ] ) hero1->make_keyboard_click_move( 'v' );

                if( p1_device == Gamepad2 && hero1->get_hero_status() == Stand && joystate_fight_g2.button[ 1 ] ) hero1->make_keyboard_click_move( 'z' );
                if( p1_device == Gamepad2 && hero1->get_hero_status() == Stand && joystate_fight_g2.button[ 0 ] ) hero1->make_keyboard_click_move( 'x' );
                if( p1_device == Gamepad2 && hero1->get_hero_status() == Stand && joystate_fight_g2.button[ 2 ] ) hero1->make_keyboard_click_move( 'c' );
                if( p1_device == Gamepad2 && hero1->get_hero_status() == Stand && joystate_fight_g2.button[ 3 ] ) hero1->make_keyboard_click_move( 'v' );

                if( p2_device == Gamepad1 && hero2->get_hero_status() == Stand && joystate_fight_g1.button[ 1 ] ) hero2->make_keyboard_click_move( 'z' );
                if( p2_device == Gamepad1 && hero2->get_hero_status() == Stand && joystate_fight_g1.button[ 0 ] ) hero2->make_keyboard_click_move( 'x' );
                if( p2_device == Gamepad1 && hero2->get_hero_status() == Stand && joystate_fight_g1.button[ 2 ] ) hero2->make_keyboard_click_move( 'c' );
                if( p2_device == Gamepad1 && hero2->get_hero_status() == Stand && joystate_fight_g1.button[ 3 ] ) hero2->make_keyboard_click_move( 'v' );

                if( p2_device == Gamepad2 && hero2->get_hero_status() == Stand && joystate_fight_g2.button[ 1 ] ) hero2->make_keyboard_click_move( 'z' );
                if( p2_device == Gamepad2 && hero2->get_hero_status() == Stand && joystate_fight_g2.button[ 0 ] ) hero2->make_keyboard_click_move( 'x' );
                if( p2_device == Gamepad2 && hero2->get_hero_status() == Stand && joystate_fight_g2.button[ 2 ] ) hero2->make_keyboard_click_move( 'c' );
                if( p2_device == Gamepad2 && hero2->get_hero_status() == Stand && joystate_fight_g2.button[ 3 ] ) hero2->make_keyboard_click_move( 'v' );
            }

            if( event.type == ALLEGRO_EVENT_JOYSTICK_AXIS )
            {
                if( p1_device == Gamepad1 || p2_device == Gamepad1 ) al_get_joystick_state( joy1, &joystate_fight_g1 );
                if( p1_device == Gamepad2 || p2_device == Gamepad2 ) al_get_joystick_state( joy2, &joystate_fight_g2 );

                if( p1_device == Gamepad1 && hero1->get_hero_status() == Stand && joystate_fight_g1.stick[ 0 ].axis[ 1 ] && event.joystick.pos == -1.0 ) hero1->make_gamepad_click_move();
                if( p1_device == Gamepad2 && hero1->get_hero_status() == Stand && joystate_fight_g2.stick[ 0 ].axis[ 1 ] && event.joystick.pos == -1.0 ) hero1->make_gamepad_click_move();
                if( p2_device == Gamepad1 && hero2->get_hero_status() == Stand && joystate_fight_g1.stick[ 0 ].axis[ 1 ] && event.joystick.pos == -1.0 ) hero2->make_gamepad_click_move();
                if( p2_device == Gamepad2 && hero2->get_hero_status() == Stand && joystate_fight_g2.stick[ 0 ].axis[ 1 ] && event.joystick.pos == -1.0 ) hero2->make_gamepad_click_move();
            }

            if( event.type == ALLEGRO_EVENT_TIMER )
            {
                if( p1_device == Keyboard ) hero1->make_keyboard_hold_move( keyboard_state, timer_1_gameloop );
                if( p2_device == Keyboard ) hero2->make_keyboard_hold_move( keyboard_state, timer_1_gameloop );

                if( p1_device == Gamepad1 || p2_device == Gamepad1 ) al_get_joystick_state( joy1, &joystate_fight_g1 );
                if( p1_device == Gamepad2 || p2_device == Gamepad2 ) al_get_joystick_state( joy2, &joystate_fight_g2 );

                if( p1_device == Gamepad1 ) hero1->make_gamepad_hold_move( joystate_fight_g1, event, timer_1_gameloop );
                if( p1_device == Gamepad2 ) hero1->make_gamepad_hold_move( joystate_fight_g2, event, timer_1_gameloop );
                if( p2_device == Gamepad1 ) hero2->make_gamepad_hold_move( joystate_fight_g1, event, timer_1_gameloop );
                if( p2_device == Gamepad2 ) hero2->make_gamepad_hold_move( joystate_fight_g2, event, timer_1_gameloop );
            }

        //DRAWING
            the_location->draw_location( 0, 0 );
            hero1->draw_hud();
            hero2->draw_hud();
            al_draw_scaled_bitmap( bitmap_round_3, 0, 0, 200, 280, sfx*775.0, sfy*20.0, sfx*64.29, sfy*90.0, 0 );
            hero1->draw_hero();
            hero2->draw_hero();
            al_wait_for_vsync();
            al_flip_display();

        //FREEING MEMORY
            if( free_fight_loading_memory )
            {
                delete the_location;
                delete hero1;
                delete hero2;
                al_destroy_bitmap( bitmap_round_1 );
                al_destroy_bitmap( bitmap_round_2 );
                al_destroy_bitmap( bitmap_round_3 );
                fight_still_loading = true;
            }
        }
    }

//POINTER DESTRUCTION
    al_destroy_display( main_display );
    al_destroy_timer( timer_1_gameloop );
    al_destroy_event_queue( event_queue );
    al_destroy_bitmap( bitmap_menu1 );
    al_destroy_bitmap( bitmap_loading1 );
    al_destroy_bitmap( bitmap_keys1 );
    al_destroy_bitmap( bitmap_keys2 );
    delete menu1_text1;
    delete menu1_text2;
    delete menu1_text3;
    delete menu1_text4;
    delete menu2_text1;
    delete menu2_text2;
    delete menu2_text3;
    delete menu2_text4;
    delete title_opponent;
    delete rp_opponent;
    delete ai_opponent;
    delete p1_controller;
    delete p2_controller;
    delete kb1_controller;
    delete kb2_controller;
    if( j_num == 1 || j_num == 2 )
    {
        delete c11_controller;
        delete c12_controller;
        if( j_num == 2 )
        {
            delete c21_controller;
            delete c22_controller;
        }
    }
    /*delete location1;
    delete location2;
    delete loc_placeholder1;
    delete loc_placeholder2;
    delete loc_placeholder3;
    delete loc_placeholder4;
    //delete loc_placeholder;
    delete title_location;
    delete the_location;
    i wszystkie hero placeholder ale to jest wyzej wewn. ifa*/

    return 0;
}
