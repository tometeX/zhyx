// 成套装备
// update by kasumi                                                         

#include <ansi.h>
#include <armor.h>

inherit SURCOAT;

void create()
{
        set_name( HIC"朱雀之翼"NOR, ({ "phoenix wing", "wing" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIC"这是一件五色织成的披风，随风飘舞时好象一对张开的翅膀。"NOR"
防御指数：50~80
特殊效果：提高有效轻功40~60级。
成套装备："HIR"[朱雀之舞]"NOR" "RED"朱雀之羽"NOR" "YEL"朱雀之眼"NOR" "GRN"朱雀之爪"NOR" "HIC"朱雀之翼"NOR"
套装效果："HIG"临时附加二百级阴阳八卦。"NOR"\n");
                set("value", 200000); 
                set("material", "feather");
                set("armor_prop/armor", 50+random(30));
                set("armor_prop/dodge", 40+random(20));
                set("no_sell", 1 );
                set("no_steal", 1 );   
                
        }
        setup();
}
int query_autoload()
{
        return 1;
}