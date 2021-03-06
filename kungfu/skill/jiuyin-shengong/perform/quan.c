// quan 九阴无极劲
// created by kasumi
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define QUAN "「" HIW "九阴无极劲" NOR "」"
 
int perform(object me, object target)
{
	string msg,str;
	int ap, dp;
        int damage;

        if (! target)
        {
        	me->clean_up_enemy();
        	target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail(QUAN "只能对战斗中的对手使用。\n");

	if (me->query_skill("jiuyin-shengong", 1) < 220)
		return notify_fail("你的九阴神功还不够娴熟，不能使用" QUAN "！\n");

	        if (me->query("neili") < 1500)
                return notify_fail("你的内力不够，不能使用" QUAN "！\n");

        if (me->query_temp("weapon"))
                return notify_fail("此招只能空手施展！\n");

        if (me->query_skill_prepared("unarmed") != "jiuyin-shengong"
           && me->query_skill_prepared("cuff") != "jiuyin-shengong")
                return notify_fail("你没有准备使用九阴神功，无法施展" QUAN "。\n");
 
       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	msg = HIC "$N" HIC "一声冷哼，左手握拳击出，招式雄浑，难擢其威！\n" NOR;
 
	ap = me->query_skill("jiuyin-shengong", 1) + me->query_skill("martial-cognize", 1) + me->query_skill("force", 1);
        dp = target->query_skill("jiuyin-shengong", 1) + target->query_skill("martial-cognize", 1) + target->query_skill("parry", 1);

        
        me->add("neili", -100);
		damage = me->query_skill("force") + me->query_skill("unarmed") + me->query_str() * 25;

        if (ap * 3/4 + random(ap) > dp)
        {
			if (me->query_skill("jiuyin-shengong", 1) > 500)
			{
			   damage = damage + random(damage/2);
			   target->receive_wound("qi", damage, me);
	           str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
	           msg += HIR "$n" HIR "连忙格挡，可是这一拳力道何等之重，哪里抵挡得住？只被打得吐血三尺，连飞三丈！\n" NOR;
			   msg += "($n"+str+")\n";
			   me->add("neili",-500); 
				if (me->query("reborn")) {
					msg += HIC "$N" HIC "再次冷哼，右手握拳击出，招式雄浑，难擢其威！\n" NOR;
					damage = damage + random(damage);
					target->receive_wound("qi", damage, me);
					str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
					msg += HIR "$n" HIR "连忙格挡，可是这一拳力道何等之重，哪里抵挡得住？只被打得吐血三尺，连飞三丈！\n" NOR;
					msg += "($n"+str+")\n";
					me->add("neili",-500); 
					msg += HIC "$N" HIC "第三次冷哼，双拳击出，招式雄浑，难擢其威！\n" NOR;
					damage = damage + random(damage);
					target->receive_wound("qi", damage, me);
					str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
					msg += HIR "$n" HIR "连忙格挡，可是这一拳力道何等之重，哪里抵挡得住？只被打得吐血三尺，连飞三丈！\n" NOR;
					msg += "($n"+str+")\n";
					me->add("neili",-500); 
					me->start_busy(3);
				}
			}
			else
			{
        	me->add("neili",-100);            
            msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 85 + random(15),
                                      HIR "$n" HIR "连忙格挡，可是这一拳力道何等之重，哪里抵"
                                          "挡得住？只被打得吐血三尺，连退数步！\n" NOR);
					me->start_busy(1);
			}
		
        } else
	      {
		            msg += HIG "只见$n" HIG "不慌不忙，轻轻一闪，躲过了$N" HIG "这一击！\n"NOR;
					me->start_busy(2);
	      }

	message_combatd(msg, me, target);
	return 1;
}
