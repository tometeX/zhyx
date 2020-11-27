#include <ansi.h>

#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC"淬火长剑"NOR, ({ "long sword", "sword"}));   
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", "这是一柄淬火处理过的长剑，异常锋利。\n");
                set("value", 8000);
                set("material", "steel");
                set("wield_msg", "$N「唰」的一声抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n插回剑鞘。\n");
        }
        init_sword(50);
        setup();
}

