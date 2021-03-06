#include <ansi.h>
#include <getconfig.h>

// #pragma optimize
// #pragma save_binary

inherit F_SAVE;
inherit F_DBASE;

#define MAX_ADVS_CAPACITY       1000
#define ADV_TIMEOUT       1800

void ready_to_start();

void create()
{
        seteuid(getuid());
        restore();
        set("channel_id", "广告精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "广告系统已经启动。\n");

        ready_to_start();
}

void ready_to_start()
{
        remove_call_out("start_adv");
        call_out("start_adv", ADV_TIMEOUT);
}

void start_adv()
{
        mapping *notes;
        int index;
        string msg;

        ready_to_start();

        if (VERSION_D->is_boot_synchronizing())
                return;

	notes = query("notes");
	//如果没有广告就返回
        if (! pointerp(notes) || ! sizeof(notes))
                return;

	index = random(sizeof(notes));
        msg = WHT + LOCAL_MUD_NAME() + "的新闻广告时间到了：\n"
              HIC "≡" HIY "──────────────────────────────────────" HIC "≡\n" NOR
              + notes[index]["msg"] +
              HIC "≡" HIY "──────────────────────────────────────" HIC "≡\n" NOR;

        CHANNEL_D->do_channel(this_object(), "sys", "广告系统开始播送广告。\n");
        message( "adv",  msg, users() );
        //CHANNEL_D->do_channel(this_object(), "chat", msg);
}

void stop_adv()
{
	remove_call_out("start_adv");
        CHANNEL_D->do_channel(this_object(), "sys", "广告系统停止播送广告。\n");
}

void remove()
{
        save();
}

void mud_shutdown()
{
        save();
}

// show all the news's title
// raw = 1: only show the non-read news
void show_advs(object me, int raw)
{
        mapping *notes;
        int i, last_time_read;
        string msg;

        notes = query("notes");
        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "目前没有任何广告。\n");
                return;
        }

	if (raw)
	{
                tell_object(me, WHT + LOCAL_MUD_NAME() + "总共发布过" HIY +
                                chinese_number(sizeof(notes)) + NOR +
                                WHT "条广告。\n" NOR);
                return;
	}

        msg = WHT "目前"+ LOCAL_MUD_NAME() + "中的广告如下。\n"
              HIC "≡" HIY "───────────────────"
              "───────────────────" HIC "≡\n" NOR;

        i = sizeof(notes);
        while (i--)
        {
                if (raw && (notes[i]["time"] <= last_time_read))
                        break;

                msg += sprintf("%s [%3d]" NOR " %-" + (40 + color_len(notes[i]["title"])) +
                               "s %s" WHT "『 " CYN "%s" NOR + WHT " 』" NOR "\n",
                               (notes[i]["time"] > last_time_read ? HIY : ""),
                               i + 1, notes[i]["title"],
                               notes[i]["author"], ctime(notes[i]["time"])[0..9]);
        }

        msg += HIC "≡" HIY "──────────────────"
               "────────────────────" HIC "≡\n" NOR;

        me->start_more(msg);
}

// This is the callback function to process the string returned from the
// editor defined in F_EDIT of player object.
void done_post(object me, mapping note, int n, string text)
{
        int i;
        mapping *notes;

        text = color_filter(text) + NOR;

        note["msg"] = text;
        notes = query("notes");

        if (! pointerp(notes) || ! sizeof(notes))
                notes = ({ note });
        else
        {
                i = sizeof(notes) - 1;
                if (note["time"] <= notes[i]["time"])
                        note["time"] = notes[i]["time"] + 1;
                notes += ({ note });
        }

        // Truncate the notes if maximum capacity exceeded.
        if (sizeof(notes) > MAX_ADVS_CAPACITY)
                notes = notes[MAX_ADVS_CAPACITY / 4 .. MAX_ADVS_CAPACITY];

        set("notes", notes);
        tell_object(me, "广告发布完毕。\n");

        save();
}

// post a news
void do_post(object me, string arg)
{
        int n;
        mapping note;

        if (! wizardp(me) || ! interactive(me))
        {
                tell_object(me, "只有巫师才能发布广告。\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "发布广告请指定一个标题。\n");
                return;
        }

        if (sscanf(arg, "%s with %d", arg, n) != 2)
                n = 0;

        if (replace_string(arg, " ", "") == "")
                arg = "无标题";
        else
                arg = color_filter(arg) + NOR;

        note = allocate_mapping(4);
        note["title"] = arg;
        note["author"] = me->name(1) + "-" + me->query("id");
        note["time"] = time();
        me->edit(bind((: call_other, __FILE__, "done_post", me, note, n :), me));
}

// read a news
void do_read(object me, string arg)
{
        int num;
        mapping *notes;

        notes = query("notes");

        if (! pointerp(notes) || ! sizeof(notes))
        {
                tell_object(me, "目前没有任何广告。\n");
                return;
        }

        if (! arg)
        {
                tell_object(me, "你想读那一条广告？\n");
                return;
        }

        if (! sscanf(arg, "%d", num))
        {
                tell_object(me, "你要读第几条广告？\n");
                return;
        }

        if (num < 1 || num > sizeof(notes))
        {
                tell_object(me, "没有这条广告。\n");
                return;
        }
        num--;
        write(sprintf(HIC "≡" HIY "──────────────────"
                               "────────────────────" HIC "≡\n"
                               NOR " [%d] %-" + (40 + color_len(notes[num]["title"])) +
                               "s %s" WHT "『 " CYN "%s" NOR + WHT " 』\n" HIC "≡"
                               HIY "───────────────────────"
                               "───────────────" HIC "≡\n\n" NOR,
                               num + 1, notes[num]["title"], notes[num]["author"],
                               ctime(notes[num]["time"])[0..9]) + notes[num]["msg"]);

}

// discard a news
void do_discard(object me, string arg)
{
        mapping *notes;
        int num;
        string author, aid;

        if (! arg || sscanf(arg, "%d", num) != 1)
        {
                tell_object(me, "你想去掉拿一条广告？\n");
                return;
        }

        notes = query("notes");
        if (! arrayp(notes) || num < 1 || num > sizeof(notes))
        {
                tell_object(me, "没有这条广告。\n");
                return;
        }

        num--;

        if ((! stringp(author = notes[num]["author"]) ||
             sscanf(author, "%*s-%s", aid) != 2 ||
             aid != me->query("id")) &&
            (string)SECURITY_D->get_status(me) != "(admin)")
        {
                tell_object(me, "只有天神才能去掉他人发布的广告。\n");
                return;
        }

        notes = notes[0..num - 1] + notes[num + 1..sizeof(notes) - 1];
        set("notes", notes);
        save();
        tell_object(me, "你删除了第 " + (num + 1) + " 条广告。\n");
}


string query_save_file() { return DATA_DIR "advd"; }
