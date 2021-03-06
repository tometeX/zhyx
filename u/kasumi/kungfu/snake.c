// powerup.c 修罗阴煞功驱蛇 by Kasumi

#include <ansi.h>
inherit F_SSERVER;

void snake_hit(object me, object target);

int exert(object me, object target)
{
	int skill;
	object weapon;

	if (target != me)
		return notify_fail("你只能放蛇在自己的兵器上。\n");

	if ( !objectp(weapon = me->query_temp("weapon")))
               return notify_fail("你必须装备兵器才能让蛇缠在上面。\n");

	if ((int)me->query("neili") < 500 )
		return notify_fail("你的内力不够无法驱蛇。\n");

	if ((int)me->query_temp("snake"))
		return notify_fail("你已经驱了蛇在兵器上了。\n");

	skill = me->query_skill("xiuluo-yinshagong",1)/10;
	me->add("neili", -100);
	me->receive_damage("qi", 0);

	message_combatd(HIM "$N" HIM "拿出一根竹管轻轻地吹了起来，只听“嗖”的一声，一条怪蛇窜到了" + weapon->name()+ HIM"缠了起来！\n" NOR, me);
	me->set_temp("snake", skill);
    call_out("snake_hit",1, me,target);
	if (me->is_fighting()) me->start_busy(3);

	return 1;
}

void snake_hit(object me, object target)
{
    object weapon;
	if (me->query_temp("snake") > 0)
	{
		me->set_temp("snake", me->query_temp("snake") - 1 );
		if (me->is_fighting())
		{
		}
		else
		{
			message_combatd(HIM "$N" HIM "手中" + weapon->name()+ HIM"上门缠绕着一条怪蛇，“丝丝”地吐着"HIR"红信"HIM"！\n" NOR, me);
		}
		remove_call_out("snake_hit");
		call_out("snake_hit",1, me,target);
		return;
	}
	else 
	{
	    me->delete_temp("snake");
		message_combatd(HIY "$N" HIY "手中" + weapon->name()+ HIM"上门缠绕的怪蛇，“嗖”的一声窜到地上不见了踪影"！\n" NOR, me);
		return;
	}
	
}

