// /d/wizard/guest_room.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "中华名人堂");
	set("long", @LONG
这里是中华历来的各位高手，其间人物不乏横行天下，睥睨武林的黑道魔头，也
不乏纵横四海，古道热肠的白道名侠。现在他们已经离开泥潭，飘身远去，这里保存
的仅仅是他们当年的形貌武技；而这些传奇人物所留下的神话故事却永远流传在江湖
之中，永不磨灭。
LONG );

	set("exits", ([
		"east": __DIR__"guest_room",
        ]));
	set("no_fight", "1");
set("objects", ([ 
]));
	setup();
}

