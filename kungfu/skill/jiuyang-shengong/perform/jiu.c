#include <ansi.h>
#include <combat.h>

#define JIU "「" HIR "九曦混阳" NOR "」"

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg;
        int ap, dp;
        int count;
        int i;
 
        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (userp(me) && ! me->query("can_perform/jiuyang-shengong/jiu"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIU "只能对战斗中的对手使用。\n");

        if (me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("你现在没有激发九阳神功为内功，难以施展" JIU "。\n");

        if (me->query_skill("jiuyang-shengong", 1) < 200)
                return notify_fail("你的九阳神功还不够娴熟，难以施展" JIU "。\n");

        if (me->query("max_neili") < 4000)
                return notify_fail("你的内力的修为不够，现在无法使用" JIU "。\n");

	if (me->query("reborn")) 
	{
		weapon = me->query_temp("weapon");
	        if (! objectp(weapon))
        	{
			if (me->query_skill_mapped("unarmed") != "jiuyang-shengong"
				|| me->query_skill_prepared("unarmed") != "jiuyang-shengong")
					return notify_fail("你现在没有准备使用九阳神功，难以施展" JIU "。\n");
	        }
        	else
		{
			if (objectp(weapon) && (string)weapon->query("skill_type") != "sword"
					&& (string)weapon->query("skill_type") != "blade")
					return notify_fail("你使用的武器不对，无法施展" JIU "。\n");
		}
	        if (objectp(weapon) && me->query_skill_mapped("sword") != "jiuyang-shengong"
        	         && (string)weapon->query("skill_type") == "sword")
				return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" JIU "。\n");
             
		else if (objectp(weapon) && (string)weapon->query("skill_type") == "blade"
                	      && me->query_skill_mapped("blade") != "jiuyang-shengong")
				return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" JIU "。\n");
	}
	else
	{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail(JIU "只能空手施展。\n");               

	if (me->query_skill_mapped("unarmed") != "jiuyang-shengong")
		return notify_fail("你现在没有激发九阳神功为拳脚，难以施展" JIU "。\n");
	
	if (me->query_skill_prepared("unarmed") != "jiuyang-shengong")
		return notify_fail("你现在没有准备使用九阳神功，难以施展" JIU "。\n");
	}
        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够，无法运用" JIU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIR "$N" HIR "大喝一声，顿时一股浩荡无比的真气至体内迸发，双掌"
              "猛然翻滚，朝$n" HIR "闪电般拍去。\n" NOR;

	if (me->query("reborn"))
		ap = me->query_skill("jiuyang-shengong", 1) * 3 / 2 + me->query_con() * 20 + me->query_skill("martial-cognize") / 4;
	else
		ap = me->query_skill("jiuyang-shengong", 1) * 3 / 2 + me->query_con() * 20;

        dp = target->query_skill("parry") + target->query_con() * 18;

        if (ap * 3 / 5 + random(ap) > dp)
        {
                count = ap / 10;
                msg += HIR "$n" HIR "只觉周围空气炽热无比，又见无数气团向"
                       "自己袭来，顿感头晕目眩，不知该如何抵挡。\n" NOR;

        } else
        {
                msg += HIY "$n" HIY "只见$N" HIY "无数气团向自己袭来，连"
                       "忙强振精神，勉强抵挡。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);
	me->add_temp("apply/unarmed_damage", count / 3);
	me->add_temp("apply/damage", count / 3);

        me->add("neili", -300);

        for (i = 0; i < 9; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(5) < 2 && ! target->is_busy())
                        target->start_busy(1);
                if (! objectp(weapon))
                   COMBAT_D->do_attack(me, target, 0, i * 2);
                else COMBAT_D->do_attack(me, target, weapon, i * 2);
        }

        me->start_busy(3 + random(5));
        me->add_temp("apply/attack", -count);
	me->add_temp("apply/unarmed_damage", -count / 3);
	me->add_temp("apply/damage", -count / 3);

        return 1;
}
