//update by xiner
#include <ansi.h> 
#include <armor.h> 
 
inherit HEAD; 
 
void create() 
{ 
        set_name( HIW"白虎战盔"NOR , ({ "tiger helmet","helmet","kui" }) ); 
        set_weight(1000);
        if( clonep() ) 
                set_default_object(__FILE__); 
        else { 
                set("unit", "具"); 
                set("long", HIW"这是一具形状怪异的头盔。"NOR"
套装效果："HIW"临时增加空手伤害二百点。"NOR"\n");
		set("value", 150000); 
		set("material", "head"); 
		set("armor_prop/force", 50+random(50));
		set("armor_prop/armor", 50+random(50));  
		set("no_sell", 1 );
		set("no_steal", 1 );              
        } 
        setup(); 
} 
int query_autoload()
{
        return 1;
}