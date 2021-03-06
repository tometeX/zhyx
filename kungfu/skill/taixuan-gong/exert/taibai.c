#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
	int count;

	if (! me->query("reborn"))
		return notify_fail("你所学的内功中没有这种功能。\n");

        if (userp(me) && (! me->query("can_perform/taixuan-gong/jing")||
		! me->query("can_perform/taixuan-gong/xuan")||
		! me->query("can_perform/taixuan-gong/hun")||
		! me->query("can_perform/taixuan-gong/po")))
		return notify_fail("你所学的内功中没有这种功能。\n");

	if (target != me)
		return notify_fail("你只能用太玄功来提升自己的战斗力。\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你的内力不够。\n");

	if ((int)me->query_temp("taibai"))
		return notify_fail("你已经在运功中了。\n");

	me->add("neili", -1000);

	me->receive_damage("qi", 500);

	message_combatd(HIM "$N" HIM "提起太玄神功，默念「" HIW "太白吟诗" HIM "」口诀，顿觉"
                        "自己力大无比。\n" NOR, me);

	count = me->query_skill("taixuan-gong", 1);
	me->add_temp("apply/force", count / 6);
	me->add_temp("str", count / 10);
	me->add_temp("dex", count / 20);
	me->set_temp("taibai", 1);
	me->start_call_out((: call_other, __FILE__, "remove_effect", me, count :), count / 2);

	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void remove_effect(object me, int count)
{
        if ((int)me->query_temp("taibai"))
        {
		me->add_temp("apply/force", - count / 6);
		me->add_temp("str", - count / 10);
		me->add_temp("dex", - count / 20);
		me->delete_temp("taibai");
		tell_object(me, "你的「" HIW "太白吟诗" NOR "」运行完毕，将内力收回丹田。\n");
        }

}

