// wu.c 群魔乱舞

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        object weapon;
        int count;
        int lvl;
        int i;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("群魔乱舞只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你没有装备剑，不能用这一招。\n");
 
	if (me->query("neili") < 200)
		return notify_fail("你的真气不够，无法施展群魔乱舞！\n");

	if ((lvl = me->query_skill("kuihua-mogong", 1)) < 150)
		return notify_fail("你的葵花魔功火候不够，无法施展群魔乱舞！\n");

	msg = HIR "$N" HIR "默运葵花魔功，身形变得奇快无比，接连向$n"
              HIR "攻出数招！\n" NOR;
        i = 5;
        if (lvl / 2 + random(lvl) > (int)target->query_skill("parry"))
        {
                msg += HIR "$n" HIR "只觉得眼前一花，发现四周都是$N"
                       HIR "的身影，不由暗生惧意，接连后退。\n" NOR;
                count = me->query_skill("kuihua-mogong", 1) / 7;
                me->add_temp("apply/attack", count);
                i += random(6);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "身法好快，哪里"
                       "敢怠慢，连忙打起精神小心应对。\n" NOR;
                count = 0;
        }

	message_combatd(msg, me, target);
	me->add("neili", -i * 20);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (i > 5 && ! target->is_busy())
                        target->start_busy(1);
        	COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
        }

        me->add_temp("apply/attack", -count);
        me->start_busy(1 + random(6));
	return 1;
}
