#include <ansi.h>
inherit NPC;

object room = 0;

mixed  ask_skill1();
mixed  ask_skill2();
mixed  ask_skill3();
mixed  ask_skill4();

void create()
{
	set_name( "小虾米", ({ "xiao xiami", "xiami" }) );
	set("long", "他就是这是金庸群侠传里面的那位小虾米。\n");
	set("attitude", "friendly");
	set("title", HIR "无敌" NOR);
	set("nickname", HIG "野球拳" NOR);
        set("force_factor", 30);
        set("max_kee", 3000);
        set("max_sen", 3000);
        set("eff_gin", 3000);
        set("eff_kee", 3000);
        set("eff_sen", 3000);
        set("kee", 3000);
        set("sen", 3000);
        set("max_force", 3000);
        set("force", 3000);
        set("max_mana", 3000);
        set("mana", 3000);
	set("age", 18);
	set_temp("apply/damage",600);
        set("gender", "男性" );
	set("str", 40);
	set("cor", 35);
	set("cps", 30);
	set("per",10);
	set("max_force",5000);
	set("force_factor",40);
	set("combat_exp", 13000000);

	set_skill("force", 500);
	set_skill("yijinjing", 500);
        set_skill("dodge", 500);
        set_skill("feiyan-zoubi", 500);
        set_skill("unarmed", 500);
        set_skill("yeqiu-quan", 500);
        set_skill("parry", 500);
        set_skill("jingang-buhuaiti", 500);
        set_skill("literate", 300);

        map_skill("force", "yijinjing");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("unarmed", "yeqiu-quan");
        map_skill("parry", "jingang-buhuaiti");
	prepare_skill("unarmed", "yeqiu-quan");

        set("inquiry", ([ 
                "野球拳"   : "野球拳练到十层也能天下无敌！",
		"石头" : (: ask_skill1 :), 
		"剪刀" : (: ask_skill2 :), 
		"布" : (: ask_skill3 :), 
		"无双乱舞" : (: ask_skill4 :), 
        ]));

	setup();
        carry_object("/d/changan/npc/obj/choupao")->wear();
}

mixed ask_skill1()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/shitou"))
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "你还不会野球拳呢，跑来捣什么乱？";

        if (me->query_skill("yeqiu-quan", 1) < 250)
                return "你的野球拳至少也要练到五层才能学会这招！";

        message_sort(HIY "\n$n" HIY "打量了$N" HIY "一眼，随手攻出一拳。$N" HIY
                     "见来势平平，并不见奇，哪知在作出抵挡的一瞬间才发觉$n" HIY
                     "拳头已经不在是拳头，而是一块石头，一块金刚石，$N" HIY "顿时再也把持不住，被"
                     "这一拳击得接连旋转了数圈，好不容易才停了下来。\n\n" NOR,
                     me, this_object()); 

        command("say 好了，你自己回去练习吧。");
        tell_object(me, HIC "你学会了「石头」。\n" NOR);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/shitou", 1);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/jiandao"))
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "你还不会野球拳呢，跑来捣什么乱？";

        if (me->query_skill("yeqiu-quan", 1) < 250)
                return "你的野球拳至少也要练到五层才能学会这招！";

        message_sort(HIY "\n$n" HIY "食指中指一分，随手攻出一招。$N" HIY
                     "见来势平平，并不见奇，哪知在作出抵挡的一瞬间才发觉$n" HIY
                     "攻过来的竟然已经变成两道气流，$N" HIY "时心中一惊，顿被"
                     "这一招击中，衣服上留下了两个黑糊糊的洞。\n\n" NOR,
                     me, this_object()); 

        command("say 好了，你自己回去练习吧。");
        tell_object(me, HIC "你学会了「剪刀」。\n" NOR);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/jiandao", 1);
        return 1;
}
mixed ask_skill3()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/bu"))
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "你还不会野球拳呢，跑来捣什么乱？";

        if (me->query_skill("yeqiu-quan", 1) < 250)
                return "你的野球拳至少也要练到五层才能学会这招！";

        message_sort(HIY "\n$n" HIY "打量了$N" HIY "一眼，随手攻出一掌。$N" HIY
                     "见来势平平，并不见奇，哪知在作出抵挡的一瞬间才发觉$n" HIY
                     "这一掌竟然遮天蔽日一般，$N" HIY "连连后退，依然被"
                     "这一掌击得晕头转向，好不容易才回过神来。\n\n" NOR,
                     me, this_object()); 

        command("say 好了，你自己回去练习吧。");
        tell_object(me, HIC "你学会了「布」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/bu", 1);
        return 1;
}

mixed ask_skill4()
{
        object me;

        me = this_player();

        if (me->query("can_perform/yeqiu-quan/luan"))
                return "这一招我不是已经教过你了吗？还罗嗦什么！";

        if (me->query_skill("yeqiu-quan", 1) < 1)
                return "你还不会野球拳呢，跑来捣什么乱？";

        if (me->query_skill("yeqiu-quan", 1) < 500)
                return "只有野球拳练到十层圆满以后才能学会这招！";

        message_sort(HIY "\n$n" HIY "昂首看都不看$N" HIY "一眼，并没有任何动作。$N" HIY
                     "却顿时觉得，天底下竟然没有任何武功能够敌得过现在得小虾米"
                     "$N" HIY "呆了一个时辰才终于回过神来。大笑道：“我明白了！”\n\n" NOR,
                     me, this_object()); 

        command("say 好了，你自己回去练习吧。");
        tell_object(me, HIC "你学会了「无双乱舞」。\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("finger"))
                me->improve_skill("finger", 1500000);
        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("unarmed"))
                me->improve_skill("unarmed", 1500000);
        if (me->can_improve_skill("yeqiu-quan"))
                me->improve_skill("yeqiu-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        me->set("can_perform/yeqiu-quan/luan", 1);
        return 1;
}