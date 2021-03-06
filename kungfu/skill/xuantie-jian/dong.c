// updated by kasumi 2007/3/30
#include <ansi.h>
#include <combat.h>

#define DONG "「" HIG "大江东去" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        int damage;
        int ap, dp, www;
        string wp, msg;

        //if (userp(me) && ! me->query("can_perform/xuantie-jian/dong"))
        //        return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DONG "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" DONG "。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的内功火候不够，难以施展" DONG "。\n");

        wp = weapon->name();

        if ((int)me->query_skill("xuantie-jian", 1) < 180)
                return notify_fail("你的玄铁剑法不够娴熟，难以施展" DONG "。\n");

       // if ((int)weapon->query_weight() < 25000
       //     && ! weapon->is_item_make() && ! environment(me)->query("biwutai") )
       //         return notify_fail("你手中的" + wp + "分量不够，难以施展" DONG "。\n");

        if ((int)me->query("neili") < 400)
                return notify_fail("你现在的内力不足，难以施展" DONG "。\n");

        if (me->query_skill_mapped("sword") != "xuantie-jian")
                return notify_fail("你没有激发玄铁剑法，难以施展" DONG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIW "$N" HIW "暗自凝神，顿时一股气劲由身后澎湃迸发，接着单"
              "手一振，手中" + wp + HIW "\n随即横空卷出，激得周围尘沙腾起"
              "，所施正是玄铁剑法「" HIG "大江东去" HIW "」。\n"NOR;

        
        www=(int)weapon->query_weight()/100;
        if (www>250) www=250;
        if (www<80) www=80;
        ap = me->query_skill("sword") + me->query("max_neili")/100 + www;        
        dp = target->query_skill("force") + target->query("max_neili")/100;
        
        if (ap * 2 / 3 + random(ap) > dp)
        {
                target->start_busy(1);
                damage = ap*2 + random(ap);
                me->add("neili", -250);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                           HIR "结果$n" HIR "奋力招架，却被$N" HIR
                                           "这一剑震的飞起，口中鲜血狂吐不止！\n" NOR);
				me->start_busy(2 + random(3));
        } 
 		else if ( me->query("str") > random(target->query("str")*2) ) 
        {
               msg += HIY"$N一剑击出，右手长袖顺势拂去，$n顷刻间只感五脏六腑都似翻转了，站在当地，\n"
			          HIY"既不敢运气，也不敢移动半步，便如僵了一般。\n"NOR;
             if (! target->is_busy())
             target->start_busy(3+random(4));
             me->start_busy(2+random(2));
        }		
		else if (ap / 3 + random(ap) > dp)
		{
		  msg += HIC"$N只觉对方冲撞而来的劲力绵绵不绝，越来越强,运出所有内力振臂一击。\n" NOR;
		  me->add("neili", -300);
          target->add("neili", -1000);
          me->start_busy(1+random(2));
             if (! target->is_busy())
          target->start_busy(1+random(2));
		} 
		else
		{
			msg += CYN "可是$n" CYN "看破了$N" CYN "的企图，急忙斜跃避开。\n"NOR;
            me->add("neili", -150);
			me->start_busy(2+random(2));
		}
        message_combatd(msg, me, target);


        return 1;
}



