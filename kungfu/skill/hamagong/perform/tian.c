// 蟾震九天
// wrote by kasumi 2009.6
#include <ansi.h>

inherit F_SSERVER;
void tie_hit(object me, object target);
#define TIAN "「" HIG "蟾震九天" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int count;
        int i;
       

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(TIAN "只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail(TIAN "只能空手使用。\n");
                
        if ((int)me->query("neili") < 500)
                return notify_fail("你当前内力不足，无法施展" TIAN "。\n");

        if ((int)me->query_skill("hamagong", 1) < 350)
                return notify_fail("你的蛤蟆功火候不够，无法施展" TIAN "。\n");

        if ((int)me->query_skill("force") < 500)
                return notify_fail("你的内功修为不够，无法施展" TIAN "。\n");

        if (me->query_skill_prepared("unarmed") != "hamagong")
                return notify_fail("你现在没有准备使用蛤蟆功，无法施展" TIAN "。\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

	    ap = me->query_skill("force") + me->query_skill("unarmed");
        dp = target->query_skill("force") + target->query_skill("dodge");
		
	    msg = HIM "$N一声清啸，全身劲气迸发，蛤蟆神功已然提到极致！只见$N双腿一登，双掌相并\n" ;   
	    msg += HIM "向前猛力推出，$n连同身前方圆三丈全在"HIG"「蟾震九天」"HIM"劲力笼罩之下！\n" ; 
		
		if (ap * 3 / 5 + random(ap) > dp)
		{
          msg += HIY "$n大吃一惊，慌乱中强行接下这一掌。只觉得对方内力滚滚而来，立即运气抵抗。\n" NOR;    
          message_combatd(msg, me, target);    
          target->start_busy(3);
	      me->start_busy(3);
          call_out("tie_hit",1, me,target);
		}
		else
		{
		 msg += HIC "$n" HIC "不敢小觑$N" HIC "的来招，腾挪躲闪，终于跳出了蛤蟆神功的气劲笼罩。\n" NOR;
		 me->start_busy(3+random(3));
		 me->add("neili", -200);
         message_combatd(msg, me, target); 
        }		 
		

        return 1;
}

void tie_hit(object me, object target)
{
	int sum, n1, n2;
	string msg;

	if( !target || !me->is_fighting(target) ) return;

	if( !living(me) || me->is_ghost() ) return;

	if( !target || environment(me) != environment(target) || !me->is_fighting() ) return;

	sum = me->query_skill("force") + me->query_skill("unarmed") + target->query_skill("force") + target->query_skill("parry");
	n1 = me->query("neili");
	n2 = target->query("neili");

	me->add("neili", -100 * sum / me->query_skill("force",1) ); 
	if(me->query("neili")<0)me->set("neili",0);

	target->add("neili", -150 * sum / target->query_skill("force",1));
	if(target->query("neili")<0)target->set("neili",0);

	if( n1 > 3000 && n2 > 3000) {
		msg = HIW"此时双方掌力均极强劲，欲分胜负，非使对方重创不可。\n"NOR;

		if( n1 > n2 )
		msg += HIW"二人又僵持一会，$n头顶透出一缕缕的白气，渐渐越来越浓，就如蒸笼一般。\n"NOR;
		else msg += HIW"二人又僵持一会，$N头顶透出一缕缕的白气，渐渐越来越浓，就如蒸笼一般。\n"NOR;
	}

	else {

		if( n1 > n2 ) msg = HIY"$N不断催动蛤蟆功猛劲，毫无衰颓迹象。稍过片刻，$n已是全身大汗淋漓。\n"NOR;
		else msg = HIY"$N脸上黑气大盛，将蛤蟆功发挥到了极致。稍过片刻，$N已是全身大汗淋漓。$n似乎依然中气十足，头顶热气蒸蒸而上。\n"NOR;
		}

	message_combatd(msg , me,target );


	if( me->query("neili") > 0 && target->query("neili") > 0 && me->is_busy() && target->is_busy() && living(me) && living(target) )
	{
		target->start_busy(3);
		me->start_busy(3);
		remove_call_out("tie_hit");
		call_out("tie_hit",1, me,target);
		return;
	}

	if( target->query("neili") <= 0 )
	{
	    msg = HIR "\n$n突然喘不过气来，全身发抖，原来内力已全部耗尽。突闻前胸一片骨裂之声，\n";
		msg += HIR"已被蛤蟆功一掌击中，哼也哼不出一声，一头栽倒在地，生死难料。\n\n" NOR;
		message_combatd(msg , me,target );
		target->unconcious();  
		return;
	}

	if( me->query("neili") <= 0 )
	{
		message_vision(HIR "\n$N脸上黑气大作，突然喘不过气来，全身发抖，原来内力已全部耗尽。蛤蟆功立时全部反弹回来，\n"
		                    "但闻前胸一片骨裂之声，哼也哼不出一声，一头栽倒在地，生死难料。\n\n" NOR, me);
	    me->unconcious();   
	}
}