#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "大金砖" NOR, ({ "gold brick", "jinzhuan", "brick" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "这是一块黄灿灿的金砖，价值"
                            "绝对不菲。\n"NOR);
                set("value", 3400000);
                set("unit", "块");
        }
}
