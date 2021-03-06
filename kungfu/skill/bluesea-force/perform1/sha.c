#include <ansi.h>
#include <combat.h>

#define SHA "「" HIW "诛仙刹神" NOR "」"
#define JUAA "「" HIR "斩仙诀" HIY "」"
#define JUAB "「" HIG "诛仙诀" HIM "」"
#define JUAC "「" HIB "戮仙诀" HIC "」"
#define JUAD "「" HIY "玄黄连环掌" HIW "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i, count;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(SHA "只能空手使用。\n");

        if ((int)me->query_skill("force",1) < 400)
                return notify_fail("你内功修为不够，难以施展" SHA "。\n");

        if ((int)me->query("max_neili") < 8000)
                return notify_fail("你内力修为不够，难以施展" SHA "。\n");

        if ((int)me->query_skill("bluesea-force", 1) < 400)
                return notify_fail("你南海玄功火候不够，难以施展" SHA "。\n");

        if (me->query_skill_mapped("strike") != "bluesea-force")
                return notify_fail("你没有激发南海玄功为掌法，难以施展" SHA "。\n");

        if (me->query_skill_mapped("force") != "bluesea-force")
                return notify_fail("你没有激发南海玄功为内功，难以施展" SHA "。\n");

        if (me->query_skill_prepared("strike") != "bluesea-force")
                return notify_fail("你没有准备南海玄功，难以施展" SHA "。\n");

        if ((int)me->query("neili") < 3000)
                return notify_fail("你现在真气不够，难以施展" SHA "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        // 第一掌
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("dodge",1) + target->query_skill("martial-cognize",1);

        if (me->query_skill("bluesea-force",1)>500) me->set_skill("count", 300);
        if (me->query_skill("bluesea-force", 1) > 600) 
                      { 
                              target->map_skill("dodge", 0); 
                      } 

        message_sort(HIY "\n只见$N" HIY "面容肃穆，倏的一掌拍出，竟是一招"
		    JUAA "以雷霆之势拍向$n" HIY "。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 4);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(20),
                                          HIR "$n" HIR "稍一犹豫，被这一掌击了"
                                           "个正中！接连退了几步，吐了一地的血。\n" NOR);
        } else
        {
                msg = HIG "然而$n" HIG "看破了$N" HIG
                       "的掌势，不慌不忙的躲过了这一击！\n" NOR;
        }
        message_vision(msg, me, target);

        // 第二掌
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query_skill("martial-cognize",1);

        message_sort(HIM "\n紧接着$N" HIM "腾空而起，忽地使出一招" JUAB "，掌影疾若奔马，如箭一般飞向$n"
              HIM "速度快的不可思议！\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 4);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "$n" HIR "正在思虑这一掌的后势，掌力已至"
                                           "胸前，只听“噗”的一声，$n吐血三尺！\n" NOR);
        } else
        {
                msg = HIG "然而$n" HIG "看破了$N" HIG
                       "的掌势，不慌不忙的躲过了这一击！\n" NOR;
        }
        message_vision(msg, me, target);

        // 第三掌
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("force") + target->query_skill("martial-cognize",1);

        message_sort(HIC "\n$N" HIC "攻势毫不停滞，第三招" JUAC "携风雷之力，以迅雷不及掩耳之势"
                     "已然向$n" HIC "猛然拍出。\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 4);
		target->start_busy(2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 90 + random(20),
                                          HIR "$n" HIR "不明所以，运功抵挡，只觉得$N的掌力怪"
                                           "异之极，直渗入至奇经八脉，登时吐血不已！\n" NOR);
        } else
        {
                msg = HIG "然而$n" HIG "看破了$N" HIG
                       "的掌势，不慌不忙的躲过了这一击！\n" NOR;
        }
        if (me->query_skill("count",1)>0) me->delete_skill("count"); 
        message_vision(msg, me, target);

        // 连击
        ap = me->query_skill("strike") + me->query_skill("bluesea-force") + me->query("str") * 15;
        dp = target->query_skill("parry") + target->query_skill("martial-cognize",1);

        msg = HIW "\n$N" HIW "冷笑一声，双掌轻轻划了个圈子，身形忽然变快，倏的使出" JUAD "化作无数掌影波浪般向$n"HIW"攻去。\n" NOR;

        if (ap * 2 / 3 + random(ap) > dp)
        {
                msg += HIY "内力激荡之下，$n" HIY "登时觉得呼吸"
                       "不畅，浑身有如重压，万分难受，只见$N"
                       HIY "一掌接一掌的攻到，有如海浪。\n" NOR;
                count = ap / 8;
        } else
        {
                msg += CYN "$n" CYN "见来掌奇快，只好振作精神勉力抵挡。\n" NOR;
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
        me->add("neili", -1000 - random(500));
        me->start_busy(3 + random(5));
        me->add_temp("apply/attack", -count);
        me->add_temp("apply/unarmed_damage", -count / 2);

        return 1;
}
