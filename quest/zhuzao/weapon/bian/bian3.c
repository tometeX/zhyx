#include <ansi.h>  
#include <weapon.h>
inherit WHIP;
void create()
{
        set_name( HIW"亮银鞭"NOR, ({"liangyin bian", "bian" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", 
                "这是一柄用纯银打造连接的亮银鞭，精光闪闪煞是好看。\n");
                set("value", 30000);   
                set("material", "silver");
                set("wield_neili", 400);
                set("wield_maxneili", 600);
                set("wield_str", 22);
                set("wield_msg", "$N「唰」的一声抖出一柄$n握在手中。\n");
                set("unwield_msg", "$N将手中的$n卷回腰间。\n");
        }
        init_whip(150);
        setup();
}
