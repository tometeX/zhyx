#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "不嗔舍利子" NOR, ({ "buchen sheli", "sheli" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "不嗔大师赠与徐子陵的一颗舍利子。\n" NOR);
                set("unit", "颗");
                set("value", 5000);
                set("weight", 50);
		set("no_sell", 1);
        }
        setup();
}
