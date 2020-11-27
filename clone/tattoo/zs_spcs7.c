#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + MAG "仙图残片" NOR, ({ "xian tu7", "xiantu7", "tu7" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "这是一张薄如蚕丝的仙图残片，上面绘有残缺不全"
                            "的国士无双纹样。\n" NOR);
                set("unit", "块");
                set("value", 10);
                set("material", "paper");
        }
}

int query_autoload()
{
        return 1;
}

