#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int perform(object me, object target)
{
        int skill;
        
        if (userp(me) && ! me->query("can_perform/jinzhong-zhao/zhao"))
                return notify_fail("你所使用的外功中没有这种功能。\n");      

        if ((int)me->query("neili") < 400)
                return notify_fail("你的内力不够。\n");

        if ((int)me->query_skill("jinzhong-zhao", 1) < 150)
                return notify_fail("你的[金刚罩]修为不够。\n");

        if ((int)me->query_temp("jinzhongzhao"))
                return notify_fail("你已经运起[金刚罩]作为护体神功了。\n");

	 if ((int)me->query_temp("jingangbuhuai"))
                return notify_fail("你已经运起金刚不坏护体神功了。\n");

        skill = me->query_skill("force");
        me->add("neili", -300);
        me->receive_damage("qi", 0);

        message_combatd(HIW "只听$N" HIW "仰天暴喝一声，全身猛然一抖，一股无形真气迅速游经八"
                            "脉罩住全身\n随即蔓向向四周，刹时间四周飞沙走石，烟尘滚滚!。\n" NOR, me);

        me->add_temp("apply/armor", skill / 4);
        me->add_temp("apply/force", skill / 5);
        me->set_temp("jinzhongzhao", 1);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);

        if (me->is_fighting()) me->start_busy(4);

        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("jinzhongzhao"))
        {
                me->add_temp("apply/armor", -(amount / 4));
                me->add_temp("apply/force", -(amount / 5));
                me->delete_temp("jinzhongzhao");
                tell_object(me, "你的[金刚罩]护体神功运行完毕，将内力收回丹田。\n");
        }
}

