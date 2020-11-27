#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "左雁殿");
	set("long", @LONG
左雁殿里空无一物，四周墙上刻满浮雕。这些
浮雕造型高古，手工细致精雅，工程惊人庞大，而
内容令人难解，描绘的都是些奇禽异兽。你虽见识
宽广，但浮雕上的奇禽异兽竟一样也没见过，真是
奇怪之极！
LONG );              
       set("exits", ([
           "east" : __DIR__"migong2",
       ]));               
	setup();
	replace_program(ROOM);
}
