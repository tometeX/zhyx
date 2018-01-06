#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "上古太虚" NOR, ({"tai xu", "tai", "xu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "\n一块金黄色的太虚，拥有无穷变化的魔力，这\n"
                            "便是传说中的至宝——上古太虚，相传为上古\n"
                            "时代，黄帝得九天玄女所送南北精铁炼制而成。\n" NOR);
                set("unit", "块");
                set("value", 10000000);
                set("item_origin", 1);
                set("material_attrib", "tai xu");
                set("material_name", HIY "上古太虚" NOR);
                set("can_make", "all");
                set("power_point", 180);
        }
}
