// Room: /u/wfoxd/eroom.c

inherit ROOM;

void create()
{
	set("short", "走廊");
	set("long", @LONG
这是去山庄东边的走廊。你可以看见走廊上精致无比的雕刻画。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  		"north" : __DIR__"eroom2",
  		"west" : __DIR__"ygc",
	]));

	setup();
	//replace_program(ROOM);
}
