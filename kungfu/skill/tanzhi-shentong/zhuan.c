#include <ansi.h>
#include <combat.h>

#define ZHUAN "「" HIR "转乾坤" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (userp(me) && ! me->query("can_perform/tanzhi-shentong/zhuan"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(ZHUAN "只能对战斗中的对手使用。\n");

        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(ZHUAN "只能空手施展。\n");

        if ((int)me->query_skill("tanzhi-shentong", 1) < 220)
                return notify_fail("你的弹指神通不够娴熟，难以施展" ZHUAN "。\n");

        if ((int)me->query_skill("qimen-wuxing", 1) < 200)
                return notify_fail("你的奇门五行修为不够，难以施展" ZHUAN "。\n");
 
        if (me->query_skill_mapped("finger") != "tanzhi-shentong")
                return notify_fail("你没有激发弹指神通，难以施展" ZHUAN "。\n");
                
       if (me->query_skill_mapped("force") != "bibo-shengong")
                return notify_fail("你没有激发碧波神功，难以施展" ZHUAN "。\n");

        if (me->query_skill_prepared("finger") != "tanzhi-shentong")
                return notify_fail("你没有准备弹指神通，难以施展" ZHUAN "。\n");

        if (me->query("max_neili") < 3500)
                return notify_fail("你的内力修为不足，难以施展" ZHUAN "。\n");

        if (me->query("neili") < 800)
                return notify_fail("你现在的真气不够，难以施展" ZHUAN "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "将全身功力聚于一指，指劲按照二十八宿方位云贯而出，正"
              "是桃花岛「" HIR "转乾坤" HIC "」绝技。\n" NOR;

        ap = me->query_skill("bibo-shengong",1)+
             me->query_skill("finger", 1) +
             me->query_skill("qimen-wuxing", 1) +
             me->query_skill("tanzhi-shentong", 1);

        dp = target->query_skill("force",1) +
             target->query_skill("dodge",1) +
             target->query_skill("parry", 1) +
             target->query_skill("qimen-wuxing", 1);

        if (ap * 2/3 + random(ap) > dp)
             {
                damage = 0;
                if (me->query("max_neili") > target->query("max_neili") * 2)
                {
                	me->start_busy(2);
                        msg += HIR "霎那间$n" HIR "只见寒芒一闪，$N" HIR "食指"
                               "已钻入$p" HIR "印堂半尺，指劲顿时破脑而入。\n"
                               HIW "你听到“噗”的一声，身上竟然溅到几滴脑浆！"
                               "\n" NOR "( $n" RED "受伤过重，已经有如风中残烛"
                               "，随时都可能断气。" NOR ")\n";
                        damage = -1;
                 }
             }   
                
               dp = target->query_skill("force",1)*3 + target->query_skill("qimen-wuxing", 1); 
                 
         if (ap * 3 / 4 + random(ap) > dp)
        {        damage=ap;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 65,
                                           HIG "\n$n不精奇门五行，顿时受创,只听“嗤啦”的一声，$n" HIG
                                           "躲闪不及，指气点中身上死穴，飞出一蓬"
                                           "血雨。\n" NOR);
        } else
        {
                msg += CYN "\n$n" CYN "见$N" CYN "来势汹涌，急忙飞身一跃而"
                       "起，避开了这一击。\n" NOR;
        }

               dp = target->query_skill("dodge",1)*3 +target->query_skill("qimen-wuxing", 1);
     
        if (ap * 2 / 3 + random(ap) > dp)
        {  damage=ap*2;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                           HIW "\n只听$n" HIW "一声惨嚎，被$N" HIW
                                           "的指气点中了要害，血肉模糊，鲜血迸流不"
                                           "止。\n" NOR);
        } else
        {
                msg += CYN "\n$n" CYN "见$N" CYN "来势汹涌，急忙飞身一跃而"
                       "起，避开了这一击。\n" NOR;
        }
                   dp = target->query_skill("parry",1)*3 +target->query_skill("qimen-wuxing", 1);
      
        if (ap * 3 / 5 + random(ap) > dp)
        {  damage=ap*3;
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIY "\n$n" HIY "奋力招架，仍是不敌，双眼渐渐失去光彩,生命好像要消失在冥冥乾坤之中\n\n$N"
                                           "的" HIY "无形指气已透体而入，$n鲜血飞射"
                                           "，无力再战。\n" NOR);
        } else
        {
                msg += CYN "\n$n" CYN "见$N" CYN "来势汹涌，急忙飞身一跃而"
                       "起，避开了这一击。\n" NOR;
        }
                            
                
              
                me->start_busy(4);
                me->add("neili", -400);
                       
        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);

        return 1;

}