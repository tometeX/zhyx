#include <ansi.h>
#include <combat.h>

#define HUI "「" HIR "毁"BLU"天"HIM"灭"HIW"地" NOR "」"

inherit F_SSERVER;

int perform(object me, object target)
{
    int skill = (int)me->query_skill("kuihua-mogong", 1), i;
    string msg;
    int ap, dp;
    int damage;

    if( !target || target == me ) target = offensive_target(me);
    if( environment(me)->query("no_fight") )
	return notify_fail("这里不准打架。\n");
    if( !target || target==me || !target->is_character() )
	return notify_fail(HUI"只能对对手使用。\n");
    if (userp(me) && ! me->query("can_perform/kuihua-mogong/hui"))
	return notify_fail("你所使用的外功中没有这种功能。\n");
    if (skill < 200 || (int)me->query_skill("kuihua-mogong", 1) < 200)
	return notify_fail("以你目前的修为来看，还不足以运用"HUI"\n");
    if (me->query("max_neili") < 2000)
	return notify_fail("你的内力修为不够运用"HUI"所需！\n");
    if (me->query("neili") < 500)
	return notify_fail("你的内力不够运用"HUI"所需！\n");

    me->start_busy(1 + random(3));
    msg = "$N开始使用葵花魔功的终极绝招----"HUI "\n"HIW"$N眼神莹然有光，似乎进入了魔境之中。\n";

    if (me->query("can_perform/kuihua-mogong/miedi")){

	msg += "$n邪邪的看着$N，不知不觉中$n表现出万分的恐惧。\n"NOR;
	msg += HIM"\n$N猛然想到了什么，$n立刻开始无限痛苦的呻吟起来！\n\n"NOR;

	ap = me->query_skill("kuihua-mogong", 1) * 3 + me->query("dex") * 20 +
	me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query("dex") * 20 +
	target->query_skill("martial-cognize", 1);

	me->start_busy(2);
	me->add("neili", -400);

	if (ap / 2 + random(ap) < dp)
	{
	    msg += HIG "然而$n" HIG "抵挡得法，将$N" HIG
	    "的攻势一一化解。\n" NOR;
	} else
	{
	    me->add("neili",-560);
	    damage = ap * 2 + random(ap * 3 / 4) - 60 - random(40);
	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
	      HIY "$n" BLU "只觉得已经跌入了万劫魔域之中，"HIY"$N"
	      WHT "如同地狱幽灵一样手舞足蹈，从九九八十一个方位杀了过去！\n" NOR);
	}

	message_combatd(msg, me, target);

    } else {
	msg += "$n邪邪的看着$N，不知不觉中$n表现出万分的恐惧。\n"NOR;
	msg += HIM"\n$N猛然想到了什么，$n立刻开始无限痛苦的呻吟起来！\n\n"NOR;

	ap = me->query_skill("kuihua-mogong", 1) * 1 + me->query("dex") * 10 +
	me->query_skill("martial-cognize", 1);
	dp = target->query_skill("parry") + target->query("dex") * 20 +
	target->query_skill("martial-cognize", 1);

	me->start_busy(2);
	me->add("neili", -400);

	if (ap / 2 + random(ap) < dp)
	{
	    msg += HIG "然而$n" HIG "抵挡得法，将$N" HIG
	    "的攻势一一化解。\n" NOR;
	} else
	{
	    me->add("neili",-260);
	    damage = ap * 1 + random(ap * 1 / 5) - 60 - random(40);
	    msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
	      HIY "$n" BLU "只觉得已经跌入了万劫魔域之中，"HIY"$N"
	      WHT "如同地狱幽灵一样手舞足蹈，从九九八十一个方位杀了过去！\n" NOR);
	}

	message_combatd(msg, me, target);

    }
    if(!me->is_fighting(target)) me->fight_ob(target);
    if(!target->is_fighting(me)) target->fight_ob(me);
    remove_call_out("checking");
    call_out("checking", 1, me);
    return 1;
}



