#include <ansi.h>
#include <combat.h>

#define TIAN "「" HIY "天刀八势" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage,ap,dp;
        string msg;
        object weapon;
        int i, count;

        if (userp(me) && ! me->query("can_perform/bagua-dao/tian"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "blade")
                return notify_fail("你所使用的武器不对，难以施展" TIAN "。\n");

        if ((int)me->query_skill("bagua-dao", 1) < 200)
                return notify_fail("你的八卦刀法不够娴熟，难以施展" TIAN "。\n");

        if ((int)me->query_skill("wai-bagua", 1) < 200)
                return notify_fail("你的外八卦神功不够娴熟，难以施展" TIAN "。\n");

        if ((int)me->query_skill("nei-bagua", 1) < 200)
                return notify_fail("你的内八卦神功不够娴熟，难以施展" TIAN "。\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("你的内功修为不足，难以施展" TIAN "。\n");

        if ((int)me->query("neili") < 500)
                return notify_fail("你现在真气不够，难以施展" TIAN "。\n");

        if (me->query_skill_mapped("blade") != "bagua-dao")
                return notify_fail("你没有激发八卦刀法，难以施展" TIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_combatd(HIY "$N" HIY "蓦地一振手中" + weapon->name() +
                        HIY "，发出万千龙吟，霎时刀光滚滚，向四面涌出"
                        "，笼罩$n" HIY "全身。\n" NOR, me, target);

        count = me->query_skill("bagua-dao", 1) / 4;

        me->add("neili", -250);
        me->add_temp("apply/attack", count);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(3) == 1 && ! target->is_busy())
                        target->start_busy(1);

                me->add_temp("pfm_tiandao", 1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->add_temp("apply/attack", -count);
        me->delete_temp("pfm_tiandao");
        
        msg = HIR"紧接着" "$N" HIR "仰天狂笑，舞起" + weapon->name() +
              HIR "斜划出一道清光，刀身腾起凛冽"
              "杀气，直贯$n" HIR "而去！\n" NOR;

       
        ap = me->query_skill("blade") + me->query_str() * 10 ;
        dp = target->query_skill("dodge") + target->query_con() * 10;

       
        if (ap * 3 / 5 + random(ap) > dp)
        {               
                damage = ap + random(ap);
                me->add("neili", -300);
              
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                           HIR "只听$n" HIR "一声惨叫，$N" HIR +
                                           weapon->name() + HIR "刀锋一闪，竟已嵌"
                                           "入$p" HIR "体内尺许，带出一蓬血雨。\n"
                                           NOR);
        } else
        {
                me->add("neili", -200);
               
                msg += CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(msg, me, target);

      
        me->start_busy(1 + random(8));
        return 1;
}
