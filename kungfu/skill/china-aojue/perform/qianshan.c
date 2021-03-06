// qianshan.c 龙跨千山

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define QIANSHAN "「" HIC "龙跨千山" NOR "」"

int perform(object me, object target)
{
	string msg;
        int ap, dp;
        int i, count;
        object weapon;

        /*if (userp(me) && ! me->query("can_perform/china-aojue/qianshan"))
                return notify_fail("你所使用的外功中没有这种功能。\n");*/

	if (! target) target = offensive_target(me);

	if (! target || ! me->is_fighting(target))
		return notify_fail(QIANSHAN "只能对战斗中的对手使用。\n");

        if (!objectp(weapon = me->query_temp("weapon")) )
                return notify_fail("此招需要持兵器施展！\n");

	if ((int)me->query_skill("china-aojue", 1) < 250)
		return notify_fail("你的中华傲诀不够深厚，不会使用" QIANSHAN "。\n");	

       if (me->query_skill_mapped("sword") != "china-aojue") 
                return notify_fail("你没有激发中华傲诀为剑法，难以施展" QIANSHAN "。\n");

	if ( me->query("neili") < 700 )
		return notify_fail("你的内力不够，不能使用" QIANSHAN "。\n");

        if (! living(target))
              return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        ap = me->query_skill("china-aojue", 1);
        dp = target->query_skill("dodge", 1);


        msg = HIC "$N" HIC"手中"+ weapon->name() +HIC"灌注强横内力暴射，访如神龙吐信，跨越千重山峰，\n"
                  "气势之猛，震古烁今。正是中华傲诀第二式:"+HIG"龙跨千山！\n" NOR;   
        message_combatd(msg, me, target);         
        count = ap;
        me->add_temp("apply/attack", count);	
        me->add_temp("apply/damage", count);
        for (i = 0; i < 16; i++)
        {
                if (! me->is_fighting(target))
                        break;
                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);
                        
               COMBAT_D->do_attack(me, target, weapon, 0);
        }
        me->add("neili", -40);
        me->start_busy(2 + random(5));     

        me->add_temp("apply/attack", -count);
        me->add_temp("apply/damage", -count);
	 

	return 1;
}
