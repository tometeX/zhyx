
//喜糖 (基本force,force,dodge,parry)各加1级


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "囍烟" NOR, ({ "xi yan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "这是二○○九年五一离子结婚发的囍烟。\n这可是黄鹤楼（1916）哦！" NOR);
                set("unit", "包");
                set("no_sell",1);
                set("weight", 10);                
             }
        setup();
}

void init()
        {
                add_action("do_chou","chou");
        }
                

int do_chou( string arg )
{       
        if (arg == "xi yan")

        {
         string mapsk;   
         object me;
        
         me = this_player();

        if ( me->query("liwu/20090501/eat1") )
        {write(HIR"你已经吃过囍烟了还想要么！\n"NOR);return 1;}

        message_vision(HIY "$N吸了一口囍烟，精神百倍，连忙对着离子一个劲儿连说:“恭喜！恭喜！\n祝：百 年 好 合！\n" NOR, me);

	message("vision", HIR"【喜报喜报】" + me->query("name") + "祝福离子夫妻二人：心心相印！永结同心！相亲相爱！百年好合！\n"NOR, users());

	log_file("static/wuyi", sprintf("%s(%s) chou 囍烟 at %s.\n",
                 me->name(1), me->query("id"), ctime(time())));

	me->set("liwu/20090501/eat1", 1);

	me->add("combat_exp", 50000);
        me->add("potential",  50000);

	if (me->can_improve_skill("sword"))
		me->improve_skill("sword", 1500000);
	if (me->can_improve_skill("unarmed"))
		me->improve_skill("unarmed", 1500000);
	if (me->can_improve_skill("finger"))
		me->improve_skill("finger", 1500000);
	if (me->can_improve_skill("blade"))
		me->improve_skill("blade", 1500000);
	if (me->can_improve_skill("hand"))
		me->improve_skill("hand", 1500000);
	if (me->can_improve_skill("cuff"))
		me->improve_skill("cuff", 1500000);
	if (me->can_improve_skill("strike"))
		me->improve_skill("strike", 1500000);

	destruct(this_object());
	return 1;
        }
	else
	{return 0;}
}
                
int query_autoload() { return 1; }