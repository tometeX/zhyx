
inherit ITEM;
#include <ansi.h>
void create()
{
    set_name( HIM"客户定单" NOR, ({ "dingdan" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张详细的定单，记载着丽春院的预定情况。\n");
	}
}