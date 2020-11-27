// longwen-pei.c 龙纹珮
// By Alf, Last Update 2002.03

#include <ansi.h>
#include <armor.h>

inherit WAIST;
int do_ding(string arg);

string query_autoload()
{
	return 1 + "";
}

void create()
{
	set_name(HIG"龙纹珮"NOR, ({"longwen pei"}));
	set_weight(500);
	if(clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit","块");
		set("long",
"\n龙凤纹玉珮传自战国宫廷，龙凤为对，寓意呈\n"
"祥，贵族男女以之作为"HIM"定情"NOR"物。这一块乃是龙\n"
"纹珮，色作莹碧，触手生温，一面雕着栩栩如\n"
"生的龙纹，另一面镌着四行小字：\n"
HIG"\n\t情深不寿\n"
"\t强极则辱\n"
"\t谦谦君子\n"
"\t温润如玉\n\n"NOR);
		set("value",50000);
		set("armor_prop/armor",25);
		set("armor_prop/personality",20);
		set("wear_msg","$N将一块$n轻轻挂在腰间。\n");
		set("unequip_msg","$N将挂在腰间的$n收了起来。\n");
		set("huang",1);
	    set("no_put",1);
	    set("no_get",1);
	    set("no_drop",1);
	    set("no_steal",1);
	    set("no_leave",1);
	}
	setup();
}

void init()
{
	add_action("do_ding","定情");
}

int do_ding(string arg)
{
	object me,who,ob,ob1;
	string arg1;
	me=this_player();
	ob=this_object();
	if (!arg) 
               return notify_fail("你要向谁定情？\n");

	if (! objectp(who = present(arg, environment(me))) || !userp(who))
               return notify_fail("这里没有"+ arg + "这个玩家。\n");

       if (!objectp(ob1 = present("fengwen pei",me)))
               return notify_fail("龙凤双佩是成对的，你只有龙纹佩，怎么拿来定情？\n");

       if (me->query("gender") == "无性")
		return notify_fail("你一个太监，也想跟别人定情？\n");

       if (who->query("gender") == "无性")
		return notify_fail("有没有搞错？" + who->name() + "可是一个太监，你也想定情？\n");

       if (who->query("gender") == me->query("gender"))
              return notify_fail("这是什么世道啊，同性恋也就算了，还搞的这么肉麻兮兮的干啥？\n");

       if (who->query("gender") == "女性")
       {
              ob1->move(who);
              message_vision("$N深情的对$n说：“我真的很喜欢你，这块凤纹佩代表我的心，请收下吧。\n",me,who);
              message_vision("$N将一块莹碧的玉佩递给$n。\n",me,who);
              tell_object(who,"你只觉得手里一阵温暖，却看到手里多了一块莹碧的玉佩，刻着栩栩如生的凤凰图象。\n");
        } else
        {
              ob->move(who);
              message_vision("$N深情的对$n说：“我真的很喜欢你，这块龙纹佩代表我的心，请收下吧。\n",me,who);
              message_vision("$N将一块莹碧的玉佩递给$n。\n",me,who);
              tell_object(who,"你只觉得手里一阵温暖，却看到手里多了一块莹碧的玉佩，刻着栩栩如生的天龙图象。\n");
        }
        return 1;
}
