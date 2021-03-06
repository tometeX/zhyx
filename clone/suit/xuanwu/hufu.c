//update by xiner
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIW"玄武守护"NOR,({"xuanwu hufu","hufu"}));
	set_weight(3000);
	if(clonep())
	set_default_object(__FILE__);
	else{
		set("unit","块");
		set("long",HIC"这是一块刻有玄武神兽的护符，能唤醒玄武套装的潜能。"NOR"
成套装备指令："HIG"huanxing"NOR"
成套装备："HIR"[玄武守护]"NOR" "HIW"玄武战甲"NOR" "HIW"玄武战盔"NOR" "HIW"玄武战靴"NOR" "HIW"玄武披风"NOR"
成套效果："HIG"牺牲部分攻击力以换取防御力的大幅度提升。"NOR"\n");
		set("value",100000);
		set("no_steal",1);
		set("no_beg",1);
		set("no_sell",1);
		set("material","crystal");
	}
	setup();
}
int query_autoload()
{
	return 1;
}

void init()
{
	add_action("do_hx","huanxing");
}

int do_hx()
{
	object jia,head,shoe,pifeng;
	object me=this_player();
	object ob=this_object();

	if(me->query_temp("xuanwueff"))
		return notify_fail("你已经呼应了玄武守护！\n");

	if(me->is_busy())
		return notify_fail("你正忙着呢!\n");

	if(!jia=present("xuanwu armor",me))
		return notify_fail("你还缺少"BLK"玄武"HIW"战甲"NOR"\n");
	if(!head=present("xuanwu helmet",me))
		return notify_fail("你还缺少"BLK"玄武"HIW"战盔"NOR"\n");
	if(!shoe=present("xuanwu shoes",me))
		return notify_fail("你还缺少"BLK"玄武"HIW"战靴"NOR"\n");
	if(!pifeng=present("xuanwu coat",me))
		return notify_fail("你还缺少"BLK"玄武"HIW"披风"NOR"\n");

	if(environment(this_object())!=me)
		return notify_fail("护符必须携带在身上才能发挥作用。\n");

	if(me->query("dex")<35)
		return notify_fail("你的先天身法不足无法施展玄武守护。\n");

//	if(me->query_skill("zuoyou-hubo")>1)
//		return notify_fail("你学有左右互搏之术，无法唤醒玄武守护的灵力。\n");

	if((int)me->query("jingli")<500)
		return notify_fail("你现在精力不够，难以唤醒玄武守护的灵力。\n");

	if((jia->query("equipped")!="worn")||(head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")||(shoe->query("equipped")!="worn"))
		return notify_fail("你必须要穿上整套玄武套装。\n"NOR);

	message_vision(HIY"$N"HIY"将内力输入"BLK"玄武守护"HIY"之中，$N"HIY"周身浮现出一层密密的鳞甲！\n"NOR,me);
	me->set_temp("xuanwueff",1);
        me->add_temp("apply/attack", - (int)me->query_dex() / 5);
        me->add_temp("apply/defense", (int)me->query_dex() / 4);
	me->add_temp("apply/armor", (int)me->query_dex() * 2);
	me->add("jingli",-300);
	call_out("xuanwu_ok",me->query_dex(),me);

	return 1;
}


void xuanwu_ok(object me)
{
	if(!me)return;
        me->add_temp("apply/attack", (int)me->query_dex() / 5);
        me->add_temp("apply/defense", - (int)me->query_dex() / 4);
	me->add_temp("apply/armor", - (int)me->query_dex()* 2);
	me->delete_temp("xuanwueff");
	message_vision(HIY"$N"HIY"精神一懈，周身中的鳞甲渐渐消失不见了！\n"NOR,me);
}