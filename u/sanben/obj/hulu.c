//紫金葫芦(唯一物品，可以把人收进来关着，grin)
//瞎三笨制作


#include <ansi.h>
#define HULU_INSIDE  "/u/sanben/obj/hulu_inside"
#define MASTER       "sanben"

inherit ITEM;


void create()
{
        set_name(YEL "紫金葫芦" NOR, ({ "zijin hulu", "hulu" }));
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "个");
                set("long", WHT"这是法宝"NOR + YEL"紫金葫芦"NOR +
                            WHT"，可以把人装在里面。\n"NOR);
                set("value", 1);
                set("no_sell",1);
                set("no_put",1);
        }
        setup();
}

void init()
{
        object me, ob;
        ob = this_object();
    if (environment(ob)->query("id") == MASTER)
                {    
             add_action("do_shou","shou");
                }
    else
        {
              add_action("do_more","more");
              add_action("do_more","data");
              add_action("do_more","info");
              add_action("do_edit","edit");
        }

}

int do_shou(string arg)
{
   object ob;

   if (! arg)
   {
      write("你要把谁收进葫芦？\n");
      return 1;
   }

   ob = present(arg,environment(environment(this_object()) ));

   if (! ob)
   {
      write("这里没有这个人你收什么收！\n");
      return 1;
   }
   if (! userp(ob))
   {
      write("这个葫芦只收player！\n");
      return 1;
   }
   if ( ob->query("id") == this_player()->query("id"))
   {
      write("自己收自己？你是不是脑子有水？！\n");
      return 1;
   }
   message_vision(HIY"只见$N举起手中的紫金葫芦，大喝一声“疾！”。$n顿时化作"
                     "一股清烟被收进了葫芦里。。。\n\n"NOR, this_player(),ob);
   ob->move(HULU_INSIDE);
   return 1;

}

int do_more(string arg)
{
    if ( arg == "zijin hulu" || arg == "hulu" )
    {
      write("你无权查看这个文件！\n");
      return 1;
    }
}

int do_edit(string arg)
{
    if ( arg == "zijin hulu" || arg == "hulu" )
    {
      write("你无权编辑这个文件！\n");
      return 1;
    }
}
