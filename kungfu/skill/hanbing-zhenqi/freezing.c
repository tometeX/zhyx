// updated by kasumi
#include <ansi.h>
inherit F_CLEAN_UP;

#define FRE "「" HIW "寒冰真气" NOR "」"

void remove_effect(object me,int amount);

int exert(object me, object target)
{
        int skill;

        if (userp(me) && ! me->query("can_perform/hanbing-zhenqi/freezing"))
                return notify_fail("你所学的内功中没有这种功能。\n");

        if ((int)me->query_temp("freezing"))
                return notify_fail("你现在正在施展" FRE "。\n");

        if (target != me)
                return notify_fail(FRE "只能对自己使用。\n");

        skill = me->query_skill("hanbing-zhenqi", 1);

        if (me->query("con") < 34)
                return notify_fail("你的先天根骨不足，无法施展" FRE "。\n");

        if (skill < 200)
                return notify_fail("你的寒冰真气等级不够，难以施展" FRE "。\n");

        if ((int)me->query("max_neili") < 2200)
                return notify_fail("你的内力修为不足，难以施展" FRE "。\n");

       

        if ((int)me->query("neili") < 500)
                return notify_fail("你目前的内力不够，难以施展" FRE "。\n");

        me->add("neili", -200);

        message_combatd(HIW "$N" HIW "一声冷笑，体内寒冰真气迅速疾转数个周"
                        "天，霎时间透骨的寒意漫向四方。\n" NOR, me);
        me->set_temp("freezing", 1);
	    	me->add_temp("apply/armor", skill / 2);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, skill/2 :), skill);
        if (me->is_fighting())
                me->start_busy(3);

        return 1;
}

void remove_effect(object me,int amount)
{
        if (me->query_temp("freezing"))
        {
			       me->add_temp("apply/armor", -amount);
             me->delete_temp("freezing");
             tell_object(me, "你的" FRE "运行完毕，将内力收回丹田。\n");
        }
}

