#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(HIG"九阴真经"NOR, ({ "jiuyin-zhenjing" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "本");
            set("material", "stone");
            set("long", "一本书皮微微泛黄的书籍。\n");
          }

    setup();
}

