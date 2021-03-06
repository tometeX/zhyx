// 纽约港

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "纽约港");
	set("long", @LONG
这里是花旗国最热闹的港口纽约港，是该国对外交往和贸易
的最大门户。这里停泊着许多大海船。码头上许多工人来来往往
搬运货物，商人四处行走，忙得不亦乐乎。若想回到中国可以在
此处(enter chuan)。这里还坐落着举世闻名的自由女神像。
LONG );
	set("exits", ([		
		"west"        : __DIR__"ny_road",
	]));
       set("item_desc", ([
           "chuan" : "一条大海船。出远海没这样的船可不行。\n",
       ]));
	set("objects",([	
             __DIR__"statue" : 1,
	]));
       set("no_sleep_room",1); 
	set("no_ride",1);	
	setup();	
}

void init()
{
        add_action("do_enter", "enter");
}


int do_enter(string arg)
{
        object ob ;
        string dir;

        ob = this_player();
        if (arg !="chuan")
        {
                tell_object(ob, "你要去哪儿？\n" );
                return 1;
        }    

        message_vision("大海船开了，缓缓地驶向中国。\n", ob);
        ob->move("/d/quanzhou/dahai");
        tell_object(ob, WHT "\n去往中国路途遥远，你只好默默等待.......\n\n" NOR);
        call_out("tpenghu", 10 , ob);
        return 1 ;
}

void tpenghu(object ob)
{
        if (! objectp(ob) || find_object("/d/quanzhou/dahai") != environment(ob))
                return;

        tell_object(ob, "航行了两个月后，大海船终于抵达了中国的嘉兴港。\n\n");
        ob->move("/d/quanzhou/jiaxinggang");
}

int valid_leave(object me, string dir) 
{    
    if ( dir == "west")     
    return notify_fail("你仔细一想，觉得自己在这里人生地不熟，\n"
                       "加之语言不通，还是不要乱走为好。\n\n"NOR);     
} 



