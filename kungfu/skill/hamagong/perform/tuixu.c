// tui.c 推天式之蓄

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int n;

        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("蛤蟆功「推天式」之蓄式只能对战斗中的对手使用。\n");

        if ( objectp(me->query_temp("weapon")) )
	         return notify_fail("你手持兵器，无法施展蛤蟆功的绝技。\n");
	         
	      if (!(int)me->query_temp("tuitimes"))
                return notify_fail("你必须先运起蛤蟆功的「推天式」了。\n");
                
        msg = HIG "$N" HIG "又“嗝”的一声大叫，两个腮帮子再一鼓，脸上一道绿光闪过......\n" NOR;   
        n=me->query_temp("tuitimes");
        n=n+1;
        me->set_temp("tuitimes",n);
		if (me->query("qi") < me->query("eff_qi"))
		{
		    me->add("qi", me->query_skill("hamagong", 1)*2);
		}
        message_combatd(msg, me, target);
         me->start_busy(1);
        return 1;
}
