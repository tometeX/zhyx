// 玄女洞/九天玄女解谜地点二

#include <ansi.h> 
inherit ROOM;

void create()
{
	set("short", "玄女洞");
	set("long", @LONG
只见这里光线十分暗淡，四处灰尘满布，似乎已有很久未曾
有人来过此处。
LONG );
	set("exits", ([		
		"up"  : __DIR__"nvwamiao",
	]));
       set("no_fight",1);	
	setup();
	
}
/*
void init()
{
    add_action("do_ketou", "ketou");  
    add_action("do_tuotai", "tuotai");      
}

*/

