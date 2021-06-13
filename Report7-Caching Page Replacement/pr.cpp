
#include <iostream>
#include <set>
#include <queue>
#include <list>
#include <unordered_map>
#include <cmath>
#include <iterator>
#include <iomanip>

struct node {
    int key, value;
    node *pre = nullptr;
    node *next = nullptr;

    explicit node(int key, int value = -1) {
        this->key = key;
        this->value = value;
    }
};

struct link {
    node *head;
    node *tail;

    link() {
        this->head = new node(-1);
        this->tail = new node(-1);
        this->head->next = tail;
        this->tail->pre = head;
    }

    ~link() {
        delete this->head;
        delete this->tail;
    }

    node *front() const {
        return this->head->next;
    }

    void remove(node *node_old) {
        node_old->pre->next = node_old->next;
        node_old->next->pre = node_old->pre;
    }

    static void insert_before(node *node_new, node *before) {
        node_new->next = before;
        node_new->pre = before->pre;
        before->pre->next = node_new;
        before->pre = node_new;
    }

    node *push_back(int key, int value = -1) const {
        node *node_new = new node(key, value);
        insert_before(node_new, this->tail);
        return node_new;
    }

    node *insert_by_value_desc(int key, int value) const {
        node *tmp = this->head->next;
        while (tmp != this->tail && tmp->value > value) {
            tmp = tmp->next;
        }
        node *node_new = new node(key, value);
        insert_before(node_new, tmp);
        return node_new;
    }

    void pop_front() const {
        if (this->head->next != this->tail) {
            node *tmp = this->head->next;
            this->head->next = tmp->next;
            tmp->next->pre = this->head;
            delete tmp;
        }
    }
};

void FIFO();

void LRU();

void MIN();

void Clock();

typedef std::unordered_map<int, node *> node_map;

static int pages_cnt, cache_size, hit = 0;
static int *pages_query;

int main() {
    using namespace std;
    ios::sync_with_stdio(false);
    istream::sync_with_stdio(false);
    ostream::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int algo;
    cin >> cache_size >> algo >> pages_cnt;
    pages_query = new int[pages_cnt];
    for (int i = 0; i < pages_cnt; ++i) {
        cin >> pages_query[i];
    }

    switch (algo) {
        case 0:
            FIFO();
            break;
        case 1:
            LRU();
            break;
        case 2:
            MIN();
            break;
        case 3:
            Clock();
            break;
        default:
            break;
    }

    cout << "Hit ratio = " << setw(5) << setfill('0') << fixed << setprecision(2) <<
         round(10000.0 * (1.0 * hit / pages_cnt)) / 100.0 << "%";
    return 0;
}

void FIFO() {
    std::queue<int> my_queue = std::queue<int>();
    std::set<int> my_set = std::set<int>();
    for (int i = 0; i < pages_cnt; ++i) {
        int query = pages_query[i];
        if (my_set.find(query) != my_set.end()) {
            ++hit;
        } else {
            if (my_set.size() >= cache_size) {
                my_set.erase(my_set.find(my_queue.front()));
                my_queue.pop();
            }
            my_set.insert(query);
            my_queue.push(query);
        }
    }
}

void LRU() {
    node_map my_map = node_map();
    my_map.reserve(cache_size);

    link lru_link = link();

    for (int i = 0; i < pages_cnt; ++i) {
        int query = pages_query[i];
        auto iter = my_map.find(query);
        if (my_map.find(query) != my_map.end()) {
            ++hit;
            // remove hit node
            lru_link.remove(iter->second);
        } else {
            if (my_map.size() >= cache_size) {
                // Delete the element at the front of the linked list
                my_map.erase(my_map.find(lru_link.front()->key));
                lru_link.pop_front();
            }
        }
        // Add a node to the back of the linked list
        my_map[query] = lru_link.push_back(query);
    }
}

void MIN() {
    typedef std::unordered_map<int, std::list<int>> list_map;
    node_map my_map = node_map();
    my_map.reserve(cache_size);

    list_map my_list_map = list_map();
    my_list_map.reserve(cache_size);

    int idx = 1;
    link min_link = link();

    for (int i = 0; i < pages_cnt; ++i) {
        const int query = pages_query[i];
        auto iter = my_map.find(query);
        if (my_map.find(query) != my_map.end()) {
            ++hit;
            // remove hit node
            min_link.remove(iter->second);
        } else {
            if (my_map.size() >= cache_size) {
                // Delete the element at the front of the linked list (which have max next time used value)
                my_map.erase(my_map.find(min_link.front()->key));
                min_link.pop_front();
            }
        }

        auto list_map_iter = my_list_map.find(query);
        if (list_map_iter == my_list_map.end()) {
            my_list_map[query] = std::list<int>();
            list_map_iter = my_list_map.find(query);
        }
        std::list<int> &tmp_l = list_map_iter->second;
        if (tmp_l.empty()) {
            while (idx < pages_cnt && pages_query[idx] != query) {
                int other = pages_query[idx];
                auto list_map_iter0 = my_list_map.find(other);
                if (list_map_iter0 == my_list_map.end()) {
                    my_list_map[other] = {};
                } else {
                    list_map_iter0->second.push_back(idx);
                }
                ++idx;
            }
            tmp_l.push_back(idx);
            ++idx;
        }

        my_map[query] = min_link.insert_by_value_desc(query, tmp_l.front());
        tmp_l.pop_front();
    }
}

void Clock() {
    node *head = new node(-1, 0);
    node *tmp = head;
    for (int i = 1; i < cache_size; ++i) {
        tmp->next = new node(-1, 0);
        tmp = tmp->next;
    }
    tmp->next = head;

    typedef std::unordered_map<int, node *> lru_map;
    lru_map my_map = lru_map();
    my_map.reserve(cache_size);

    for (int i = 0; i < pages_cnt; ++i) {
        int query = pages_query[i];
        auto iter = my_map.find(query);
        if (iter != my_map.end()) {
            ++hit;
            iter->second->value = 1;
        } else {
            while (head->value != 0) {
                --head->value;
                head = head->next;
            }
            iter = my_map.find(head->key);
            if (iter != my_map.end()) {
                my_map.erase(iter);
            }
            my_map[query] = head;
            head->key = query;
            head->value = 1;
            head = head->next;
        }
    }
}