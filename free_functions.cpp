#include "headers.hpp"

void Various_Procedures::menu_go_down( int &marked_menu, Text *menu_text1, Text *menu_text2, Text *menu_text3, Text *menu_text4 )
{
    if( marked_menu != 3 ) marked_menu++;
    if( marked_menu == 1 )
    {
        menu_text1->change_color_to_white();
        menu_text2->change_color_to_grey();
    }
    else if( marked_menu == 2 )
    {
        menu_text2->change_color_to_white();
        menu_text3->change_color_to_grey();
    }
    else if( marked_menu == 3 )
    {
        menu_text3->change_color_to_white();
        menu_text4->change_color_to_grey();
    }
}

void Various_Procedures::menu_go_up( int &marked_menu, Text *menu_text1, Text *menu_text2, Text *menu_text3, Text *menu_text4 )
{
    if( marked_menu != 0 ) marked_menu--;
    if( marked_menu == 2 )
    {
        menu_text4->change_color_to_white();
        menu_text3->change_color_to_grey();
    }
    else if( marked_menu == 1 )
    {
        menu_text3->change_color_to_white();
        menu_text2->change_color_to_grey();
    }
    else if( marked_menu == 0 )
    {
        menu_text2->change_color_to_white();
        menu_text1->change_color_to_grey();
    }
}

void Various_Procedures::hero_go_right( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 )
{
    if( mark != 3 && mark != 7 ) mark++;
    if( mark == 1 )
    {
        hero1->allow_red_border( true );
        hero0->allow_red_border( false );
        hero1->allow_write_name( true );
        hero0->allow_write_name( false );
    }
    else if( mark == 2 )
    {
        hero2->allow_red_border( true );
        hero1->allow_red_border( false );
        hero2->allow_write_name( true );
        hero1->allow_write_name( false );
    }
    else if( mark == 3 )
    {
        hero3->allow_red_border( true );
        hero2->allow_red_border( false );
        hero3->allow_write_name( true );
        hero2->allow_write_name( false );
    }
    else if( mark == 5 )
    {
        hero5->allow_red_border( true );
        hero4->allow_red_border( false );
        hero5->allow_write_name( true );
        hero4->allow_write_name( false );
    }
    else if( mark == 6 )
    {
        hero6->allow_red_border( true );
        hero5->allow_red_border( false );
        hero6->allow_write_name( true );
        hero5->allow_write_name( false );
    }
    else if( mark == 7 )
    {
        hero7->allow_red_border( true );
        hero6->allow_red_border( false );
        hero7->allow_write_name( true );
        hero6->allow_write_name( false );
    }
}

void Various_Procedures::hero_go_left( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 )
{
    if( mark != 0 && mark != 4 ) mark--;
    if( mark == 2 )
    {
        hero2->allow_red_border( true );
        hero3->allow_red_border( false );
        hero2->allow_write_name( true );
        hero3->allow_write_name( false );
    }
    else if( mark == 1 )
    {
        hero1->allow_red_border( true );
        hero2->allow_red_border( false );
        hero1->allow_write_name( true );
        hero2->allow_write_name( false );
    }
    else if( mark == 0 )
    {
        hero0->allow_red_border( true );
        hero1->allow_red_border( false );
        hero0->allow_write_name( true );
        hero1->allow_write_name( false );
    }
    else if( mark == 6 )
    {
        hero6->allow_red_border( true );
        hero7->allow_red_border( false );
        hero6->allow_write_name( true );
        hero7->allow_write_name( false );
    }
    else if( mark == 5 )
    {
        hero5->allow_red_border( true );
        hero6->allow_red_border( false );
        hero5->allow_write_name( true );
        hero6->allow_write_name( false );
    }
    else if( mark == 4 )
    {
        hero4->allow_red_border( true );
        hero5->allow_red_border( false );
        hero4->allow_write_name( true );
        hero5->allow_write_name( false );
    }
}

