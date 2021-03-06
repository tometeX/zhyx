#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

#include "fight.h"



void create()
{
        set_name("神秘长老", ({ "shenmi zhanglao", "zhanglao" }));
        set("long", @LONG
一位神秘的丐帮长老，没有人知道他的来历。
LONG);

        set("title", "丐帮九袋长老");
        set("gender", "男性");
        set("age", 40);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 40000);
        set("max_jing", 30000);
        set("neili", 43000);
        set("max_neili", 43000);
        set("jiali", 1800);
        set("combat_exp", 22000000);
        set("score", 30000000);
        set("shen_type", 1);
        
        set_skill("force", 600);
		set_skill("huimeng-xinfa", 600);
        set_skill("dodge", 600);
        set_skill("feiyan-zoubi", 600);
        set_skill("unarmed", 600);
        set_skill("nap-unarmed", 600);     
        set_skill("parry", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "huimeng-xinfa");
        map_skill("unarmed", "nap-unarmed");
        map_skill("parry", "nap-unarmed");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("unarmed", "nap-unarmed");

        create_family("丐帮", 18, "长老");


        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 500);
        set_temp("apply/unarmed_damage", 500);
        set_temp("apply/armor", 500);

        setup();
        carry_object("/d/gaibang/npc/obj/cloth")->wear();

}

void attempt_apprentice(object ob)
{
        string title = ob->query("title");
        int lvl = ob->query("family/beggarlvl");

        if (! permit_recruit(ob))
                return;

        if (ob->query("combat_exp") < 1000000)
        {
                command("say 你的江湖经验不够，还是先向其他师父学习吧。");
                return;
        }

        if (ob->query("shen") < 20000)
        {
                command("say 你身为丐帮弟子，竟然不做好事？");
                return;
        }

        if (ob->query("family/beggarlvl") < 9)
        {
                command("say 你在本帮的地位太低，还是先向其他师父学习吧。");
                return;
        }


        command("nod");
        command("say 我便收下你，希望日后努力上进，能有所作为。");
        command("recruit " + ob->query("id"));

        if (ob->query("class") != "beggar")
                ob->set("class", "beggar");

        if (lvl > 0)
        {
                ob->set("family/beggarlvl", lvl);
                ob->set("title", title);
        }
}
