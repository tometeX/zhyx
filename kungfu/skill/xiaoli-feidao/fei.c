// shan.c

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("小李飞刀只能在战斗中对对手使用。\n");

    /*    if (! objectp(weapon = me->query_temp("handing")) ||
            (string)weapon->query("skill_type") != "throwing")
                return notify_fail("你现在手中并没有拿着飞刀。\n"); */

        if ((skill = me->query_skill("xiaoli-feidao", 1)) < 100)
                return notify_fail("你的小李飞刀不够娴熟。\n");

        if ((int)me->query("neili") < 100)
                return notify_fail("你内力不够了。\n");

        me->add("neili", -50);
     //   weapon->add_amount(-1);

        msg= HIW "忽然间只见$N" HIW "手中寒光一闪，正是小李飞刀，例无虚发！\n\n"
             NOR + HIR "一股鲜血从$n" HIR "咽喉中喷出……\n" NOR;
        message_combatd(msg, me, target);


        me->start_busy(random(5));

        if ( ! target->query("reborn_start/die") )
        {
           tell_object(target, BLINK HIG"\n\n在丧命于小李飞刀的这一刻，你似乎明白了"
                        "生死原来竟是如此的相近！\n你感到从今以后你似乎"
                        "在天上地下，甚至阴间都能遨游自如了。\n\n"NOR);
           target->set("reborn_start/die", 1);
        }
        target->die(me);
        me->reset_action();
        return 1;
}
