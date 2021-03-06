// jinyong.c 金庸

inherit NPC;
#include <ansi.h>;
#define  LEITAI             "/u/sanben/leitai/leitai"

int do_bihua(string arg);
int do_no();
void shout_message(string msg);
int accept_object(object me, object ob);
int ask_award();

void create()
{       int i;
        object master;
        set_name(HIY "金庸" NOR, ({ "jin yong", "jin", "yong" }) );
        set("title", HIG"武侠始祖" NOR);
        set("nickname", HIC"一支玉笔尽舒怀"NOR);
        set("gender", "男性");
        set("age", 35);
        set("no_get", 1);
        set("long",
           "这就是武侠世界的创始人金庸金大侠。\n");
        set("attitude", "friendly");       

        for(i = 1; i < 6; i++)
        {
           master = new("/u/sanben/leitai/npc" + i);
           master->restore();
           set("idlist/" + i, master->query("id"));
           set("namelist/" + i, master->query("name"));        
           destruct(master);
        }
        set("inquiry", ([ 
            "打擂台" : "要打擂台就先付五十两黄金给我。",                          
            "擂台"   : "要打擂台就先付五十两黄金给我。",                          
            "比武"   : "要打擂台就先付五十两黄金给我。",              
            "奖励"   : ( : ask_award : ),                        
         ])); 
        setup();       
        carry_object("/clone/misc/cloth")->wear();      
}


void init()
{
        ::init();   
                  
        add_action("do_bihua", "bihua");
        add_action("do_bihua", "fight");
        add_action("do_no", "beg");
        add_action("do_no", "steal");
        add_action("do_no", "quanjia");
        add_action("do_no", "persuade");
        add_action("do_no", "touxi");
        add_action("do_no", "ansuan");
        add_action("do_no", "kill");
        add_action("do_no", "hit");  
        add_action("do_no", "crattack");  
        add_action("do_no", "spattack");  
        add_action("do_no1", "auction");  
        add_action("do_no1", "du");           
        add_action("do_no1", "study");    
        add_action("do_no1", "read");                                    
        add_action("do_no1", "summon");
        add_action("do_no1", "eat");
        add_action("do_no1", "drink");
        add_action("do_ready", "ready");
        add_action("re_set","reset");      
        add_action("set_wp","setwp");
        add_action("set_pfm","setpfm");
        add_action("set_ok","setok");
        add_action("re_set","reset"); 

        add_action("do_du", "du");
        add_action("do_du", "study");        
}

int do_du()
{
    write("比武场所禁止读书!\n");
    return 1;
}

int ask_award()
{
    int i, flag;
    int pot, tihui;
    string msg;

    object me;

    me = this_player();
    flag = 0;     

    for(i = 1; i < 6; i++)
    {
       if ( query("idlist/" + i) == me->query("id") ) 
       {        
          flag = i;
          break;
       }
    }
   
    if ( flag == 0 ) 
    {
       command("say 你又不是五大高手之一，领什么奖励!");
       return 1;
    }

    if ( time() - me->query("leitai/time") < 24 * 3600)
    {
       command("say 你必须守住一天擂台才能有奖励!");
       return 1;
    } 

    if ( time() - me->query("leitai/last_award") < 24 * 3600 )
    {
       command("say 24小时内只能要一次奖励!");
       return 1;
    }

    command("say 嗯，好的。\n");

    me->set("leitai/last_award", time());

    pot = 500 * flag + 1000 + random(200);
    tihui = 200 * flag + 1000 + random(100);

    if ( me->query("potential") >= me->query_potential_limit() )
       {  pot = 1; }
    if ( me->query("experience") >= me->query_experience_limit() )
       {  tihui = 1; }

    me->add("potential", pot);
    me->add("experience", tihui);

    msg = "由于"NOR HIR + me->query("name") + NOR HIY"成功守住一天擂台，\n"
          "            特给予奖励" + chinese_number(pot) + "点潜能及" +
          chinese_number(tihui) + "点实战体会。\n";  
    shout_message(msg);  
    return 1;
}


