//dazao.c
//by wsw 2004 2 25
//打造装备
/*
dazao
     /armor		原始装备
           /file  文件
           /att   属性
     /baoshi  	材料
     /time    	给物的时间
     /gold
     	   /num  数量
     	   /done ok
     /done		条件满足
     /ask       问过了。

*/

// #include <norumor.c>

#include <ansi.h>
inherit NPC;
//int do_give(string arg);
int accept_ok(object who);
int dazao();
object get_item(object who);
int do_cancel();

int do_counter();
void if_dazao(string arg,object me);
void get_room(string arg,object me);
void make_counter(string arg,object me,string str,int price);


void create()
{
	set_name(HIM"打造师"NOR, ({"master"}));
	set("long","他可以帮你打造高级的防具。\n");
	set("gender", "男性");
	set("combat_exp", 1000);
	set("age", 26);
	set("per", 14);
	set("attitude", "friendly");
	set("shen_type", 1);
	set_skill("unarmed", 10);
	set("max_price",20);
    //    set("inquiry", ([
    //             "打造" : (: dazao :),
    //             "dazao" : (: dazao :),
    //             "放弃" : (: do_cancel :),
    //             "cancel" : (: do_cancel :),
    //             "柜台" : (: do_counter :),

    //     ]) );//        if( clonep() ) CHANNEL_D->register_relay_channel("rumor");
	setup();

	// carry_object("/d/obj/cloth/linen")->wear();
	// carry_object("/d/wiz/npc/caishen")->wear();
	// add_money("silver", 1);
}
/*
void init()
{
	int i;
	object ob;
	object *obj = all_inventory();

	//::init();
	if (obj)
	{
		for (i = 0; i < sizeof(obj); i++)
		{
			destruct(obj[i]);
		}
	}
	if (interactive(ob = this_player()) && !is_fighting())
	{
		remove_call_out("greeting");
		call_out("greeting", 1, ob);
	}

	//       add_action("do_give", "give");
}

void greeting(object ob)
{
        if( !ob || !visible(ob) || environment(ob) != environment() ) return;
            say( name()+"笑咪咪地说道：这位" +RANK_D->query_respect(ob)
                                + "，你是来打装备的吧？。\n");
}

int accept_object(object who, object ob)
{

	int gold=F_VENDOR_SALE->get_inflation();
	string *file=({
		NEWITEMS_DIR+"/newarmor/armor",
		NEWITEMS_DIR+"/newarmor/boots",
		NEWITEMS_DIR+"/newarmor/cloth",
		NEWITEMS_DIR+"/newarmor/finger",
		NEWITEMS_DIR+"/newarmor/hands",
		NEWITEMS_DIR+"/newarmor/head",
		NEWITEMS_DIR+"/newarmor/neck",
		NEWITEMS_DIR+"/newarmor/shield",
		NEWITEMS_DIR+"/newarmor/surcoat",
		NEWITEMS_DIR+"/newarmor/waist",
		NEWITEMS_DIR+"/newarmor/wrists"});

	if (!who->query("dazao/ask")) {
		tell_object(who,HIW"你这是干什么啊？想行贿吗？我可不吃这一套!\n"NOR);
		command("kick "+who->query("id"));
		return 0;
	}
	if (ob->query("armor_prop/armor")) {
		if ( who->query("dazao/armor")) {
			tell_object(who,HIW"你已经给过了!\n"NOR);
			return 0;
		}
		if (ob->query("level") < 1) {
			who->set("dazao/armor/file",file[random(sizeof(file))]);


		}
		else {
			who->set("dazao/armor/file",base_name(ob));
			who->set("dazao/armor/att",ob->query_entire_dbase());
		}
		gold=(ob->query("level")+1)*500*gold;
		who->set("dazao/gold/num",gold);
		tell_object(who,HIW"你打造这件装备需要"+
		    F_VENDOR_SALE->price_string(gold)+"手工费。\n");
		accept_ok(who);
		return 1;
	}
	//金属块升级装备的等级，
	if (ob->query("material") == "metal" && ob->query("level") >0) {
		if ( !who->query("dazao/armor")) {
			tell_object(who,HIW"你要升级什么装备啊？\n"NOR);
			return 0;
		}
		if (ob->query("level")-who->query("dazao/armor/att/level") != 1 ) {
			tell_object(who,HIW"这样东西对你的装备不起什么作用。\n"	NOR);
			return 0;
		}
		if (who->query("dazao/baoshi")) {
			tell_object(who,HIW"你已经给过了!\n"NOR);
			return 0;
		}
		who->set("dazao/baoshi/file",base_name(ob));
		who->set("dazao/baoshi/att",ob->query_entire_dbase());
		accept_ok(who);
		return 1;
	}
	//宝石升级装备的属性
	if (ob->query("material") == "baoshi" && ob->query("level") >0) {
		if ( !who->query("dazao/armor")) {
			tell_object(who,HIW"你要升级什么装备啊？\n"NOR);
			return 0;
		}
		if (who->query("dazao/armor/att/level") != ob->query("level")) {
			tell_object(who,HIW"这样东西对你的装备不起什么作用吧？\n"	NOR);
			command("? "+who->query("id"));
			return 0;
		}
		if (who->query("dazao/baoshi")) {
			tell_object(who,HIW"你已经给过了!\n"NOR);
			return 0;
		}
		who->set("dazao/baoshi/file",base_name(ob));
		who->set("dazao/baoshi/att",ob->query_entire_dbase());
		accept_ok(who);
		return 1;
	}

	//如果给钱。
	if (ob->query("money_id")) {
		if ( !who->query("dazao/armor")) {
			tell_object(who,HIW"你给钱给我干嘛？\n"NOR);
			return 0;
		}
		if ( who->query("dazao/gold/done") == "ok") {
			tell_object(who,HIW"你的钱是不太多了？救济一下穷人吧！\n"NOR);
			return 0;
		}
		if (ob->value()<who->query("dazao/gold/num")) {
			tell_object(who,HIW"太少了吧？\n"NOR);
			return 0;
		}
		who->set("dazao/gold/done","ok");
		accept_ok(who);
		return 1;
	}

	tell_object(who,HIW"这样东西我拿着没有用啊？\n");
	command("kick "+who->query("id"));
	return 0;

}

int accept_ok(object who)
{
	who->set("dazao/time",time());
	if (who->query("dazao/armor")
	  && who->query("dazao/baoshi")
	  && who->query("dazao/gold/done") == "ok")
	{
		who->set("dazao/done","ok");
		write("好的，过一个小时后来拿吧!\n");
	}
	return 1;
}


int dazao()
{
	object ob,obj=this_object();
	object who=this_player();

	if (who->query("dazao/done") == "ok") //拿装备
	{
		if(time()-who->query("dazao/time") <= 3600) {
			tell_object(who,HIW"不要急，你的装备还没有打好呢。\n"NOR);
			return 1;
		}
		ob=get_item(who);
		if(ob && ob->move(who)) {
			tell_object(who,HIW"这是你打造的装备。\n");
			command("addoil "+who->query("id"));
		} else {
			tell_object(who,HIW"不好意思，你的东西弄丢了。\n");
		}
		who->delete("dazao");
		return 1;
	}
	else {
		if (who->query("dazao/ask")) {
			tell_object(who,HIW"你烦不烦啊？！\n"NOR);
			return 1;
		}
		tell_object(who,HIW"你是要打造装备吗？你找对人了！\n"NOR);
		command(":D "+who->query("id"));
		who->set("dazao/ask","done");
		return 1;

	}

}

object get_item(object who)
{
    object ob;
    mapping attribute;
    string *key;
    int level,i,j,color;
    string *str=({
	HIW"普通",
	HIW"精致",
	HIW"卓越",
	HIW"非凡",
	HIW"神圣",
	});
    mixed *att=({
    	({"red",	"dodge",	({4,9,18,28,30})}),
    	({"blue",	"armor",	({13,17,46,70,75})}),
    	({"yellow",	"spells",	({4,9,18,28,30})}),
    	({"purple",	"armor_vs_force",({80,220,410,650,700})}),
    	({"green",	"armor_vs_spells",({80,220,410,650,700})}),
    	});

    ob=new(who->query("dazao/armor/file"));
    if (!ob) return 0;
    attribute=who->query("dazao/armor/att");
    if (mapp(attribute)) {
 	    key=keys(attribute);
   	    key = sort_array(key, 0);
	    for(j=0; j<sizeof(key); j++) {
        	ob->set(key[j], attribute[key[j]]);
	    }
    }
    //如果不是打造过的装备，清除原有属性
    if (!ob->query("changed")) {
    	ob->delete("armor_prop");
    	ob->set("armor_prop/armor",10);
    }

    level = who->query("dazao/baoshi/att/level");
    if (level > 5) level = 5;
    if (level < 1) level = 1;

    //如果是加金属打造
    if (who->query("dazao/baoshi/att/material") == "metal") {
    	ob->set("level",level);
    	ob->set_name(str[level-1]+"的"+ob->query("name")+NOR,ob->parse_command_id_list());
    	ob->set("type","dazao");
    	ob->set("long",ob->query("name"));
		if (level==1) 	ob->set("armor_wiel/exp",50);
		if (level==2) 	ob->set("armor_wiel/exp",100);
		if (level==3) 	ob->set("armor_wiel/exp",500);
		if (level==4) 	ob->set("armor_wiel/exp",1000);
		if (level==5) 	ob->set("armor_wiel/exp",1500);

    }

    //如果是宝石打造
    if (who->query("dazao/baoshi/att/material") == "baoshi") {
    	j=10;
    	switch (color=who->query("dazao/baoshi/att/color")) {
    		case 1 : j=0;break;
     		case 2 : j=1;break;
    		case 4 : j=2;break;
     		case 3 : j=3;break;
     		case 6 : j=4;break;
     		case 5: j=random(sizeof(att));break;
     		case 7: j=random(sizeof(att));break;
//     		default	j=10;
   		}
		if (j== 10) return 0;
		ob->set("armor_prop/"+att[j][1],att[j][2][level-1]);
		//钻石再加一次。
		if (color == 7) {
			i=j;
			while (j == i) j = random(sizeof(att));
			ob->set("armor_prop/"+att[j][1],att[j][2][level-1]);
		}
    }
	ob->set("changed",1);
//	ob->set("long",ob->query("name"));
    return ob;

}

int do_cancel()
{
	object who=this_player();
    if (who->query("dazao")) {
	who->delete("dazao");
	tell_object(who,HIW"不要打造了？好吧，不过你以前给我的东西我可不还哦。\n");
	command("shrug "+who->query("id"));
    	return 1;
    } else return 0;
}

int do_counter()
{
	object me=this_player();

	if (me->query("playercity/counter/num") >= 1) {
		write("你已经有了一个柜台了。\n");
		return 1;
	}
	write("你需要买柜台吗？我这里送货上门哦。(Y/N):");
	input_to((:if_dazao:),me);
	return 1;
}

void if_dazao(string arg,object me)
{
	if (arg != "Y" && arg != "y") {
		write("以后没事不要来烦我！\n");
		return;
	}

	write("请输入你要摆放柜台的房间号（格式：x*y*z*）：");
	input_to((: get_room :),me);
}

void get_room(string arg,object me)
{
	int price;

	if (!arg) return;
	if(member_array(arg+".c",get_dir(PLAYERCITY_FILE_DIR)) <= -1) {
		write("没有这个房间。\n");
		return ;
	}

	arg=PLAYERCITY_FILE_DIR+arg+".c";

	if ( arg->query("owner_id") != me->query("id")) {
		write("这不是你的房间。\n");
		return;
	}
	if ( arg->query("outdoors")) {
		write("柜台不能摆在室外。\n");
		return;
	}

	price = F_VENDOR_SALE->get_inflation();
    price *=10000;
	write("一个柜台需要花费"+F_VENDOR_SALE->price_string(price)+"，\n你确定要买吗？(Y/N):");
	input_to((: make_counter :),me,arg,price);
}

void make_counter(string arg,object me,string str,int price)
{
	string counter_name;
	if (arg != "Y" && arg != "y") {
		write ("好吧，需要的时候再找我。\n");
		return;
	}
	if (price > me->query("balance")) {
		write("你银行户头上没有这么多钱。\n");
		return;
	}
	write("文件名："+str+"\n");
	//生成柜台文件
	counter_name=PLAYERCITY_FILE_DIR+"obj/counter-"+me->query("id")+".c";
    if (cp(PLAYERCITY_FILE_DIR+"obj/counter.c",counter_name)) {
    	write("你花费"+F_VENDOR_SALE->price_string(price)+"买下了一个柜台。\n");
    	log_file("playercity",sprintf("[%s] %s buy %s at %s.\n",ctime(time()),
    		this_player()->query("id"),counter_name,str));
    }
    else { write("买柜台失败！\n");return;}

}
*/
