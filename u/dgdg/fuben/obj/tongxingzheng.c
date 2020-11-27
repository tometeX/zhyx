


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "通行证" NOR, ({ "tongxing zheng","zheng" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n这是一张金黄的令牌，上面写着“通行证”三字，凭此令牌可以出入神农洞。\n" NOR);
                set("unit", "张");
                set("value", 50000000);
                set("no_sell", 1);
                set("no_steal",1);
                set("no_put", 1); 
                set("no_drop", 1);
                set("weight", 10);
                set("no_light", "这东西你也想烧？小心出事哦！"); 
                set("material", "paper");                 
             }
        setup();
}
      void init() 
      { 
              if( this_player() == environment() ) 
              { 
                      remove_call_out("destroy");  
                      call_out("destroy", 300);  
              } 
      } 
      int destroy()  
      {  
          tell_room(environment(this_object()),   
                     "突然间，天空中一道闪电把你手中的通行证击了个粉碎!\n");  
          destruct(this_object());  
          return 1;  
      } 