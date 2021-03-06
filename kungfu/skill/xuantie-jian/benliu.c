//benliu.c 大海奔流
// looo/2001/6/24
#include <ansi.h>

#include <combat.h>
inherit F_SSERVER;

int perform(object me, object target)

{
        object weapon;
        string msg;

        int i, j, skill;
        skill = (int) (me->query_skill("sword"));
        j = skill/3;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))

                return notify_fail("「大海奔流」只能在战斗中对对手使用。\n");

        if (me->query("gender") != "男性")
                return notify_fail("你不是堂堂男子,无法使出如此绝技。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")

                return notify_fail("你必须使用武器才能使用「大海奔流」！\n");

        if(me->query_skill_mapped("sword") != "xuantie-jian") 
                return notify_fail("你没有用玄铁剑法，无法使用大海奔流！\n");

        if( (int)me->query_skill("xuantie-jian", 1) < 220 )

                return notify_fail("你的玄铁剑法还不够娴熟，使不出「大海奔流」绝技。\n");

        if ((int)weapon->query_weight() < 30000)

                return notify_fail("你手中的" + weapon->name() + "分量不够，无法施展大海奔流。\n");

        if( (int)me->query_skill("nuhai-kuangtao", 1) < 220 )

                return notify_fail("你的怒海狂涛等级还不够，使不出「大海奔流」绝技。\n");

        if( (int)me->query_skill("force") < 200 )

                return notify_fail("你的内功等级不够，不能使用「大海奔流」。\n");

        if ((string)me->query_skill_mapped("force") != "nuhai-kuangtao")
                return notify_fail("你没有激发怒海狂涛心法，无法使用玄铁剑法。\n");

        if( (int)me->query_str() < 45 )

                return notify_fail("你的膂力还不够强劲，使不出「大海奔流」来。\n");


        if ( me->query_skill_mapped("sword") != "xuantie-jian")


               return notify_fail("你没有剑，无法使用「大海奔流」！\n");

        if( (int)me->query("max_neili") < (me->query_skill("force")+j+2500) )

                return notify_fail("你的内力修为需要进一步提高，才能使出「大海奔流」这种必杀。\n");

        if( (int)me->query("neili") < (me->query_skill("force")+j) )

                return notify_fail("你现在真气太弱，还敢使用「大海奔流」？\n");


        msg = HIM "\n$N" HIM "大吼一声，手持"+ weapon->name() + HIM "挟巨浪潮涌之势,从轻而响，从响而轻，忽寂然\n"
              HIM "无声，忽轰轰之声，反复七次，向" HIM "$n" HIM "席卷而去。\n" NOR;
        message_combatd(msg, me, target);

        me->add_temp("apply/str", 10);
        me->add_temp("apply/damage", j);
        me->add_temp("apply/attack", j);

        me->add("neili", -(me->query_skill("force")+400));



        for (i = 1; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;
                msg = HIR "\n人意无情，剑气纵横！！\n" NOR;
                message_vision(msg,me,target);
                COMBAT_D->do_attack(me, target, weapon, 0);
        }

        me->start_busy(4);

        target->start_busy(1);

        me->add_temp("apply/str", -10);
        me->add_temp("apply/damage", -j);
        me->add_temp("apply/attack", -j);

        return 1;
}

