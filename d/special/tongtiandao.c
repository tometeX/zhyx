// regiser: tongtiandao 
// by Rcwiz for HERO

#include <ansi.h>

int is_chat_room() { return 1; } 

inherit ROOM;

void create()
{
        set("short", HIW "通天岛" NOR);
        set("long", @LONG
这里是一处极荒凉的小岛，四周云雾弥漫，海波荡漾。
所有PK过度的玩家均会被禁闭在此反省二十四小时。
    旁边有一个牌子(paizi)。
LONG );
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("exits", ([
                "out"     :     "/d/city/wumiao",
        ]));
        set("item_desc", ([
                "paizi" : HIR "得饶人处且饶人！\n" NOR
        ]));
}

void init()
{        
        add_action("do_notify", ({"eat", "drink", "yun", "exert", 
                                  "perform", "miss", "suicide" }));
}

int do_notify()
{
        write("好好在此反省吧！\n");
        return 1;
}

int valid_leave(object me, string dir)
{
        if (me->query_condition("pk")
           && dir == "out")
             return notify_fail(HIR "\n好好在此反省吧，时候到了自然会放你离开。\n" NOR);

        return ::valid_leave(me, dir);
}

