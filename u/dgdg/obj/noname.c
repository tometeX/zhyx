#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIM "无名之物" NOR, ({"no name", "no", "name"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", sort_msg(HIM "非金非玉非石非木无名之物，看似平凡"
                                         "但又似不平凡，忽隐忽现，忽明忽暗。"
                                         "似乎包容着不为人知的力量，但却感觉"
                                         "不到一点能量。\n" NOR));
                set("unit", "块");
                set("value", 20000000);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("item_origin", 1);
                set("material_attrib", "no name");
                set("material_name", HIM "无名之物" NOR);
                set("can_make", "all");
                set("power_point", 300);
        }
}

void init()
{                             
                    if (environment(this_object())->query("id") != "zhisha") 
                      {     
                           message("vision", HIY + "无名之物忽然搜的一声飞走了，" 
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
                                      HIC"无名之物忽然飞到了你手里。\n"NOR); 
                           } 
                      } 
}
