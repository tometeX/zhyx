

#include <ansi.h>
inherit ITEM;
//void tai_status();
int get_baoshi(int sta,string mess1);
void baoshi_attribute(object obj,int i,int j);

void create()
{
        set_name(HIM"宝石炼制台(tai)"NOR, ({"tai"}) );
        set("short", HIM"宝石炼制台(tai)"NOR);
        set_max_encumbrance(5000);
      //   set_max_items(10);
        set("temperature",25);
        set_temp("max_temp",25);
        set_temp("min_temp",25);

        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "口");
                 set("no_get", 1);
                 set("no_put", 1);
	set ("long", @LONG
这是炼制宝石的地方。
在这里你可以用如下命令炼制宝石:
    init    :   租用宝石炼制台(十金一次）
    add     :	把宝石放进宝石炼制台
    jiawen  :	用内力和法力给宝石炼制台加温
    jiangwen:	用内力和法力给宝石炼制台降温
    finish  :	结束炼制
    tem     :   量宝石炼制台的温度
LONG);

                set("value", 50);
        }
}

int is_container() { return 1; }

void init()
{
	add_action("do_init", "init");
	add_action("do_add","add");
	add_action("do_jiawen", "jiawen");
	add_action("do_jiangwen", "jiangwen");
	add_action("do_finish", "finish");
	add_action("do_get","get");
	add_action("do_put","put");
	add_action("do_tem","tem");

}

int do_init()
{
   	object me = this_player();
   	object obj,ob = this_object();

//     if (me->query("balance")<200000) return notify_fail("宝石炼制台是白用吗？十金一次！\n");
     	if(ob->query_temp("user") && ob->query_temp("user") != me->query("id"))
     	{
     		if ( time()-ob->query_temp("init_time")<300 && ((obj=present(ob->query_temp("user"))) || (obj = present(ob->query_temp("user"), environment(me)))))
   			return notify_fail(obj->name()+"正在用呢，请等五分钟再试试！\n");
   	}
//      me->add("balance",-100000);
	reload_object(ob);
	ob->set_temp("init_time",time());
        ob->set_temp("user",me->query("id"));
         message_vision("$N花了十金租用了"+ob->name()+"准备炼制宝石。\n",me);
        message("channel:chat",HIM"【空穴来风】：听说"+me->name()+"开始炼制宝石。\n"NOR,users());
         remove_call_out("do_temperature");
         call_out("do_temperature", 2);
                return 1;
}

int do_add(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        object item;
	if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了宝石炼制台了吗？\n");
        if(!arg) return notify_fail("你要将什么东西加进宝石炼制台里？\n");
        if( sscanf(arg, "%s in tai", item_name)!=1 )
                return notify_fail("用法：add <> in tai。\n");
        item=present(item_name, me);
        if (! present(item_name, me)) return notify_fail("你身上没有这东西。\n");
     	if (sizeof(all_inventory(ob))>=2) return notify_fail(ob->name()+"里面已经放满了。\n");
        message_vision( "$N将一"+item->query("unit")+item->query("name")+"放进"+ob->name()+"。\n",me);
        item->move(ob);

        return 1;

}

int do_get(string arg)
{
	string item_name;
        object me = this_player();
        object ob = this_object();
        if(!arg) return notify_fail("你要干什么？\n");
        if( sscanf(arg, "%s from tai", item_name)==1 && ob->query_temp("user") != me->query("id"))
                return 1;//notify_fail("不要拿别人的东西\n");
        return 0;

}

int do_put(string arg)
{
	string item_name;
        if(!arg) return notify_fail("你要干什么？\n");
        if( sscanf(arg, "%s in tai", item_name)==1 )
                return 1;
        return 0;

}

int do_jiawen()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   int k;

   inv = all_inventory(ob);
   if( !sizeof(inv) )
	return notify_fail("宝石炼制台里什么都没有，加什么温，烧空气啊？\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了宝石炼制台了吗？\n");
   if (me->query("force")<200) return notify_fail("你的内力不够！\n");
   if (me->query("mana")<200) return notify_fail("你的法力不够！\n");
   if (me->is_busy()) return notify_fail("你正忙着呢。\n");

      me->add("force",-150);
       me->add("mana",-150);
   if (random(2)==0) tell_room(environment(me),HIR+me->name()+"默运神功，双手变得通红,然后按在"+ob->name()+HIR+"上，使其慢慢地变热。 \n"NOR);
   else tell_object(me,HIR+me->name()+"默运神功，双手变得通红,然后按在"+ob->name()+HIR+"上，使其慢慢地变热。 \n"NOR);
    if (!wizardp(me)) me->start_busy(1);
     ob->add("temperature",100);
   if (ob->query("temperature")>3500) {
   	for (k=0;k<sizeof(inv);k++) destruct(inv[k]);
 	tell_object(me,ob->name()+"温度过高，材料汽化消失了！\n");
   	reload_object(ob);
   	return 1;
   }
   if (ob->query("temperature")>ob->query_temp("max_temp")) ob->set_temp("max_temp",ob->query("temperature"));

   return 1;
}

