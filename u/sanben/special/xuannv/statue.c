// 女娲像

#include <ansi.h>
inherit ITEM;

#define QINGTIAN    "/u/sanben/special/xuannv/xuanyin.h"
#define XUANNVJIAN       "/u/sanben/special/xuannv/xuannvjian.h"
#define SPECIAL     "/data/item/special/"

void create()
{
        set_name(HIW "女娲像" NOR, ({ "statue"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "此女娲雕像一副庄严宝相，顿时另你敬"
                               "畏之心油然而生，不敢正视。\n" NOR);
                set("unit", "个");                
                set("no_sell",1);
                set("weight", 10000);
                set("no_get",1);                
             }
        setup();
}
