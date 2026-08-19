#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<char> cate(41);  //进程类型
vector<int> st(41);  //进程开始时间
vector<int> k(41);  //进程拥有的任务数量
vector<int> w(41);  //特殊进程的忍耐限度
vector<vector<pair<int,int>>> task(41,vector<pair<int,int>>(41));  //进程每个子任务的需求资源和任务长度
vector<bool> vis(41,true);  //每种资源的可用情况，初始都可用
vector<int> owner(41,0);  //每种资源的拥有者
vector<int> tmp(41,-1);  //进程状态，0表示资源申请状态，1表示任务运行状态，-1表示尚未开始或者已经结束
vector<unordered_set<int>> resource(41);  //进程占有的资源统计
vector<int> val(41,0);  //进程收益
vector<int> total(41,0);  //进程总持续段数
vector<int> during(41,0);  //特殊进程已经忍耐的时间
vector<int> proc(41,1);  //每个进程进行到第几个子任务，从第一个开始
vector<int> cnt(41,0);  //每个进程已经执行当前子任务的时间

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n>>m;
    for (int i=1;i<=n;++i) {
        cin>>cate[i];
        if (cate[i]=='X') {
            cin>>st[i]>>k[i];
        } else {
            cin>>st[i]>>w[i]>>k[i];
        }
        for (int j=1;j<=k[i];++j) {
            cin>>task[i][j].first>>task[i][j].second;
        }
    }
    int t;  //总运行时间，如果到了一个很大的时间还没结束，说明有死锁
    for (t=1;t<=80000;++t) {
        //段首
        unordered_set<int> s;  //记录所有被申请的资源编号
        unordered_map<int,unordered_set<int>> ask;  //记录申请资源的进程，按资源分类
        unordered_map<int,int> pid,cid;  //记录所有申请的进程中编号最小的一个，所有抢占的C进程中编号最大的一个，按资源分类
        //检查所有进程，分为要申请和不申请两类
        for (int i=1;i<=n;++i) {
            if ((tmp[i]==-1 && st[i]<t) || st[i]>t) {
                continue;  //已经终止的进程
            }
            if (tmp[i]==1) {
                //不申请
                ++cnt[i];
            } else {
                if (st[i]==t) {
                    tmp[i]=0;  //在t时刻开始的进程
                }
                int r=task[i][proc[i]].first;
                s.insert(r);
                ask[r].insert(i);
                if (pid.find(r)==pid.end()) {
                    pid[r]=i;
                } else {
                    pid[r]=min(pid[r],i);
                }
                if (cate[i]=='C' && during[i]==w[i]) {
                    if (cid.find(r)==cid.end()) {
                        cid[r]=i;
                    } else {
                        cid[r]=max(cid[r],i);
                    }
                }
            }
        }
        for (int r:s) {
            int res=0;  //最终得到资源的进程
            if (cid.find(r)!=cid.end()) {
                res=cid[r];
            } else if (vis[r]) {
                res=pid[r];
            }
            //处理得到资源的进程
            if (res) {
                resource[res].insert(r);
                tmp[res]=1;
                vis[r]=0;
                during[res]=0;
                ++cnt[res];
                if (cate[res]=='C' && owner[r]!=0) {
                    resource[owner[r]].erase(r);
                }
                owner[r]=res;
            }
            //处理未得到资源的进程
            for (int pro:ask[r]) {
                if (pro!=res) {
                    if (cate[pro]!='X') {
                        ++during[pro];
                    }
                    if ((cate[pro]=='B' && during[pro]==w[pro]) || (cate[pro]=='C' && during[pro]==w[pro]+1)) {
                        during[pro]=0;
                        tmp[pro]=1;
                        ++cnt[pro];
                    }
                }
            }
        }
        //段中
        for (int i=1;i<=n;++i) {
            if (tmp[i]!=-1) {
                ++total[i];
                if (tmp[i]==1) {
                    val[i]+=resource[i].size();
                }
            }
        }
        //段末
        for (int i=1;i<=n;++i) {
            if (tmp[i]==-1) {
                continue;
            }
            if (cate[i]=='A' && during[i]==w[i]) {
                //已经到忍耐限度的A类进程放弃已拥有的全部资源
                for (int it:resource[i]) {
                    vis[it]=1;
                    owner[it]=0;
                }
                resource[i].clear();
            } else if (proc[i]==k[i] && cnt[i]==task[i][proc[i]].second) {
                tmp[i]=-1;
                //终止的进程释放资源
                for (int it:resource[i]) {
                    vis[it]=1;
                    owner[it]=0;
                }
                resource[i].clear();
            } else if (cnt[i]==task[i][proc[i]].second) {
                //当前的子任务进行完，准备下一个子任务
                tmp[i]=0;
                cnt[i]=0;
                ++proc[i];
            }
        }
    }
    for (int i=1;i<=n;++i) {
        if (tmp[i]!=-1) {
            total[i]=-1;
        }
    }
    for (int i=1;i<=n;++i) {
        cout<<val[i]<<" "<<total[i]<<'\n';
    }
    return 0;
}