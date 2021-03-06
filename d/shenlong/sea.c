// sea.c
// Modified by haiyan

#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", "大海");
        set("long",@LONG
你正处在茫茫大海之中。你极目远望，只见海天一线，周围连个黑点都没有。
耳边只有海浪的拍打声。
LONG);   
        set("no_clean_up", 0);
        setup();
}

void init()
{
      add_action("do_swimming", "swim");
      add_action("do_swimming", "youyong");
}

int do_swimming()
{
    object me = this_player();
    int t = (int)me->query("max_qi");

    tell_object(me, "你奋力挥动双臂，漫无目的地向前游去。\n");
    me->receive_damage("qi", t/10 + random(t/5));

    if (random(3) == 1)
       tell_object(me, HIC"突然你看见一条鲨鱼向你游来。你急忙转身，拼命向前游去。\n"NOR);

    if (random(10) < 5)
    {
       tell_object(me, "你眼见神龙岛越来越近，不由精神一振。\n"); 
       if (random(10) < 6)
       {
          me->move("/d/shenlong/haitan");
          tell_object(me, "你终于游到岸边，浑身湿漉漉地爬了上来。\n"); 
          message("vision", "你发现一个浑身水淋淋的家伙被海水冲上岸来，不由得走近一看，原来是" +
                   me->name() + "。\n", environment(me), me);
       }
    }
    else
    {
       if ((int)me->query("qi") < 0)
       {
           me->set("qi", 0);
           tell_object(me, "你筋疲力尽，渐渐失去了知觉。\n");
           me->unconcious();
           me->move("/d/shenlong/haitan");
           message("vision", "你发现一个浑身水淋淋的家伙被海水冲上岸来，不由得走近一看，" +
                   "原来是" + me->name() + "。\n", environment(me), me);
       }
    }
    return 1;
}

