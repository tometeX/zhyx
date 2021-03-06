// jie.c 华山剑法「截手式」

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int level, dp;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("华山剑法「截手式」只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if(me->query_skill_mapped("sword") != "huashan-sword") 
                return notify_fail("你并未使用华山剑法，无法使出「截手式」！\n");

        if (target->is_busy())
                return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");
                
        if ((level = me->query_skill("huashan-sword", 1)) < 60)
                return notify_fail("你的华山剑法不够娴熟，不会使用「截手式」。\n");

        if (me->query("neili") < 80)
                return notify_fail("你现在真气不够，无法使用「截手式」。\n");

        msg = HIW "但见$N" HIW "长剑一勒，使出华山剑法绝技之"
              "“截手式”，转折之际天衣无缝，\n一剑既出，后着"
              "源源倾泻，如大浪跃滩，层层叠叠，迅然扑向$n"
              HIW "！\n" NOR;

        me->add("neili", -40);

        if (living(target))
                dp = target->query_skill("parry", 1) / 2;
        else    dp = 0;

        if (random(level) > dp)
        {
                msg += HIR "结果$p" HIR "瘁不及防，连连倒退"
                       "几步，一时间无法回手！\n" NOR;
                target->start_busy(level / 30 + 1);
        } else
        {
                msg += CYN "但是$p" CYN "识破了$P" CYN "的用意，"
                       "自顾将手中的剑舞成一团剑圈，$P"
                       CYN "一怔之下再也攻不进去。\n" NOR;

                me->start_busy(5);
        }
        message_combatd(msg, me, target);

        return 1;
}

