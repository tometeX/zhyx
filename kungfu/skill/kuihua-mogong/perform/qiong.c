// qiong 无穷无尽

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QIONG "「" HIR "无穷无尽" NOR "」"
 
int perform(object me, object target)
{
	string msg;
        int ap, dp, ap1, dp1,attack_time,i,damage;
        object weapon;

        if (userp(me) && ! me->query("can_perform/kuihua-mogong/qiong"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail(QIONG "只能在战斗中对对手使用。\n");

	if (me->query_skill("kuihua-mogong", 1) < 250)
		return notify_fail("你的葵花魔功还不够娴熟，不能使用" QIONG "！\n");

        if ((int)me->query("max_neili") < 3800)
                return notify_fail("你的内力修为不足，难以施展" QIONG "。\n");

	if (me->query("neili") < 200)
		return notify_fail("你的真气不够，无法施展" QIONG "\n");

        if (weapon = me->query_temp("weapon"))
        {
                if (weapon->query("skill_type") != "sword" &&
                    weapon->query("skill_type") != "pin" &&
					weapon->query("skill_type") != "xsword")
                        return notify_fail("你手里拿的不是剑，怎么施"
                                           "展" QIONG "？\n");
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("你并没有准备使用葵"
                                           "花魔功，如何施展" QIONG "？\n");
        }
        if (weapon && me->query_skill_mapped("sword") != "kuihua-mogong")
                return notify_fail("你没有准备使用葵花魔功，难以施展" QIONG "。\n");

        if (! weapon && me->query_skill_prepared("unarmed") != "kuihua-mogong")
                return notify_fail("你没有准备使用葵花魔功，难以施展" QIONG "。\n");

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

       

        ap = me->query_skill("dodge");
        dp = target->query_skill("dodge");
		
		if (( random(ap/4) > dp) && me->query("reborn"))
        {	
				msg = HIR "\n$N" HIR "尖啸一声，猛然进步欺前，一招竟直袭$n" HIR "要害，速度之快，令"
				"人见所未见，闻所未闻。\n" NOR;
                msg += HIR "这一招速度之快完全超出了$n" HIR "的想象，被$N"
                       HIR "这一招正好击中了丹田要害，$n" HIR "像滩烂泥似的瘫了下去！\n" NOR;
                message_combatd(msg, me, target);
                me->add("neili", -400);
                target->unconcious();  
                return 1;
		}else{
				ap1 = me->query_skill("dodge") + me->query_skill("parry");
                dp1 = target->query_skill("dodge") + target->query_skill("parry");
				attack_time = (int) me->query_skill("kuihua-mogong", 1) / 100;
				if (attack_time>15){
					attack_time=15;
				}
				if (!me->query("reborn")){
					attack_time=1;
				}
				msg ="";
				for (i = 0; i < attack_time; i++){
					if (ap1 * 3 / 4 + random(ap1) > dp1)
					{
					 msg += HIR "\n$N" HIR "尖啸一声，猛然进步欺前，一招竟直袭$n" HIR "要害，速度之快，令"
					"人见所未见，闻所未闻。\n" NOR;
                     damage = ap * 2 + random(ap);
                     msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 85 + random(15),
                                                HIR "这一招速度之快完全超出了$n" HIR "的想象，$n" HIR
                                                "尖叫一声，已然中招。\n" NOR);
                     me->add("neili", -150);
                     me->start_busy(1 + random(2));
					}
					else
					{
					 msg += HIR "\n$N" HIR "尖啸一声，猛然进步欺前，一招竟直袭$n" HIR "要害，速度之快，令"
					"人见所未见，闻所未闻。\n" NOR;
                     msg += HIC "$n" HIC "知道来招不善，急忙闪避，没出一点差错。\n" NOR;
                     me->add("neili", -80);
                     me->start_busy(1 + random(2));
					}
				}
                message_combatd(msg, me, target);
                return 1;
		}

	return 1;
}
