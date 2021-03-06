// tui.c 推天式之发

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        int n,damage;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「推天式」之发式只能对战斗中的对手使用。\n");

        if ( objectp(me->query_temp("weapon")) )
	         return notify_fail("你手持兵器，无法施展蛤蟆功的绝技。\n");
	         
	      if (!(int)me->query_temp("tuitimes"))
                return notify_fail("你必须先运起蛤蟆功的「推天式」了。\n");
      
        n=me->query_temp("tuitimes");        
                
        msg = HIY"$N"HIY"“阁阁”的大叫数声，运起蛤蟆功劲力，双腿一弯双掌齐发，向前推出......\n"
              HIG"这一推实乃$N"HIG"毕生功力之所聚，$n猛然感受到山洪海啸般的劲力袭来。\n" NOR;   
        msg += HIM"$N"HIM"第一推刚完，第二推又已迅速异常的赶到，前劲未衰，后劲继至，一连推了"HIG""+chinese_number(n)+HIG""HIM"次。\n" NOR;
        
        damage = me->query_skill("force")* n;
        damage += random(damage/2);
		
		if (n>10)
		{
		     msg +=  HIR "$n" HIR "奋力低档，但是$N" HIR "的来势何等浩大，$n"HIR"吐出一口鲜血后如同断线的风筝般飞了出去。\n" NOR;		
		     target->receive_wound("qi", damage, me);
			 str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));			
			 msg += "($n"+str+")\n";
		}
		else
		{        
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage,100,
                                         HIR "$n" HIR "奋力低档，但是$N" HIR "的来势何"
                                         "等浩大，$n" HIR "登时觉得气血不畅，“哇”的"
                                          "吐出了一口鲜血。\n" NOR);
		}
        
        
        message_combatd(msg, me, target);
        me->delete_temp("tuitimes");
        me->start_busy(2+random(4));
        return 1;
}
