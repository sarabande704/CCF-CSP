#include <bits/stdc++.h>
using namespace std;

//词汇节点
struct Node {
    int pre,next;
    int symbol;  //词汇在词汇表中的下标
    int wid;  //所属单词的编号
    bool active;  //该节点是否在链表中
};

struct Candidate {
    int freq;
    int x,y;  //备选词汇对在词汇表中的下标
    int merged_len;  //词汇对总长
    int len_first;  //前一个词汇长度
    string merged_str;  //合并后的词汇对
    //大顶堆
    bool operator<(const Candidate &o) const {
        if (freq!=o.freq) {
            return freq<o.freq;
        }
        if (merged_len!=o.merged_len) {
            return merged_len>o.merged_len;
        }
        if (len_first!=o.len_first) {
            return len_first>o.len_first;
        }
        return merged_str>o.merged_str;
    }
};

//为pair<int,int>自定义unordered_map的哈希函数
struct PairHash {
    size_t operator()(const pair<int,int> &p) const {
        return (size_t)p.first*1000003+p.second;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<string> words(n);  //读入的单词序列
    vector<int> freqs(n);  //单词频率
    for (int i=0;i<n;++i) {
        cin>>words[i]>>freqs[i];
    }
    //初始化词汇表，词汇表元素为构成单词的所有字母，按字母序排列
    set<char> chars_set;
    for (string &w:words) {
        for (char &c:w) {
            chars_set.insert(c);
        }
    }
    vector<string> vocab;  //词汇表
    unordered_map<string,int> symbol_to_id;  //建立词汇表中的词汇到其下标之间的映射
    for (char c:chars_set) {
        string s(1,c);
        int id=vocab.size();
        vocab.push_back(s);
        symbol_to_id[s]=id;
    }
    //初始化单词链表，也就是切分结果，初始状态，单词按字母一个个切分
    vector<Node> nodes;  //用数组模拟切分链表
    vector<int> head(n,-1);  //头指针集合，-1表示为空
    unordered_map<pair<int,int>,int,PairHash> pair_freq;  //词汇对频率
    unordered_map<pair<int,int>,unordered_set<int>,PairHash> pair_edges;  //词汇对到nodes下标的映射，快速找到其位置
    priority_queue<Candidate> pq;  //存放候选词汇对
    //更新
    auto update_pair=[&](int a,int b,int left_node,int delta,int wid) {
        pair<int,int> key={a,b};  //词汇对
        pair_freq[key]+=delta;  //更新频率
        if (pair_freq[key]==0) {
            pair_freq.erase(key);
            pair_edges.erase(key);
            return;  //删除词汇对
        }
        if (delta>0) {
            pair_edges[key].insert(left_node);  //新加入了词汇对
        } else {
            pair_edges[key].erase(left_node);  //删除词汇对的一个下标
        }
        Candidate c{
            pair_freq[key],a,b,
            vocab[a].length()+vocab[b].length(),
            vocab[a].length(),
            vocab[a]+vocab[b]
        };
        pq.push(c);
    };
    //建立链表，初始统计
    for (int i=0;i<n;++i) {
        string w=words[i];
        int f=freqs[i];
        vector<int> syms;  //对每个单词，存放构成它的每个字母在词汇表中的下标
        for (char c:w) {
            syms.push_back(symbol_to_id[string(1,c)]);
        }
        int prev=-1;
        for (int j=0;j<syms.size();++j) {
            int cur=nodes.size();
            nodes.push_back({prev,-1,syms[j],i,true});
            if (prev==-1) {
                head[i]=cur;
            } else {
                nodes[prev].next=cur;
            }
            prev=cur;
        }
        for (int cur=head[i];cur!=-1 && nodes[cur].next!=-1;cur=nodes[cur].next) {
            int nxt=nodes[cur].next;
            int a=nodes[cur].symbol,b=nodes[nxt].symbol;
            pair<int,int> key={a,b};
            pair_freq[key]+=f;
            pair_edges[key].insert(cur);
        }
    }
    //把初始的候选词汇对加入到优先级队列
    for (auto p:pair_freq) {
        if (p.second>0) {
            int a=p.first.first,b=p.first.second;
            pq.push(Candidate{p.second,a,b,vocab[a].length()+vocab[b].length(),vocab[a].length(),vocab[a]+vocab[b]});
        }
    }
    //主循环
    while (vocab.size()<m) {
        Candidate best;  //最佳的词汇对
        bool found=false;  //如果found为false，说明所有单词都被合并，结束循环
        while (!pq.empty()) {
            best=pq.top();
            pq.pop();
            pair<int,int> key={best.x,best.y};
            //优先队列有可能存在一个词汇对有不同记录（频率不一样），所以要先检验
            auto it=pair_freq.find(key);
            if (it!=pair_freq.end() && it->second==best.freq && best.freq>0) {
                found=true;  //找到了
                break;
            }
        }
        if (!found) {
            break;
        }
        //插入词汇表
        int x=best.x,y=best.y,z=vocab.size();
        string new_str=vocab[x]+vocab[y];
        vocab.push_back(new_str);
        symbol_to_id[new_str]=z;
        //更新操作，因为题目要求从左往右合并，所以对词汇对的位置先排序
        pair<int,int> key={x,y};
        vector<int> left_nodes(pair_edges[key].begin(),pair_edges[key].end());
        sort(left_nodes.begin(), left_nodes.end(), [&](int a, int b) {
            if (nodes[a].wid != nodes[b].wid) return nodes[a].wid < nodes[b].wid;
            return a < b;
        });
        for (int left:left_nodes) {
            if (!nodes[left].active) {
                continue;
            }
            int right=nodes[left].next;
            if (!nodes[right].active) {
                continue;
            }
            int wid=nodes[left].wid;
            int freq=freqs[wid];
            int prev_node=nodes[left].pre,next_node=nodes[right].next;
            int pa_sym=-1,bn_sym=-1;
            if (prev_node!=-1) {
                pa_sym=nodes[prev_node].symbol;
            }
            if (next_node!=-1) {
                bn_sym=nodes[next_node].symbol;
            }
            //删除旧边
            if (prev_node != -1) update_pair(pa_sym, x, prev_node, -freq, wid);
            update_pair(x, y, left, -freq, wid);
            if (next_node != -1) update_pair(y, bn_sym, right, -freq, wid);
            // 标记旧节点为非活跃
            nodes[left].active = false;
            nodes[right].active = false;
            // 创建新节点
            int new_node = nodes.size();
            nodes.push_back({prev_node, next_node, z, wid, true});
            if (prev_node != -1) nodes[prev_node].next = new_node;
            else head[wid] = new_node;
            if (next_node != -1) nodes[next_node].pre= new_node;
            // 增加新边
            if (prev_node != -1) update_pair(pa_sym, z, prev_node, freq, wid);
            if (next_node != -1) update_pair(z, bn_sym, new_node, freq, wid);
        }
    }
    //输出结果
    for (string s:vocab) { 
        cout<<s<<'\n';
    }
    return 0;
}