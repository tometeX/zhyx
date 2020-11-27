// storyd.c

#include <ansi.h>

inherit F_DBASE;

// 每 20 天刷新故事
#define REFRESH_TIME    20 * 86400

static string *story_name;

static object  running_story;
static mapping history;
static mapping book_reclaim = ([
        "canhezhi" :    21600,
        "lunyu" :       10800,
        "jingluoxue" :  10800,
        "xuanfengtui":  10800,
        "9yin1" :       86400,
        "9yin2" :       86400,
                ]);
static int step;
int    filter_listener(object ob);

private void init_story();
private void ready_to_start();
private void go_on_process(object ob);
int filter_story(string arg);

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "故事精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "故事系统已经启动。");

        init_story();

        history = allocate_mapping(sizeof(story_name));
        ready_to_start();
}

void init_story()
{
        CHANNEL_D->do_channel( this_object(), "sys", "故事系统更新所有故事。");
        story_name = get_dir(STORY_DIR + "*.c");
        story_name = map_array(story_name, (: $1[0..<3] :));
        set_temp("last_update", time());
}

private void ready_to_start()
{
        if (time() - query_temp("last_update") > REFRESH_TIME)
                init_story();

        remove_call_out("start_story");
        remove_call_out("process_story");
        call_out("start_story", 600 + random(300));
}

private void go_on_process(object ob)
{
        remove_call_out("start_story");
        remove_call_out("process_story");
        call_out("process_story", 1, ob);
}

int clean_up()
{
        return 1;
}

object query_running_story()
{
        return running_story;
}

private varargs void start_story(string sname)
{
        string *all_story;
        string name;
        object ob;

        ready_to_start();

        CHANNEL_D->do_channel(this_object(), "sys", "故事系统开始选择故事。");

        if (sname)
                all_story = explode(sname, ",");
        else
                all_story = filter_array(story_name, (: filter_story :));
        while (sizeof(all_story))
        {
                name = all_story[random(sizeof(all_story))];
                if (undefinedp(history[name]))
                        history += ([ name : time() ]);
                else
                        history[name] = (int)time();

                CHANNEL_D->do_channel(this_object(), "sys",
                                      "故事系统选择了故事(" + name + ")。");
 
                all_story -= ({ name });
                name = STORY_DIR + name;
                if (ob = find_object(name))
                        destruct(ob);
        
                catch(ob = load_object(name));
                running_story = ob;
        
                if (objectp(ob))
                {
                        step = 0;
                        go_on_process(ob);
                        break;
                }
        }
}

void remove_story(string story)
{
        story_name -= ({ story });
}

string *query_all_story()
{
        return story_name;
}

void process_story(object ob)
{
        mixed line;
        object *listeners;
        string prompt;

        go_on_process(ob);

        if (! objectp(ob))
        {
                ready_to_start();
                return;
        }

        line = ob->query_story_message(step);
        step++;

        prompt = ob->prompt();
        if (! prompt) prompt = HIG "【故事传闻】" NOR;
        if (functionp(line)) catch(line = evaluate(line));
        if (stringp(line))
        {
                listeners = filter_array(users(), (: filter_listener :));
                message( "story",  prompt + WHT + line + "\n" NOR, listeners );
        }

        if (intp(line) && ! line)
        {
                ready_to_start();
                destruct(ob);
        }
}

int filter_listener(object ob)
{
        if (ob->query("env/no_story")) return 0;
        return 1;
}

void give_gift(string gift, int amount, string msg)
{
        object ob, pob;
        object env;
        mapping ips;
        string ip, *ks;

        ips = ([ ]);
        foreach (pob in all_interactive())
        {
                if (wizardp(pob) || ! pob->query("born") ||
                    ! living(pob) || ! environment(pob) ||
                    pob->is_ghost() ||
                    environment(pob)->is_chat_room())
                        continue;

                ip = query_ip_number(pob);
                if (undefinedp(ips[ip])) ips[ip] = ({ pob }); else ips[ip] += ({ pob });
        }

        if (sizeof(ips) >= 1)
        {
                // 需要三个以上的IP登录才给与奖品

                // 随即抽一个IP
                ks = keys(ips);
                ip = ks[random(sizeof(ks))];

                // 在该IP地址上随即抽取一个玩家
                pob = ips[ip][random(sizeof(ips[ip]))];

                env = environment(pob);
                while (env && env->is_character())
                        env = environment(env);

                if (! objectp(env)) return;

                tell_room(env, msg);
                while (amount-- > 0)
                {
                        ob = new(gift);
                        ob->move(env);
                }
                CHANNEL_D->do_channel( this_object(),
                        "sys", sprintf(NOR WHT "赠品%s" NOR WHT "掉到了"
                                HIC "%s" NOR WHT "(%O" NOR WHT ")。" NOR,
                                ob->name(), env->short(), env));
        }
}

void add_reclaim_book(string book_name, int delay)
{
        if(file_size(STORY_DIR + book_name + ".c") == -1) return;
        
        if(undefinedp(book_reclaim[book_name]))
                book_reclaim += ([book_name:delay]);
        else
                book_reclaim[book_name] = delay;
}

mapping query_reclaim()
{
        return book_reclaim;
}

int filter_story(string arg)
{
        string books, *br_keys = keys(book_reclaim);
        int flag = 0;

        for(int i = 0; i < sizeof(br_keys); i++) {
                books = br_keys[i];
                if(time() - history[books] > book_reclaim[books]) {
                        flag = 1;
                        break;
                }
        }

        if(flag && arg != books) return 0;

        if(arg == "challenge") return 1;

           if(time() - history[arg] > 1800) return 1;
}

mapping query_history()
{
        return history;
}

