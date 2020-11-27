#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + CYN "邯郸石" NOR, ({"handan shi", "handan", "shi"}));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", CYN "这是一块通体乌黑的石头，触手处清凉光滑。可以用来打造指套，基础伤害：50~80。\n" NOR);
                set("unit", "块");
                set("value", 8000);
                set("item_origin", 1);
                set("material_attrib", "stone");
                set("material_name", NOR + CYN "邯郸石" NOR);
                set("can_make", ({ "指套" }));
                set("power_point", 50);
        }
}

int query_autoload()
{
        return 1;
}

