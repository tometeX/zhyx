


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "武林英雄帖" NOR, ({ "yingxiong tie"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n一张精美的武林英雄帖，持有这个可以参加华山论剑比武大会。\n" NOR);
                set("unit", "块");
                set("value", 200000);
                set("weight", 10);                
             }
        setup();
}
