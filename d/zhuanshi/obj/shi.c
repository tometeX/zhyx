// 转世神器之 女娲石 
// Create by yuchang

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(YEL "女娲石" NOR, ({ "nvwa shi", "nvwa", "shi" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "块");
                set("long", YEL "这是一块泛着七彩光芒的石头，传说此石乃女娲的"
                                "护身符。\n" NOR);
                set("value", 10000);
                set("no_sell", 1);
        }
        setup();
}
int query_autoload()
{
       return 1;
}

