#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "众生百态图" NOR, ({ "baitai tu", "baitai", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "芸芸终生，人生百态，尽在此图中。");
                set("can_tattoo", ({ "胸口", "后背", }));
                set("tattoo_type", ({ "悟性" }));
                set("tattoo_int", 4);
                set("tattoo_special", "selfstudy");
                set("tattoo_spcname", "无师自通");
        }
}
