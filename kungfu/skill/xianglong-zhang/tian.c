#include <ansi.h>
#include <combat.h>

#define TIAN "「" HIW "龙翔九天" NOR "」"
#define TIANA "「" HIR "亢龙有悔" HIW "」"
#define TIANB "「" HIG "震惊百里" HIW "」"
#define TIANC "「" HIB "双龙取水" HIW "」"
#define TIAND "「" HIY "飞龙在天" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i, count;

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/hui"))
                return notify_fail("你尚未学会「"HIR"亢龙有悔"NOR"」无法领会"TIAN"。\n");

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/zhen"))
                return notify_fail("你尚未学会「"HIG"震惊百里"NOR"」无法领会"TIAN"。\n");

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/qu"))
                return notify_fail("你尚未学会「"HIB"双龙取水"NOR"」无法领会"TIAN"。\n");

        if (userp(me) && ! me->query("can_perform/xianglong-zhang/fei"))
                return notify_fail("你尚未学会「"HIY"飞龙在天"NOR"」无法领会"TIAN"。\n");

	if (! me->query("reborn"))        
		return notify_fail("你尚未转世重生，无法领会此绝招！\n");

        if ((int)me->query("str") < 46)
                return notify_fail("你的先天膂力孱弱，难以施展"TIAN"。\n");

        if ((int)me->query("con") < 42)
                return notify_fail("你的先天根骨孱弱，难以施展"TIAN"。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(TIAN "只能空手使用。\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("你内功修为不够，难以施展" TIAN "。\n");

        if ((int)me->query("max_neili") < 10000)
                return notify_fail("你内力修为不够，难以施展" TIAN "。\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 400)
                return notify_fail("你降龙十八掌火候不够，难以施展" TIAN "。\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("你没有激发降龙十八掌，难以施展" TIAN "。\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("你没有准备降龙十八掌，难以施展" TIAN "。\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("你现在真气不够，难以施展" TIAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        // 第一掌
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("dodge") + target->query("dex") * 15;

        message_sort(HIW "\n忽然$N" HIW "身形激进，左手一划，右手竟使出一招"
		    TIANA "以排山倒海之势向$n" HIW "狂涌而去。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(20),
                                          HIR "$N身形一闪，竟已晃至$n跟前，$n躲"
                                          "闪不及，顿被击个正中。\n" NOR);
        } else
        {
                msg = HIC "却见$n气贯双臂，凝神应对，$N掌"
                      "力如泥牛入海，尽数卸去。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第二掌
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query("str") * 15;

        message_sort(HIW "\n$N" HIW "一掌既出，身子已然抢到离$n" HIW "一"
                     "丈之外，后掌推前掌两股掌力道合并，使出" TIANB
                     "不顾一切般击向$n" HIW "。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "$n一声惨嚎，被$N这一掌击中胸前，"
                                          "喀嚓喀嚓断了几根肋骨。\n" NOR);
        } else
        {
                msg = HIC "可是$n全力抵挡招架，竟似游刃有"
                      "余，将$N的掌力卸于无形。\n" NOR;
        }
        message_vision(msg, me, target);

        // 第三掌
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("force") + target->query("con") * 15;

        message_sort(HIW "\n紧跟着$N" HIW "右掌斜挥，前招掌力未消，此招掌"
                     "力又到，一式" TIANC "双掌上下晃动，如一堵无形气"
		     "墙，向$n" HIW "疾冲而去。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "结果$n躲闪不及，$N掌劲顿时穿胸而"
                                          "过，顿时口中鲜血狂喷。\n" NOR);
        } else
        {
                msg = HIC "$n眼见来势凶猛，身形疾退，瞬间"
                      "飘出三丈，脱出掌力之外。\n" NOR;
        }
        message_vision(msg, me, target);

        // 连击
        ap = me->query_skill("strike") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query("int") * 15;

        msg = HIW "\n$N" HIW "连击三掌后突然跃至空中，居高临下使出" TIAND "双掌翻滚扑向$n"HIW"。\n" NOR;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "面对$N" HIR "这排山倒海般的攻"
                       "势，完全无法抵挡，招架散乱，连连退后。\n" NOR;
                count = ap / 8;
        } else
        {
                msg += HIC "$n" HIC "心底微微一惊，心知不妙，急忙"
                       "凝聚心神，竭尽所能化解$N" HIC "数道掌力。\n" NOR;
                count = ap / 20;
        }
        message_vision(msg, me, target);

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
	target->start_busy(3 + random(5));
        me->add("neili", -2000 - random(1000));
        me->start_busy(3 + random(5));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 2);

        return 1;
}
