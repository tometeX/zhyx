// wudu.c 蓝凤凰
#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
	set_name("蓝凤凰", ({ "lan fenghuang", "lan" }));
	set("long",  "她身穿蓝布印白花衫裤，围一条绣花围裙，色彩灿烂，金碧辉煌，\n耳上垂一对极大的黄金耳环，足有酒杯口大小。\n");
	set("gender", "女性");
	set("age", 20);
	set("attitude", "peaceful");
	set("shen_type", 1);
	set("str", 37);
	set("int", 32);
	set("con", 35);
	set("dex", 36);
	
	set("max_qi", 6000);
	set("max_jing", 3000);
	set("neili", 7500);
	set("max_neili", 7500);
	set("jiali", 10);
	set("combat_exp", 25000000);
	set("score", -10000);

        set_skill("force", 560);
        set_skill("xiuluo-yinshagong", 560);
        set_skill("dodge", 540);
        set_skill("jinshe-youshenbu", 540);
        set_skill("hand", 540);
        set_skill("qianzhu-wandushou", 540);
        set_skill("parry", 540);
        set_skill("throwing", 540);
        set_skill("hansha-sheying", 540);
        set_skill("literate", 520);
        set_skill("poison", 300);
        set_skill("wudu-qishu", 300 );
        set_skill("martial-cognize", 540);

        map_skill("force", "xiuluo-yinshagong");
        map_skill("dodge", "jinshe-youshenbu");
        map_skill("hand", "qianzhu-wandushou");
        map_skill("throwing", "hansha-sheying");
        map_skill("parry", "jinwu-goufa");
        map_skill("sword", "jinwu-goufa");
        map_skill("whip", "ruanhong-zhusuo");
        map_skill("poison", "wudu-qishu");

        prepare_skill("hand", "qianzhu-wandushou");

        create_family("五毒教", 0, "教主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.wan" :),
                (: perform_action, "hand.zhugu" :),
                (: exert_function, "recover" :),
        }) );


	setup();
	carry_object("/clone/misc/cloth")->wear();
}
