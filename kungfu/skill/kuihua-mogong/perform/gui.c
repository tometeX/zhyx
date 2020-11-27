// gui.c 鬼魅身法

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
	string msg;
        int ap, dp;

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail("鬼魅身法只能对战斗中的对手使用。\n");

	if (target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
		
	if ((int)me->query_skill("kuihua-mogong", 1) < 100)
		return notify_fail("你的葵花魔功不够深厚，不会使用鬼魅身法。\n");

	msg = HIR "$N" HIR "身子忽进忽退，身形诡秘异常，在$n"
              HIR "身边飘忽不定。\n" NOR;

        ap = me->query_skill("kuihua-mogong", 1) * 3 / 2 +
             me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

	if (ap / 2 + random(ap) > dp)
        {
		msg += HIR "结果$p" HIR "只能紧守门户，不敢妄自出击！\n" NOR;
		target->start_busy(ap / 45 + 2);
	} else
        {
		msg += CYN "可是$p" CYN "看破了$P" CYN "的身法，并没"
                       "有受到任何影响。\n" NOR;
		me->start_busy(1);
	}
	message_combatd(msg, me, target);

	return 1;
}
