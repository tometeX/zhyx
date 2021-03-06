//updated by kasumi
#include <ansi.h>
#include <combat.h>

#define DAIZONG "「" HIC "岱宗如何" NOR "」"

inherit F_SSERVER;
string attack1(object me, object target, int damage);

int perform(object me, object target)
{           
		int ap, dp;
		int damage;
		string msg;
		object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(DAIZONG "只能对战斗中的对手使用。\n");
  

        if (! objectp(weapon = me->query_temp("weapon"))
           || (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" DAIZONG "。\n");


        if (me->query_skill("wuyue-shenjian", 1) < 250)
                return notify_fail("你的五岳神剑修为不够，难以施展" DAIZONG "。\n");

        if (me->query("neili") < 1000)
                return notify_fail("你的真气不够，难以施展" DAIZONG "。\n");

        if (me->query_skill_mapped("sword") != "wuyue-shenjian")
                return notify_fail("你没有激发五岳神剑，难以施展" DAIZONG "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");	
				
		if (target->query_temp("daizong"))
                return notify_fail("对方现在已经无力防御，放胆攻击吧。\n");

              
		msg=HIM "\n只见$N" HIM "右手"+weapon->name()+HIM"斜指而下，左手五指正在屈指而数，从一数到五，握而成拳，"
			     HIM"又将拇指伸出，次而食指，终至五指全展，似乎在进行一种复杂的心算！\n" NOR;

        ap = me->query_skill("sword") + me->query("int") * 20;
		dp = target->query_skill("dodge") +  target->query("int") * 12; 
	
        if (ap * 3 / 4 + random(ap) > dp)
        {        	
           damage = ap*7 + random(ap*4);
           me->start_busy(1+random(3));
           me->add("neili", -500);
                
          msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100,
                                   (: attack1, me, target, damage :));    
                        		
        } else
	      {
	       	msg = HIG "只见$n" HIG "并不慌张，只是轻轻一闪，就躲过了$N"
	               HIG "这一击！\n"NOR;
	         me->start_busy(2+random(3));
           me->add("neili", -400);
	      }

		message_vision(msg, me, target);
	return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;
		object weapon = me->query_temp("weapon");

		msg = HIR "\n$N微微一笑，左手胸有成竹地一握，右手" + weapon->name()+ HIR "电光火石般刺向$n破绽要害！\n"
			        HIR "只听”噗嗤“一声，$n已被刺中要害！\n" NOR;           

        if (! target->query_temp("daizong"))
        {
                msg += HIM "$n只觉得四肢麻木，如同灌了铅一般，无力动弹。\n" NOR;
	
                target->add_temp("apply/parry", -400);
                target->add_temp("apply/dodge", -400);
                target->set_temp("daizong", 1);
        }
        call_out("daizong_end", 10 + random(15), me, target);
        return msg;
}

void daizong_end(object me, object target)
{
        if (target && target->query_temp("never_juemie"))
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "深深吸入一口气，脸色由"
                                        "白转红，看起来好多了。\n" NOR, target);                       
                }                
                target->add_temp("apply/parry", 400);
                target->add_temp("apply/dodge", 400);
                target->delete_temp("daizong");
        }
        return;
}
