inherit ROOM;

void create()
{
	set("short", "六百级技能测试场");
	set("long", @LONG这里是馨儿主持的技能测试场所
这里都是六百级别ｎｐｃ。
LONG );
	set("objects", ([
		__DIR__"npc/test11" : 1,
//		__DIR__"npc/test12" : 1,
	]));
	set("exits", ([
		"down" : __DIR__"test",
//		"up"   : __DIR__"test1",
	]));
	setup();
        //replace_program(ROOM);
}