int set_wp(string arg)
{
    object me;
    me = this_player();

    if ( ! me->query_temp("leitai/set_start") ) return 0;

    if ( !arg ) return notify_fail("你想设置什么兵器？\n");
    if ( me->delete_temp("leitai/set/wpe") )
         return notify_fail("你已经给替身设置过兵器了，如想重设请输入reset。\n");
    me->delete_temp("leitai/setok");

    switch(arg)
    {

      case "斧":
           me->set_temp("leitai/set/wpc","斧");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/axe"));
           break;
      case "刀": 
           me->set_temp("leitai/set/wpc","刀");
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/sword1"));
           break;
      case "鞭": 
           me->set_temp("leitai/set/wpc","鞭");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/changbian"));
           break;
      case "铁掌": 
           me->set_temp("leitai/set/wpc","铁掌");
           me->set_temp("leitai/set/hand", 1);
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/hand"));
           break;
      case "锤": 
           me->set_temp("leitai/set/wpc","锤");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/hammer"));
           break;
      case "剑": 
           me->set_temp("leitai/set/wpc","剑");
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/sword1"));
           break;
      case "棍": 
           me->set_temp("leitai/set/wpc","棍");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/qimeigun"));
           break;
      case "指套": 
           me->set_temp("leitai/set/wpc","指套");
           me->set_temp("leitai/set/hand", 1);
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/finger"));
           break;
      case "杖": 
           me->set_temp("leitai/set/wpc","杖");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/tiegun"));
           break;
     default :
           write(HIC"设置的兵器必须是「斧、刀、鞭、铁掌、锤、剑、棍、指套、杖」"
                 "其中的一种。\n"NOR);
           return 1;
    } 
    write(HIG"\n设置了你的替身将持有兵器" + me->query_temp("leitai/set/wpe")->name()
          + "。\n"NOR);   
    if (me->query_temp("leitai/set/pfm"))        
        write(HIM"\n如果都设置好了请输入setok，\n"
              "系统将为你自动生成你的替身接受以后人的挑战。\n"NOR);  
    else 
        write(HIM"\n请继续用setpfm来设置你替身的绝招。\n"
              "格式如setpfm taixuan-gong|unarmed|xuan\n"NOR);
    return 1;

}

int set_pfm(string arg)
{
    object me;
    string sk, type, pfm, *allpfm, *allpfm_ok, msg;
    int i;
    me = this_player();  
    msg = ""; 

    if ( ! me->query_temp("leitai/set_start") ) return 0;
    me->delete_temp("leitai/setok");

    if ( !arg || sscanf(arg, "%s|%s|%s", sk, type, pfm) != 3 ) 
       return notify_fail("你想设置什么绝招？比如:setpfm taixuan-gong|sword|jing\n");    

    if ( ! me->query("can_perform/" + sk + "/" + pfm) )
       return notify_fail(HIR"你并不会使用这一绝招呀？\n"
              "请注意格式为setpfm 技能名称|技能种类|绝招名称\n"NOR);    

    if ( ! me->query_temp("leitai/set/pfm") )
    {
       allpfm = ({});
       allpfm_ok = ({});
    }
    else
    {
       allpfm = me->query_temp("leitai/set/pfm");
       allpfm_ok = me->query_temp("leitai/set/pfmok");
    }
    if ( sizeof(allpfm) > 2 )
        return notify_fail("很抱歉，你已经设置满三个绝招了。\n请输入setok，"
                           "若不满意可reset后重新设置绝招。\n");    
    if (member_array(sk + "|" + type + "|" + pfm, allpfm ) != -1 )
        return notify_fail("这个绝招你已经设置过了。\n");    

    allpfm += ({ sk + "|" + type + "|" + pfm });  
    allpfm_ok += ({ type + "." + pfm });
 
    me->set_temp("leitai/set/pfm", allpfm); 
    me->set_temp("leitai/set/pfmok", allpfm_ok); 

    for (i = 0; i < sizeof(allpfm); i++ )
    {
         msg += allpfm[i] + "\n";   
     }
     write(HIG"\n目前你给替身设置的绝招为：\n"NOR HIC + msg + "\n"NOR);     
     write(HIY"你已经为替身设置了" + sizeof(allpfm) + "个绝招\n"); 
     if ( sizeof(allpfm) < 3 )
         write(HIY"如果觉得可以了请输入"NOR HIG+ "setok"NOR
                HIY"，如果还想设置绝招请继续。\n"NOR); 
     else
         write(HIR"绝招设置已满三个，可以的话请输入" NOR HIG "setok" NOR
               HIR"，若不满意可"NOR HIG + "reset" NOR 
               HIR"后重新设置。\n"NOR); 
     return 1;
}

