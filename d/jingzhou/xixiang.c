inherit ROOM;

void create()
{
        set("short", "丫鬟卧房");
        set("long", @LONG
这是丫鬟的房间。房中陈设简单，没什么东西。
LONG );

        set("exits", ([
                "east" : __DIR__"houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/juyou" : 1,
        ]));
        set("cost", 0);
        set("coor/x", -480);
	set("coor/y", -230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}

