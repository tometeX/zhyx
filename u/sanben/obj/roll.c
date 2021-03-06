
//春卷(加10万潜能)

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "春卷" NOR, ({ "chunjuan", "roll" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一个春节才能吃到的春卷，看得你直流口水。\n" NOR);
                set("unit", "个");
                set("value", 10);
                set("no_sell",1);
                set("weight", 10);
             }
        setup();
}

void init()
{
     add_action("do_eat","eat");
}

int do_eat(string arg)
{
        object me;
        int year, *date;
        date = localtime(time());
        year = date[5];

        me = this_player();

        if (!arg || (arg != "chunjuan" &&
                     arg != "roll"))
                return 0;

        if (me->query("reward/gift/chunjuan/" + year))
        {
                write(HIR "你已经吃过今年的春卷了，多吃会消化不良的!\n" NOR);
                return 1;
        }

        me->set("reward/gift/chunjuan/" + year, 1);
        message_vision(HIW "$N" HIW "将春卷一口吞了。\n" NOR, me);

        me->add("potential", 100000);

        tell_object(me, HIG "恭喜你增加了十万点潜能。"
                            "感谢你对本站的支持，祝你新春快乐！\n" NOR);
        destruct(this_object());
        return 1;
}

int query_autoload()
{ return 1; }
