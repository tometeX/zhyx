#include <ansi.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill,lv;

        if (target != me)
                return notify_fail("你只能用先天功来提升自己的战斗力。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("powerup"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");
        me->add("neili", -100);

        message_combatd(HIW "$N" HIW "微一凝神，运起先天气功，足底尘土泛"
                        "起，全身真气冲关欲出。\n" NOR, me);

        me->add_temp("apply/attack", skill * 2 / 5);
        me->add_temp("apply/dodge", skill * 1 / 4);
        me->add_temp("apply/parry", skill * 1 / 5);
        me->set_temp("powerup", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me,
                              skill :), skill);
        if (me->is_fighting()) me->start_busy(3);

	if ( (lv = me->query_skill("xiantian-gong", 1)) >= 180 && me->query_skill("taoism", 1) > 399 && me->query("family/family_name") == "全真教")
        {
		if (me->can_improve_skill("force"))
			me->improve_skill("force", lv * 2);

		if (me->query_skill("xiantian-gong", 1) >= 180 && me->can_improve_skill("xiantian-gong") && SKILL_D("xiantian-gong")->valid_learn(me))
			me->improve_skill("xiantian-gong", lv * 2);
        }

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("powerup"))
        {
                me->add_temp("apply/attack", -amount * 2 / 5);
                me->add_temp("apply/dodge", -amount * 1 / 4);
                me->add_temp("apply/parry", -amount * 1 / 5);
                me->delete_temp("powerup");
                tell_object(me, "你的先天功运行完毕，将内力收回丹田。\n");
        }
}
