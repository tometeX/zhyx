#include <ansi.h>
#include <combat.h>

#define YONG "「" HIY "汹涌" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int i, count;

        if (userp(me) && ! me->query("can_perform/bizhen-qingzhang/yong"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(YONG "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(YONG "只能空手使用。\n");

        if ((int)me->query_skill("bizhen-qingzhang", 1) < 250)
                return notify_fail("你碧针清掌火候不够，难以施展" YONG "。\n");

        if (me->query_skill_mapped("strike") != "bizhen-qingzhang")
                return notify_fail("你没有激发碧针清掌，难以施展" YONG "。\n");

        if (me->query_skill_prepared("strike") != "bizhen-qingzhang")
                return notify_fail("你没有准备碧针清掌，难以施展" YONG "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，难以施展" YONG "。\n");

        if ((int)me->query("max_neili") < 5000)
                return notify_fail("你的内力修为不够，难以施展" YONG "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你现在的真气不足，难以施展" YONG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIY "$N" HIY "轻哼一声，双掌挥舞出一个大圈，双掌翻滚，"
		"汹涌澎湃的劲气如波浪一般涌向$n。\n" NOR;  

        ap = me->query_skill("strike") + me->query("str") * 10;
        dp = target->query_skill("parry") + target->query("dex") * 8;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "面对$N" HIR "这汹涌澎湃的攻"
                       "势，完全无法抵挡，招架散乱，连连退后。\n" NOR;
                count = ap / 7;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，心知不妙，急忙"
                       "凝聚心神，竭尽所能化解$N" HIC "数道掌力。\n" NOR;
                count = 0;
        }
        message_combatd(msg, me, target);

        me->add_temp("apply/attack", count);
        me->add_temp("apply/unarmed_damage", count / 2);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        me->add("neili", -600);
        me->start_busy(1 + random(6));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 2);
        return 1;
}

