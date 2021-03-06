// dongqu.c 大江东去

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
	int ap, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("大江东去只能对战斗中的对手使用。\n");

        if (me->query("gender") != "男性")
                return notify_fail("你不是堂堂男子,无法使出如此绝技。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if(me->query_skill_mapped("sword") != "xuantie-jian") 
                return notify_fail("你没有用玄铁剑法，无法使用大江东去！\n");

        if ((int)me->query_skill("xuantie-jian", 1) < 100)
                return notify_fail("你的玄铁剑法不够娴熟，不能使用大江东去。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的内功火候不够，不能使用大江东去。\n");

	if ((int)weapon->query_weight() < 30000)
		return notify_fail("你手中的" + weapon->name() + "分量不够，无法施展大江东去。\n");

        if ((int)me->query("neili") < 300 )
                return notify_fail("你现在内力太弱，不能使用大江东去。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你没有激发玄铁剑法，不能施展大江东去。\n");

        if ((string)me->query_skill_mapped("force") != "nuhai-kuangtao")
                return notify_fail("你没有激发怒海狂涛心法，无法使用玄铁剑法。\n");

        msg = HIC "$N" HIC "一声大喝，手中的" + weapon->name() + HIC "就如"
              "长虹一般劈向$n" HIC "！\n"NOR;

        me->start_busy(2);
            ap = me->query_skill("sword") + weapon->query_wight() / 500 + 100;
	dp = target->query_skill("force");
        if (me->query("character") == "光明磊落")
                ap += ap / 2;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                target->start_busy(1);
            	damage = ap + random(ap/2);
		damage = me->query("jiali");
                me->add("neili", -200);
		msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 30,
                                           HIR "$p" HIR "奋力招架，却被$P" HIR
		                           "这一剑震的飞起，口中鲜血狂吐不止！\n" NOR);
        } else
        {
                msg += CYN "可是$p" CYN "看破了$P" CYN "的企图，急忙斜跃避开。\n"NOR;
                me->add("neili", -50);
        }
        message_combatd(msg, me, target);

        return 1;
}
