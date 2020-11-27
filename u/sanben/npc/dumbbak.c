//彩票登记员

#include <ansi.h>

#define  SAVE_FILE      "/data/lot/sign.o" 

inherit NPC;

//int accept_ask(object ob,object me,string arg);
//mixed do_list();

void create()

{
    set_name(HIC"瞎大笨"NOR, ({"xia daben", "daben", "dumb" }));
    set("title", HIW"［"HIG"元宵礼物发放员"HIW"］"NOR);
    set("gender", "男性");
    setup();
}

void init()
{
     object me;
     ::init();

        add_action("do_list", "list");
        add_action("do_delete", "delete");
        add_action("do_delete2", "delete2");
        add_action("do_add", "add");
        add_action("do_add2","add2");


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

            write(HIG"瞎大笨说道：可以要奖票的人请ask dumb about "NOR 
                                 HIY "奖票\n"
                     "            list" NOR HIG"可以查询有哪些人能拿。\n"NOR
                  HIW"            巫师已经对报名id进行过过滤了。\n\n"NOR);     
     return ;
}

mixed do_list()
{
    object me;
    string msg;
    int i;

    me = this_player();

      if ( time() - me->query_temp("last_sign") < 5 )
    
        return command("say 你刚刚才麻烦过我，等会再说吧！\n");

    me->set_temp("last_sign", time());    
    restore_object(SAVE_FILE,1);

    msg = HIY"目前尚有" + sizeof(query("mark")) + "人能拿两张奖票：\n"NOR HIG;
    
    if ( sizeof(query("mark")) > 0 )
    {
       for(i=0;i<sizeof(query("mark"));i++)
       {
          msg += query("mark")[i];
          if ( i < sizeof(query("mark")) - 1 ) msg += "、";
          if ( (i+1) % 5 == 0 ) msg += "\n";
       }
    }

    msg += NOR HIY"\n目前尚有" + sizeof(query("mark2")) + "人能拿一张奖票：\n"NOR HIG;
    if ( sizeof(query("mark2")) > 0 )
    {
       for(i=0;i<sizeof(query("mark2"));i++)
       {
          msg += query("mark2")[i];
          if ( i < sizeof(query("mark2")) - 1 ) msg += "、";
          if ( (i+1) % 5 == 0 ) msg += "\n";
       }
    }
    tell_object(me, msg + NOR"\n");    
    return 1;
}

int accept_ask(object me,string arg)
{     
     string *mark, *mark2;
     object ob, piao1, piao2;
     int i;

  //   if (arg != "报名抽奖" && arg != "报名" && arg != "抽奖报名")

    if (arg != "奖票" && arg != "奖劵")

     return 0;
    
     ob = this_object();
    
     mark = ({});

     
     if ( time() - me->query_temp("last_sign") < 5 )
     {
        command("say 你刚刚才麻烦过我，等会再说吧！\n");
        return 1;
     }
 
     me->set_temp("last_sign", time());  

     restore_object(SAVE_FILE);  

     if ( sizeof(query("mark")) > 0 )       
          mark = query("mark");

     for(i=0; i<sizeof(mark); i++) 
     {

        if ( mark[i] == me->query("id"))
        {  
            command("say 你能得到两张奖票，祝你抽奖好运！");
            piao1 = new("/u/sanben/yuanxiao/lot_card");
            piao2 = new("/u/sanben/yuanxiao/lot_card");
            piao1->move(me);
            piao2->move(me);
	     message_vision(HIW"瞎大笨拿出两张彩票给$N。\n"NOR, me);
            mark -= ({ me->query("id")});
            ob->set("mark", mark); 
            assure_file(SAVE_FILE);
            save_object(SAVE_FILE,1);
            return 1;
        }
     } 

     if ( sizeof(query("mark2")) > 0 )       
          mark2 = query("mark2");

     for(i=0; i<sizeof(mark2); i++) 
     {

        if ( mark2[i] == me->query("id"))
        {  
            command("say 你能得到一张奖票，祝你抽奖好运！");
            piao1 = new("/u/sanben/yuanxiao/lot_card");
           
            piao1->move(me);
            
	     message_vision(HIW"瞎大笨拿出一张彩票给$N。\n"NOR, me);
            mark2 -= ({ me->query("id")});
            ob->set("mark2", mark2); 
            assure_file(SAVE_FILE);
            save_object(SAVE_FILE,1);
            return 1;
        }
     }    

    
    command("say 对不起，记录里现在没有你的名字。");

     return 1;
}

int do_delete( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;    
    mark = ({});

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"你要把哪个id删除出A类玩家?\n"NOR);

    restore_object(SAVE_FILE, 1);  

    if ( ! query("mark") ) return notify_fail(HIR"目前没有A类玩家。\n"NOR);
    
    for(i=0;i<sizeof(query("mark"));i++)
    {
       if ( query("mark")[i] == arg ) 
       {
           same = 1;    
           break;  
       }        
    }
    if ( same == 0 ) return notify_fail(HIR"A类玩家里没有" + arg + "这个id！\n"NOR);
    
    mark = query("mark");
    mark -= ({ arg });

    set("mark", mark);

    write(HIG"成功将" + arg + "这个id删除出A类玩家。\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}

int do_delete2( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;
    set("mark2", ({}) );

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"你要将哪个id删除出B类玩家?\n"NOR);

    restore_object(SAVE_FILE,1);  

    if ( ! query("mark2") ) return notify_fail(HIR"目前没有B类玩家。\n"NOR);
    
    for(i=0;i<sizeof(query("mark2"));i++)
    {
       if ( query("mark2")[i] == arg ) 
       {
           same = 1;    
           break;  
       }        
    }
    if ( same == 0 ) return notify_fail(HIR"B类玩家里没有" + arg + "这个id报名！\n"NOR);
    
    mark = query("mark2");
    mark -= ({ arg });

    set("mark2", mark);

    write(HIG"成功将" + arg + "这个id删除出B类玩家。\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}


int do_add( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;
    mark = ({});

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"你要在A类玩家里增加哪个id?\n"NOR);

    restore_object(SAVE_FILE,1);      
    
    for(i=0;i<sizeof(query("mark"));i++)
    {
       if ( query("mark")[i] == arg ) 
       {
          same = 1; 
          break;
       }      
    }
    if ( same == 1 ) return notify_fail(HIR + arg + "这个id已经在A类玩家里了！\n"NOR);
    

     if ( sizeof(query("mark")) > 0 )       
          mark = query("mark");
   
    mark += ({ arg });

    set("mark", mark);

    write(HIG"成功将" + arg + "这个id增加进A类玩家。\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}

int do_add2( string arg )
{
    object me;
    int i, same;
    string *mark;

    me = this_player();    
    same = 0;
    mark = ({});

    if ( ! wizardp(me) ) return 0;
    if ( ! arg ) return notify_fail(HIR"你要在B类玩家里增加哪个id?\n"NOR);

    restore_object(SAVE_FILE,1);      
    
    for(i=0;i<sizeof(query("mark2"));i++)
    {
       if ( query("mark2")[i] == arg ) 
       {
          same = 1; 
          break;
       }      
    }
    if ( same == 1 ) return notify_fail(HIR + arg + "这个id已经在B类玩家里了！\n"NOR);   

    if ( sizeof(query("mark2")) > 0 )       
          mark = query("mark2");

    mark += ({ arg });

    set("mark2", mark);

    write(HIG"成功将" + arg + "这个id增加进B类玩家。\n"NOR);
    save_object(SAVE_FILE,1);
    return 1;
}

