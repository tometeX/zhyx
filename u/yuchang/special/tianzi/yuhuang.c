// 玉皇顶/真命天子解谜地点

#include <ansi.h> 
inherit ROOM;

#define QINGTIAN    "/u/yuchang/special/tianzi/qingtian.h"
#define TIANZIJIAN       "/u/yuchang/special/tianzi/tianzijian.h"
#define SPECIAL     "/data/item/"

void create()
{
	set("short", "玉皇顶");
	set("long", @LONG
此处便是泰山绝顶。这里有一座玉帝观，观前为古登封台
，厉代皇帝封禅的仪式都是在这里举行。传说真命天子在此诚
心磕头(ketou) 会受天赐恩赏。台下有一无字碑，据说是汉武
帝所立。不远处有一石碣，上书「孔子小天下处」。正中往上
便是武林盟主所在之处—封禅台。
LONG );
	set("exits", ([
		"southdown" : "/d/taishan/nantian",
		"eastdown"  : "/d/taishan/riguan",
		"west"      : "/d/taishan/zhangren",
		"up"        : "/d/taishan/fengchan",
	]));
	set("objects",([
	//	"/d/taishan/npc/wei-shi2" : 3,
             __DIR__"wuzibei" : 1,
	]));
       set("no_fight",1);
	set("outdoors", "taishan");
	setup();
      
	//replace_program(ROOM);
}

void init()
{
    add_action("do_ketou", "ketou");  
    add_action("do_tuotai", "tuotai");      
}

