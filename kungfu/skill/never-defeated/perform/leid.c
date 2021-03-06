// lei.c 天打雷劈

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
	      string msg,str;
        int level,damage,n,ap,dp;
 
	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
	        return notify_fail("天打雷劈只能在战斗中对对手使用。\n");

	if (me->query_skill("never-defeated", 1) < 220)
		return notify_fail("你的不败神功还不够娴熟，不能使用天打雷劈！\n");

        if (! objectp(weapon = me->query_temp("weapon")))
                return notify_fail("你必须手持兵刃才能施展天打雷劈！\n");

	if (me->query("neili") < 500)
		return notify_fail("你的真气不够！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("never-defeated", 1) * 3 / 2 + me->query_skill("martial-cognize", 1);
        dp = target->query_skill("parry") + target->query_skill("martial-cognize", 1);

      if (ap * 3/ 5 + random(ap * 2) > dp)

     {
     	   msg = HIC "$N" HIC "大喝一声，手中的" + weapon->name() +
              HIC "长劈而下，看似简单，竟然封住了$n"
              HIC "所有的退路！\n" NOR;
        msg += HIR "$n" HIR"无法参透其玄机，惨嚎伴随飞溅的鲜血在空气中回荡......\n"NOR;


        level = me->query_skill("never-defeated", 1);
        
        
        if (level < 1000)  {target->receive_wound("qi", target->query("qi")/2000,me);}
        else if (level < 1200) {target->receive_wound("qi", target->query("qi")/1500,me);}
        else {target->receive_wound("qi", target->query("qi")/1200,me);}                   
        
        
	      str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	      msg += "($n"+str+")\n";
	      me->add("neili", -300);
	      me->start_busy(4 + random(4));
        message_combatd(msg, me, target);

             	return 1;
        }
        
  else 
  	  {
  	  	message_combatd(HIG"$n轻轻一跳，避过了$N这一招", me, target);
         me->add("neili", -300);
	      me->start_busy(2 + random(4));
	    }

}
