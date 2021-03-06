// 浪剑式 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg,msg1;
        int ap, dp, i;
        int damage;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("你只能对战斗中的对手使用绝招。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用浪剑式？\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你现在的真气不够，无法使用浪剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 500)
		return notify_fail("你的独孤九剑还不到家，无法使用浪剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用浪剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "气运丹田，长剑往前一荡，正是独孤九剑"HIM"“浪剑式”"HIC"，霎时剑气激荡，如层层海浪激向$n"HIC"。\n" NOR;
        message_sort(msg, me, target);
		for (i = 0; i < 6; i++)
		{
		   msg1=HIY"              第"+chinese_number(i+1)+HIY"浪！\n"NOR;
		  
		   damage = me->query_skill("lonely-sword",1)*3/2;
		   damage = damage + random(damage/2);
		   if (me->query("character") == "狡黠多变"){
				damage = damage * 1.25;
		   }
		   msg1 += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "完全无法抵御，为$N" HIR "的剑气所伤，“哇”地吐出一口鲜血！\n" NOR);	
		   message_combatd(msg1, me, target);
		}
		if (me->query("character") == "狡黠多变"){
				me->start_busy(3);
		   }else{
				me->start_busy(3+random(4));
		}
		me->add("neili", -600);	

	return 1;
}
