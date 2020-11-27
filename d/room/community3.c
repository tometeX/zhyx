#include <room.h>

inherit BUILD_ROOM; 
void create()
{
	set("short", "三号社区");
	set("long", @LONG
这里是三号社区，绿茵茵的草地上坐落着许多各色各样的房屋。草
丛中开着一些不知名的小花，有红的、黄的，还有紫的。花瓣上、草叶
上的露珠闪着晶莹的光。
LONG );
	set("exits", ([		
		"west" : __DIR__"community2",
	]));
	set("no_clean_up", 0);
	set("outdoors", "city");
       set("max_room", 15);
       set("no_fight", 1); 
	setup();
	//replace_program(ROOM);
}

