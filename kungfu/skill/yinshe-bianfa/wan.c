#include <ansi.h>
#include <combat.h>

#define QIAN "「" HIW "蛇影万道" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
	object weapon;
	string msg;
	int ap, dp;
        int count;
	int i, attack_time;


	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
                return notify_fail(QIAN "只能对战斗中的对手使用。\n");

	if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "whip")
                return notify_fail("你使用的武器不对，难以施展" QIAN "。\n");

	if ((int)me->query_skill("yinshe-bianfa", 1) < 180)
		return notify_fail("你的银蛇鞭法不够娴熟，难以施展" QIAN "。\n");

	if (me->query("neili") < 400)
		return notify_fail("你的真气不够，难以施展" QIAN "。\n");

        if (me->query_skill_mapped("whip") != "yinshe-bianfa")
                return notify_fail("你没有激发银蛇鞭法，难以施展" QIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = MAG "$N" MAG "一声长吟，手中" + weapon->name() + MAG "顿时化做无数条银蛇，从四面八方同时向$n" MAG "袭去。\n" NOR;       

	ap = me->query_skill("whip");
	dp = target->query_skill("dodge");
        attack_time = 7;

	if (ap / 2 + random(ap * 2) > dp)
	{
		msg += HIR "结果$n" HIR "被$N" HIR "攻了个措手不及，$n"
                      HIR "慌忙招架，心中叫苦。\n" NOR;

                count = ap / 4;
                attack_time += random(3);
        } else
        {
                msg += HIC "$n" HIC "见$N" HIC "这几鞭招式凌厉，诡异"
                      "无比，只得苦苦招架。\n" NOR;
                count = 0;
        }
    	message_combatd(msg, me, target);        

        me->add_temp("apply/attack", count);
        me->add_temp("apply/damage", count / 2);

	for (i = 0; i < attack_time; i++)
	{
		if (! me->is_fighting(target))
		       break;
                if (! target->is_busy() && random(3) == 1)
                       target->start_busy(1); 
	        COMBAT_D->do_attack(me, target, weapon, 0); 
	}


        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count / 2);
		me->add("neili", -250);
	    me->start_busy(1 + random(attack_time / 2));
	return 1;
}
