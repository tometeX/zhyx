#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(CYN"唐家家谱"NOR, ({ "jiapu" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "张");
            set("material", "paper");
            set("long", "一张唐家家谱\n");
          }

    setup();
}
