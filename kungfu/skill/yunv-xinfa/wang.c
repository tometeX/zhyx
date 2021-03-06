// wang.c 玉女忘情心诀
// looo/2001/6/23
#include <ansi.h>
#include <combat.h>
inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        string msg;

        int skill, i;
        if (! target || target == me)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("只能在战斗中才能体会「忘情」。\n");


        if (me->query("gender") == "男性")
                return notify_fail("女儿家的心事你怎能明白？\n");


        if (me->query("neili") < 200)
                return notify_fail("你的真气不够。\n");

        if (me->query_temp("wang"))
                return notify_fail("你已经进入「"HIW"忘情"NOR"」的境界了。\n");

        if (me->query_skill("yunv-xinfa",1) < 200)

                return notify_fail("你的玉女心法还不够精熟。\n");

        if (me->query_skill_mapped("sword") != "yunv-jian")
                return notify_fail("你没有激发玉女剑法!\n");

	if (!me->query_temp("weapon") ||
	    me->query_temp("weapon")->query("skill_type") != "sword")
		return notify_fail("你使用的兵器不对!\n");

        skill = me->query_skill("yunv-xinfa");
        i = skill / 50 + 1;             
        if (random(i) > 3)

        {
message_combatd(HIW "$N" HIW "蓦然回首，忧郁眼神淡如清水，完全不将外界事物放在心上，\n"              
                        HIW "剑招突变，一会儿，情意绵绵，一会儿却舍命相拼，意欲寻死，\n"
                        HIW "一招一式若神来之笔，拿捏的异常准确！\n" NOR, me);
        tell_object(me, HIM "既已无缘，何需誓言，你不觉间进入忘情境界。\n");
        me->add_temp("apply/attack", skill / 3); 

        me->set_temp("wang", 1);
        me->add("neili", -100);

        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill / 3 :), skill);


         }
       else {
                msg = HIM "$N" HIM "心乱如麻，一时之间不能进入忘情境界。\n" NOR;
                me->start_busy(3);
            }
        message_combatd(msg, me, target);
        return 1;
}

void remove_effect(object me, int amount)
{
        if (me->query_temp("wang"))
        {
                me->add_temp("apply/attack", -amount);

                me->delete_temp("wang");
                tell_object(me, "一阵心痛，又勾起了你伤心的往事，忘情之意顿消.\n");
        }
}
