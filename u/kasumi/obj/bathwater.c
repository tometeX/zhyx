


#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "强效沐浴液" NOR, ({ "bath water", "muyu ye" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "\n一瓶壁绿剔透的液体，据说可以清洗掉身上所有的纹身。你可以通过（use）来使用。\n" NOR);
                set("unit", "块");
                set("value", 1000000);
                set("weight", 10);                
             }
        setup();
}

void init()
	{
		add_action("do_use","use");
	}
		

int do_use( string arg )
{		
	 string mapsk;	 
	 object me;

        if ( ! arg || (arg != "bath water" && arg != "muyu ye") )
          return 0;
	
	      me = this_player();
	      
	      if (me->query("tattoo/chest_long")=="七重冥王站立于炼狱白骨堆之上，无数冤魂围绕其身")
	      	me->delete("special_skill/hatred/");
	      if (me->query("tattoo/chest_long")=="九条蛟龍，相互盘绕缠缚，栩栩如生")
	      	me->delete("special_skill/power/");
	      if (me->query("tattoo/chest_long")=="一只浴火凤凰盘旋在云间，令人称奇")
	      	me->delete("special_skill/wrath/");
	      if (me->query("tattoo/chest_long")=="无数僧人朝拜佛祖，金光散布，神圣庄严")
	      	me->delete("special_skill/health/");
	      if (me->query("tattoo/chest_long")=="百鬼夜行，无数冤魂哀鸣恸哭，让人毛骨悚然")
	      	me->delete("special_skill/agile/");
	      if (me->query("tattoo/chest_long")=="托塔天王，站立于南天门之下，神威凛凛")
	      	me->delete("special_skill/ironskin/");
	      if (me->query("tattoo/chest_long")=="大慈大悲观世音菩萨，坐八宝莲花，千支手姿态各异")
	      	me->delete("special_skill/clever/");
	      if (me->query("tattoo/chest_long")=="万里江山，波澜壮阔，气势恢弘磅礴之极")
	      	me->delete("special_skill/mystery/");
	      if (me->query("tattoo/chest_long")=="后羿弯弓搭箭，九个太陽盘旋在空中")
	      	me->delete("special_skill/self/");
	      if (me->query("tattoo/chest_long")=="九仪天尊座于八宝莲花上，周身仙霞缭绕，似幻似真")
	      	me->delete("special_skill/divine/");
	      if (me->query("tattoo/chest_long")=="一名天神，手持巨斧，开天辟地的图案")
	      	me->delete("special_skill/recover/");
	      if (me->query("tattoo/chest_long")=="一副神农氏亲尝百草的图案")
	      	me->delete("special_skill/medicine/");	
	      if (me->query("tattoo/chest_long")=="这是一副佛祖寿辰，众仙朝获的图案。")
	      	me->delete("special_skill/buddhism/");	
	      if (me->query("tattoo/chest_long")=="芸芸终生，人生百态，尽在此图中。")
	      	me->delete("special_skill/selfstudy/");	
	      if (me->query("tattoo/chest_long")=="一副不死战神战斗的图案")
	      	me->delete("special_skill/nodie/");
	      if (me->query("tattoo/chest_long")=="一名天神，手持巨斧，开天辟地的图案")
	      	me->delete("special_skill/kingkong/");
	      if (me->query("tattoo/chest_long")=="无双国士，征战四海，平定天下")
	      	me->delete("special_skill/shuang/");		      	
	      if (me->query("tattoo/back_long")=="七重冥王站立于炼狱白骨堆之上，无数冤魂围绕其身")
	      	me->delete("special_skill/hatred/");
	      if (me->query("tattoo/back_long")=="九条蛟龍，相互盘绕缠缚，栩栩如生")
	      	me->delete("special_skill/power/");
	      if (me->query("tattoo/back_long")=="一只浴火凤凰盘旋在云间，令人称奇")
	      	me->delete("special_skill/wrath/");
	      if (me->query("tattoo/back_long")=="无数僧人朝拜佛祖，金光散布，神圣庄严")
	      	me->delete("special_skill/health/");
	      if (me->query("tattoo/back_long")=="百鬼夜行，无数冤魂哀鸣恸哭，让人毛骨悚然")
	      	me->delete("special_skill/agile/");
	      if (me->query("tattoo/back_long")=="托塔天王，站立于南天门之下，神威凛凛")
	      	me->delete("special_skill/ironskin/");
	      if (me->query("tattoo/back_long")=="大慈大悲观世音菩萨，坐八宝莲花，千支手姿态各异")
	      	me->delete("special_skill/clever/");
	      if (me->query("tattoo/back_long")=="万里江山，波澜壮阔，气势恢弘磅礴之极")
	      	me->delete("special_skill/mystery/");
	      if (me->query("tattoo/back_long")=="后羿弯弓搭箭，九个太陽盘旋在空中")
	      	me->delete("special_skill/self/");
	      if (me->query("tattoo/back_long")=="九仪天尊座于八宝莲花上，周身仙霞缭绕，似幻似真")
	      	me->delete("special_skill/divine/");
	      if (me->query("tattoo/back_long")=="一名天神，手持巨斧，开天辟地的图案")
	      	me->delete("special_skill/recover/");
	      if (me->query("tattoo/back_long")=="一副神农氏亲尝百草的图案")
	      	me->delete("special_skill/medicine/");	
	      if (me->query("tattoo/back_long")=="这是一副佛祖寿辰，众仙朝获的图案。")
	      	me->delete("special_skill/buddhism/");	
	      if (me->query("tattoo/back_long")=="芸芸终生，人生百态，尽在此图中。")
	      	me->delete("special_skill/selfstudy/");	
	      if (me->query("tattoo/back_long")=="一副不死战神战斗的图案")
	      	me->delete("special_skill/nodie/");
	      if (me->query("tattoo/back_long")=="一名天神，手持巨斧，开天辟地的图案")
	      	me->delete("special_skill/kingkong/");
	      if (me->query("tattoo/back_long")=="无双国士，征战四海，平定天下")
	      	me->delete("special_skill/shuang/");
	 
	      me->delete("tattoo/special/");
	      
	      me->delete("tattoo/tattoo_str");
	      me->delete("tattoo/tattoo_con");
	      me->delete("tattoo/tattoo_int");
	      me->delete("tattoo/tattoo_dex");
	      me->delete("tattoo/tattoo_per");
	      
	      me->delete("tattoo/face_long");
	      me->delete("tattoo/chest_long");
	      me->delete("tattoo/back_long");
	      me->delete("tattoo/leftarm_long");
	      me->delete("tattoo/rightarm_long");
	      me->delete("tattoo/buttock_long");

	      me->delete("special_skill/recover/");
	      me->delete("special_skill/medicine/");
	      me->delete("special_skill/buddhism/");
	      me->delete("special_skill/selfstudy/");
	      me->delete("special_skill/nodie/");
	      me->delete("special_skill/kingkong/");
	      me->delete("special_skill/shuang/");		
	      
	      me->delete("tattoo/tattoo");   
	      
        message_vision(HIG "$N"HIG"把沐浴液抹在身上，皮肤又凉转热，再而变得火烧般的剧痛......\n" NOR, me); 
        
        me->unconcious();

		destruct(this_object());
      return 1;
}

string query_autoload()
{
        if ( ! query("owner") )
                return 0;

        return query("owner");
}

void autoload(string owner)
{       
     if (owner) set("owner", owner);
}


		


       	