#include <weapon.h>
#include <ansi.h>

inherit SWORD;
void create()
{
        set_name(MAG"玄真剑"NOR,({ "xuanzhen jian", "xuanzhen", "sword", "jian" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 80000);
                set("material", "steel");
                set("weapon_prop/dodge", -5);
                set("weapon_prop/parry", 5); 
                set("wield_neili", 300);
                set("wield_maxneili", 700);
                set("wield_str", 22);
                set("wield_msg", HIY"$N“唰”的一声抽出一把青锋剑。\n"NOR);
                set("long", "这是一柄四尺来长的古剑。\n");                
                set("unwield_msg", HIY "青锋剑幻作一道白光，「唰」地飞入剑鞘。\n" NOR);                
        }
        init_sword(250);
        setup();
}

