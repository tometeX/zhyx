#include <ansi.h>
#include <combat.h>

#define SHA "「" HIR "「一线观潮」" NOR "」"

inherit F_SSERVER;
inherit SKILL;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
 
        if (! target) target = offensive_target(me);
 
        if (! target || ! me->is_fighting(target))
                return notify_fail(SHA "只能在战斗中对对手使用。\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
              (string)weapon->query("skill_type") != "blade")
                return notify_fail("你使用的武器不对，难以施展" SHA "。\n");

        if (me->query_skill("force") < 400)
              return notify_fail("你的内功修为不够，难以施展" SHA "。\n");

        if (me->query_skill("billow-blade", 1) < 300)
                return notify_fail("你的沧浪刀法修为不够，难以施展" SHA "。\n");

        if (me->query_skill_mapped("blade") != "billow-blade")
                return notify_fail("你没有激发沧浪刀法，难以施展" SHA "。\n");

        if (me->query("neili") < 1000)
                return notify_fail("你的内力不够，难以施展" SHA "。\n");
                
        if(me->query_temp("no_sha"))
                return notify_fail("你内息未稳，无法使用" SHA "！\n");   

        if (! living(target))
               return notify_fail("对方都已经这样了，用不着这么费力吧？\n");

                    message_vision(HIR"$N啸声连连，气势冲天，刀光起处，施展出沧浪刀法绝技 【 一 线 观 潮 】！！\n"NOR, me);

        ap = me->query_skill("blade") + me->query_dex() * 5;
        dp = target->query_skill("force") + target->query_con() * 5;

                damage = ap / 3 + random(ap/3);

                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           YEL "〾⿰⿱⿲⿳⿴⿵⿶⿷⿶⿷⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
      ⿳⿴"HIC"第"NOR+YEL"⿵⿶"HIC"一"NOR+YEL"⿷⿸"HIC"重"NOR+YEL"⿹⿸"HIC"沧"NOR+YEL"⿹⿷"HIC"浪"NOR+YEL"⿶⿴"HIC"刀"NOR+YEL"⿵⿶"HIC"涌"NOR+YEL"⿵⿳
〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿶⿷⿶⿷⿻〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
"HIW"$N幻出层层刀浪，仿如水天相接，泛起一道银线，乍隐乍现，微微起伏
远远望去，"HIW"刀影像亿万银鱼跳跃追逐，又似无数游龙排成一线，乘风破浪而来！！\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 45,
                                           YEL "〾⿰⿱⿲⿳⿴⿵⿶⿷⿶⿷⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
      ⿳⿴"HIC"第"NOR+YEL"⿵⿶"HIC"二"NOR+YEL"⿷⿸"HIC"重"NOR+YEL"⿹⿸"HIC"沧"NOR+YEL"⿹⿷"HIC"浪"NOR+YEL"⿶⿴"HIC"刀"NOR+YEL"⿵⿶"HIC"涌"NOR+YEL"⿵⿳
〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿶⿷⿶⿷⿵⿶⿷⿸⿹⿺⿻〾
"HIW"前波未平，第二层刀浪又至，"HIW"似满江碎银狂泻，如托起耸江潮峰，澎湃而来！！\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           YEL "〾⿰⿱⿲⿳⿴⿵⿶⿷⿶⿷⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
      ⿳⿴"HIC"第"NOR+YEL"⿵⿶"HIC"三"NOR+YEL"⿷⿸"HIC"重"NOR+YEL"⿹⿸"HIC"沧"NOR+YEL"⿹⿷"HIC"浪"NOR+YEL"⿶⿴"HIC"刀"NOR+YEL"⿵⿶"HIC"涌"NOR+YEL"⿵⿳
〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿵⿶⿶⿷⿶⿷⿷⿸⿹⿺⿻〾
"HIW"三重刀浪相激，势如满江涌潮，声如山崩地裂，"HIW"掀起万钧的巨浪，摧枯拉朽！！\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           YEL "〾⿰⿱⿲⿳⿴⿵⿶⿶⿷⿶⿷⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
      ⿳⿴"HIC"第"NOR+YEL"⿵⿶"HIC"四"NOR+YEL"⿷⿸"HIC"重"NOR+YEL"⿹⿸"HIC"沧"NOR+YEL"⿹⿷"HIC"浪"NOR+YEL"⿶⿴"HIC"刀"NOR+YEL"⿵⿶"HIC"涌"NOR+YEL"⿵⿳
〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿷⿸⿹⿺⿻〾⿰⿱⿲⿶⿷⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
"HIW"刀浪接踵而至，潮尖如受惊猛狮突兀立起，陡起丈高水柱，刀光闪闪，破水而出！！\n"
                                           NOR);
        message_combatd(msg, me, target);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           YEL "〾⿰⿱⿲⿳⿴⿶⿷⿶⿷⿵⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾
      ⿳⿴"HIC"第"NOR+YEL"⿵⿶"HIC"五"NOR+YEL"⿷⿸"HIC"重"NOR+YEL"⿹⿸"HIC"沧"NOR+YEL"⿹⿷"HIC"浪"NOR+YEL"⿶⿴"HIC"刀"NOR+YEL"⿵⿶"HIC"涌"NOR+YEL"⿵⿳
〾⿰⿱⿲⿳⿴⿵⿶⿷⿸⿹⿺⿻〾⿰⿱⿲⿳⿴⿶⿷⿶⿷⿵⿶⿷⿸⿹⿺⿻〾
"HIW"刀浪滚滚而来，像银山滚动，雪屋耸摇，顷刻，刀浪呼啸而过，如大浪淘尽，波涛泛白，经久不息！！\n"
                                           NOR);
        message_combatd(msg, me, target);

        if (ap / 2 + random(ap) > dp)
        {
                damage = ap / 2 + random(ap/3);
                me->add("neili", -500);
                me->start_busy(3+random(3));
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 70,
                                           HIR "漫天的刀浪汹涌而至，穿透$n"HIR"的躯体，只留下无数细碎的刀痕，
$n"HIR"的眼中突然流露出莫名的恐惧，所有的景象已变得支离破碎，
$n"HIR"向前狂奔，仿佛要抓住什么，却冲入无穷无尽的黑暗，只有阵阵凄厉的惨叫在苍穹之间回荡！！\n"
                                           NOR);
        } else
        {
                me->add("neili", -800);
                me->start_busy(3+random(4));
                msg = CYN "$n" CYN "见$P" CYN "来势汹涌，不敢轻易抵"
                       "挡，连忙飞身腾挪，躲闪开来。\n" NOR;
        }
        message_combatd(msg, me, target);
        
        me->set_temp("no_sha",1);
        call_out("sha_ok", 3+random(4), me);   

        return 1;
}

void sha_ok(object me) {
  if (!me) return;
  me->delete_temp("no_sha");
}


