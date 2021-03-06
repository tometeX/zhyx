// gaibang npc code

inherit NPC;

void create()                                                                   
{
        set_name("裘万家", ({"qiu wanjia", "qiu", "wanjia"}));
        set("title", "丐帮二袋弟子");
        set("gender", "男性");
        set("age", 16);
        set("rank", 2);
        set("long",
                "这是位地痞似的丐帮二袋弟子，看来是个吃得看的小地痞。\n");
        set("attitude", "peaceful");
        set("class", "beggar");
        set("str", 19);
        set("int", 20);
        set("con", 20);
        set("dex", 23);
        set("max_qi", 150);
        set("max_jing", 140);
        set("neili", 370);
        set("max_neili", 370);
        set("jiali", 10);
        set("combat_exp", 12000);
        set_skill("force", 35);
        set_skill("jiaohua-neigong", 35);
        set_skill("unarmed", 35);
        set_skill("changquan", 35);
        set_skill("dodge", 35);
        set_skill("feiyan-zoubi", 35);
        set_skill("parry", 35);
        set_skill("begging", 35);
        set_skill("checking", 35);
        map_skill("force", "jiaohua-neigong");
        map_skill("unarmed", "changquan");
        map_skill("dodge", "feiyan-zoubi");
        create_family("丐帮", 20, "弟子");
        setup();

        carry_object("/d/gaibang/obj/budai")->set_amount(1);
        carry_object("/d/gaibang/obj/budai")->wear();
}

#include "/kungfu/class/gaibang/promote.h"

