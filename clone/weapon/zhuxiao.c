#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_XIAO;

void create()
{
        set_name(NOR + GRN "翠竹萧" NOR, ({ "zhu xiao", "zhu", "xiao" }));
        set_weight(600);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("material", "bamboo");
                set("unit", "只");
                set("long", "这是一把练习剑法用的竹萧。\n");
                set("wield_msg", "$N拿出一把$n，握在手中。\n");
                set("unequip_msg", "$N放下手中的$n。\n");
        }
        setup();
}

void init()
{
        add_action("play_xiao", "play");
}

