#include <bits/stdc++.h>
using namespace std;
int cnt; //剩余的任务数量
int n,m,T,k;
vector<int> t(105); //每个CPU的时间片
vector<int> task(105); //每个任务的工作量
vector<int> res(105); //每个任务从第一次被处理到执行完毕的总时间
vector<unordered_set<int>> s(105); //每个任务的S集合
vector<queue<int>> q(105); //不同的队列
set<int> timing; //要进行处理的时间点
vector<unordered_set<int>> vec(10005); //某个事件点要处理的CPU集合
vector<int> id(105); //每个CPU对应的队列号
vector<bool> vis(105,false); //该任务之前是否被运行过
vector<int> mp(105); //每个CPU正在处理的任务

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
	cin>>n>>m>>T;
	cnt=n;
	for (int i=1;i<=m;++i) {
		cin>>t[i];
	}
	for (int i=1;i<=n;++i) {
		cin>>task[i]>>k;
		while (k--) {
			int tmp;
			cin>>tmp;
			s[i].insert(tmp);
		}
	}
	for (int i=1;i<=m;++i) {
		id[i]=i;
	}
	for (int i=1;i<=n;++i) {
		int id=(i-1)%m+1;
		if (i<=m) {
			int tmp;
			if (s[i].find(id)!=s[i].end()) {
				tmp=min(t[id],(task[i]+1)/2);
			} else {
				tmp=min(t[id],task[i]);
			}
			timing.insert(tmp);
			vec[tmp].insert(id);
			mp[id]=i;
			vis[i]=true;
		}
		if (i>m) {
			q[id].push(i);
		}
	}
	for (int i=T;i<=10005;i+=T) {
		timing.insert(i);
	}
    unordered_set<int> st; //某个时刻，可能当前CPU下的队列没有任务，但是后续循环后会分配到任务
    if (n<m) {
        for (int i=n+1;i<=m;++i) {
            st.insert(i);
        }
    }
	while (cnt) {
		int tmp=*(timing.begin());
        for (auto it:st) {
            vec[tmp].insert(it);
        }
        st.clear();
		timing.erase(tmp);
		//对每个CPU 
		for (int it:vec[tmp]) {
			int pos=id[it];  //每个CPU对应的队列
			int proc=mp[it];  //当前处理的任务
			if (proc==0) {
				continue;
			}
			if (s[proc].find(it)!=s[proc].end()) {
				if ((task[proc]+1)/2<=t[it]) {
					task[proc]=0;
					--cnt;
					res[proc]=tmp-res[proc];
				} else {
					task[proc]-=t[it]*2;
					q[pos].push(proc);
				}
			} else {
				if (task[proc]<=t[it]) {
					task[proc]=0;
					--cnt;
					res[proc]=tmp-res[proc];
				} else {
					task[proc]-=t[it];
					q[pos].push(proc);
				}
			}
			mp[it]=0;
		}
		//循环
		if (tmp%T==0) {
			for (int i=1;i<=m;++i) {
				int pos=id[i];
				pos=(pos%m)+1;
				id[i]=pos;
			}
		}
		//取新任务
		for (int it:vec[tmp]) {
			int pos=id[it];
			if (!q[pos].empty()) {
				int proc=q[pos].front();
				q[pos].pop();
				if (!vis[proc]) {
					res[proc]=tmp;
					vis[proc]=true;
				}
				int cl;
				if (s[proc].find(it)!=s[proc].end()) {
					cl=min(t[it],(task[proc]+1)/2);
				} else {
					cl=min(t[it],task[proc]);
				}
				cl+=tmp;
				timing.insert(cl);
				vec[cl].insert(it);
				mp[it]=proc;
			} else {
                st.insert(it);
            }
		}
	}
	for (int i=1;i<=n;++i) {
		cout<<res[i]<<" ";
	}
    return 0;
}