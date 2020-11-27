#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "安全区");
        set("long", @LONG
这里是比武台下的安全区，在这里你很安全，嘿嘿！
LONG );
        set("biwutai",1);
        set("no_fight",1);
        set("no_sleep_room",1);
        set("no_steal",1);
        set("no_beg",1);
        set("no_get_from",1);
              set("objects", ([ 
                      "/adm/npc/shizhe": 1, 
              ])); 

        set("exits", ([
                "out" : __DIR__"kedian",
                "leitai" : __DIR__"leitai",
        ]));
        setup();
}
int no_die(object me)
{               
        message_vision (HIC"安全使者手指朝$N一指，$N顿时恢复了精神\n"NOR,me);
        me->revive();
        me->set("eff_qi",me->query("max_qi")); 
        me->set("eff_jing",me->query("max_jing"));               
        me->add("qi",5);
        me->add("jing",5); 
        me->clear_condition("poison");
        return 1;
}


