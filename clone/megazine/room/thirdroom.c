#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIW "〖地狱〗杂志社展览厅" NOR);
	set("long", @LONG
这是〖地狱〗杂志社的展览厅，你可以看见一些资料。
LONG
	);

	set("exits", ([
                "down" : __DIR__"secondroom",
                "up"   : __DIR__"fourroom",
        ]));

        set("item_desc", ([
                "tenet" : HIW "提供更多的机会与玩家交流。\n" NOR,
                "item"  : HIW "1.婚姻介绍。2.玩家联系。3.广告服务。4.为你组织其它活动。\n" NOR,
        ]));

        set("no_fight",1);
        setup();
        //replace_program(ROOM);
}