int do_ketou()
{
     object me, qingtian, tianzijian;
     string fn, fc, answer;     
 
     me = this_player();

     if (! me->query("special_skill/emperor") )
     return notify_fail("这里只有真命天子才能叩拜，寻常草民速速离去！\n\n");
     if (  me->query("tianzi/item") &&  me->query("tianzi/tuotai")  )
     return notify_fail("上天已经知道你的诚心了，不用再磕头了！\n\n");
    
     if (me->is_busy() || me->is_fighting())
     {
            write("你忙完了再说吧！\n");
            return 1;
     }
     if (me->query("jing") < 20)
     {
            write("你精力不足！\n");
            return 1;
     }
     if (me->query("jing") > 20) 
          me->add("jing", -20);
     else me->set("jing", 1);

     me->start_busy(2 + random(2));

     message_vision(HIC "$N" HIC "说道：“弟子" + me->query("name") +
                        "在此诚心叩拜。”\n\n" NOR, me);
     message_vision(HIC "只见$N" HIC "面向南方，跪在地上恭恭敬敬磕了三个头。\n\n"
                    NOR, me);
     me->start_busy(2 + random(2));

     if (random(100) < 2 )
     {
             message_vision(HIC "磕头完毕，$N缓缓站起身来。\n\n" NOR, me);             
             return 1;
     } 
     else 
     {     if (  ! me->query("tianzi/item") )
         {
            message_vision(HIY "刹时间只见天边显现出炎、黄二帝，朝$N笑道：\n不错，不错。"
                           "此子虔心祭天，看来确实没有选错人哪！\n如今我等便赐你天子宝"
                           "甲与利剑。今后你需惩恶助贫，以利苍生，不得有误！\n\n" NOR, me);    
           me->set("tianzi/item", 1); //记录下已经拿过物品了

           //获得青天甲
           fc = read_file(QINGTIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIW "这张护甲异乎寻常，周身散发出淡淡的雾气将其笼罩，"
                               "什么也看不清。\n" HIC
                              "护甲缘上刻着一行小字：众神赐于真命天子" 
                               + me->query("name") +
                              "(" + me->query("id") + ")。\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));          

           fn = SPECIAL + me->query("id")[0..0] + "/" 
                +  me->query("id") + "-qingtian";

           if (file_size(fn + ".c") > 0)
           {
                if (qingtian = find_object(fn)) destruct(qingtian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           qingtian = load_object(fn);
           qingtian->move(me, 1);
           me->set("can_summon/qingtian",fn);
         
           //获得天子剑
           fc = "";
           fc = read_file(TIANZIJIAN);
         
           fc = replace_string(fc, "LONG_DESCRIPTION",
                               HIY "这是上天众神赐于真命天子的神剑利器，"
                               "上面笼罩着一层金光。\n" HIW
                              "剑柄上刻着一行小字：众神赐于真命天子" 
                               + me->query("name") +
                              "(" + me->query("id") + ")。\n" NOR);
           fc = replace_string(fc, "ID", me->query("id"));

           fn = SPECIAL + me->query("id")[0..0] + "/" + 
                me->query("id") + "-tianzijian";

           if (file_size(fn + ".c") > 0)
           {
                if (tianzijian = find_object(fn)) destruct(tianzijian);
                rm(fn + ".c");
           }

           assure_file(fn);
           write_file(fn + ".c", fc);

           VERSION_D->append_sn(fn + ".c");
           tianzijian = load_object(fn);


           tianzijian->set("owner/" + me->query("id"), 5000000);
           tianzijian->set("magic/imbue",50);

           tianzijian->move(me, 1);
           me->set("can_summon/tianzijian",fn); 

           message_vision(HIW "\n只见" HIC"青天甲" NOR HIW"与"NOR HIY"真命天子剑" NOR
                          HIW"刷的一声飞到了$N身上！”\n\n" NOR, me);  
           return 1;
        }  
      // 脱胎换骨,调整天赋
       if (  ! me->query("tianzi/tuotai") )
           {                               
                message_vision(HIY "炎帝突然显现出来道：汝仍在此叩拜?"
                               "可是尚对自身天赋不满?\n\n"NOR, me);
                write(HIR"炎帝赐你一次脱胎换骨的机会，可以重新调整四项天赋，\n"
                      "但是脱胎换骨后以前增加的先天属将全部无效，\n"
                      "实战经验及一切技能全部清除，你可想清楚了？Y/N\n\n" NOR);
		  input_to("do_yes", answer);               
           }
 
     }  
     return 1;
                  
}

int do_yes(string answer)
{   
   object me;
   me = this_player();
   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	
   	me->set_temp("tianzi/tuotai/ask",1);

       write(HIG"好的，既然你心意已决，你可以重新分配80点天赋，\n"
                "单项必须大于等于13，小于等于30,\n"
                "指令是tuotai <膂力> <悟性> <根骨> <身法>\n\n"NOR);
     	
   } else
   {            
   	write("好的，改变主意的话随时回来。\n");
   }
   return 1;	
}

int do_tuotai(string arg)
{
    object me;
    int tmpstr, tmpint, tmpcon,tmpdex;
    string answer;

    me = this_player();
    if	( ! me->query_temp("tianzi/tuotai/ask") ) return 0;
    if( !arg || sscanf(arg, "%d %d %d %d", tmpstr, tmpint, tmpcon,tmpdex)!=4 )
                return notify_fail(HIG"指令格式：tuotai <膂力> <悟性> <根骨> <身法>\n"NOR);
 
    if( tmpstr<13) return notify_fail("你所选择的膂力参数不能小于13。\n");
    if( tmpint>30) return notify_fail("你所选择的悟性参数不能大于30。\n");
    if( tmpint<13) return notify_fail("你所选择的悟性参数不能小于13。\n");
    if( tmpcon>30) return notify_fail("你所选择的根骨参数不能大于30。\n");
    if( tmpcon<13) return notify_fail("你所选择的根骨参数不能小于13。\n");
    if( tmpdex>30) return notify_fail("你所选择的身法参数不能大于30。\n");
    if( tmpdex<13) return notify_fail("你所选择的身法参数不能小于13。\n");
    if((tmpstr+tmpint+tmpcon+tmpdex)>80) 
    return notify_fail("你所选择的参数总和不能大于80。\n");
    write(HIC "指定天赋为 臂力:" + tmpstr + " 悟性:" + tmpint + " 根骨:" +
          tmpcon + " 身法:" + tmpdex + "，可以吗？Y/N。\n" NOR, me);

    me->set_temp("/tianzi/tuotai/str",tmpstr);
    me->set_temp("/tianzi/tuotai/int",tmpint);
    me->set_temp("/tianzi/tuotai/con",tmpcon);
    me->set_temp("/tianzi/tuotai/dex",tmpdex);

    input_to("do_yes2", answer);
    return 1;
}

int do_yes2(string answer)
{
   object me;
   mapping my, my_sk;
   string skills_name;

   me = this_player();
   my = me->query_entire_dbase();
   my_sk = me->query_skills();

   if ( answer == "Y" || answer == "yes" || answer == "y" )
   { 	 	
      message_vision(HIY "只见一道金光钻入了$N体内，$N顿时感到头痛欲裂，"   
                         "苦不堪言。\n\n"NOR, me);

        my["str"] = me->query_temp("/tianzi/tuotai/str");
        my["int"] = me->query_temp("/tianzi/tuotai/int");
        my["con"] = me->query_temp("/tianzi/tuotai/con");
        my["dex"] = me->query_temp("/tianzi/tuotai/dex");
       	me->set("combat_exp", 0);       	
		me->set("max_neili",0);
		me->set("neili",0);
		me->set("max_jingli",0);
		me->set("jingli",0);
		me->set("max_qi",100);
		me->set("eff_qi",100);
		me->set("qi",100);
		me->set("max_jing",100);
		me->set("eff_jing",100);
		me->set("jing",100);
              me->set("shen",0);
              me->delete("breakup");
              me->delete("animaout");
              me->set("mud_age",0);            
              me->set("age", 14);

  		foreach(skills_name in keys(my_sk))
	      {
		   me->delete_skill(skills_name);
             }
        me->delete("gift");
        me->delete_temp("tianzi");
        me->set("tianzi/tuotai",1);
        me->unconcious();        
        me->set("potential", me->query_potential_limit() );

   } else
   {
   	  write("那请重新选择天赋。\n");
   }
   return 1;		

}