int set_ok(string arg)
{
    object me;
    string msg1, msg2, *pfm;
    int i;
    me = this_player();  
    msg2 = "";

    if ( ! me->query_temp("leitai/set_start") ) return 0;
    if ( me->query_temp("leitai/setok") < 1 )
    {
       msg1 = me->query_temp("leitai/set/wpc");
       if (! msg1) msg1 = HIR"无"NOR;

       pfm = me->query_temp("leitai/set/pfm");
       if (! pfm) msg2 = HIR"    无"NOR;
       else
          {
             for( i = 0; i < sizeof(pfm); i++ )
             {
                 msg2 += "    " + pfm[i] + "\n"; 
             }
          }  
        me->add_temp("leitai/setok", 1);   
        write("你现在给你替身作出的设置是:\n"
              "兵器:\n    " + msg1 + "\n绝招:\n" + msg2 +
              "\n如果都可以的话请再输入一次setok，若不满意可reset后重新设置。\n");
     }
     else
     {
        call_other(__FILE__, "finish", me);
     }
     return 1;
}

int re_set()
{
     object me;
     me = this_player();
     if ( ! me->query_temp("leitai/set_start") ) return 0;
     me->delete_temp("leitai/set");
     me->delete_temp("leitai/setok");
     write(HIY"请重新输入兵器及绝招的设置。\n"NOR);
     return 1;
}

void finish(object me)
{
     object npc, npc1, master, mrt, *inv, *obj;
     string msg;
     int i, ii, level;

     level = me->query_temp("leitai/level");

     //若原来已有替身的先消除掉
     if ( me->query_temp("leitai/old_lvl") )     
         rm("/data/leitai/npc" + me->query_temp("leitai/old_lvl") + ".o");  
  
    for(i = 1; i < level; i++)
    {     
      if ( file_size("/data/leitai/npc" + (i + 1) + ".o") > 0 )
      {
          cp("/data/leitai/npc" + (i + 1) + ".o",
              "/data/leitai/npc" + i + ".o");  

          npc1 = new("/u/sanben/leitai/npc" + i);
          npc1->set("level",i);

         switch(i)
         {
          case 1 :
               npc1->set("nickname", HIC "东邪" NOR );  
               break;          
          case 2 :
               npc1->set("nickname", HIR "西毒" NOR); 
               break;                      
          case 3 :
               npc1->set("nickname", HIY "南帝" NOR);   
               break;                     
          case 4 :
               npc1->set("nickname", HIW "北丐" NOR);  
               break;                      
          case 5 :
               npc1->set("nickname", HIW "中神通" NOR);  
               break;                      
         }   
         npc1->save();
         destruct(npc1);
        if ( file_size("/data/leitai/npc" + (i + 2) + ".o") < 0 )
           rm("/data/leitai/npc" + (i + 1) + ".o"); 
      }      
    } 

     npc = new(__DIR__"npc" + level);
     if ( ! npc )
     {
         write(HIR"无法复制你的替身，请联系巫师！\n"NOR);
         return; 
     }   

     npc->do_copy(me);  
    
     npc->delete("weapon");           
     npc->delete("hand");     
     
     if (me->query_temp("leitai/set/wpe"))
     {
        if (me->query_temp("leitai/set/hand"))       
            npc->set("hand", base_name(me->query_temp("leitai/set/wpe")));       
    
        else
            npc->set("weapon", base_name(me->query_temp("leitai/set/wpe")));     
     }    
     
     npc->delete("pfm");
     npc->set("pfm", me->query_temp("leitai/set/pfmok"));

     npc->save();  
     npc->restore();   
   
    
     msg = "恭喜"NOR HIR + me->name() + "(" + me->query("id") + ")"NOR
            HIY"获得新一界"NOR + npc->query("nickname") + NOR HIY"称号。"NOR;
     shout_message(msg); 
     destruct(npc);

     for(i = 1; i < 6; i++)
     {
        master = new("/u/sanben/leitai/npc" + i);
        master->restore();
        set("idlist/" + i, master->query("id"));
        set("namelist/" + i, master->query("name"));       
        destruct(master);
     }
     
    //以下部分更新名人堂
    for( ii = 1; ii < 6; ii++)
    {
	if (mrt = find_object(__DIR__"mrt" + ii))
	{  	
          tell_room(mrt, HIR"接上头通知，现在这里开始改造，闲杂人等一律离开。\n\n"NOR);	
	   inv = all_inventory(mrt);
  	   for(i=0; i<sizeof(inv); i++)
          {
		if ( ! inv[i]->is_player() )
            	   destruct(inv[i]);
              else
              {
                 inv[i]->move("/d/city/guangchang");                
              }   
	    }          
	    destruct(mrt);
	}
     }

     if ( me )
     {
         me->delete_temp("leitai");
         me->set("leitai/time", time()); 
         tell_object(me, HIG"\n你的本次打擂圆满结束。\n"NOR);       
     }  
}


