#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("徐子陵", ({ "xu ziling", "xu", "ziling"}));
        set("long", "一个俊俏的白衣少年，他就是名震天下的徐子陵。\n"); 
        set("nickname", HIR "九字真言" HIY "金刚不坏体" NOR);
        set("title", HIY "陆佰级" NOR);
        set("gender", "男性");
        set("age", 26);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 30);

        set("max_qi", 50000);
        set("max_jing", 40000);
        set("max_neili", 20000);
        set("neili", 20000);
        set("jiali", 100);
        set("combat_exp", 100000000);

        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: perform_action, "parry.jingang" :),
                (: perform_action, "hand.jie" :),
                (: perform_action, "hand.jiuzi" :),
        }) );

        set_skill("dodge", 600);
        set_skill("hand", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("shou-yin", 600);
        set_skill("jiuzi-zhenyan", 600);
        set_skill("jingang-buhuaiti", 600);
        set_skill("jinzhong-zhao", 600);	
        set_skill("zhuangzi-wu", 600);
        set_skill("force", 600);
        set_skill("changsheng-jue", 600);
        set_skill("blade", 600);
        set_skill("badao-daofa", 600);
        set_skill("literate", 500);
//      set_skill("count", 200);
        set_skill("buddhism", 350);
        set_skill("lamaism", 350);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "badao-daofa");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("parry", "jingang-buhuaiti");
        map_skill("hand", "jiuzi-zhenyan");
		
	set_temp("apply/damage", 300);
	set_temp("apply/unarmed_damage", 350);
        set_temp("apply/armor", 700);
        set("apply/dodge", 400); 

        prepare_skill("hand", "jiuzi-zhenyan");

        setup();

        carry_object("/d/zhuanshi/sky/npc/obj/cloth1")->wear();
        carry_object("/d/zhuanshi/sky/npc/obj/hands")->wear();
}


int accept_fight(object ob)
{
        if (is_fighting())
        {
                message_vision(CYN "$N" CYN "对$n" CYN "叫道：你先别急"
                               "，我打完这架就来领教你的。\n" NOR,
                               this_object(), ob);
                return -1;
        }       

        if (query("qi") < 200 ||
            query("jing") < 100 ||
            query("neili") < 250)
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道：我现"
                               "在太累了，待我歇会儿再说吧。\n" NOR,
                               this_object(), ob);
                return -1;
        }
  

        message_vision(HIW "$N" HIW "大喜道：好好好！我正手痒痒，咱们"
                       "来比划比划！\n" NOR, this_object(), ob);

        competition_with(ob);
        return -1;
}


void win()
{
        object ob;
        if (! objectp(ob = query_competitor()))
                return;

        message_vision(CYN "$N" CYN "看了看$n" CYN "，嘿嘿笑道：你的水"
                       "平太菜了，要好好练功，好好练功。\n" NOR,
                       this_object(), ob);

        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        set("neili", query("max_neili"));
	remove_all_enemy(1);

        ::win();
}


void lost()
{
	command("say 你已经很强了啊！");
        ::lost();
}

void unconcious()
{
        say( HIC"徐子陵说道：“想搞我没那么容易。”说完就从怀里拿出一颗天王保命丸塞进嘴里嚼了起来。\n"NOR);
        say( HIC"片刻之间，徐子陵又恢复了精神，“嘿嘿”奸笑了两声。\n"NOR);
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        set("neili", query("max_neili"));
	remove_all_enemy(1);
	lost();
}
void die()
{
        unconcious();
}

