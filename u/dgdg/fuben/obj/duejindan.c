// 上古十大神丹之 真龙丹 
// Create by dgdg 2010/1

#include <ansi.h>

inherit ITEM;

//int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "渡厄金丹" NOR, ({ "due jindan", "jindan" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "个");
                set("long", NOR + YEL "这是一个泛着七彩光芒的丹药，传说此神丹是神农的哎心沥血之作。\n"
                                      "吃(chi)过此丹死亡后不会丢失经验，潜能以及技能。\n" NOR);
                                      

        }
        setup();
}



void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "chi");
}


int do_eat(string arg)
{
        object me = this_player();

        if (me->is_busy())
                return notify_fail("你现在正忙着呢。\n");

        if (me->is_fighting())
                return notify_fail("战斗中无法吃东西。\n");

        if (arg && id(arg))
        {
                if (me->query("skybook/guard/death") >= 1)
                  // || me->query("combat_exp") > 2500000)
                        return notify_fail(HIW "\n你正在受到狼神大人的保护呢，留着下次再吃吧n" NOR);
          if (random(4)!=1) 
          	{
                log_file("static/using", sprintf("%s(%s) use 渡厄金丹 at %s.\n",
                                                 me->name(1), me->query("id"),
                                                 ctime(time())));

                message_vision(HIY "$N" HIY "拼命地咬" + query("name") + HIY"突然喀嚓一声,"+query("name")+HIY"给咬碎了，霎时间一道光华闪过$P" HIY "的面庞。\n" NOR, me);

                tell_object(me, HIC "冥冥中你似乎受到了某种的启迪，往日的一切烦"
                                "恼渐渐消逝殆尽。\n" NOR);

                me->add("skybook/guard/death", 1);
                me->start_busy(1);
                destruct(this_object());
                return 1;
              }
           else 
           	{
           		
           		tell_object(me, HIW "\n你啃啊啃啊，把大板牙都啃嘣了，可是没等把金丹吃下去，却把这个神丹啃坏了！哟，不好了！\n" NOR);
           		destruct(this_object());  
           		return 1;
              }
           
        }
}


int query_autoload()
{
	return 1;
}