#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "右雁殿");
	set("long", @LONG
   右雁殿里空无一物，四周墙上刻满浮雕。
这些浮雕造型高古,手工细致精雅，工程惊人庞大，
内容令人难解，描绘的都是些奇禽异兽你虽见识宽
广，但浮雕上的奇禽异兽竟一样也没见过，真是奇
怪之极！
LONG );
              set("no_stab", 1); 
       set("exits", ([
		"east" : __DIR__"migong2",
                "east" :"d/jingyan/migong2",		                          	
		                          	]));
                set("no_clean_up", 0);
	setup();
	replace_program(ROOM);
}
