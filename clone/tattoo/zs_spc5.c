#include <ansi.h>

inherit __DIR__"tattoo";

void create()
{
        set_name(NOR + WHT "不死战神图" NOR, ({ "busi tu", "busi", "tu" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "这是一张古旧的图片，上面绘着些纹样。");
                set("unit", "张");
                set("value", 99000);
                set("material", "paper");
                set("tattoo_long", "一副不死战神战斗的图案");
                set("can_tattoo", ({ "胸口", "后背", }));
                set("tattoo_type", ({ "根骨" }));
                set("tattoo_con", 4);
                set("tattoo_special", "nodie");
                set("tattoo_spcname", "不死金身");
        }
}
