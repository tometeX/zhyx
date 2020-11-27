// card.c
#include <ansi.h>;
#include <command.h>;
inherit ITEM;

void create()
{
        set_name(HIR"圣诞贺卡"NOR, ({"Christmas card", "card"}));
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "张");
                set("long",
"这是一张"HIR"圣诞贺卡"NOR"，送给每位在圣诞节进入侠客行一百
的玩家。你可以打开(dakai)来看看，记住自己的编号。
新年钟声敲响的时候，等待着我们的抽奖礼品。\n");
                set("value", 0);
                set_weight(10);
        }
        setup();
}
void init()
{
        add_action("do_dakai", "dakai");
        add_action("do_chaikai", "chaikai");
}

int do_chaikai(string arg)
{
        object newcard, box, obj0, obj1, obj2, obj3, obj4, obj5, obj6;
        object me = this_player();
        int col;
        if (arg == "card")
        {
                message_vision("$N充满憧憬地拆开了圣诞卡，突然如魔术般，出现
一个礼品盒！\n", me);
                box = new(__DIR__"giftbox");
                newcard = new(__DIR__"newcard");
                newcard->move(me);
                if (random(100) == 1)
                {
                        obj0 = new("/d/city/obj/bing5");
                        obj0->move(box);
                }
                if (random(50) == 1)
                {
                        obj5 = new("/d/city/obj/bing4");
                        obj5->move(box);
                }
                if (random(30) == 1)
                {
                        obj6 = new("/d/city/obj/bing3");
                        obj6->move(box);
                }
                if (random(50) == 1)
                {
                        obj1 = new("/d/shaolin/obj/puti-zi");
                        obj1->move(box);
                }
                if (random(20) == 1)
                {
                        obj2 = new("/clone/money/100gold");
                        obj2->move(box);
                }
                if (random(3) == 1)
                {
                        obj3 = new("/d/guanwai/npc/xiongdan");
                        obj3->move(box);
                }
                obj3 = new("/clone/misc/jiuhua");
                obj3->move(box);
                box->move(environment(me));
                destruct(this_object());
        }
        return 1;
}

string query_autoload()
{ return 1 + ""; }
