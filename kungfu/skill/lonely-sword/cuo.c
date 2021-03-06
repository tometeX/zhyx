// 挫剑式 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	    object weapon;
        string msg, wp;
        int ap, dp;
        int damage;
		object weapon2;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("挫剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用挫剑式？\n");

	if ((int)me->query("neili") < 500)
		return notify_fail("你现在的真气不够，无法使用挫剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 400)
		return notify_fail("你的独孤九剑还不到家，无法使用挫剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用挫剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "手中长剑肆意挥洒，忽的使出独孤九剑"HIM"“挫剑式”"HIC"，手中长剑以匪夷所思的角度攻向$n"HIC"。\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 10;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "急忙招架，哪知$N"HIR"的长剑不可思议的从缝隙中破招而入，顿时刺出一个血窟窿！\n" NOR);
		
		message_combatd(msg, me, target);
		if (objectp(weapon2 = target->query_temp("weapon")) && random(3)==1)
		{
			  wp = weapon2->name();                                                        
              weapon2->set("consistence", 0);									 
              weapon2->move(environment(me));
		      message_combatd(HIC "只听“啪”的一声脆响，$n" HIC "手"
                                                "中的" + wp + HIC "在$N" HIC "剑气激荡"
                                                "下应声而碎，脱手跌落在地上。\n" NOR, me, target);                                      
		}  		
		me->start_busy(2);
		me->add("neili", -300);
	

	return 1;
}
