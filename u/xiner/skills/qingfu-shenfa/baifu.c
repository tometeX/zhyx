//by xiner 02/3/2009

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int amount, int amount1);

inherit F_CLEAN_UP;

int perform(object me, object target)
{
        object weapon;  
        string msg;
        int count, cnt, skill;

        if ((int)me->query_temp("baifu"))
                return notify_fail("你已经运起「云龙百蝠」了。\n");

        if ((int)me->query_skill("qingfu-shenfa", 1)< 200)
                return notify_fail("你的青蝠身法等级不够，难以施展此项绝技！\n");

        if ((me->query_skill_mapped("force") != "jiuyang-shengong")) 
                return notify_fail("你现在没有激发九阳神功为内功，不敢轻易施展「云龙百蝠」。\n"); 

        if ((int)me->query_dex() < 30)
                return notify_fail("你的身法不够使用「云龙百蝠」绝技！\n");

        if ((int)me->query_skill("force", 1)< 200)
                return notify_fail("你的内功火候不够，难以施展此项绝技！\n");

        if ((int)me->query_skill("dodge", 1)< 200)
                return notify_fail("你的轻功修为不够，不会使用此项绝技！\n");

        if ((int)me->query("max_neili") < 1000)
                return notify_fail("你的内力修为不够使用「云龙百蝠」！\n");

        if ((int)me->query("neili") < 250)
                return notify_fail("你此时的内力不足！\n");

        msg = HIB "$N" HIB "运起九阳神功，施展「云龙百蝠」绝技,"
                  "长啸一声犹如一只蝙蝠一样纵身而起，身体变得越来越轻。\n" NOR;
        
        message_combatd(msg, me, target);
        skill = me->query_skill("qingfu-shenfa", 1);
        cnt =(int)( (int)me->query_condition("drunk") / 3);

        count = skill / 50 + cnt;

        if (me->is_fighting())
                me->start_busy(2);

        me->add_temp("dex", count);
        me->set_temp("baifu", 1);
        me->start_call_out((: call_other,  __FILE__, "remove_effect", me, count :), skill / 2);

        me->add("neili", -200);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if ((int)me->query_temp("baifu"))
        {
                me->add_temp("dex", -amount);
                me->delete_temp("baifu");
                tell_object(me, "你的「云龙百蝠」运功完毕，将内力收回丹田。\n");
        }
}

