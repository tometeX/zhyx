// 落剑式 by kasumi

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
		return notify_fail("落剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用落剑式？\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你现在的真气不够，无法使用落剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 800)
		return notify_fail("你的独孤九剑还不到家，无法使用落剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用落剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "挟剑猛然欺近$n" HIC "，电光火石间突然飞身跃起，一剑劈下，正是独孤九剑"HIM"“落剑式”"HIC"。\n" NOR;

        damage = me->query_skill("lonely-sword",1) * 6;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(30),
		                           HIR "$n" HIR "急忙变招防御，可惜为时已晚，长剑从头上的“百汇穴”经“任督二脉”到丹田的\n"
								   HIR"“气海穴”划过，$n"HIR"重伤之余，真气涣散！\n" NOR);
		
		message_combatd(msg, me, target);
		if (random(2)==1){
			target->set("neili",0);
		}else{
			target->add("neili",-target->query("neili")*2/3);
		}
		me->start_busy(2)+random(3);
		me->add("neili", -300);
	

	return 1;
}
