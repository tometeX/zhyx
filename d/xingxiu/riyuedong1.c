#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "日月侧洞");
        set("long", @LONG
这里是星宿派总舵所在地日月洞侧洞。只见漆黑一片，唯
有前方不远处有些许光线。墙上隐隐约约可见记载着一些
奇怪的文字。
LONG);
        set("exits", ([
             "out" : __DIR__"xxh1",
        ]));

        setup();
        //replace_program(ROOM);
}

void init()
{
        add_action("do_mianbi", "mianbi");
}

int do_mianbi(string arg)
{
        object me;
        int cost;

        me = this_player();
        if (me->is_busy())
                return notify_fail("等你忙完了手头的事情再说！\n");

        if (me->is_fighting())
                return notify_fail("你边打架一边面壁？真有你的。\n");

        if (me->query("jing") < me->query("max_jing") * 7 / 10)
                return notify_fail("你现在的精不够，无法面壁。\n");

        if (me->query_skill("poison", 1) < 250)
                return notify_fail("你对基本毒技理解太浅，面壁获得不了什么进境。\n");

        if (! arg || ! sscanf(arg, "%d", cost))
                return notify_fail("你要花多少潜能进行面壁？\n");

        if (cost >= me->query("potential") - me->query("learned_points"))
                return notify_fail("你现在没有这么多的潜能！\n");

        if (cost < 100)
                return notify_fail("你至少要花一百点潜能才能有所进步。\n");

        message_vision(HIC "\n$N" HIC "找了一个地方坐了下来，开"
                       "始专心研究石壁上所载的基本毒技。\n\n" NOR, me);

        me->set_temp("pending/mianbi", 1);
        me->set_temp("potential_cost", cost);
        me->set_short_desc("正坐在地下专心面壁。");
        me->start_busy((:call_other, __FILE__, "mianbi" :),
                       (:call_other, __FILE__, "halt_mianbi" :));
        return 1;
}

int mianbi(object me)
{
        int cost;

        cost = me->query_temp("potential_cost");
        if (cost > 0)
        {
                cost = random(cost) + 1;
                if (cost > 3) cost = 3;
        } else
                cost = 0;

        me->improve_skill("poison", me->query_int() / 5 +
                          random(me->query_skill("poison", 1) * cost));
        me->add("learned_points", cost);
        if (me->add_temp("potential_cost", -cost) > 0)
                return 1;

        me->set_temp("pending/mianbi", 0);
        me->set_short_desc(0);
        message_vision(HIG "$N" HIG "面壁完毕，露出一丝邪气，站了起来。\n" NOR, me);
        return 0;
}

int halt_mianbi(object me)
{
        tell_object(me, HIY "你突然恍然大悟，站了起来。\n" NOR);
        tell_room(environment(me), HIY + me->name() + HIY "突然恍然大悟"
                                   "，站了起来。\n" NOR, me);
        me->set_temp("pending/mianbi", 0);
        me->delete_temp("potential_cost");
        me->set_short_desc(0);
        return 1;
}



