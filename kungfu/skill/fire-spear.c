
inherit SKILL;
#include <ansi.h>

mapping zhaoshi = ([
        "dodge" : ({ -50,-10,10,20,30,50,60,30,20,-30,}),
        "damage"        : ({ 150,100,90,70,50,30,40,80,70,130,}),
        "parry" : ({ -25,-50,-80,-20,-20,-25,-50,-80,-20,-20,}),
        "force" : ({  130,100,80,70,60,60,70,80,100,120, }),
        "attack"        : ({  130,100,80,70,60,60,70,80,100,120, }),
        "damage_type"   : ({ "砸伤","内伤","瘀伤","重伤","震伤","点穴","反震伤","砸伤","割伤","刺伤"}),
        "limbs" : ({    "左胸","左肩","左手","左脚","左臂","左脚","左腿",
                                "右胸","右肩","右手","右脚","右臂","右脚","右腿",
                                "面门","天灵盖","小腹","后背","腰际", }),
        "action"        : ({ 
                "$N使一招"+BLINK""+HIW"「迎门三不过」"NOR"，手中$w连续刺向$n面门，哽嗓，前心",
                "$N运足精神，抖起$w，一招"+BLINK""+HIG"「拨草寻蛇」"NOR"刺向$n$l",
                "$N一个跨步，使一招"+BLINK""+HIC"「高山流水」"NOR"，手中$w势若飞瀑刺向$n的$l",
                "$N一按枪把，啪！地一声抖出"+BLINK""+HIM"「五朵枪花」"NOR"。上下左右，虚虚实实刺向$n全身要害",
                "只见$N一个斜跨，使个"+BLINK""+HIR"「举火烧天势」"NOR"，手中$w带出一道寒气，由下而上疾挑$n$l",
                "只见$N手腕一翻，手中$w从意想不到的角度刺向$n的$l。\n这一招"+BLINK""+HIB"「灵蛇出洞」"NOR"快若闪电，毒辣无比",
                "$N使个"+BLINK""+MAG"「飞鸟投林势」"NOR"，身形斜飞，从侧面突出一枪，径刺$n$l",
                "$N似欲退走，可是忽地一个转身，百忙中使出一招"+BLINK""+RED"「回马枪」"NOR"，$w一挺刺向$n$l",
                "$N大吼一声，手中$w微扬，一招「风起云涌」，霎时枪影如封墙，\n有若旎转钢刀般挟以万钧之势封向$n",
                "$N反身一弹，重重枪影先将敌人身形罩住，而后一招「覆雨翻云」，\n只见寒芒一闪，$w己闪电般射向$n",
                "$N使出「火龙腾云」，七道红芒一经泛出有若苍鹰猎兔以雷霆万钧之势，快愈飘风的刺向$n",
                "$N$w指地，身形半曲，使出一招「浴火凤凰」，往前射去，\n只见一道红芒掠过，人枪如流星似的划过空间，冲向$n",
                "$N微一反身，己使出「天火燎原」，舞出万朵火花，只见红光闪闪，\n$n被罩入一片红光之中",
                "$N狂喝一声，$w己泛起一道红芒，只见狂风大作，\n$N枪势一带，这招「火云敝日」摧枯拉朽，击向$n",
                "$N$w一抖，枪影满天，$n顿时被罩在这招「晚霞满天」的一片火光之中",
                "$N$w一抖，向$n脚下磋来，搅起一片尘土，这招「火烧连营」逼得$n连连后退，无处落脚",
                        }),
 
]);

 
int valid_learn(object me)
{
return notify_fail("看来只能学习了。\n");
}

int valid_enable(string usage)
{
//return usage=="spear" || usage=="parry";
return usage=="sword" || usage=="parry";
}

mapping query_action(object me, object weapon)
{
int *force,*attack,*dodge,*parry,*damage;
string *action,*damage_type;

force = zhaoshi["force"];
attack = zhaoshi["attack"];
dodge = zhaoshi["dodge"];
parry = zhaoshi["parry"];
damage = zhaoshi["damage"];
action = zhaoshi["action"];
damage_type = zhaoshi["damage_type"];

return  ([      
        "action"        :       action[random(sizeof(action))],
        "attack"        :       attack[random(sizeof(attack))],
        "dodge" :       dodge[random(sizeof(dodge))],
        "damage"        :       damage[random(sizeof(damage))],
        "parry" :       parry[random(sizeof(parry))],
        "force" :       force[random(sizeof(force))],
        "damage_type"   :       damage_type[random(sizeof(damage_type))],
        ]);
}

int practice_skill(object me)
{
string msg,*msgs;
if( (int)me->query("sen") < 30)
        return notify_fail("你的精神无法集中了，休息一下再练吧。\n");
if( (int)me->query("kee") < 30 )
        return notify_fail("你现在手足酸软，休息一下再练吧。\n");
if( (int)me->query("force") < 10 )
        return notify_fail("你的内力不够了。\n");
msgs=zhaoshi["action"];
msg=msgs[random(sizeof(msgs))];
msg=replace_string(msg,"$n","枪靶");
msg=replace_string(msg,"$w","手中长枪");
msg=replace_string(msg,"$l","靶身");
message_vision(msg+"\n",me);
me->receive_damage("kee", 30);
me->add("force", -10);
return 1;
}

string perform_action_file(string func)
{
return CLASS_D("star") + "/shengdou/"+func;
}

