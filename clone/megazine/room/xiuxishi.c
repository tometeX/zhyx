// Room: /clone/megazine/xiuxishi.c

inherit ROOM;

void create()
{
        set("short", "休息室");
	set("long", @LONG
这是〖地狱〗办公室的休息室，在这里可以喝喝茶聊聊天。
LONG
	);

	set("exits", ([ 
                "east" : "/d/city/wfoxd",
	]));

        set("objects",([
                  "/clone/food/peanut" : 2,
                  "/d/taohua/obj/cha"  : 2,
        ]));

        set("no_fight", "1");
	setup();
	//replace_program(ROOM);
}
