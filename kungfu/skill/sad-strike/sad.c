// sad.c 黯然消魂

#include <ansi.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i,j;
 
	if (! target)
	{
		me->clean_up_enemy();
		target = me->select_opponent();
	}

        if (! target || ! me->is_fighting(target))
                return notify_fail("「黯然销魂」只能在战斗中对对手使用。\n");
 
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("「黯然销魂」只能空手使用。\n");
		
        if ((int)me->query("neili") < 500)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("sad-strike", 1) < 170)
                return notify_fail("你的黯然销魂掌火候不够，无法使用「黯然销魂」！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，无法使用「黯然消魂」！\n");

        if (! me->query_skill_prepare() &&
            me->query_skill_mapped("unarmed") != "sad-strike" ||
            me->query_skill_prepare() &&
            me->query_skill_prepared("unarmed") != "sad-strike" &&
            me->query_skill_prepared("strike") != "sad-strike")
                return notify_fail("你现在没有准备使用黯然销魂掌，无法使用「黯然消魂」！\n");

        msg = HIM "$N" HIM "心如止水，黯然神伤，随手使出了"
              HIR "“黯然销魂”" HIM "！\n" NOR;
        ap = me->query_skill("strike") + me->query("str") * 10;
        dp = target->query_skill("parry") + target->query("dex") * 10;
        if (ap / 2 + random(ap) > dp || !living(target))
        {
                count = ap / 20;
                msg += HIY "$n" HIY "见$P" HIY "这一招变化莫测，奇幻无"
                       "方，不由大吃一惊，慌乱中破绽迭出。\n" NOR;
        } else
        {
                msg += HIC "$n" HIC "不敢小觑$P" HIC
                       "的来招，腾挪躲闪，小心招架。\n" NOR;
                count = 0;
        }

        message_vision(msg, me, target);
        me->add_temp("apply/attack", count);

        me->add("neili", -200);
        j = random(6);
        if (j < 3) j = 3;
   for (i = 0; i < 6; i++)
	{
		if (! me->is_fighting(target))
			break;
                if (random(3) == 0 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me,target,me->query_temp("weapon"));
	}

        target->start_busy(1);
        me->start_busy(1 + random(4));
        me->add_temp("apply/attack", -count);

        return 1;
}
