#include <ansi.h>
#include <combat.h>

#define JUESHA "「" HIW "「九穹绝刹掌」" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int i, ap, dp, pp, count;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("「九穹绝刹掌」只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("「九穹绝刹掌」只能空手使用。\n");
                
        if (me->query("max_neili") < 2200)
                return notify_fail("你的内力修为还不够，无法施展「九穹绝刹掌」。\n");

        if ((int)me->query("neili") < 1200)
                return notify_fail("你的真气不够！\n");

        if ((int)me->query_skill("tie-zhang", 1) < 250)
                return notify_fail("你的铁掌火候不够，无法使用「九穹绝刹掌」！\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功修为不够，无法使用「九穹绝刹掌」！\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("你没有激发铁掌掌法，难以施展「九穹绝刹掌」。\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("你现在没有准备使用铁掌掌法，难以施展「九穹绝刹掌」。\n");

        if (me->query_skill_prepared("cuff") == "tiexian-quan"
            || me->query_skill_prepared("unarmed") == "tiexian-quan" )
                return notify_fail("施展「九穹绝刹掌」时铁掌掌法不宜和铁线拳互背！\n");

        if ((string)me->query_skill_mapped("force") != "tianlei-shengong")
                return notify_fail("你必须激发天雷神功才能施展出「九穹绝刹掌」！\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

                msg = HIC "$N" HIC "一声怒喝，体内几股真气急速运转，双臂陡然暴长数尺。只听破空之声骤响，\n"
                HIC "突然$N" HIC "双掌迎风一挥，幻出万千虚影，这才是铁掌的精华绝招！！！\n" 
                HIC"\n           " HIC"┏━━━━━┓\n"
                HIC"           " HIC"┃九穹绝刹掌┃\n"
                HIC"           " HIC"┗━━━━━┛\n" NOR;

        ap = me->query_skill("strike");
        dp = target->query_skill("parry");
        pp = me->query_skill("tianlei-shengong",1) + me->query_skill("tiezhang-xinfa",1);
        ap += pp / 3;

        if (ap * 2 / 3 + random(ap) > dp)
        { 
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "$n" HIR "勘破不透掌中虚实，$N" HIR
                                           "双掌正中$p" HIR "前胸，“喀嚓喀嚓”接"
                                           "连断了数根肋骨。\n" NOR);
	        message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$n" CYN "见$N" CYN "这掌来势非凡，不敢"
                       "轻易招架，当即飞身纵跃闪开。\n" NOR;
	        message_combatd(msg, me, target);
        }
     
            msg = HIW "紧接着$N" HIW "双臂一震，运转天雷神功，一股浑厚至极的内劲汹涌澎湃，带着排山\n"
                     HIW"倒海之势向$n" HIW "席卷而至。\n" NOR;
	        message_combatd(msg, me, target);

        count = ap / 6;
        me->add_temp("apply/attack", count);
	 me->add_temp("apply/unarmed_damage", count / 2);
              
       
        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);
        	COMBAT_D->do_attack(me, target, 0, i*2);
        }

        me->add("neili", -800);
        me->start_busy(4 + random(3));
        me->add_temp("apply/attack", -count);
		me->add_temp("apply/unarmed_damage", -count / 2);
        return 1;
}