int do_bihua(string arg)
{
        object me;
        object ob;
        object old;
        me = this_player();


        if ( ! me->query_temp("leitai") )
        {
                write("现在没轮到你打擂台。\n");
                return 1;
        }
        if (! arg || ! objectp(ob = present(arg)))
        {
                write("你要和谁比划？\n");
                return 1;
        }
        if (me == ob)
        {
                write("你是不是以为天下就你自己是老大，再没有第二个英雄了。\n");
                return 1;
        }
        if ( userp(ob))
        {
                write("这里不能进行玩家间的比试。\n");
                return 1;
        }
        if ( base_name(ob) == __DIR__"jinyong" )
        {
                write("金大侠是裁判，你跟他较什么劲!\n");
                return 1;
        }

        if (! living(ob))
        {
                write("你还是等人家醒了再说吧。\n");
                return 1;
        }
        if (me->is_fighting() && me->query_competitor())
        {
                write("你现在正在和" + me->query_competitor()->name() +
                      "比试呢。\n");
                return 1;
        }
        if (ob->is_fighting())
        {
                write("人家正在动手，你上去插手干什么？\n");
                return 1;
        }
        if (me->query("qi") * 100 / me->query("max_qi") < 70)
        {
                write("你现在体力不够充沛，何必忙着动手？\n");
                return 1;
        }
        if (ob->query("qi") * 100 / ob->query("max_qi") < 70)
        {
                write("人家现在似乎体力不支，还是等会儿再说吧。\n");
                return 1;
        }
        message_vision(HIY "\n$N" HIY "对$n点头道：很好，来吧，不必客气！\n\n" NOR,
                       ob, me);    
        if ( ! ob->is_busy() ) 
        {
            ob->exert_function("powerup"); 
            ob->exert_function("shield");
        }
        me->competition_with(ob);
        return 1;
}
int accept_object(object me, object ob)
{             
        int i, ii;
        object jy, *users, master;       
        
        jy = this_object();       
        
        if (ob->query("money_id") && ob->value() >= 500000)
        {    

            if ( me->query("combat_exp") < 1000000 )
            {
                command("say 这点经验也来打擂台，献丑了吧？");
                return 0;
            }       
            for(i = 1; i < 6; i++)
           {
                master = new("/u/sanben/leitai/npc" + i);
                master->restore();
                set("idlist/" + i, master->query("id"));
                set("namelist/" + i, master->query("name"));        
                destruct(master);
            }
     
            if ( me->query("id") == query("idlist/5") )
            {
                command("say 老大，你已经是擂主了，还自己打自己啊？");
                return 0;
            }

            users = users();
            for(i=0;i<sizeof(users);i++)
            {
                if ( users[i]->query_temp("leitai") 
                     && users[i]->query("id") == me->query("id") )
                { 
                   command("say 你现在不是正在打擂吗，还要给我钱干什么？");
                   return 0;            
                }
                if ( users[i]->query_temp("leitai") 
                     && users[i]->query("id") != me->query("id") )
                { 
                   command("say 现在正有人在打擂，你迟点再来吧。");
                   return 0;            
                }

            }       

            command("say 嗯，那我这就安排你打擂吧。若你准备好了就输入ready。");          
            

            me->set_temp("leitai/paid", 1);
            me->set_temp("leitai/prepare", 1);              
            
            me->set_temp("leitai/level",0);                    
 
            for( ii=1; ii < 6; ii++)
            {
               if ( query("idlist/" + ii ) == me->query("id") )
               {
                   me->set_temp("leitai/old_lvl",ii);
                   me->set_temp("leitai/level",ii);    
               }   
            }            
            destruct(ob);

            remove_call_out("remind");
            call_out("remind", 900, me);

            remove_call_out("end_all");
            call_out("end_all", 1200, me);
            return 1;
       } else
       {
            command("say 打擂一次五十两黄金，不还价！");
            return 0;
       }        
}

