#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIY"五香花生秘方"NOR, ({ "hsmfang" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "面");
            set("material", "paper");
            set("long", "五香花生秘方。\n");
          }

    setup();
}
