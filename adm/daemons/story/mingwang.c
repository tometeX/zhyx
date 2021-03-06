// story:donghai 东海龙传说

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "奥林匹斯山上...",
        "十年的泰坦之战让这座神山几乎变成了废墟。",
        "最终泰坦难敌众神之力被关进冥界的最底部塔尔塔托斯。",
        "诸神之神宙斯坐在宝座上，冷冷的盯着台下的弟弟冥王哈迪斯。",
        "宙斯：哈迪斯，作为我的亲弟弟，你为何联合泰坦发动叛乱？",
        "哈迪斯：哼！我的能力远在你之上，凭什么你高居奥林匹斯山顶，而我确在冥界！",
        "众神转头望向宙斯，似乎在期待些什么。",
        "宙斯沉吟片刻，说道：来人，把哈迪斯身上的枷锁打开，我今天就要你见识挑战神威的后果！",
        "哈迪斯：哈哈哈！正如我愿，今天我就要让奥林匹斯山易主！",
        "随着哈迪斯身上枷锁的打开，慢慢的在他周围聚集起无数面目狰狞的凶灵，似乎整个大地都在颤抖！",
        "宙斯右手探空一抓，雷霆之杖已握于手中，天空顿时聚集起大片乌云，雷鸣电闪，一场大的风暴正在逼近！",
        "哈迪斯默念法咒，忽然间分身出无数个哈迪斯，携无数凶灵齐齐攻向宙斯！",
        "宙斯高高举起雷霆，万千道闪电瞬间击中雷霆，发出的白光几乎把整个黑暗的大地都照亮了！",
        "哈迪斯：去死吧！",
        "宙斯将雷霆指向哈迪斯，刹那间，无数道强劲的闪电从雷霆疾射而出，将哈迪斯的幻影瞬间击碎。",
        "哈迪斯眼见不敌，随即化作一缕黑烟，急速逃离了奥林匹斯山。",
        (: give_gift, "hadisi" :),
        "听说冥王哈迪斯(ha disi)被宙斯击败，逃到了凡间。",
});

string prompt() { return HIM "【神话传说】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出现在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
