// 截剑式 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg,name;
        int ap, dp;
        int damage;
		object equipment;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("截剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用截剑式？\n");
		
	if (target->is_busy())
		return notify_fail(target->name() + "目前正自顾不暇，放胆攻击吧！\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("你现在的真气不够，无法使用截剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 200)
		return notify_fail("你的独孤九剑还不到家，无法使用截剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用截剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");
		damage = me->query_skill("lonely-sword",1) * 10;
		
        msg = HIC "但见$N" HIC "长剑一勒，忽的使出独孤九剑"HIM"“截剑式”"HIC"，一剑既出，如大浪跃滩，层层叠叠然扑向$n"HIC"。\n" NOR;       
		
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
		                           HIR "$n" HIR "眼前一花，瞬间已中数剑！\n" NOR);
		if (random(5)>1){
			msg += HIR "$n" HIR "中剑后经脉受损，连连倒退几步，一时间无法回手！\n" NOR;		 
			target->start_busy(3 + random(7));
		}
		
		me->start_busy(2);
		me->add("neili", -300);
	
	message_combatd(msg, me, target);

	return 1;
}
