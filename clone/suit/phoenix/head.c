// 成套装备
// update by kasumi
#include <ansi.h> 
#include <armor.h> 
 
inherit HEAD; 
 
void create() 
{ 
        set_name( YEL"朱雀之眼"NOR , ({ "phoenix eye","eye" }) ); 
        set_weight(800); 
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "具"); 
                set("long", YEL"这是一具形状怪异的头盔。"NOR"
防御指数：40~70
特殊效果：提高有效内功50~100级。
成套装备："HIR"[朱雀之舞]"NOR" "RED"朱雀之羽"NOR" "YEL"朱雀之眼"NOR" "GRN"朱雀之爪"NOR" "HIC"朱雀之翼"NOR"
套装效果："HIG"临时附加二百级阴阳八卦。"NOR"\n");
                set("value", 150000); 
                set("material", "head"); 
                set("armor_prop/force", 50+random(50));
		            set("armor_prop/armor", 40+random(30));  
		            set("no_sell", 1 );
                set("no_steal", 1 );              
        } 
        setup(); 
} 
int query_autoload()
{
        return 1;
}