int do_no()
{
        command("say " + this_player()->name() + "！这里众目睽睽，岂能做此不义之事？");
        return 1;
}

int do_no1()
{
    if ( !wizardp(this_player()))
    { 
        command("say " + this_player()->name() + "，这里不能干这个事。");
        return 1;
    }
    return 0;
}

int do_ready()
{
    object me;
    me = this_player();
    if (! me->query_temp("leitai/prepare") ) return 0;

    me->delete_temp("leitai/prepare");
    call_other(__FILE__, "get_npc_out", (me->query_temp("leitai/level") + 1) );  
    return 1;
}

void remind(object me)
{
    if ( me ) 
       tell_object(me, HIG"请注意，你的打擂时间还剩十分钟。\n"NOR);
}

void end_all(object me)
{    
    
    if ( me ) 
    {
       tell_object(me, HIG"很抱歉，你的打擂时间已经超过了。\n"NOR);
       me->delete_temp("leitai");
    }      
       
}


int get_npc_out(int level)
{
     object npc, me;
     string msg;

     me = this_player();
        
     if ( level > 5 ) level = 5;
     npc = new(__DIR__"npc" + level);   
     npc->set("qi", npc->query("max_qi"));  
     npc->set("eff_qi", npc->query("max_qi"));  
     npc->set("jing", npc->query("max_jing"));  
     npc->set("eff_jing", npc->query("max_jing")); 
     npc->set("neili", npc->query("max_neili"));  
     npc->set("born_time", time());
  
     if (npc) npc->move(LEITAI);  
     
     msg = "现在扬州武庙三楼演武大厅正在举行擂台挑战赛，"
                  "\n            由玩家"NOR HIR+
                  me->name() + "(" + me->query("id") + ")" + NOR HIY 
                 "挑战"NOR + npc->query("nickname") + NOR HIG + npc->name() + 
                 "(" + npc->query("id") + ")"NOR + 
                 HIY"的替身，\n            欢迎大家前来观看！\n\n"NOR;
     call_other(__FILE__, "shout_message", msg);

     message_vision(HIW"\n只见金大侠大手一挥，$N急匆匆地跑上了擂台，准备应战。\n\n"NOR, npc); 
     message_vision(HIC"$N对$n说道：事不宜迟，咱们这就开始比试吧。\n\n"NOR, npc, me); 
     return 1;
}

void set_tishen(object winner)
{   
    int lvl;        
    lvl = winner->query_temp("leitai/level");
    winner->set_temp("leitai/set_start", 1);
    
    tell_room(LEITAI, HIC"\n金庸说道：不错不错，恭喜"NOR HIR+ winner->name() +
                             NOR HIC"晋升五大高手之列。\n\n"NOR);
 
    tell_object(winner, HIW"现在请你根据提示为自己的替身作出设置，具体如下：\n"NOR 
                HIG"设置替身将持有什么兵器的格式为setwp 兵器类型\n"NOR
                HIC"可供选择的兵器有：\n"
                "「斧、刀、鞭、铁掌、箫剑、锤、剑、棍、指套、杖」\n"NOR                 
                HIY"设置替身所出绝招的格式为setpfm 技能名称|技能类型|绝招名称\n"
                "如：setpfm taixuan-gong|unarmed|xuan。\n"NOR 
                HIR"最多可为替身设置三个绝招。\n"
                "打擂有时间限制，请尽快！\n"NOR);
}

void shout_message(string msg)
{
        message("channel:chat", HIY "【武林快报】金庸[Jin Yong]：" + msg + "\n" NOR,
                all_interactive());
}

void unconcious()
{
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        remove_all_enemy(1);
}
void die()
{
        unconcious();
}



