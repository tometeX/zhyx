// po.c 太极拳「破」字诀

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("「破」字诀只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用「破」字诀！\n");         
                
        if ((int)me->query_skill("taiji-quan", 1) < 150)
                return notify_fail("你的太极拳不够娴熟，不会使用「破」字诀。\n");
                                
        if ((int)me->query("neili", 1) < 200)
                return notify_fail("你现在真气太弱，不能使用「破」字诀。\n");
                        
        msg = HIW "$N" HIW "默运太极神功，使出太极拳「破」字诀，双拳缓缓打向$n"
              HIW "的小腹。\n" NOR;
        me->add("neili", -100);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2 || !living(target))
        {
                me->start_busy(3);
                target->start_busy(random(3));
                target->add("neili", -400);
                damage = (int)me->query_skill("force");
                damage += random(damage / 2) + me->query("jiali");
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 30,
                                           HIR "这一拳看似平淡无奇，但气劲封了$n"
                                           HIR "所有的退路，一拳正好命中！\n"
                                           ":内伤@?");
        } else 
        {
                me->start_busy(3);
                msg += CYN "可是$p" CYN "看破了$P"
                       CYN "的企图，急收小腹，向后纵开。\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

