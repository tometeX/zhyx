#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(HIW "轮回剑" NOR, ({ "lunhui jian", "lunhui", "jian" }));
        set_weight(4000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "剑身厚重憨厚，散发着淡淡佛光。\n" NOR);
                set("unit", "柄");
                set("value", 40000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", HIW "一道佛光划过，轮回剑已落入$N" HIW "手中。\n" NOR);

                set("unwield_msg", HIW "佛光闪过，$N" HIW "手中的轮回剑已悄然隐没 。\n" NOR);
                set("stable", 100);
        }                                                                                                                    
        init_sword(100);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;

        if (me->query_skill_mapped("sword") != "lunhui-jian" ||
            me->query_skill("lunhui-jian", 1) < 190)
                return damage_bonus / 2;

        if (random(5) == 1)
        {
               n = me->query_skill("sword");
               victim->receive_damage("qi", n * 3 / 5, me);
               victim->receive_wound("qi", n * 2 / 7, me);
               return HIW "$N" HIW "一声佛号，手中轮回剑犹如佛光闪耀，十八罗汉力量聚集在剑身，"
                      "一时间狂涌而出，贯向$n" HIW "！\n" NOR;
        }
        return damage_bonus;
}

