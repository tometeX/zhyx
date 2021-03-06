#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIY "炎龙神冠" NOR, ({ "yanlong shenguan", "shenguan", "yanlong" }));
        set_weight(4000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "一顶用龙角和龙鳞做成的头冠。\n" NOR
                            HIC "有效招架修正：+ 10       有效轻功修正：  + 5\n" NOR
                            HIC "抗毒效果修正：+ 5%       防御效果等级：   10\n" NOR
                            HIC "抗毒回避修正：+ 5%\n" NOR);
                set("unit", "顶");
                set("value", 500000);
                set("armor_prop/armor", 10);
                set("armor_prop/avoid_poison", 5);
                set("armor_prop/reduce_poison", 5);
                set("armor_prop/dodge", 10);
                set("armor_prop/parry", 10);
                set("wear_msg", HIY "$N" HIY "轻轻地把$n"
                    HIY "戴在头上。\n" NOR);
                set("remove_msg", HIC "$N" HIC "轻轻地把$n"
                    HIC "从腰间取了下来。\n" NOR);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
