//hbd_chen.c

#include <ansi.h>

inherit NPC;

#define PLACE "ca"
#define TYPE  "bad"
#define WAIT_TIME 60

mapping bang_bad = ([ 
        "name" : "黑白道",
        "id"   : "hbd",
        "place": "bje",      //总会
        "boss" : "黑白郎君",
        "place_name" : "长安" //分会
]);

void create()
{
        set_name("陈武", ({ "chen wu", "chen" }));
        set("gender", "男性");
        set("age", 28);
        set("long", "他就是" + bang_bad["name"] + "设在" + bang_bad["place_name"] + "的分坛首领。\n");
        set("nickname",HIB"黑"HIW"白"HIR"刹星"NOR);
        set("title",HIB"黑"HIW"白"NOR"道分坛主"NOR);
        set("per",22);
        set("combat_exp", 800000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        set_skill("unarmed", 20);
        set_skill("dodge", 20);
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver",2);
}
#include <boss_bad.h>