int do_jiangwen()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   int k;

   inv = all_inventory(ob);
   if( !sizeof(inv) )
	return notify_fail(ob->name()+"里什么都没有，降什么温啊？\n");
   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了宝石炼制台了吗？\n");
   if (me->query("force")<200) return notify_fail("你的内力不够！\n");
   if (me->query("mana")<200) return notify_fail("你的法力不够！\n");
   if (me->is_busy()) return notify_fail("你正忙着呢。\n");

       me->add("force",-150);
       me->add("mana",-150);

   if (random(2)==0) tell_room(environment(me),HIW+me->name()+"默运神功，双手蒙上一层寒霜,然后按在"+ob->name()+HIW+"上，使其慢慢地变冷。 \n"NOR);
   else tell_object(me,HIW+me->name()+"默运神功，双手蒙上一层寒霜,然后按在"+ob->name()+HIW+"上，使其慢慢地变冷。 \n"NOR);
    if (!wizardp(me)) me->start_busy(1);
   if (ob->query("temperature")>=100) ob->add("temperature",-100);
   	else ob->add("temperature",-20);
   if (ob->query("temperature")<=-273) {
   	for (k=0;k<sizeof(inv);k++) destruct(inv[k]);
 	tell_object(me,ob->name()+"温度达到了绝对零度，材料被冻坏消失了！\n");
   	reload_object(ob);
   	return 1;
   }

   if (ob->query("temperature")<ob->query_temp("min_temp")) ob->set_temp("min_temp",ob->query("temperature"));

   return 1;
}

int do_finish()
{
   object me = this_player();
   object ob = this_object();
   mixed *inv;
   string mess;
   int i,min_temp,max_temp,suss,suss1,*color1,tmp; //sta为炼完状态，0：失败，物品消失；1：失败，物品不消失；
   		//2：成功，得到同级合成宝石；3、成功，得到高一级合成宝石

   if (ob->query_temp("user") != me->query("id")) return notify_fail("你租用了宝石炼制台了吗？\n");
           remove_call_out("do_temperature");

   mess="";
   inv = all_inventory(ob);
   if( !sizeof(inv) )
	return notify_fail("宝石炼制台里什么都没有，你想干什么啊？\n");
   if( sizeof(inv)<=1) 	return get_baoshi(random(2),mess);//一颗总不能用来合成吧？
   for(i=0; i<sizeof(inv); i++) //台里含有非宝石类杂质、宝石等级不同，sta=0
   	if (inv[i]->query("material") != "baoshi" ||inv[0]->query("level") !=inv[i]->query("level"))
   	{
   		mess=HIG+"炼制的材料好象不纯。\n"+NOR;
         return get_baoshi(random(2),mess);
   	}

   min_temp=-50-(int)inv[0]->query("level")*50;
    if (min_temp<-273) min_temp=-270;
   max_temp=1000+(int)inv[0]->query("level")*500;
   if (ob->query_temp("min_temp") > min_temp)
   {
   	mess=HIG+"材料融化后，需要经过极寒才能重新结晶。\n"+NOR;
      return get_baoshi(random(2),mess);
   }

   if (ob->query_temp("max_temp") < max_temp)
   {
   	mess=HIG+"应该加热到足够的温度才能使宝石完全融化。\n"+NOR;
      return get_baoshi(random(2),mess);
   }

/*
   tmp=(int)(((int)(min_temp*1.1)-ob->query_temp("min_temp"))/10);//最低温度影响
   if (tmp<0) tmp*=-1;
   suss=tmp;
   tmp= (int)(ob->query_temp("max_temp")-(int)(max_temp*1.1)/10);//最高温度影响
   if (tmp<0) tmp*=-1;
   suss+=tmp;
*/
   suss1=inv[0]->query("level")*10+10;//等级越高，成功度越低
   suss=random(100); //成功率
   tmp=(ob->query("temperature")-(inv[0]->query("level")*100))/5; //完成温度的影响
   if (tmp<0) tmp*=-1;
   suss-=tmp;

   tmp=0;
   for(i=0; i<sizeof(inv);i++)
   {
   	if (inv[0]->query("color") != inv[i]->query("color")) tmp=1;
   }

   //suss=100;//测试用
    if (suss>suss1 && tmp==0) return get_baoshi(2,mess);
    else if (suss>suss1 && tmp==1) return get_baoshi(3,mess);
    else if (suss>suss1-33) return get_baoshi(1,mess);
   else return get_baoshi(0,mess);

}

