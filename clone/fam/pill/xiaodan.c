#include <ansi.h>
inherit COMBINED_ITEM;

string query_autoload()
{
        return query_amount() + "";
}

void create()
{
        set_name(HIG "削神无根丹" NOR, ({ "xiaoshen dan","dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "这是一颗消减记录的仙丹。\n" NOR);
                set("base_unit", "颗");
                set("base_value", 0);
                set("base_weight", 50);
                set("only_do_effect", 1);
                 //            set("no_get", 1); 
                  //    set("no_put", 1); 
                 //     set("no_drop", 1); 
                      set("no_beg", 1); 
                set("gift_msg", HIC "突然间你的皮肤透过一道光泽。\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        int point;

        point = query("gift_point");
  if(me->query("gift/str/fail")<1){
            me->add("gift/str/fail", -1);
               me->add("gift/str/all", -1);
       }
         add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

void autoload(string param)
{
        int amt;

        if (sscanf(param, "%d", amt) == 1)
                set_amount(amt);
}

void setup()
{
        set_amount(1);
        ::setup();
}
