// powerup.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

        if (target != me)
                return notify_fail("你只能用神照经神功提升自己的战斗力。\n");

        if ((int)me->query("neili") < 200)
                return notify_fail("你的内力不够了。");

        if ((int)me->query_temp("powerup"))
                return notify_fail("你已经在运功中了。\n");

        skill = me->query_skill("force");

        me->add("neili", -200);
        me->receive_damage("qi", 0);

        message_combatd(HIR "$N" HIR "凝聚神照经功力，只听全身骨骼劈里啪啦"
                        "一阵爆响，面色赤红，煞是惊人。\n" NOR, me);

        if (me->query("breakup"))
        {    
	     me->add_temp("apply/attack", skill * 2 / 3);
	     me->add_temp("apply/defense", skill / 3);
	     me->add_temp("apply/parry", skill / 5);
	     me->add_temp("apply/dodge", skill / 5);
	     me->add_temp("apply/unarmed_damage", skill / 4);
        }
        else
        {
	     me->add_temp("apply/attack", skill / 3);
	     me->add_temp("apply/defense", skill / 4);
	     me->add_temp("apply/parry", skill / 5);
	     me->add_temp("apply/dodge", skill / 5);	    
        }

        me->set_temp("powerup", 1);
        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, skill:), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int amount)
{
        if ((int)me->query_temp("powerup"))
        {
             if (me->query("breakup"))
             {
	        me->add_temp("apply/attack", - (amount * 2 / 3));
 	        me->add_temp("apply/defense", - (amount / 3));
	        me->add_temp("apply/parry", - (amount / 5));
	        me->add_temp("apply/dodge", - (amount / 5));
	        me->add_temp("apply/unarmed_damage", -(amount / 4));
             }
             else
             {
 	        me->add_temp("apply/attack", - (amount / 3));
 	        me->add_temp("apply/defense", - (amount / 4));
	        me->add_temp("apply/parry", - (amount / 5));
	        me->add_temp("apply/dodge", - (amount / 5));  	               
             }
                me->delete_temp("powerup");
                tell_object(me, "你的神照经神功运行完毕，将内力收回丹田。\n");
        }
}
