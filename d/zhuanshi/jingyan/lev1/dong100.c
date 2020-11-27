#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", CYN"石洞"NOR);
	set("long", CYN @LONG
这是一个黑漆漆石洞，周围都是坚硬的石壁,左面有阶梯
似乎可以一直往下去。 
LONG NOR);
	set("exits", ([
		"north" : __DIR__"dong99",
		"south" : __DIR__"dong10",
                "down" : "/d/jingyan/lev2/dong21"
                	]));
	set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
