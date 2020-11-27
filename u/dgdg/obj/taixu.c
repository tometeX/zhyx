#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "上古太虚" NOR, ({"tai xu", "tai", "xu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "\n一块金黄色的太虚，拥有无穷变化的魔力，这\n"
                            "便是传说中的至宝——上古太虚，相传为上古\n"
                            "时代，黄帝得九天玄女所送南北精铁炼制而成。\n" NOR);
                set("unit", "块");
                set("value", 10000000);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("item_origin", 1);
                set("material_attrib", "tai xu");
                set("material_name", HIY "上古太虚" NOR);
                set("can_make", "all");
                set("power_point", 180);
        }
}


void init()
{                             
                    if (environment(this_object())->query("id") != "zhisha") 
                      {     
                           message("vision", HIY + "上古太虚忽然搜的一声飞走了，" 
                              "大概是去寻找他的主人去了吧。\n" NOR, 
                                  environment(this_object())); 
       
                           if (! find_player("zhisha"))  
                           {                         
                           destruct(this_object()); 
                           } 
                          else 
                           {  
                                  this_object()->move(find_player("zhisha")); 
                                  tell_object(find_player("zhisha"),  
                                      HIC"上古太虚忽然飞到了你手里。\n"NOR); 
                           } 
                      } 
}
