#include <string>
#include <iostream>
#include <unordered_map>

using namespace std;
typedef unordered_map<int, int *> map;
typedef map::const_iterator iter;

static int r = 0;       // the number of resource_remain types
static int *resource_total;   // Total number of resources
static int *resource_remain;   // Number of remaining resources
static int *req_buff;   // Number of resources requested buff
static string cmd_buff; // Command buff

const string cmd_new = "new";             // Command NEW
const string cmd_request = "request";     // Command REQUEST
const string cmd_terminate = "terminate"; // Command TERMINATE

static map process_req; // The number of required resources declared when the process is newly created
static map process_got; // The number of resources acquired by the process

// Initialize the array to 0
int *init_arr(int size)
{
    int *arr = new int[size];
    for (int i = 0; i < size; ++i)
    {
        arr[i] = 0;
    }
    return arr;
}

void read_to_req_buff()
{
    for (int i = 0; i < r; ++i)
    {
        cin >> req_buff[i];
    }
}

bool check_total()
{
    for (int i = 0; i < r; ++i)
    {
        if (resource_total[i] < req_buff[i])
        {
            return false;
        }
    }
    return true;
}

bool check_remain()
{
    for (int i = 0; i < r; ++i)
    {
        if (resource_remain[i] < req_buff[i])
        {
            return false;
        }
    }
    return true;
}

bool check_need(const int *got, const int *max_req)
{
    for (int i = 0; i < r; ++i)
    {
        if (got[i] + req_buff[i] > max_req[i])
        {
            return false;
        }
    }
    return true;
}

bool check_safe()
{
    int size = process_req.size();
    int **got = new int *[size];
    int **need = new int *[size];
    bool *finish = new bool[size];
    iter it_got = process_got.begin(), it_req = process_req.begin();
    for (int i = 0; i < size; ++it_got, ++it_req, ++i)
    {
        finish[i] = false;
        got[i] = new int[r];
        need[i] = new int[r];
        for (int j = 0; j < r; ++j)
        {
            got[i][j] = it_got->second[j];
            need[i][j] = it_req->second[j] - got[i][j];
        }
    }
    int *remain = new int[r];
    for (int i = 0; i < r; ++i)
    {
        remain[i] = resource_remain[i];
    }

    int fin_cnt = 0;
    int one_loop_cnt = 1;
    while (one_loop_cnt)
    {
        one_loop_cnt = 0;
        for (int k = 0; k < size; ++k)
        {
            if (finish[k])
            {
                continue;
            }
            bool enough = true;
            for (int j = 0; j < r; ++j)
            {
                if (remain[j] < need[k][j])
                {
                    enough = false;
                    break;
                }
            }
            if (enough)
            {
                ++one_loop_cnt;
                finish[k] = true;
                for (int j = 0; j < r; ++j)
                {
                    remain[j] += got[k][j];
                }
            }
        }
        fin_cnt += one_loop_cnt;
    }
    for (int i = 0; i < size; ++i)
    {
        delete[] got[i];
        delete[] need[i];
    }
    delete[] got;
    delete[] need;
    delete[] finish;
    delete[] remain;
    return fin_cnt == size;
}

bool parse_command(int pid)
{

    iter got = process_got.find(pid);
    cin >> cmd_buff;
    if (cmd_new == cmd_buff)
    {
        read_to_req_buff();
        if (got == process_got.end() && check_total())
        {
            int *req_new = init_arr(r);
            process_got[pid] = req_new;
            process_req[pid] = req_buff;
            req_buff = new int[r];
            return true;
        }
    }
    else if (cmd_request == cmd_buff)
    {
        read_to_req_buff();
        if (got != process_got.end() && check_remain())
        {
            int *got_res = got->second;
            int *max_req = process_req.find(pid)->second;
            if (check_need(got_res, max_req))
            {
                for (int i = 0; i < r; ++i)
                {
                    got_res[i] += req_buff[i];
                    resource_remain[i] -= req_buff[i];
                }
                if (check_safe())
                {
                    return true;
                }
                else
                {
                    for (int i = 0; i < r; ++i)
                    {
                        got_res[i] -= req_buff[i];
                        resource_remain[i] += req_buff[i];
                    }
                }
            }
        }
    }
    else if (cmd_terminate == cmd_buff && got != process_got.end())
    {
        int *got_res = got->second;
        for (int i = 0; i < r; ++i)
        {
            resource_remain[i] += got_res[i];
        }
        delete[] got_res;
        iter p_req = process_req.find(pid);
        delete[] p_req->second;
        process_req.erase(p_req);
        process_got.erase(got);
        return true;
    }
    return false;
}

int main()
{
    process_req = map();
    process_got = map();
    cin >> r;
    resource_total = new int[r];
    resource_remain = new int[r];
    req_buff = new int[r];
    for (int i = 0; i < r; ++i)
    {
        cin >> resource_total[i];
        resource_remain[i] = resource_total[i];
    }

    int pid;
    while (cin >> pid)
    {
        if (parse_command(pid))
        {
            cout << "OK\n";
        }
        else
        {
            cout << "NOT OK\n";
        }
    }
    delete[] resource_total;
    delete[] resource_remain;
    delete[] req_buff;
    for (const auto &it : process_req)
        delete[] it.second;
    process_req.clear();
    process_got.clear();
}