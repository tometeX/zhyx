 // sandou 银蛇三抖

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string perform_name() {return HIY"银蛇三抖"NOR;}

int perform(object me, object target)
{
      int lv,ap,dp,fp,pp,damage;
	  string msg;
      object weapon;

      weapon = me->query_temp("weapon");
      lv = me->query_skill("yinshe-bianfa",1);
 
      if( !target ) target = offensive_target(me);
     
      if( !target
       || !me->is_fighting(target) )
            return notify_fail("「银蛇三抖」只能在战斗中对对手使用。\n");

      if(!weapon
       || weapon->query("skill_type") != "whip"
       || me->query_skill_mapped("whip") != "yinshe-bianfa")
            return notify_fail("你手里没有鞭，无法使用「银蛇三抖」！\n");             

      if((int)me->query_skill("yinshe-bianfa",1) < 200 )
            return notify_fail("你的银蛇鞭法不够娴熟，不能使用「银蛇三抖」！\n");

        if((int)me->query("neili") < 500 )
            return notify_fail("你的内力太少，不能使用「银蛇三抖」！\n");
      
      message_vision(HIY"\n$N连续抖动手中鞭子，"+weapon->query("name")+HIY+"循着诡异的途径向$n袭去！\n"NOR, me,target);
	    ap = me->query_skill("whip");
        dp = target->query_skill("dodge",1);
        fp = target->query_skill("force",1);
        pp = target->query_skill("parry",1);

		 msg = HIM "$N" HIM "将内力全都运到了鞭上，呼的一鞭，当头直抽。\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "斜身闪开。\n" NOR;
        else
        {
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70 + random(10),
                                           HIR "$n" HIR "急忙后退，竟然躲避不及，被$N"
                                           HIR "这一鞭抽得血肉模糊，接连后退。\n" NOR);
        }

        msg += HIM "\n$N" HIM "一抖手中" + weapon->name() + HIM "，鞭子想长了眼睛似的，反转抽向$n，令人匪夷所思。\n" NOR;
        if (ap / 2 + random(ap) < fp)
                msg += CYN "$n" CYN "纵身从鞭上越过。\n" NOR;
        else
        {
                damage = ap + random(ap / 2);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(10),
                                           HIR "此招来势当真快及，$n" HIR "哪里来得及闪"
                                           "避招架？只见$N" HIR "长鞭掠过，$n"
                                           HIR "腰间霎时鲜血淋漓！\n" NOR);
        }

        msg += HIM "\n$N" HIM "再抖了抖手腕，"+ weapon->name()+ HIM "直奔$n后心，速度之快，部位之准，当真闻所未闻。\n" NOR;
        if (ap / 2 + random(ap) < pp)
                msg += CYN "$n" CYN "身在空中，不及变招，只能挥出一招，正击中$N"
                       CYN "鞭上，略一借力，飘然避去。\n" NOR;
        else
        {
                damage = ap + random(ap);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(10),
                                           HIR "$n" HIR "身在空中，哪里来得及变招？只见$N"
                                           HIR "此鞭抽过，$n" HIR "大声惨呼，鲜血四下飞溅！\n" NOR);
        }

		me->add("neili", -300);
        me->start_busy(3);
        message_combatd(msg, me, target);

      return 1;
}
