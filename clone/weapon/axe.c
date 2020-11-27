#include <weapon.h>
inherit AXE;

void create()
{
        set_name("板斧", ({ "axe", "banfu", "fu" }));
        set_weight(7000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄沉重的板斧，臂力高者方使得顺手。\n");
                set("value", 300);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n别回腰间。\n");
        }
        init_axe(50);
        setup();
}
