// longsword.c 长剑
#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIW"小侠的"HIY"魔剑"NOR, ({ "boss sword", "sword", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIY "此乃上古神器之首，拥有着无穷的力量，据说"
                                "拥有此剑者可驰骋人、魔、神三界，势不可挡。\n"
                                 NOR);
                set("value", 200);
                set("material", "steel");
                 set("wield_msg", HIY "$N" HIY "一声轻呼，两条神龙自天而下，拥着一把周身泛着\n"
                                 "金光的神剑，刹那间此剑犹如一道流星划过，落入$N" HIY "手中。\n" NOR);                               
                set("unwield_msg", HIY "$N" HIY "心意一转，剑已归鞘。\n" NOR);
               
               
        }
        init_sword(1000);
        setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
        int my_exp, ob_exp;
        
        switch (random(3))
        {
        case 0:
                if (! victim->is_busy())
                victim->start_busy(20 + random(20));
                return HIY "$N" HIY "挥舞着手中的魔剑，万道彩光自中而出，直逼得"
                           "$n" HIY "连连后退。\n" NOR;

        case 1:
                n = me->query_skill("sword");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                return HIR "$N" HIR "反转手中魔剑，猛然间，数道金光划向$n" HIR "，$n" HIR
                           "正惊异间，却已中剑。\n" NOR;

        }
        return damage_bonus;
}