// 破剑式 by kasumi

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
 
int perform(object me, object target)
{
	object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target)
        {
	        me->clean_up_enemy();
	        target = me->select_opponent();
        }

	if (! target || ! me->is_fighting(target))
		return notify_fail("破剑式只能对战斗中的对手使用。\n");
 
	if (! objectp(weapon = me->query_temp("weapon")) ||
	    (string)weapon->query("skill_type") != "sword")
		return notify_fail("无剑如何运用破剑式？\n");

	if ((int)me->query("neili") < 1000)
		return notify_fail("你现在的真气不够，无法使用破剑式！\n");

	if ((int)me->query_skill("lonely-sword", 1) < 200)
		return notify_fail("你的独孤九剑还不到家，无法使用破剑式！\n");

	if (me->query_skill_mapped("sword") != "lonely-sword") 
		return notify_fail("你没有激发独孤九剑，无法使用破剑式！\n");

       if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIC "$N" HIC "窥出$n"HIC"的破绽，狡黠一笑，忽的使出独孤九剑"HIM"“破剑式”"HIC"，一剑精妙无比地刺向$n"HIC"。\n" NOR;

        damage = me->query_int() * me->query_skill("lonely-sword",1)/6;
        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60+random(15),
		                           HIR "$n" HIR "身处破绽，全然无法阻挡$N" HIR "这精妙的一招，剑锋过肉，鲜血迸流！\n" NOR);
		me->start_busy(1);
		me->add("neili", -400);
	
	message_combatd(msg, me, target);

	return 1;
}
