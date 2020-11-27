// 养颜术.c

#include <ansi.h>

inherit SKILL;

string type() { return "knowledge"; }

int practice_skill(object me)
{
        return notify_fail("养颜术只能靠学(learn)来提高。\n");
}
int valid_learn(object me)
{
        if (me->query("per") > 30 )
                return notify_fail("你没必要学这门技能了。\n");

        return 1;
}

void skill_improved(object me)
{
    tell_object(me, HIM "你在驻颜打扮方面的心得有所提高！\n" NOR );
    me->add("per", 0.1);
}



