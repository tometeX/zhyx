
#include <ansi.h>

inherit NPC;
inherit F_DEALER;

//int ask_reborn(); 
int ask_tiaozheng();
//string ask_2009NewYearGift();

void create()

{
    set_name(HIG"狼神"NOR, ({"dgdg_boss"}));
    set("title", HIR"［"HIW"隐藏BOSS"HIR"］"NOR);
    set("gender", "男性");
        set("str", 35);
        set("int", 13);
        set("con", 34);
        set("dex", 32);
        set("per", 40);

    set("vendor_goods", ({         
                "/d/zhuanshi/obj/zhen",
                "/u/kasumi/obj/bathwater",                                      
        }));
    set("max_qi", 80000);
        set("max_jing", 20000);
        set("neili", 60000);
        set("max_neili", 60000);
        set("jiali", 200);

        set("combat_exp", 95000000);
        set_skill("unarmed", 700);
        set_skill("sword", 750);
        set_skill("claw", 700);
        set_skill("strike", 800);
        set_skill("hand", 700);
        set_skill("cuff", 700);
        set_skill("parry", 800);
        set_skill("dodge", 800);
        set_skill("force", 800);
        set_skill("yunv-xinjing", 750);
        set_skill("zhuangzi-wu", 800);
        set_skill("suxin-jian", 1000);
        set_skill("qiankun-danuoyi", 700);
        set_skill("yinyang-shiertian", 800);
        set_skill("martial-cognize", 700);
        set_skill("zuoyou-hubo", 400);

        map_skill("parry", "qiankun-danuoyi");
        map_skill("force", "yunv-xinjing");
        map_skill("dodge", "zhuangzi-wu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("sword", "suxin-jian");
        map_skill("strike", "liuyang-zhang");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("unarmed", "yinyang-shiertian");   
        
        set("inquiry", ([ 
                   // "转世" : (: ask_reborn :),                   
                    //"新年礼物" : (: ask_2009NewYearGift :),  
                    "调整天赋" : (: ask_tiaozheng :),                   
                ]));      
        
        set("chat_chance_combat", 150);
        set("chat_msg_combat", ({
	        (: command("perform unarmed.tian") :),	       
	        (: exert_function, "recover" :),
	        (: exert_function, "powerup" :),	       
        }));
        
        set_temp("apply/attack", 500);
        set_temp("apply/defense", 300);
        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 300);

  
    setup();
   
    carry_object("/d/death/obj/weapon60")->wield();
   
}


void init()
{
     object me;
     ::init();

        add_action("do_list", "list");
        add_action("do_buy", "buy");
        
        if( interactive(me = this_player()) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }

}

void greeting(object ob)

{
     object me;
     me=this_player();
     if (!ob || !present(ob, environment())) return;
     command("look " + me->query("id"));
     /*command("say 小朋友骨骼清奇，实在是百年难得一见的练武奇才！");
     command("say 我这里有几本武功秘籍，便宜卖给你了。");
     command("say 以后惩恶扬善，维护世界和平的重任就交给你了！！");*/
     
     return ;
}


