#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "回春堂药店内厅");
        set("long", @LONG
这里是回春堂药店的内厅，你一走进这里，发现药的气味比外面还要浓上
很多。你看见一个小童正在这里埋着头整理药材。
LONG );
        set("no_fight", 1);
        set("objects", ([
                __DIR__"npc/liandan_tongzi"     : 1,
        ]));
        set("exits", ([
                "west" : __DIR__"huichuntang",
                "north": __DIR__"liandan_yaoshi",
        ]));

        set("coor/x",-10);
	set("coor/y",1010);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

