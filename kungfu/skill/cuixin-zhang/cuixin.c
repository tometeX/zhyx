#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage, lvl;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("夺命催心只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon"))
                return notify_fail("你必须是空手才能使用夺命催心！\n");
 
        lvl = me->query_skill("cuixin-zhang", 1);

        if (lvl < 120)
                return notify_fail("你的催心掌还不够纯熟！\n");

        if (me->query_skill("force") < 120)
                return notify_fail("你的内功火候太低，无法使出夺命催心。\n");

        if (me->query("neili") < 800)
                return notify_fail("你的内力不够，无法使出夺命催心。\n");
 
        msg = HIR "$N" HIR "聚气于掌，仰天一声狂啸，刹那间双掌交错，一招"
                  "「夺命催心」带着阴毒内劲直贯$n" HIR "！\n"NOR;

        ap = me->query_skill("strike") + lvl;

        if (living(target))
              dp = target->query_skill("parry");
        else  dp = 1;

        if ( ap / 2 + random(ap) > dp + random(dp) )
        {
        me->add("neili", -300);
        damage = lvl * 4 + random(lvl);
        target->affect_by("cuixin_zhang",
                ([ "level" : me->query("jiali") + random(me->query("jiali")),
                "id"    : me->query("id"),
                "duration" : lvl / 50 + random(lvl / 20) ]));
        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70, 
               HIR "只听$n" HIR "惨叫一声，只感两耳轰"
               "鸣，目不视物，喷出一大口鲜血，软软瘫倒。\n" NOR);

        me->start_busy(2);
        target->start_busy(1 + random(2));
        }
    else
        {
        msg += HIY "$p见$P来势汹涌，急忙纵身一跃而起，躲开了这致命的一击！\n" NOR;
        me->add("neili", -300);
        me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

