// an.c 太极拳「按」字诀
// Modify by haiyan

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (userp(me) && ! me->query("can_perform/taiji-quan/an")) 
                return notify_fail("你还不会使用「按」字诀。\n"); 

        if (! target || ! me->is_fighting(target))
                return notify_fail("「按」字诀只能对战斗中的对手使用。\n");

        if (objectp(me->query_temp("weapon")))
                return notify_fail("你必须空手才能使用「按」字诀！\n"); 
                
        if ((int)me->query_skill("taiji-quan", 1) < 400)
                return notify_fail("你的太极拳不够娴熟，不会使用「按」字诀。\n");
                                
        if ((int)me->query("neili", 1) < 300)
                return notify_fail("你现在真气太弱，不能使用「按」字诀。\n");
                        
        msg = HIG "$N" HIG "双拳上下挥动，使出太极拳「按」字诀，$n"
              HIG "感到一股强大的劲力从头顶压落。\n" NOR;
        me->add("neili", -200);

        if (random(me->query_skill("force")) > target->query_skill("force") / 2)
        {
                me->start_busy(3);
                target->start_busy(random(3));
                damage = (me->query("qi",1) + me->query("jing",1) * 2 + 
                         me->query("shen",1) / 500 + me->query("neili",1)) / 20; 
                damage = damage + random(damage / 3);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                           damage, 50,
                                           HIY "$n" HIY "登感呼吸不畅，胸闷难当，"
                                           HIY "喉头一甜，狂喷数口"HIR"鲜血"HIY"！\n"
                                           ":内伤@?");
        } else 
        {
                me->start_busy(3);
                msg += HIY "$p" HIY "急运内功，聚劲于外，挺身硬接了$P"
                       HIY "这一招，“砰”的一声巨响，双方各自震退数步！\n" NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}

