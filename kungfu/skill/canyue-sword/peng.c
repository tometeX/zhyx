//lian.c 众星捧月
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, count,skill;
        skill = (int)(me->query_skill("sword"));       
        i = 4 + (int)me->query_skill("canyue-sword",1)/50;
        if (i > 12)
        	i=12;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("「众星捧月」只能在战斗中对对手使用。\n");        

        if (!objectp(weapon = me->query_temp("weapon")) )
                return notify_fail("你必须使用武器才能使用「众星捧月」！\n");

        if ((string)weapon->query("skill_type") != "sword")
                return notify_fail("你没有用剑，无法使用「众星捧月」！\n");

        if(me->query_skill_mapped("sword") != "canyue-sword") 
                return notify_fail("你没有用残月剑法，无法使用「众星捧月」！\n");

        if( (int)me->query_skill("canyue-sword", 1) < 250 )
                return notify_fail("你的残月剑法还不够娴熟，使不出「众星捧月」绝技。\n");

        if( (int)me->query_skill("force") < 300 )
                return notify_fail("你的内功等级还不够，使不出「众星捧月」绝技。\n");

        if( (int)me->query("max_neili") < 3000 )
                return notify_fail("你的内力修为需要进一步提高，才能使出「众星捧月」这招。\n");

        if( (int)me->query("neili") < 500 )
                return notify_fail("你现在真气太弱，还敢使用「众星捧月」？\n");


        msg = HIM "\n$N" HIM "傲然一笑，手中"+ weapon->name() + HIM "挽出一个完美的满月，周围点点星光灿烂闪烁，俨然一幅「众星捧月」的美景。\n"
              HIM "忽然间星图变幻，万千星光护着一道朦胧华丽的月光向" HIM "$n" HIM "不断电射而去。\n" NOR;

        message_combatd(msg, me, target);
        
        count=skill/5;
        
        me->add_temp("apply/damage", count/2);
        me->add_temp("apply/attack", count);
        me->set_temp("canyue-sword/max_pfm", 1);

        while (i--)
        {
                if (! me->is_fighting(target))
                        break;
                if (! target->is_busy() && random(2)==1)
                        target->start_busy(1);                
                COMBAT_D->do_attack(me, target, weapon, 0);
                me->add("neili", -30);
        }

        me->start_busy(3+random(4));      
        
        me->add_temp("apply/damage", -count/2);
        me->add_temp("apply/attack", -count);
        me->delete_temp("canyue-sword/max_pfm");

        return 1;
}

