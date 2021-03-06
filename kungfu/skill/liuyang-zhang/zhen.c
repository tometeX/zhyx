
// zhen.c 一掌震天

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;



#define ZHEN "「" HIY "一掌震天" NOR "」"

int perform(object me, object target)
{
        int ap, dp, damage;
        string msg, pmsg;
        
         if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }
	    if (! target || ! me->is_fighting(target))
                return notify_fail(ZHEN "只能对战斗中的对手使用。\n");

        if ((int)me->query_skill("bahuang-gong", 1) < 250)
                return notify_fail("你八荒六合唯我独尊功火候不够，难以施展" ZHEN "。\n");

        if ((int)me->query_skill("liuyang-zhang", 1) < 300)
                return notify_fail("你的天山六阳掌不够娴熟，难以施展" ZHEN "。\n");

        if (me->query("max_neili") < 3500)
                return notify_fail("你的内力修为不足，难以施展" ZHEN "。\n");

        if (me->query_skill_mapped("strike") != "liuyang-zhang")
                return notify_fail("你没有激发天山六阳掌，难以施展" ZHEN "。\n");

        if (me->query_skill_prepared("strike") != "liuyang-zhang")
                return notify_fail("你没有准备天山六阳掌，难以施展" ZHEN "。\n");

        if (me->query_skill_mapped("force") != "bahuang-gong")
                return notify_fail("你没有激发八荒六合唯我独尊功，难以施展" ZHEN "。\n");

        if (me->query("neili") < 800)
                return notify_fail("你现在真气不足，难以施展" ZHEN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");


        msg = HIW" \n只见$N" HIW "忽然掌缘隐隐泛出殷红之色，丝丝白气缭绕其间，转瞬间已将$P的手掌包了起来。\n" +
             "待得此时，$n" HIW "已觉不妙，哪知正待闪躲，$N" HIW "这招「" HIY "一掌震天" HIW "」已然推至胸前，来势虽\n" +
             "缓，但$p只觉身周的空气仿佛已经凝结，这一掌之力已将上下左右前后包了起来，实是难\n"+
             "以摆脱。瞬间的空气流动直如一个真空大洞，使得身周的人均觉得一阵气滞！\n\n"NOR;

        ap = me->query_skill("force") + me->query_skill("strike") + me->query_skill("dodge") + me->query_skill("parry");
        dp = target->query_skill("force")*2 + target->query_skill("parry") + target->query_skill("dodge");
             
        if (ap *2/3 + random(ap) > dp)
        {
                damage = ap+random(ap/2);
                me->add("neili", -500);

                pmsg = HIR "$n" HIR "眼见$N" HIR "一招已至，掌劲如洪，内力澎湃，然而苦于身陷旋涡之中，避无可避，只是\n" +
                       "稍微挪动脚步也已困难之极，结果被$N" HIR "一掌印在胸前，登感一阵痛入骨髓，却是肋骨被\n" +
                       "这一掌之力震断，气血翻涌已然失控，一口鲜血如箭般从口鼻中喷了出来！\n\n" NOR;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100, pmsg);
                
                me->start_busy(2);      
        } else
        {
                msg += HIG "岂料$n" HIG "机敏异常，一眼道破$N" HIG "这招的破绽之处乃是旋涡的中心，其间极为薄弱，于是\n"+
                       "单手成指，竟刺破$N" HIG "的旋涡屏障，接连两指点在$P手心的" HIR "少府"
                       HIG "、" HIR "劳宫" HIG "二穴！结果$N" HIG "穴道被\n" +
                      "封，这内力无处宣泄，竟反蚀其身，震得$P脸如金纸，口唇紫青，差点受了内伤！\n\n" NOR;

                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

