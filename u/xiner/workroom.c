// Room of wizard that haven't modify own workroom
// Updated by Lonely

#include <ansi.h>
#include <room.h>
inherit CREATE_CHAT_ROOM;

int is_chat_room() { return 1; }

void create()
{
        set("short", HIW"馨儿的工作间"NOR);
        set("long",HIG @LONG
这是一间普普通通的办公室，透过落地式的窗户可以看到
远处群山之间的峡谷翠绿的柳树。不远处的一片杏树林，朵朵
杏花艳态娇姿，繁花丽色，胭脂万点，占尽春风。
LONG NOR);

        set("exits", ([ /* sizeof() == 1 */
                "north" : "/d/wizard/wizard_room",
                "down"  : "/d/city/kedian",
                "sky1"  : "/d/zhuanshi/sky/sky1",
        ]));

        set("objects", ([
                "/u/xiner/npc/shuanger": 1,
           ]));

        set("valid_startroom", 1);
        set("no_fight",1);
        set("sleep_room", "1");
        set("no_clean_up", 0);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" && ! wizardp(me))
                return notify_fail("那里只有巫师才能进去。\n");
        return ::valid_leave(me, dir);
}
