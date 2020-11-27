#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIY"名人堂"NOR);
        set("long",
"这里放置着当世五大高手的雕像，若你能打败他们其中的任何一人也\n"
"以将他们取而代之，在此立起你的雕像为后人称道。\n\n"); 
	set("no_fight", 1);
	set("no_steal", 1);
	set("no_sleep_room", 1);      
	set("objects", ([
                __DIR__"npc1" : 1,
                __DIR__"npc2" : 1,
                __DIR__"npc3" : 1,
                __DIR__"npc4" : 1,
                __DIR__"npc5" : 1,  
	]));
	set("exits", ([
		"east" : __DIR__"beidajie2",
		"up"   : __DIR__"wumiao2",
                "down" : "/d/wizard/herodoor"
	]));	
	setup(); 
}
