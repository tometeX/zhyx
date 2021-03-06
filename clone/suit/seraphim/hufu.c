//update by xiner
#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIB"青龙护符"NOR,({"seraphim hufu","hufu"}));
	set_weight(3000);
	if(clonep())
	set_default_object(__FILE__);
	else{
		set("unit","块");
		set("long",HIC"这是一枚青龙护符，能唤醒青龙套装的潜能。"NOR"
成套装备指令："HIG"huanxing"NOR"
成套装备："HIB"[青龙护符]"NOR" "HIR"蛟龙之鳞"NOR" "HIR"虬龙之角"NOR" "HIR"夔龙之足"NOR" "HIR"应龙之翼"NOR"
成套效果："HIG"唤醒体内潜在的力量，临时附加武器伤害和有效等级。"NOR"\n");
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

	if(me->query_temp("seraphimeff"))
		return notify_fail("你已经呼应了青龙护符！\n");

	if(me->is_busy())
		return notify_fail("你正忙着呢!\n");

	if(!jia=present("seraphim armor",me))
		return notify_fail("你还缺少"HIR"蛟龙之鳞"NOR"\n");
	if(!head=present("seraphim horn",me))
		return notify_fail("你还缺少"HIR"虬龙之角"NOR"\n");
	if(!shoe=present("seraphim foots",me))
		return notify_fail("你还缺少"HIR"夔龙之足"NOR"\n");
	if(!pifeng=present("seraphim wing",me))
		return notify_fail("你还缺少"HIR"应龙之翼"NOR"\n");

	if(environment(this_object())!=me)
		return notify_fail("护符必须携带在身上才能发挥作用。\n");

	if(me->query("con")<35)
		return notify_fail("你的先天根骨不足无法施展青龙护符。\n");

//	if(me->query_skill("zuoyou-hubo")>1)
//		return notify_fail("你学有左右互搏之术，无法唤醒青龙之力的灵力。\n");

	if((int)me->query("jingli")<500)
		return notify_fail("你现在精力不够，难以唤醒青龙之力的灵力。\n");

	if((jia->query("equipped")!="worn")||(head->query("equipped")!="worn")||(pifeng->query("equipped")!="worn")||(shoe->query("equipped")!="worn"))
		return notify_fail("你必须要穿上整套青龙套装。\n"NOR);

	message_vision(HIG"$N"HIG"手中"HIB"青龙护符"HIG"一闪化做一条青龙附与$N"HIG"的兵器之上！\n"NOR,me);
	me->set_temp("seraphimeff",1);
	me->add_temp("apply/club", (int)me->query_con()/5);
	me->add_temp("apply/whip", (int)me->query_con()/5);
	me->add_temp("apply/sword", (int)me->query_con()/5);
	me->add_temp("apply/blade", (int)me->query_con()/5);
	me->add_temp("apply/staff", (int)me->query_con()/5);
	me->add_temp("apply/hammer", (int)me->query_con()/5);
	me->add_temp("apply/damage", 200);
	me->add("jingli",-300);
	call_out("seraphim_ok",me->query_con(),me);

	return 1;
}


void seraphim_ok(object me)
{
	if(!me)return;
	me->delete_temp("seraphimeff");

	me->add_temp("apply/club", - (int)me->query_con()/5);
	me->add_temp("apply/whip", - (int)me->query_con()/5);
	me->add_temp("apply/sword", - (int)me->query_con()/5);
	me->add_temp("apply/blade", - (int)me->query_con()/5);
	me->add_temp("apply/staff", - (int)me->query_con()/5);
	me->add_temp("apply/hammer", - (int)me->query_con()/5);
	me->add_temp("apply/damage", - 200);

	message_vision(HIG"$N"HIG"微微一愣，兵器上的青龙渐渐消失不见了！\n"NOR,me);
}