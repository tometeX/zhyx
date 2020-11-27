// liumang.c 流氓

inherit "/inherit/char/b_npc.c";   

void create()
{
        set_name("打手", ({ "da shou", "da", "shou" }));
	set("gender", "男性");
	set("age", 19);
        set("long", "他是一个成天游手好闲的流氓。经常强抢人家地盘！\n");
	
        set("combat_exp", 4000000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 200);
	set_skill("dodge", 200);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}
