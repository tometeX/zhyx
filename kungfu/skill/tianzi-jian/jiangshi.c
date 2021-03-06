#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;

#define JIANGSHI "「" HIW "天子降世" NOR "」"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        object weapon;

        if (userp(me) && ! me->query("can_perform/tianzi-jian/jiangshi"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target)target = me->select_opponent();

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIANGSHI "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" JIANGSHI "。\n");

        if (me->query_skill_mapped("sword") != "tianzi-jian") 
                return notify_fail("你没有激发天子剑法，难以施展" JIANGSHI "。\n"); 
 
        if (me->query_skill("tianzi-jian", 1) < 150)
                return notify_fail("你的天子剑法还不够娴熟，难以施展" JIANGSHI "。\n");

        if (me->query("neili") < 400)
                return notify_fail("你的内力不够，难以施展" JIANGSHI "。\n");
 
        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        msg = HIG "\n$N" HIG "轻挥手中利剑，从意想不到之处向"
              "$n" HIG"直刺过来，隐隐已现出王者霸气。\n" NOR;
 
        ap = me->query_skill("tianzi-jian", 1) * 2  +              
             me->query_skill("martial-cognize", 1);

        dp = target->query_skill("parry") +
             target->query_skill("martial-cognize", 1);

        me->add("neili", -150);

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;
	         me->start_busy(2);
        } else
        {
                me->add("neili", -200);
	         me->start_busy(3);
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 90 + random(5),
                                           HIR "$n" HIR "急忙飞身躲避，然而这一剑来得过快"
                                          "，只听$n" HIR "一声惨叫，这一剑已刺中$n，" HIR "顿"
                                          "时鲜血飞溅。\n" NOR); 
        }
        message_sort(msg, me, target);
        return 1;
}

