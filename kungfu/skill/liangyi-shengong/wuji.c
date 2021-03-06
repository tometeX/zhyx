// 日月无极
//created by kasumi

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill,lv;
		skill = me->query_skill("chess",1);

		if (skill<300)
		      return notify_fail("你弈棋之道不够纯熟，无法运功。\n");
			  
        if (target != me)
                return notify_fail("你只能用日月无极来提升自己的有效招架。\n");

        if ((int)me->query("neili") < 150)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("kl/wuji"))
                return notify_fail("你已经在运功中了。\n");
		if ((int)me->query_temp("kl/taxue"))
                return notify_fail("你已经运起了踏雪无痕，无法同时再运用日月无极了。\n");

        
        me->add("neili", -100);
        me->receive_damage("qi", 0);
		message_vision(HIW "$N微一凝神，运起两仪心法，只见$N全身被一团真气围绕。\n" NOR, me);        
        me->add_temp("apply/parry", skill / 3);       
        me->set_temp("kl/wuji", 1);

		if ( (lv = me->query_skill("chess", 1)) >= 200 && me->query("family/family_name") == "昆仑派")
		{
			if (me->can_improve_skill("liangyi-shengong"))
			me->improve_skill("liangyi-shengong", lv * 2);
		}

        me->start_call_out((:call_other, __FILE__, "remove_effect", me, skill / 3:), skill);
        if (me->is_fighting()) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("kl/wuji"))
        {
                me->add_temp("apply/parry", -amount);               
                me->delete_temp("kl/wuji");
                tell_object(me, "你的日月无极运行完毕，将内力收回丹田。\n");
        }
}