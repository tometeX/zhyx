// 山猫(adx) by snow 2000-05-15

#include <ansi.h>
inherit ROOM;

string look_shelf();

void create ()
{
        set ("short", "比武台");
        set("long", @LONG
这是一个四丈见方的擂台。粗壮结实的木柱撑起一片平台，四角的支柱上
高挂着四副对联，四面的观众都能清楚地看到台上的手起脚落。擂台角上有个
兵器架(shelf) ，刀剑鞭棒样样俱全，比武台后面是贵宾席。
LONG );
        set("info_sends",1);
        set("biwutai",1);
        set("exits", ([
                "north"   : __DIR__"caipan",
                "down"   : __DIR__"kantai2",
        ]));
set("item_desc", ([
                "shelf" : (: look_shelf :),
        ]));


        set("no_openshelf", 1);

        setup();
}

void init()
{
        add_action ("do_fight","fight");
        add_action ("do_fight","kill");
        add_action ("do_fight","hit");
        add_action ("do_work","quit");
        add_action ("do_work","halt");
        add_action("do_take","take");
        add_action("do_open","open");
        add_action("do_close","close");

}

int do_fight(string arg)
{
        object me=this_player();
        object *inv=all_inventory(environment(me));
        object ob;
        object who;
        int i;

        if(!arg) { 
                write("你要同谁比武？\n");
                return 1;
        }
        ob=present(arg, environment(me));
        if(!ob) {
                write("这里没有这个人！\n");
                return 1;
        }
        if(ob==me) {
                write("你要同自己比武？？？\n");
                return 1;
        }
        if(!interactive(ob)) {
                write("他现在无法同你比武！\n");
                return 1;
        }
        if(!userp(me) || !userp(ob)) {
                write("他现在无法同你比武！\n");
                return 1;
        }

        for(i=0; i<sizeof(inv); i++) {
                who=inv[i];
                if(who->is_fighting()) {
                        write("台上"+who->query("name")+"等正在比武，请稍侯！\n");
                        return 1;
                }
        }

        message("channel:chat",HIW"【比武场】"+
                me->query("family/family_name")+"的"+me->query("name")+"与"+
                ob->query("family/family_name")+"的"+ob->query("name")+
                "在比武台上较量高低！\n\n"NOR,users());

        me->set("biwu_fighter",1);
        ob->set("biwu_fighter",1);

	me->set_temp("last_opponent",ob);
	ob->set_temp("last_opponent",me);

        me->kill_ob(ob);
        ob->kill_ob(me);
        return 1;
}

void info_sends(string str)
{
        tell_room(__DIR__"kantai1", str);
        tell_room(__DIR__"kantai2", str);
        tell_room(__DIR__"kantai3", str);
}

int no_die(object me)
{
        object ob,obj,where;
	string id,id1;
	ob = me->query_temp("last_opponent");
	if (! ob)
		{
			message_vision (HIC"$N就地翻了十八个驴打滚，滚下了擂台！\n"NOR,me);
			me->revive();
			me->move(__DIR__"kantai1");
			me->set("eff_qi",me->query("max_qi")); 
			me->set("eff_jing",me->query("max_jing"));               
			me->add("qi",10);
			me->add("jing",10); 
			me->clear_condition();
			return 1;
		}
	
	id=ob->query("id");
	id1=me->query("id");

        me->delete_temp("last_opponent");
        ob->delete_temp("last_opponent");
        me->remove_all_killer();
        ob->remove_all_killer();
	me->clear_condition();
	ob->clear_condition();

        me->set("eff_qi",me->query("max_qi"));
        me->set("qi", me->query("max_qi"));
        me->set("eff_jing",me->query("max_jing"));  
        me->set("jing", me->query("max_jing"));
        me->set("jingli", me->query("max_jingli"));
        me->set("neili", me->query("max_neili"));
	me->revive();

        ob->set("eff_qi", ob->query("max_qi"));
        ob->set("qi", ob->query("max_qi"));
        ob->set("eff_jing", ob->query("max_jing"));
        ob->set("jing", ob->query("max_jing"));
	ob->set("jingli", ob->query("max_jingli"));
        ob->set("neili", ob->query("max_neili"));

        message("channel:chat",HIW"【比武场】"+
                ob->query("family/family_name")+"的"+ob->query("name")+"在比武台击败"+
                me->query("family/family_name")+"的"+me->query("name")+"！\n\n"NOR,users());

        message_vision (CYN"$N重重地摔在地上！\n"NOR,me);
        message_vision (CYN"\n$N慢慢从地上爬将起来，被壮汉扶着走下比武台。\n"NOR,me);
        me->move(__DIR__"kantai1");
        message_vision (CYN"$N被壮汉扶着慢慢走了过来。\n"NOR,me);
        message_vision (CYN"几名壮汉欢呼着簇拥着$N走下比武台。\n"NOR,ob);
        ob->move(__DIR__"kantai3");
        message_vision (CYN"$N被几名壮汉簇拥着走了过来。\n"NOR,ob);

        me->delete("biwu_fighter");
        ob->delete("biwu_fighter");

        if (!where=find_object(__DIR__"gate"))
                where=load_object(__DIR__"gate");
        obj=present("gongping zi", where);
        if(obj->query("fangshi")!="个人赛") {
                if(obj->query("start/juesai"))
                        obj->jieshu_biwu(id, id1);
                        obj->keep_biwu(id);
        }
        return 1;
}

