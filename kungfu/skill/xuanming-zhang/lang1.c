#include <ansi.h>
#include <combat.h>

#define LANG "「" HIM "惊涛骇浪" NOR "」"

inherit F_SSERVER;

string final1(object me, object target, int lvl);
string final2(object me, object target, int lvl);
string final3(object me, object target, int lvl);
string final4(object me, object target, int lvl);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl, p;

        if (userp(me) && ! me->query("can_perform/xuanming-zhang/lang1"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LANG "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(LANG "只能空手施展。\n");

        if ((int)me->query_skill("xuanming-shengong", 1) < 220)
                return notify_fail("你的玄冥神功火候不够，无法施展" LANG "。\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 220)
                return notify_fail("你的玄冥神掌不够熟练，无法施展" LANG "。\n");

        if ((int)me->query("max_neili") < 3000)
                return notify_fail("你的内力修为不足，无法施展" LANG "。\n");

        if (me->query_skill_mapped("force") != "xuanming-shengong")
                return notify_fail("你没有激发玄冥神功为内功，无法施展" LANG "。\n");

        if (me->query_skill_prepared("strike") != "xuanming-zhang")
                return notify_fail("你没有准备玄冥神掌，无法施展" LANG "。\n");

        if ((int)me->query("neili") < 800)
                return notify_fail("你的真气不够，无法施展" LANG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "\n$N" HIW "默运玄冥神功，展出绝招「" HIM "惊涛骇浪" HIW "」，猛然间欺身"
              "向前，双掌齐出，掌风阴寒无比，掌未到，风先至，瞬息间双掌已拍向$n" HIW "！\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);

        //ap = me->query_skill("strike") + me->query_skill("force");
        ap = me->query_skill("strike") + me->query_skill("force")+(int)me->query_skill("dulong-shenzhua",1)/4;
        dp = target->query_skill("dodge") + target->query_skill("force");

        me->start_busy(4);

        // 第一掌

        msg += HIM "\n$N" HIM "右掌向内一转，忽又向前，猛然间直袭$n" HIM "面门。\n" NOR;
        //if (ap  / 2 + random(ap) > dp)
        if (ap *2 / 3 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                me->add("neili", -300);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                          (: final1, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看见$N" HIY "来势汹涌，急忙提气跃开。\n" NOR;
                me->add("neili", -180);
        }
        message_sort(msg, me, target);


        // 第二掌

        msg += HIM "\n$N" HIC "收回掌劲，沉寂一瞬后，忽地左掌携一阵阴风击向$n" HIC "后背。\n" NOR;
        //if (ap  / 2 + random(ap) > dp)
        if (ap *2 / 3 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                me->add("neili", -300);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60,
                                          (: final2, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看见$N" HIY "来势汹涌，急忙提气跃开。\n" NOR;
                me->add("neili", -180);
        }
        message_sort(msg, me, target);


         
        // 第四掌
     if ((int)target->query("qi")> 0&& me->is_fighting(target) && (int)me->query_skill("xuanming-zhang", 1) > 599) 
        {
        msg = HIM "\n$N" HIC "长舒一口气，双掌齐齐推出，阵阵阴风随掌劲而至，$n" HIC "只觉已濒临绝境。\n" NOR;
        //if (ap  / 2 + random(ap) > dp)
        if (ap *3/ 5 + random(ap) > dp)
        { 
                //damage = ap + random(ap / 2);
                damage = ap*2 + random(ap / 2);
                me->add("neili", -400);

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final4, me, target, lvl :));
                                           
        } else
        {
                msg += HIY "$n" HIY "看见$N" HIY "来势汹涌，急忙提气跃开。\n" NOR;
                me->add("neili", -180);
        }
        message_sort(msg, me, target);
        return 1;
}
}

string final1(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         ([ "level" : me->query("jiali") * 10,
                            "id"    : me->query("id"),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "正欲闪躲，却见$N" HIR "突然绕到$p" HIR "身后，$n" HIR "心中一"
                   "惊，背后中掌，顿觉脊梁处一股寒气升起，尽损三焦六脉。\n" NOR;

}

string final2(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         ([ "level" : me->query("jiali") * 10,
                            "id"    : me->query("id"),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "眼见无法闪避，伸出右掌强接此招，$n" HIR "惨叫一"
                   "声，只觉阵阵寒气从掌缘传来，尽损三焦六脉。\n" NOR;

}

string final3(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         ([ "level" : me->query("jiali") * 10,
                            "id"    : me->query("id"),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "勉强迎敌，怎奈还未等$n" HIR "反应过"
                   "来，胸口又中一掌，顿觉呼吸困难，心烦意乱，斗志全失。\n" NOR;

}

string final4(object me, object target, int lvl)
{
        target->affect_by("xuanming_poison",
                         ([ "level" : me->query("jiali") * 10,
                            "id"    : me->query("id"),
                            "duration" : lvl / 40 + random(lvl / 20) ]));

        return HIR "$n" HIR "身受重伤，见$N" HIR "攻势毫无停顿之意，只能长叹一声，硬接下来袭"
               "的致命毒掌，一时间口吐乌血，全身经脉似已断裂。\n" NOR;

}
