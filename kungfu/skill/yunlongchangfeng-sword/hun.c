// hun.c 云龙长风

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("yunlongchangfeng-sword", 1);

        if (! me->is_fighting(target))
                return notify_fail("云龙长风只能对战斗中的对手使用。\n");

        if(me->query_skill_mapped("sword") != "yunlongchangfeng-sword") 
                return notify_fail("你没有用云龙长风剑法，无法使用云龙长风绝招！\n");

        if (skill < 100)
                return notify_fail("你的云龙长风剑法等级不够，练好了再来！\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对。\n");

        if (me->query("neili") < 500)
                return notify_fail("你的内力不够。\n");
        
        ap = me->query_skill("sword") + me->query_skill("force");
        ap += me->query("jiali");
        ap += me->query("jianu");

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIY "$N" HIY "腾身而起，宛如飞龙般向$n猛卷而去，手中" + weapon->name() + 
               HIY "瞬间劈出无数招，如同狂风暴雨。\n" NOR;

        message_combatd(msg, me, target);

        n = (int)me->query("tianmo_jieti/times");
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        msg = HIY "\n天地突然黯淡下来，整个空间寂静无声，诡异地让人感到不安。\n"
              "$N" HIY "在空中飘浮，混身发着金光，突然" + weapon->name() + HIY "如一道闪电，劈向了$n。\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIR "$n" HIR "惊惶失措，急切间匆忙抵挡，却为时已晚！\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
		str = COMBAT_D->status_msg((int)target->query("qi") * 100 /(int)target->query("max_qi"));
		msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIW "$n" HIW "急晃身形，险险避开，却也惊出一身冷汗。\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(me->query("id")) ) target->kill_ob(me);
	me->add("neili",-damage/3);
        return 1;
}


