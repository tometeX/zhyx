#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "九地玄玉" NOR, ({"xuan yu", "xuan", "yu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n一块绿色的九地玄玉，拥有能医重病，又能毒\n"
                            "杀人于一身的至宝——九地玄玉，相传神农氏\n"
                            "所用神农尺就是用这枚九地玄玉精炼而成。\n" NOR);
                set("unit", "块");
                set("value", 10000000);
                set("no_get",1); 
                set("no_beg",1); 
                set("no_steal",1); 
                set("no_drop",1); 
                set("no_put",1); 
                set("no_sell",1); 
                set("no_give",1); 
                set("item_origin", 1);
                set("material_attrib", "xuan yu");
                set("material_name", HIG "九地玄玉" NOR);
                set("can_make", "all");
                set("power_point", 160);
        }
}


void init()
{                             
                    if (environment(this_object())->query("id") != "dgdg") 
                      {     
                           message("vision", HIY + "九地玄玉忽然搜的一声飞走了，" 
                              "大概是去寻找他的主人去了吧。\n" NOR, 
                                  environment(this_object())); 
       
                           if (! find_player("dgdg"))  
                           {                         
                           destruct(this_object()); 
                           } 
                          else 
                           {  
                                  this_object()->move(find_player("dgdg")); 
                                  tell_object(find_player("dgdg"),  
                                      HIC"九地玄玉忽然飞到了你手里。\n"NOR); 
                           } 
                      } 
}
