// 成套装备
// update by kasumi
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
void create()
{
        set_name( RED"朱雀之羽"NOR, ({ "phoenix armor","armor","jia" }) );
        set_weight(1500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", RED"这是一件五彩斑斓的羽衣。"NOR"
防御指数：150~250
特殊效果：百分之二十的几率化解对手的攻击。
成套装备："HIR"[朱雀之舞]"NOR" "RED"朱雀之羽"NOR" "YEL"朱雀之眼"NOR" "GRN"朱雀之爪"NOR" "HIC"朱雀之翼"NOR"
套装效果："HIG"临时附加二百级阴阳八卦。"NOR"\n");
                set("value", 100000); 
                set("material", "feather");                              
                set("armor_prop/armor", 150 + random(100));
                set("warm_cloth", 1);  
                set("no_sell", 1 );
                set("no_steal", 1 );              
        }
        setup();
}

int query_autoload()
{
        return 1;
}


mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;       

        if (random(5)==1 )
        {               
                result = ([ "damage": -damage ]);               
                result += (["msg" : HIM"只见光芒大放，$N攻击之处，$n所穿的羽衣竟然根根羽毛随力道流转，化解了$N的攻击！\n"NOR]);                     
                return result;
        }
}
