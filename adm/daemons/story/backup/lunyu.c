#include <ansi.h>

object book = find_object("/clone/book/lbook4");

object get_owner()
{
    object owner;
    if(objectp(book)) {
        owner = environment(book);
        if(owner->is_character()) return owner;
    }
    return 0;
}

object book_owner = get_owner();

string get_book()
{
    if(objectp(book)) destruct(book);
    if(objectp(book_owner) && userp(book_owner)) book_owner->unconcious();
    return "苟读：...............丫的你去死吧！";
}

nosave string book_owner_name = objectp(book_owner) ? book_owner->query("name") : "某人";

nosave mixed *story = ({
        "苟读：这两天闲来无事，看来得读读书了，不然学业的荒废了。",
        "苟读：咦……我那本先师传下来的《论语》怎么不见了，我得好好找找！",
        "苟读开始翻箱倒柜找书......",
        "苟读挠了挠头道：怎么找不到了呢？",
        "苟读恍然大悟：哦！原来前两天借给" + book_owner_name + "了，这厮也是，借这么久都不来还。",
        "苟读：看来真是“书非借而不能读也。”我且去看看这小子现在有多用功。",
        "苟读来到" + book_owner_name + "面前。",
        book_owner_name + "正与一群小孩在地上玩泥巴呢，脸上身上弄到到出龌龊不堪。",
                "苟读：%—*（）（—……*—%￥###￥*（）（%*",
                "苟读：你这小子！原以为你借我书在发奋用功，没想到你如此不长进。",
        "苟读：罢了，你这样的人也只有玩泥巴了，把书拿来！",
        book_owner_name + "：切！你这破书什么用没有，同来折纸飞机纸都太软了。",
        book_owner_name + "掏出一本破书丢给苟读",
        (: get_book :),
        book_owner_name + "被苟读打晕了。",
        "苟读悻悻的回到逍遥谷。",
});

string prompt() { return HIW "【武林轶事】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}
