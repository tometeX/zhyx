//  by yuchang

#include <ansi.h>
inherit ROOM;
int do_open_men(string arg);

void create()
{
        set("short", "傲剑山庄");
        set("long", HIG"
                   A____________________A 
                  /||||||||||||||||||||||\   
               {//LLLLLLLLLLLLLLLLLLLLLLL\\/}   
                ^^||^^【傲 剑 山 庄】 ^^||^^ 
                  ||    ||---||---||    ||   
[]__[]___[]___[]__|[]___[]___||___[]___[]|__[]___[]___[]__[]  
|______________________|_|________|_|______________________| 

"NOR
        );
        set("no_fight", 1);

        set("exits",([
                "east" : __DIR__"shangu8",
                // "enter" : __DIR__"square", 
        ]));
}

void init()
{

        add_action("do_open_men", "open");
        
}
int do_open_men(string arg)
{
        object ob, me = this_player();
        object room;
        
        if (!arg || arg != "men" )
        {
            write("你是要打开门(men)吗?\n");
            return 1;
        }
        message_vision("$N用手指凌空一点，吱地一声，打开一道大门。\n", this_player());
        message("vision", HBMAG"【傲剑山庄】恭喜"+me->query("name")+"通过千回谷，顺利来到傲剑山庄!\n"NOR,
                users());
        set("exits/enter",  __DIR__"square");
        remove_call_out("close");
        call_out("close", 5, this_object());
        return 1;
}

void close(object room)
{        
        room->delete("exits/enter");
        message("vision", "大门慢慢地关上了。\n", room);
        
}


