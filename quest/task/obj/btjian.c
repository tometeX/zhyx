//TASK物品
//瞎三笨制作


#include <ansi.h>

#define  SET_TASK   "/quest/task/set_task"

inherit ITEM;


void create()
{
        set_name(CYN "镔铁长剑" NOR, ({ "btjian"}));
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "把");
                set("owner_id", "feng xifan");
                set("owner", "冯锡范");

                set("value",10);
                set("no_sell",1);
                set("no_put",1);
        }
        setup();
}

void init()
{
	add_action("do_give","give");
}


int do_give(string arg)

{

	object me,ob;

	ob = this_object();
	me = this_player();

    return call_other(SET_TASK, "do_return", ob, me, arg);

}


string long()
{
        return "这是" + query("owner") + "的" + query("name") +
               "(" + query("id") + ")。\n";

}