int get_baoshi(int sta,string mess1)
{
   object me = this_player();
   object obj,ob = this_object();
   string mess, me_name,ob_name;
   int i,k,sum,*kind=({0,0});
   mixed *inv;

   me_name=me->name();
   ob_name=ob->name();
   inv = all_inventory(ob);
   mess=HIG+me_name+"觉得差不多了，收起神功，屏住呼吸，小心翼翼地打开"+ob_name+"。\n";
   switch(sta)
   {
   	case 0:
   		mess+=HIG+"但是"+ob_name+"里面空空如也，什么都没有。\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			destruct(inv[k]);
                message("channel:chat",HIM"【空穴来风】：听说"+me_name+"炼制宝石失败，所有材料付之一炬。\n"NOR,users());
   		break;
   	case 1:
   		mess+=HIG+"发现原来炼制的材料还在里面，只好又尴尬地拿了出来。\n"+NOR;
   		for (k=0;k<sizeof(inv);k++)
   			inv[k]->move(me);
                message("channel:chat",HIM"【空穴来风】：听说"+me_name+"炼制宝石失败，还好，材料还在。\n"NOR,users());
   		break;
   	case 2://同级合成宝石
   		obj=inv[0];
   		if (sizeof(inv)>1) for (k=1;k<sizeof(inv);k++) destruct(inv[k]);
   		if (obj->query("color")==0)
   		{
   			i=random(3)+1;//原石随机生成红 蓝 黄三色
   			if (i==3) i=4;
   		}else i=obj->query("color");
   		baoshi_attribute(obj,i,obj->query("level")+1);
   		obj->move(me);
   		mess+=HIG+"发现里面一颗"+obj->name()+HIG+"闪闪发光。\n";
   		mess+=me_name+"迫不急待地一把抓了出来。\n"+NOR;
                message("channel:chat",HIM"【空穴来风】：听说"+me_name+"炼制宝石成功，炼成了"+obj->name()+"。\n"NOR,users());
		break;
   	case 3:
   		obj=inv[0];
   		sum=0;
   		for(k=0; k<sizeof(inv);k++)
   		{
   			sum+=inv[k]->query("color");
   			kind[k]=inv[k]->query("color");
   		}
   		if (sizeof(inv)>1) for (k=1;k<sizeof(inv);k++) destruct(inv[k]);

   		if (sum>=7)
   		{
   			i=7;
   			if (sum==8 && member_array(6,kind)>=0) i=6;
   			if (sum==9 && member_array(5,kind)>=0) i=5;
   			if (sum==10 && member_array(6,kind)>=0) i=6;
   		}
   		else if (sum<=4) i=3;
   		else if (sum==5 && member_array(3,kind)>=0) i=3;
   		else if (sum==6 && member_array(5,kind)>=0) i=5;
   		else i=sum;
   		baoshi_attribute(obj,i,obj->query("level"));
   		obj->move(me);
   		mess+="发现里面一颗"+obj->name()+HIG+"闪闪发光。\n";
   		mess+=me_name+"迫不急待地一把抓了出来。\n"+NOR;
                message("channel:chat",HIM"【空穴来风】：听说"+me_name+"炼制宝石成功，炼成了"+obj->name()+"。\n"NOR,users());
		break;

   }
   mess+=mess1;
   tell_room(environment(me),mess);
   reload_object(ob);
   return 1;
}

void baoshi_attribute(object obj,int i,int j)
{
   object me = this_player();
   string *attr;
   int k;
   mixed *color=({
   		({GRN,"原石",0,"",""}),
   		({HIR,"红色宝石",1,"red",({"damage"})}),
   		({HIB,"蓝色宝石",2,"blue",({"attack"})}),
    		({MAG,"紫色宝石",3,"purple",({"damage","attack"})}),
                ({HIY,"黄色宝石",4,"yellow",({"luck"})}),
                ({YEL,"橙色宝石",5,"orange",({"damage","luck"})}),
   		({HIG,"绿色宝石",6,"green",({"attack","luck"})}),
   		({HIW,"钻石",7,"dimond",({"damage","attack","luck"})})
   	}),
   	*level=({
   		({0,"",""}),
   		({1,"破碎的",10}),
   		({2,"有裂纹的",20}),
   		({3,"有瑕疵的",30}),
   		({4,"纯净的",40}),
   		({5,"完美的",50})
   	});
   	if (j>5) j=5;
   	obj->set_name(color[i][0]+level[j][1]+color[i][1]+NOR,({color[i][3]+" baoshi","baoshi"}));
   	obj->set("color",i);
   	obj->set("level",j);
       obj->set("long","一颗闪闪发光的"+obj->name()+"\n好象可以镶嵌(inset)什么东西上面。\n是由("+me->query("name")+")炼制的。\n");
   	set("changed",1);
   	attr=color[i][4];
   	for (k=0;k<sizeof(attr);k++)
   	    obj->set("prop/"+attr[k],level[j][2]/2+random(level[j][2]/2));
}

int do_tem()
{
   object me=this_player();
   object ob=this_object();
   if (!ob->query_temp("user"))  return notify_fail("你要干嘛？\n");;
   if ( wizardp(me) ||( me==present(ob->query_temp("user")) && (me == present(ob->query_temp("user"), environment(me)))))
   	tell_object(me,"温度："+this_object()->query("temperature")+" \n");
   else  tell_object(me,"别人在炼宝石呢，不要捣乱，不准偷看。\n");
   return 1;
}

void do_temperature()
{
	if (this_object()->query("temperature") > 25)
	{
		this_object()->add("temperature",-1);
	}
	else if (this_object()->query("temperature") < 25)
	{
		this_object()->add("temperature",1);
	}
	call_out("do_temperature", 2);

}
