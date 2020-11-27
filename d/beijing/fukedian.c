inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "虎坊客栈");
        set("long", @LONG
这是京城虎坊路街头邻街的一家客栈。客栈不大，前厅挂着一幅猛虎下山
的巨画。当门挂着对鸳鸯球。球上系着几个小小的黄铜风铃。微风掠过，风铃
发出清脆悦耳的叮咚声。上有横批“虎坊客栈”。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("objects", ([
                __DIR__"npc/xiaoer3" : 1,
        ]));
        set("exits", ([
                "south" : __DIR__"fu_2",
                  "north" : __DIR__"kediandayuan",
        ]));
        set("no_clean_up", 0);
        set("coor/x",-10);
	set("coor/y",981);
	set("coor/z",0);
	setup();
        //replace_program(ROOM);
}

/*
int valid_leave(object me, string dir)
{
	if (! me->query_temp("rent_paid") && dir == "north")
	        return notify_fail(CYN "店小二一下挡在你面前，白眼一翻：怎麽着，想白住啊？\n" NOR);
	if (me->query_temp("rent_paid") && dir == "south")
	        return notify_fail(CYN "店小二跑到门边拦住：客官已经付了银子，怎麽不住店就走了呢！\n" NOR);

	return ::valid_leave(me, dir);
}
*/
