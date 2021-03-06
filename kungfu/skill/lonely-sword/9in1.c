// 九式合一 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	    object weapon;
        string msg, wp,name;
        int ap, dp;
        int damage;
		object weapon2;
		object equipment;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("独孤九剑之九式合一只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用九式合一？\n");

	if ((int)me->query("neili") < 2000)
		return notify_fail("你现在的真气不够，无法使用挫剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 900)
		return notify_fail("你的独孤九剑还不到家，无法使用独孤九剑之九式合一！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用九式合一！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "大喝一声“看招！”，忽的手中剑光暴涨，独孤九剑九式剑招连绵而出！\n" NOR;

        damage = me->query_skill("lonely-sword",1);
                damage  = damage + random (damage);

		msg += HIM"                      破剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIG"                      浪剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIY"                      撩剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIR"                      落剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIC"                      挫剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIW"                      截剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIY"                      荡剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 110,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIG"                      离剑式！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 120,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);
		msg += HIG"                      九式合一！\n" NOR;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 130,
		                           HIR "$n" HIR "只觉的剑光闪耀，眩晕只见顿时被刺出一个血窟窿！\n" NOR);								   
		
		
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

		if (objectp(equipment = target->query_temp("armor/hands")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "身上的" + name + HIW "被划破跌落在地。\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/cloth")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "身上的" + name + HIW "被划破跌落在地。\n" NOR, me, target);
		}
		if (objectp(equipment = target->query_temp("armor/armor")) && random(3)==1)
		{
		  name = equipment->name();      
		  equipment->move(environment(me));
		  message_combatd(HIW "$n" HIW "身上的" + name + HIW "被划破跌落在地。\n" NOR, me, target);
		}
		
		if (! target->query_temp("lonely_dang") && me->query("character") == "狡黠多变" && random(3)==1)
        {           
                target->add_temp("apply/force", -500);
                target->add_temp("apply/parry", -500);
                target->add_temp("apply/dodge", -500);
                target->set_temp("lonely_dang", 1);
        		msg = HIM "$n只觉得恍如灵魂出窍，全身的力气竟似一丝丝远离自己而去，无助之极。\n" NOR;
				message_combatd(msg, me, target);
				call_out("dang_end", 5 + random(8), me, target);		
		}
		
		if (me->query("character") == "狡黠多变" && random(4)==1){
				target->set("neili",0);
		}		
		me->start_busy(3+random(4));
		me->add("neili", -1500);
	

	return 1;
}

void dang_end(object me, object target)
{
        if (target && target->query_temp("lonely_dang"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口气，脸色由"
                                        "白转红，看起来好多了。\n" NOR, target);                       
                }                
                target->add_temp("apply/force", 500);
                target->add_temp("apply/parry", 500);
                target->add_temp("apply/dodge", 500);
                target->delete_temp("lonely_dang");
        }
        return;
}
