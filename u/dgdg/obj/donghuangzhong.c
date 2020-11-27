// tiejia.c 铁甲
//
#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name( HIG"东皇钟"NOR, ({ "donghuang zhong","zhong" }) );
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
		set("long", HIW"一个青铜大钟，相传为东皇太一的兵器。钟上刻着无数上古文字，散发着黄色的豪光。具有极强的防御能力。\n" NOR);
                set("material", "steel");
		set("value", 2000);
                set("armor_prop/armor", 500 + random(100)); 
                set("armor_prop/dodge", 200 + random(100));
                set("armor_prop/parry", 200 + random(100));

        }
        setup();
}