string look_shelf()
{
        return 
"\n
这个是无意用千年红木定做的一个的兵器架，色彩鲜艳，十分华丽。
架上摆满了: 
                 钢刀(blade)    长剑(sword)
                 钢杖(staff)    长鞭(whip)
                 铁锤(hammer)   长棍(club)
                 暗器(throwing) 短兵(dagger)
                 钢甲(armor)

参加比武者可以按需要，随便拿取(take)使用。

                                     巫师组  敬启 
\n";
}

int do_open()
{
        if(wizardp(this_player()))
        {
                message_vision("$N把兵器架启封了。\n", this_player());
                this_object()->delete("no_openshelf");
                return 1;
        }
        else return 0;
}
int do_close()
{
        if(wizardp(this_player()))
        {
                message_vision("$N拿了条封条把兵器架给封了。\n", this_player());
                this_object()->set("no_openshelf", 1);
                return 1;
        }
        else return 0;
}

int do_work()
{
        write("这里不能使用这个指令！\n");
        return 1;
}
int do_take(string arg)
{
        object obj,ob;
        ob = this_player();
        if(this_object()->query("no_openshelf"))
        {
                message_vision("非大比武的时候，兵器架给封住了。\n", ob);
                return 1;
        }
        if( !arg || arg=="" )
        {
                message_vision("$N站在兵器架前，还没想好要什么兵器。\n", ob);
                return 1;
        }
        switch (arg)
        {
                case "sword":
                        obj = new("/clone/weapon/changjian");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一口长剑。\n",ob);
                        break;
                case "blade":
                        obj = new("/clone/weapon/gangdao");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一口钢刀。\n",ob);
                        break;
                case "staff":
                        obj = new("/clone/weapon/gangzhang");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一杆钢杖。\n",ob);
                        break;
                case "whip":
                        obj = new("/clone/weapon/changbian");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一条长鞭。\n",ob);
                        break;
                case "club":
                        obj = new("/clone/weapon/qimeigun");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一条齐眉棍。\n",ob);
                        break;
                case "hammer":
                        obj = new("/clone/weapon/hammer");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一把铁锤。\n",ob);
                        break;
                case "throwing":
                        obj = new("/clone/weapon/lianzi");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一包铁莲子。\n",ob);
                        break;
                case "dagger":
                        obj = new("/clone/weapon/dagger");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一把匕首。\n",ob);
                        break;
                case "armor":
                        obj = new("/clone/weapon/tiejia");
                        obj -> move(ob);
                        message_vision("$N从兵器架上取下一副铁甲。\n",ob);
                        break;
                default:
                        message_vision("$N站在兵器架前，还没想好要什么兵器。\n", ob);
        }
        return 1;
}

int valid_leave(object me, string dir)
{
        if ( !wizardp(me) && dir=="north" ) {
                return notify_fail("你即不是这里的巫师也不是武林宗师不能到贵宾席。\n");
        }

        if ( !wizardp(me) && dir=="down" ) {
                if( me->query("biwu_fighter") )
                        return notify_fail("你马上要比武了，不要到处乱跑。\n");
        }

        me->delete_temp("last_opponent");
        me->delete_temp("last_damage_from");
        me->remove_all_killer();

        return ::valid_leave(me, dir);
}