void Various_Procedures::hero_go_down( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 )
{
    if( mark >= 0 && mark <= 3 ) mark += 4;
    if( mark == 4 )
    {
        hero4->allow_red_border( true );
        hero0->allow_red_border( false );
        hero4->allow_write_name( true );
        hero0->allow_write_name( false );
    }
    else if( mark == 5 )
    {
        hero5->allow_red_border( true );
        hero1->allow_red_border( false );
        hero5->allow_write_name( true );
        hero1->allow_write_name( false );
    }
    else if( mark == 6 )
    {
        hero6->allow_red_border( true );
        hero2->allow_red_border( false );
        hero6->allow_write_name( true );
        hero2->allow_write_name( false );
    }
    else if( mark == 7 )
    {
        hero7->allow_red_border( true );
        hero3->allow_red_border( false );
        hero7->allow_write_name( true );
        hero3->allow_write_name( false );
    }
}

void Various_Procedures::hero_go_up( int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 )
{
    if( mark >= 4 && mark <= 7 ) mark -= 4;
    if( mark == 0 )
    {
        hero0->allow_red_border( true );
        hero4->allow_red_border( false );
        hero0->allow_write_name( true );
        hero4->allow_write_name( false );
    }
    else if( mark == 1 )
    {
        hero1->allow_red_border( true );
        hero5->allow_red_border( false );
        hero1->allow_write_name( true );
        hero5->allow_write_name( false );
    }
    else if( mark == 2 )
    {
        hero2->allow_red_border( true );
        hero6->allow_red_border( false );
        hero2->allow_write_name( true );
        hero6->allow_write_name( false );
    }
    else if( mark == 3 )
    {
        hero3->allow_red_border( true );
        hero7->allow_red_border( false );
        hero3->allow_write_name( true );
        hero7->allow_write_name( false );
    }
}

void Various_Procedures::hero_enter( SIDE half, HEROES &chosen_hero, int &mark, Hero_Portrait *hero0, Hero_Portrait *hero1, Hero_Portrait *hero2, Hero_Portrait *hero3, Hero_Portrait *hero4, Hero_Portrait *hero5, Hero_Portrait *hero6, Hero_Portrait *hero7 )
{
    if( mark == 0 )
    {
        hero0->allow_red_border( false );
        hero0->allow_blue_border( true );
        if( half == Left ) chosen_hero = Panda;
        hero1->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero6->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 1 )
    {
        hero1->allow_red_border( false );
        hero1->allow_blue_border( true );
        hero0->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero6->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 2 )
    {
        hero2->allow_red_border( false );
        hero2->allow_blue_border( true );
        hero0->allow_blue_border( false );
        hero1->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero6->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 3 )
    {
        hero3->allow_red_border( false );
        hero3->allow_blue_border( true );
        if( half == Right ) chosen_hero = Panda;
        hero0->allow_blue_border( false );
        hero1->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero6->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 4 )
    {
        hero4->allow_red_border( false );
        hero4->allow_blue_border( true );
        hero0->allow_blue_border( false );
        hero1->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero6->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 5 )
    {
        hero5->allow_red_border( false );
        hero5->allow_blue_border( true );
        hero0->allow_blue_border( false );
        hero1->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero6->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 6 )
    {
        hero6->allow_red_border( false );
        hero6->allow_blue_border( true );
        hero0->allow_blue_border( false );
        hero1->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero7->allow_blue_border( false );
    }
    else if( mark == 7 )
    {
        hero7->allow_red_border( false );
        hero7->allow_blue_border( true );
        hero0->allow_blue_border( false );
        hero1->allow_blue_border( false );
        hero2->allow_blue_border( false );
        hero3->allow_blue_border( false );
        hero4->allow_blue_border( false );
        hero5->allow_blue_border( false );
        hero6->allow_blue_border( false );
    }
}

void Various_Procedures::loc_go_right( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 )
{
    if( mark != 2 && mark != 5 ) mark++;
    if( mark == 1 )
    {
        loc1->allow_red_border( true );
        loc0->allow_red_border( false );
    }
    else if( mark == 2 )
    {
        loc2->allow_red_border( true );
        loc1->allow_red_border( false );
    }
    else if( mark == 4 )
    {
        loc4->allow_red_border( true );
        loc3->allow_red_border( false );
    }
    else if( mark == 5 )
    {
        loc5->allow_red_border( true );
        loc4->allow_red_border( false );
    }
}

