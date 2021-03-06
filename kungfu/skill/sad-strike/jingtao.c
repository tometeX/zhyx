// updated by Kasumi
     
#include <ansi.h>

inherit F_SSERVER; 
       
int perform(object me, object target) 
{ 
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail( "「怒海惊涛」只能在战斗中对对手使用。\n");
 
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail( "「怒海惊涛」只能空手使用。\n");

		 if (me->query("family/family_name") != "古墓派")     
                return notify_fail("只有古墓弟子才能用「怒海惊涛」。\n");     

        if( me->query_skill_mapped("force") != "surge-force" )
                return notify_fail("你所用内功的并非怒海狂涛，使不出「怒海惊涛」！\n");

        if( (int)me->query_skill("surge-force",1) < 400 )
                return notify_fail("你内功修为太差，不能运用「怒海惊涛」！\n");

        if( me->query_skill("sad-strike",1) < 400 )
                return notify_fail("你黯然销魂掌修为太差，不能运用「怒海惊涛」！\n");
	
        if( (string)me->query_skill_mapped("unarmed") != "sad-strike")
		return notify_fail("你并没有激发黯然销魂掌作为掌法。\n");

        if( (string)me->query_skill_prepared("unarmed") != "sad-strike")
		return notify_fail("你并没有准备黯然销魂掌。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        if( me->query("neili") < 1200 )
                return notify_fail("你的内力不够使用「怒海惊涛」！\n");

        ap = me->query_skill("force") + me->query_skill("unarmed") + me->query_skill("dodge") + me->query_skill("parry") ;
	dp = target->query_skill("force") + me->query_skill("unarmed") + target->query_skill("dodge") + target->query_skill("parry");

     msg = HIW"\n$N的掌风隐隐带着潮涌之声，掌风鼓荡，竟似有狂潮涌来，这正是神雕大侠当年在海边练出的绝技。\n"NOR;
	
	 if (ap + random(ap) > dp)
	{
		msg += HIR"$n哪里躲避得开，大惊下已经给$N的掌风印上胸口，一口鲜血狂喷而出！\n"NOR;

		target->receive_wound("qi",ap+random(ap),me);
		str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n" ;		
         if (! target->is_busy()) 
			target->start_busy(1);
	} else
	{
		msg +=CYN"$n见状不妙，立刻就地一个打滚，虽然姿势难看以及，不过总算避开了$N这一掌。\n"NOR;
	}
      message_combatd(msg, me, target);


    msg = HIW"\n$N在掌风达到顶峰之时，跟着“魂不守舍”、“倒行逆施”、“若有所失”，连出三招。\n"NOR;
	
	if (ap + random(ap) > dp)
	{

		msg +=HIR"$n惊魂未定，正喘气之际，不提防又一阵猛烈的气浪扑面冲来，复遭$N掌风重创！\n"NOR;
		target->receive_wound("qi",ap+random(ap),me);
		str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n" ;		
		
             if (! target->is_busy()) 
			target->start_busy(1);
	} else
	{
		msg += CYN"$n顾不得反击，急身后退三丈，脸颊给$N的掌风扫到，微微发红，不过总算避开了$N这三掌。\n"NOR;
	}
	message_combatd(msg, me, target);
	
         msg = HIW "\n跟着$N腾身而起，一招“行尸走肉”，闪电般踢出一脚。\n"NOR;

	if (ap + random(ap) > dp)
	{
		msg += HIR"$n眼看着这霸气冲天的一脚，已然放弃了抵抗，整个脸部给$N重重踹上，牙齿皆碎，面目血色狰狞！\n"NOR;
		target->receive_wound("qi",ap*3/2+random(ap),me);
		str =  COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n" ;		
		
                if (! target->is_busy()) 
			target->start_busy(1);
	} else
	{
		msg += CYN"$n双足点地，拔天而起，从$N的头顶掠过，脚下劲气呼啸而过，真是险之又险！\n"NOR;
	}
	message_combatd(msg, me, target);

        me->add("neili",-1000);
	    me->start_busy(2+random(3));

        return 1;
}        
