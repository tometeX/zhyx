inherit ROOM;

void create()
{
	set("short", "五百级技能测试场");
	set("long", @LONG这里是馨儿主持的技能测试场所
这里都是五百级别ｎｐｃ。
LONG );
	set("objects", ([
		__DIR__"npc/test01" : 1,
//		__DIR__"npc/test02" : 1,
	]));
	set("exits", ([
		"down" : "/d/wizard/wizard_room",
		"up"   : __DIR__"test1",
	]));
	setup();
        //replace_program(ROOM);
}

