// daxiao.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;        

        if (target != me)
                return notify_fail("你只能用大小庄提升自己的战斗力。\n");

		if ((int)me->query_skill("linji-zhuang", 1) < 150)
                return notify_fail("你的临济十二庄火候不够，难以施展大小庄。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("daxiao"))
                return notify_fail("你已经在运功中了。\n");
		if ((int)me->query_temp("longhe"))
                return notify_fail("你正在运行龙鹤庄中，不能运行大小庄。\n");
		if ((int)me->query_temp("fengyun"))
                return notify_fail("你正在运行风云庄中，不能运行大小庄。\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);        

        message_combatd(HIY "$N" +HIY "席地而坐，五心向天，运行天地二庄，益气升阳，益阴潜阳，升降反正，天地二气交泰于身。\n" NOR, me);

        if (me->query_skill("jinzhong-zhao", 1) )
			me->add_temp("apply/force", skill / 5);    
		else
            me->add_temp("apply/force", skill / 3);       
        me->set_temp("daxiao", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("daxiao"))
        {       
		     if (me->query_skill("jinzhong-zhao", 1) )
				 me->add_temp("apply/force", -amount/5);
			 else
				 me->add_temp("apply/force", -amount/3);              
                me->delete_temp("daxiao");
             tell_object(me, "你的大小庄运行完毕，将内力收回丹田。\n");
        }
}