int ask_tiaozheng()
{
         int i;
         int points;
         int tmpstr, tmpint, tmpcon, tmpdex, tmpadd;
         object me;
         mapping my;
 
         if (! objectp(me = this_player()) ||
             ! userp(me))
                 return 1;
         if (me->query("scborn_gift"))
                 return notify_fail("你已经调整过天赋了。\n");
        // if (me->query("age")>14)
                // return notify_fail("你已经超龄了，请找杨六哪只色狼处理。\n");
                command("say 指令格式：ask dgdg_boss tiaozheng <膂力> <悟性> <根骨> <身法>\n");
         my = me->query_entire_dbase();
         tmpadd = my["str"] + my["int"] + my["con"] + my["dex"]
 //if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
               //  return notify_fail("指令格式：tiaozheng <膂力> <悟性> <根骨> <身法>\n");
 
 
 if( tmpstr<13) return notify_fail("你所选择的膂力参数不能小于13。\n");
 if( tmpint<13) return notify_fail("你所选择的悟性参数不能小于13。\n");
 if( tmpcon<13) return notify_fail("你所选择的根骨参数不能小于13。\n");
 if( tmpdex<13) return notify_fail("你所选择的身法参数不能小于13。\n");
 
 if((tmpstr+tmpint+tmpcon+tmpdex)>tmpadd) return notify_fail("你所选择的参数总和不能大于转世前数据。\n");
 if((tmpstr+tmpint+tmpcon+tmpdex)<tmpadd) return notify_fail("你所选择的参数总和不能小于转世前数据。\n");
 
         
 
         my["str"] = tmpstr;
         my["int"] = tmpint;
         my["con"] = tmpcon;
         my["dex"] = tmpdex;
 
 
         write(sprintf(HIY "\n你这次获得的四项先天天赋分别是：\n"
                           "膂力：【 " HIG "%d" HIY " 】 "
                           "悟性：【 " HIG "%d" HIY " 】 "
                           "根骨：【 " HIG "%d" HIY " 】 "
                           "身法：【 " HIG "%d" HIY " 】\n"
                           "你已经调整好天赋!\n\n" NOR,
                       tmpstr, tmpint, tmpcon, tmpdex));
         me->set("scborn_gift", 1);
 
         return 1;



/*
int ask_reborn()
{
	  int n;
    object me;
    object *inv;
    object room;
    me = this_player();
   
    inv = deep_inventory(me);
    command("look " + me->query("id"));
 
           for (n = 0; n < sizeof(inv); n++)
        {
                if (! playerp(inv[n])) continue;
                else
                {
                	command("say 你背的是谁？还不快快放下！");
                  return 1;
                }
        }
        
    if (me->query("reborn"))
    	{
    		command("say 转了还转，你转得不嫌头晕阿！");
        return 1;
    	}

    if ( (int)me->query_skill("martial-cognize",1) < 600 )
    {
       command("say 你的武学修养还不够，无法转世！");
       return 1;
    }
    room = find_object("/d/zhuanshi/sky/sky1");
        if (! room) room = load_object("/d/zhuanshi/sky/sky1");
        me->move(room);

    return 1;
}



string ask_2009NewYearGift()
{
        object me;
        object ob;

        me = this_player();
        
        if (me->query("gift2009/newyear/get"))
        {
            return "要了还想要啊？真贪心，没有啦！！\n";
        }      
                
        message_vision(HIY "$N拿出一个巧克力递给$n。\n" NOR, this_object(), me);

        ob = new("/u/kasumi/obj/chocolate");
        ob->move(me, 1);
        me->set("gift2009/newyear/get", 1);

        return "好吧，这个巧克力你拿去吃吧。\n";
}


*/

/*
string ask_cake()
{
        object me;
        object ob;

        me = this_player();
        
        if (me->query("gift2007/mid-autumn/get"))
        {
            return "要了还想要啊？真贪心，没有啦！！\n";
        }      
                
        message_vision(HIY "$N拿出一个中秋月饼递给$n。\n" NOR, this_object(), me);

        ob = new("/u/kasumi/mooncake");
        ob->move(me, 1);
        me->set("gift2007/mid-autumn/get", 1);

        return "好吧，这个中秋月饼你拿去吃吧。\n";
}


string ask_tianjing()
{
        object me;
        object ob;

        me = this_player();
        
        if (me->query("gift2007/national-day/get"))
        {
            return "要了还想要啊？真贪心，没有啦！！\n";
        }
        
        
        if (me->query("reborn"))
        {
        	  message_vision(HIY "$N拿出一块寰宇天晶递给$n。\n" NOR, this_object(), me);
            ob = new("/d/death/obj/tianjing");
            ob->move(me, 1);
            me->set("gift2007/national-day/get", 1);
            return "好吧，国庆快乐，好好加油哦！\n";      
        } 
               
        		return "条件不够啊，先转世吧！\n";
          
}


int recognize_apprentice(object ob, string skill)
{
        if (! ob->query("can_learn/yinyang-shiertian/kasumi"))
        {
                message_vision(CYN "$N" CYN "做了个鬼脸，对$n" CYN "说"
                               "道：我又不是你师父，为啥要教你？\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (skill != "yinyang-shiertian")
        {
                command("say 其他的武功我可教不了你，找你自己的师傅吧。");
                return -1;
        }

        return 1;
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

        if (ob->query("combat_exp") < 500000)
        {
                message_vision(CYN "$N" CYN "嘻嘻一笑，对$n" CYN "道："
                               "你还是先把功夫练好了再说吧。\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (query("qi") < 5000 ||
            query("jing") < 2000 ||
            query("neili") < 5000)
        {
                message_vision(CYN "$N" CYN "摇摇头对$n" CYN "道：我现"
                               "在太累了，待我歇会儿再说吧。\n" NOR,
                               this_object(), ob);
                return -1;
        }

        if (ob->query("can_learn/yinyang-shiertian/kasumi"))
        {
                message_vision(CYN "$N" CYN "对$n" CYN "道：好，那咱们"
                               "就再玩玩。\n" NOR, this_object(), ob);
                return 1;
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
        ::win();
}


void lost()
{
        object ob;
        int exp, pot, sc, ww;
        string msg;

        exp = 20000 + random(10000);
        pot = 2000 + random(1000);
        sc = 800 + random(300);
        ww = 800 + random(300);

        if (! objectp(ob = query_competitor()))
                return;

        message_sort(HIW "\n$N" HIW "哎呀一声，抹了抹头上的汗，喜道：这"
                     "位" + RANK_D->query_respect(ob) + HIW "，你的武功"
                     "真厉害！的确是可塑之材。这样吧，我传授你一套绝密武功。\n" NOR,
                     this_object(), ob);

        tell_object(ob, HIC "\n小虾同意传授你「阴阳十二天」绝学。\n" NOR);
        ob->set("can_learn/yinyang-shiertian/kasumi", 1);
        ob->improve_skill("martial-cognize", 1500000);

        if (ob->query("potential") > ob->query_potential_limit()) 
        	pot = 1;

        ob->add("combat_exp", exp);
        ob->improve_potential(pot);
        ob->add("score", sc);
        ob->add("weiwang", ww);

        msg = HIC "\n通过这次的历练，你获得了" +
              chinese_number(exp) + "点经验、" +
              chinese_number(pot) + "点潜能、" +
              chinese_number(sc) + "点江湖阅历及" +
              chinese_number(ww) + "点江湖威望。\n" NOR;

        tell_object(ob, sort_msg(msg));

        ::lost();
}
*/