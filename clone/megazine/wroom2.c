// Room: /u/wfoxd/wroom2.c

inherit ROOM;

void create()
{
	set("short", "走廊");
	set("long", @LONG
这是去山庄西边的走廊。你可以看见走廊上精致无比的雕刻画。
LONG
	);
	set("exits", ([ /* sizeof() == 4 */
  		"east" : __DIR__"xiaohuayuan",
	]));

	setup();
	//replace_program(ROOM);
}
