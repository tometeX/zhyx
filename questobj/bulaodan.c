#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIR"不老丹"NOR, ({ "bulaodan" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "丸");
            set("material", "stone");
            set("long", "一丸传说中的不老神丹\n");
          } 
    ::init_item();
}  