void Various_Procedures::loc_go_left( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 )
{
    if( mark != 0 && mark != 3 ) mark--;
    if( mark == 1 )
    {
        loc1->allow_red_border( true );
        loc2->allow_red_border( false );
    }
    else if( mark == 0 )
    {
        loc0->allow_red_border( true );
        loc1->allow_red_border( false );
    }
    else if( mark == 4 )
    {
        loc4->allow_red_border( true );
        loc5->allow_red_border( false );
    }
    else if( mark == 3 )
    {
        loc3->allow_red_border( true );
        loc4->allow_red_border( false );
    }
}

void Various_Procedures::loc_go_down( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 )
{
    if( mark < 3 ) mark += 3;
    if( mark == 3 )
    {
        loc3->allow_red_border( true );
        loc0->allow_red_border( false );
    }
    else if( mark == 4 )
    {
        loc4->allow_red_border( true );
        loc1->allow_red_border( false );
    }
    else if( mark == 5 )
    {
        loc5->allow_red_border( true );
        loc2->allow_red_border( false );
    }
}

void Various_Procedures::loc_go_up( int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 )
{
    if( mark > 2 ) mark -= 3;
    if( mark == 0 )
    {
        loc0->allow_red_border( true );
        loc3->allow_red_border( false );
    }
    else if( mark == 1 )
    {
        loc1->allow_red_border( true );
        loc4->allow_red_border( false );
    }
    else if( mark == 2 )
    {
        loc2->allow_red_border( true );
        loc5->allow_red_border( false );
    }
}

void Various_Procedures::loc_enter( PLACES &chosen_loc, int &mark, Location_Miniature *loc0, Location_Miniature *loc1, Location_Miniature *loc2, Location_Miniature *loc3, Location_Miniature *loc4, Location_Miniature *loc5 )
{
    if( mark == 0 )
    {
        chosen_loc = Planets;
        loc0->allow_red_border( false );
        loc0->allow_blue_border( true );
        loc1->allow_blue_border( false );
        loc2->allow_blue_border( false );
        loc3->allow_blue_border( false );
        loc4->allow_blue_border( false );
        loc5->allow_blue_border( false );
    }
    else if( mark == 1 )
    {
        chosen_loc = Tree;
        loc1->allow_red_border( false );
        loc1->allow_blue_border( true );
        loc0->allow_blue_border( false );
        loc2->allow_blue_border( false );
        loc3->allow_blue_border( false );
        loc4->allow_blue_border( false );
        loc5->allow_blue_border( false );
    }
    else if( mark == 2 )
    {
        chosen_loc = HolderP;
        loc2->allow_red_border( false );
        loc2->allow_blue_border( true );
        loc0->allow_blue_border( false );
        loc1->allow_blue_border( false );
        loc3->allow_blue_border( false );
        loc4->allow_blue_border( false );
        loc5->allow_blue_border( false );
    }
    else if( mark == 3 )
    {
        chosen_loc = HolderP;
        loc3->allow_red_border( false );
        loc3->allow_blue_border( true );
        loc0->allow_blue_border( false );
        loc1->allow_blue_border( false );
        loc2->allow_blue_border( false );
        loc4->allow_blue_border( false );
        loc5->allow_blue_border( false );
    }
    else if( mark == 4 )
    {
        chosen_loc = HolderP;
        loc4->allow_red_border( false );
        loc4->allow_blue_border( true );
        loc0->allow_blue_border( false );
        loc1->allow_blue_border( false );
        loc2->allow_blue_border( false );
        loc3->allow_blue_border( false );
        loc5->allow_blue_border( false );
    }
    else if( mark == 5 )
    {
        chosen_loc = HolderP;
        loc5->allow_red_border( false );
        loc5->allow_blue_border( true );
        loc0->allow_blue_border( false );
        loc1->allow_blue_border( false );
        loc2->allow_blue_border( false );
        loc3->allow_blue_border( false );
        loc4->allow_blue_border( false );
    }
}
