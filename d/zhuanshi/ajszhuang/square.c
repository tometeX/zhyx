// by yuchang
inherit ROOM;

void create()
{
	set("short", "大殿");
	set("long", @LONG
这里是废弃的大殿中，到处都丢着破烂生锈的刀剑、甲胄，
殿角白骨森森，似在多年之前，曾有武士在这里进行过殊死
的拼杀。地面上到处插着箭矢，刀剑遗留满地，几百年来，
一直未曾打扫过。
LONG
	);

	set("exits", ([
		"north" : __DIR__"zoulang",
                "out" : __DIR__"shanzhuang",
	]));
	
	setup();
	replace_program(ROOM);
}



