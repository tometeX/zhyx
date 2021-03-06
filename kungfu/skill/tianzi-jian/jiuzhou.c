#include <ansi.h>
#include <combat.h>

#define JIUZHOU "「" HIY "九洲臣服" NOR "」"
inherit F_SSERVER;

int perform(object me, object target)
{
        int damage, i, count;
        string msg, sub_msg;
        int ap, dp;
        object weapon;       
        int lvl;

        if (userp(me) && ! me->query("can_perform/tianzi-jian/jiuzhou"))
                return notify_fail("你所使用的外功中没有这种功能。\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(JIUZHOU "只能对战斗中的对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("你使用的武器不对，难以施展" JIUZHOU "。\n");   
        if (me->query_skill_mapped("sword") != "tianzi-jian")
                return notify_fail("你没有激发天子剑法，难以施展" JIUZHOU "。\n");

        if ((int)me->query("max_neili") < 4000)
                return notify_fail("你内力修为不够，难以施展" JIUZHOU "。\n");

        lvl = (int)me->query_skill("tianzi-jian", 1);
        if (lvl < 250)
                return notify_fail("你天子剑法火候不够，难以施展" JIUZHOU "。\n");

        if ( me->query("int") < 15 ) 
                return notify_fail("你的先天悟性不足，无法使用此招。\n");   

        if ((int)me->query("neili") < 800)
                return notify_fail("你现在真气不够，难以施展" JIUZHOU "。\n");

        if (! living(target))
                return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

        message_sort(HIY "\n$N" HIY "突显帝王之态，纵声高呼：\n\n"NOR
                     HIR"  普天之下，莫非王土！天子降世，九洲臣服！\n\n"NOR
                     HIW "     旋即但见天边似乎飞来千军万马，连同$N" HIW"的剑招尽数袭向$n"
                     "。\n\n" NOR, me, target);

        weapon = me->query_temp("weapon");

       //天子降世单招攻击
        msg = HIG "\n只见$N" HIG "轻挥手中利剑，从意想不到之处向"
              "$n" HIG"直刺过来，隐隐已现出王者霸气。\n" NOR;
 
        ap = me->query_skill("tianzi-jian", 1) * 2 +              
             me->query_skill("martial-cognize", 1);

        dp = target->query_skill("parry", 1) +
             target->query_skill("martial-cognize", 1);

        me->add("neili", -150);

        if (ap * 4 / 5 + random(ap) < dp)
        {
                msg += HIY "幸亏$n" HIY "全力躲闪，才将$N" HIY
                       "这一招化解。\n" NOR;	         
        } else
        {
                me->add("neili", -200);	        
                damage = ap + random(ap);                            
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(5),
                                           HIR "$n" HIR "急忙飞身躲避，然而这一剑来得过快"
                                          "，只听$n" HIR "一声惨叫，这一剑已刺中$n，" HIR "顿"
                                          "时鲜血飞溅。\n" NOR); 
        }
        message_sort(msg, me, target);

       //再出九剑(八连招 + 一单招)
       if (! me->is_fighting(target) ) return 1;

        msg = HIY "紧接着$N" HIY "又连续施出九剑，招招从不同方位攻向$n" HIY"要害。\n" NOR; 

       
        count = ap / 8;        

        me->add_temp("apply/attack", count);

        for (i = 0; i < 8; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) == 1 && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, weapon, i * 2);
        }
        me->add_temp("apply/attack", -count);

       if ( ! me->is_fighting(target) ) return 1;

       
        if (ap * 4 / 5 + random(ap) > dp)
        {       
                damage = ap + random(ap);
                target->receive_damage("qi", damage * 2 / 3 , me);
                target->receive_wound("qi", damage * 2 / 3, me);
                msg += HIR "最后一剑招数精奇，$n" HIR 
                      "避无可避，终被刺中，顿遭重创！\n" NOR;
        } else
        {
                msg += HIC "好在$n" HIC "提前预防，勉强躲开$N" HIC"这致命一击。\n" NOR;
        }
        message_combatd(msg, me, target);
        me->add("neili", - ( 400 + random(50)) ); 
        me->start_busy(3 + random(2));
        return 1;
}
