#include <weapon.h>
#include <ansi.h>
inherit SWORD;
void create()
{
        set_name(HIW"冲灵剑"NOR, ({ "chongling-sword" }) );
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("material", "iron");
                set("long", "这是一把铁剑。\n");
        }
        init_sword(5);
        setup();
}

