#include <ansi.h>
inherit ITEM;
void create()
{
    set_name(YEL"棋盘"NOR, ({ "qipan" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("unit", "个");
            set("material", "stone");
            set("long", "一个石制棋盘\n");
          }

    setup();
}

