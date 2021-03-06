 // nezha.c
 //哪吒三太子
 //PLZW 2003-11-29

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("哪吒三太子", ({ "ne zha", "ne", "zha" , "nezha"}) );
        set("title", HIM "莲花童子" NOR);
        set("gender", "男性");
        set("age", 16);
        set("long", "这是一个淘气可爱的小孩子，却隐隐透出不凡的气质。\n");
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 25000);
        set("neili", 25000);
        set("max_jing", 25000);
        set("jing", 25000);
        set("max_qi", 30000);
        set("qi", 30000);
        set("jingli", 25000);
        set("max_jingli", 25000);

        set("str", 120);
        set("int", 45);
        set("con", 120);
        set("dex", 120);

        set_skill("unarmed", 1500);
        set_skill("sword", 1500);
        set_skill("parry", 1500);
        set_skill("dodge", 1500);
        set_skill("force", 1500);

        set("jiali", 400);

        set_temp("apply/attack", 400);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 1000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

 		message_vision(HIW "$N" HIW "冷哼一声，变出三头六臂挥舞着手中的乾坤圈向你袭来。\n" NOR,	this_object(), ob);
        ::fight_ob(ob);
        if (! is_killing(ob->query("id")))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N扫了$n一眼，没有理$n。\n",
                       this_object(), ob);
        return 0;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
		me->set("neili", me->query("max_neili"));
        switch(random(8))
        {
        	case 7:
		        ob->receive_wound("qi", 400 + random(400), me);
        		return HIY "$N"HIY"手中"HIR"混天凌"HIY"射出各种光芒眩目夺人，一道道神采映射得天地尽\n"
        					"失色彩， 迅捷无伦的击中$n" HIY"，令人避无可避！\n" NOR;
        		break;
        	case 6:
        	    ob->receive_wound("qi", 300 + random(300), me);
				return HIC "$N"HIC"手中"HIG"乾坤圈"HIC"化作数道光芒向$n袭来，$n被打得连吐几口鲜血。\n" NOR;
        		break;
        	default:
        	    ob->receive_wound("qi", 200 + random(200), me);
        		return HIR "$N" HIR "手中火焰枪蓦的腾起数道火焰，将$n接连逼退了数步，惨叫连连。\n" NOR;
        		break;
        }
        	
}

void unconcious()
{
        die();
}

void die()
{
        object ob;
        switch(random(3))
        {
            case 2:
                ob = new("/clone/gift/fenghuolun");
                break;
            default:
                ob = new("/clone/gift/huntianling");
                break;
        }
        command("chat 呀！想不到凡人也有如此厉害的！");
        message_sort(HIR "$N" HIR "吐一口鲜血，驾云而去。只听叮玲玲一声"
                     "轻响，$N" HIR "掉下了一" + ob->query("unit") +
                     ob->name() + HIR "。\n", this_object());
        ob->move(environment());
        destruct(this_object());
}

void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N急急忙忙的走了。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + name() + HIM "被托塔李天王捉回天庭，等候玉帝发落。\n" NOR);
                destruct(this_object());
                return;
        }
        NPC_D->random_move(this_object());
}

