// /d/wizard/guest_room.c

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", HIR "匿名留言室" NOR);
	set("long", @LONG
如果您有问题留言给本站巫师但又不想其他玩家看到，那
么您可以在这里(post)，其他玩家将不能看到您的留言，在这
里您可以举报有问题的id和其他作弊行为，本站巫师将为您的
留言完全保密。
LONG );

	set("exits", ([
		//"north": __DIR__"herodoor",
        "down": "/d/wizard/advice",
        "up": __DIR__"wizard_room",
        ]));

	set("no_fight", 1);

	setup();
	"/clone/board/noname_b"->foo();
}

int valid_leave(object me, string dir)
{
	if (dir == "up" && ! wizardp(me))
		return notify_fail("上面乃是天界，只有巫师才能上去！\n");

	return ::valid_leave(me, dir);
}


