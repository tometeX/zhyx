// youming.c

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int di);

int exert(object me, object target)
{
        int skill;
        int di;
        object weapon;

        if (target != me)
                return notify_fail("你只能用幽冥庄提升自己的战斗力。\n");

		if ((int)me->query_skill("linji-zhuang", 1) < 180)
                return notify_fail("你的临济十二庄火候不够，难以施展幽冥庄。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_temp("youming"))
                return notify_fail("你已经运起幽冥庄了。\n");
		if (!me->query_temp("weapon"))
                return notify_fail("你必须装备兵器才能运行幽冥庄。\n");

        skill = me->query_skill("force");

        me->add("neili", -100);
        me->receive_damage("qi", 0);

        if (me->query("reborn")) di = skill / 2; else di = skill / 4;
        
        if (objectp(weapon = me->query_temp("weapon")))
        {
                if (di <= 100)
					message_combatd(MAG "$N" MAG "默运内力，就见那" +
                                        weapon->name() + MAG "隐隐透出一股光芒，闪烁不定。\n" NOR, me);                      
                if (di <= 200 && di>100 )
                        message_combatd(MAG "$N" MAG "潜运内力，只见" +
                                             weapon->name() + MAG "闪过一道光华，气势摄人，令人肃穆。\n" NOR, me);
                 if (di >= 200)             
                message_combatd(MAG "$N" MAG "脸色一沉，运起幽冥庄，霎时间" +
                                    weapon->name() + MAG "光华四射，漫起无边杀意。\n" NOR, me);
        }        
        me->add_temp("apply/damage", di);
        me->set_temp("youming", 1);
        me->start_call_out((: call_other,__FILE__, "remove_effect", me, di :), skill);

        if (me->is_fighting()) me->start_busy(3);

        return 1;
}

void remove_effect(object me, int di)
{
        if (me->query_temp("youming"))
        {              
                me->add_temp("apply/damage", -di);
                me->delete_temp("youming");
                tell_object(me, "你的幽冥庄运行完毕，将内力收回丹田。\n");
        }
}
