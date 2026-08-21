#include <bits/stdc++.h>
using namespace std;
int n,id=0;
unordered_map<string,vector<int>> mp;  //存放目录文件名到id的映射，一个文件名可能对应好几个文件
//文件结构体
struct file {
    int cate;  //文件种类，0代表目录文件，1代表普通文件
    int id;  //唯一标识一个文件
    int fa=-1;  //双亲目录id
    long long siz=0;  //文件大小，只有普通文件才有
    long long LD=0,LR=0;  //配额
    long long LD_size=0,LR_size=0;  //后代已占用的空间
    unordered_set<string> child_cata,child_file;  //存放孩子目录文件和孩子普通文件的名字
};
vector<file> vec(1);  //根据id唯一找到一个文件

struct Node {
    int id;
    int parent;
    string name;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin>>n;
    file p;
    p.id=++id;
    vec.push_back(p);  //根目录文件
    mp["root"].push_back(id);
    while (n--) {
        char op;
        string path;
        long long siz,ld,lr;
        cin>>op>>path;
        if (op=='C') {
            cin>>siz;
            int pre_id=1;  //上一层目录的id，初始化为根目录
            string str;  //路径中出现的文件名
            unordered_set<int> st;  //路径中出现过的目录id
            vector<Node> rollback;  //若执行不成功，撤销所有的操作
            st.insert(1);
            int flag=1;  //成功与否，初始化为成功
            for (int i=1;i<path.length();++i) {
                if (path[i]!='/') {
                    str+=path[i];
                } else {
                    if (vec[pre_id].child_cata.find(str)!=vec[pre_id].child_cata.end()) {
                        for (int cur_id:mp[str]) {
                            if (vec[cur_id].fa==pre_id) {
                                st.insert(cur_id);
                                pre_id=cur_id;
                                str="";
                                break;
                            }
                        }
                    } else {
                        if (vec[pre_id].child_file.find(str)!=vec[pre_id].child_file.end()) {
                            flag=0;
                            break;
                        }
                        file newf;
                        newf.cate=0;
                        newf.id=++id;
                        newf.fa=pre_id;
                        vec.push_back(newf);
                        vec[pre_id].child_cata.insert(str);
                        mp[str].push_back(id);
                        st.insert(id);
                        rollback.push_back((Node){id,pre_id,str});
                        str="";
                        pre_id=id;
                    }
                }
            }
            if (flag) {
                if (vec[pre_id].child_cata.find(str)!=vec[pre_id].child_cata.end()) {
                    flag=0;
                } else if (vec[pre_id].child_file.find(str)!=vec[pre_id].child_file.end()) {
                    long long oldsiz;
                    int oldid;
                    for (int fid:mp[str]) {
                        if (vec[fid].fa==pre_id) {
                            oldid=fid;
                            oldsiz=vec[fid].siz;
                            break;
                        }
                    }
                    for (int fid:st) {
                        if (!vec[fid].LD && !vec[fid].LR) {
                            continue;
                        }
                        if (fid==pre_id && vec[fid].LD) {
                            if (vec[fid].LD_size-oldsiz+siz>vec[fid].LD) {
                                flag=0;
                                break;
                            }
                        }
                        if (vec[fid].LR) {
                            if (vec[fid].LR_size-oldsiz+siz>vec[fid].LR) {
                                flag=0;
                                break;
                            }
                        }
                    }
                    if (flag) {
                        file newf;
                        newf.cate=1;
                        newf.fa=pre_id;
                        vec[oldid].fa=-1;
                        newf.id=++id;
                        newf.siz=siz;
                        vec.push_back(newf);
                        mp[str].push_back(id);
                        for (int fid:st) {
                            vec[fid].LR_size=vec[fid].LR_size-oldsiz+siz;
                            if (fid==pre_id) {
                                vec[fid].LD_size=vec[fid].LD_size-oldsiz+siz;
                            }
                        }
                    }
                } else {
                    for (int fid:st) {
                        if (!vec[fid].LD && !vec[fid].LR) {
                            continue;
                        }
                        if (fid==pre_id && vec[fid].LD) {
                            if (vec[fid].LD_size+siz>vec[fid].LD) {
                                flag=0;
                                break;
                            }
                        }
                        if (vec[fid].LR) {
                            if (vec[fid].LR_size+siz>vec[fid].LR) {
                                flag=0;
                                break;
                            }
                        }
                    }
                    if (flag) {
                        file newf;
                        newf.cate=1;
                        newf.fa=pre_id;
                        newf.id=++id;
                        newf.siz=siz;
                        vec.push_back(newf);
                        mp[str].push_back(id);
                        vec[pre_id].child_file.insert(str);
                        for (int fid:st) {
                            vec[fid].LR_size=vec[fid].LR_size+siz;
                            if (fid==pre_id) {
                                vec[fid].LD_size=vec[fid].LD_size+siz;
                            }
                        }
                    }
                }
            }
            //如果不成功，则撤销所有新建的目录，恢复到原始状态
            if (!flag) {
                for (int i=rollback.size()-1;i>=0;--i) {
                    Node roll=rollback[i];
                    vec[roll.id].fa=-1;
                    vec[roll.parent].child_cata.erase(roll.name);
                }
            }
            if (flag) {
                cout<<"Y\n";
            } else {
                cout<<"N\n";
            }
        } else if (op=='R') {
            int pre_id=1;  //上一层目录的id，初始化为根目录
            string str;  //路径中出现的文件名
            unordered_set<int> st;  //路径中出现过的目录id
            st.insert(1);
            int flag=1;  //路径中的文件或者目录是否都存在
            for (int i=1;i<path.length();++i) {
                if (path[i]!='/') {
                    str+=path[i];
                } else {
                    if (vec[pre_id].child_cata.find(str)==vec[pre_id].child_cata.end()) {
                        flag=0;
                        break;
                    } else {
                        for (int fid:mp[str]) {
                            if (vec[fid].fa==pre_id) {
                                st.insert(fid);
                                pre_id=fid;
                                str="";
                                break;
                            }
                        }
                    }
                }
            }
            if (flag) {
                int cur_id=-1;
                for (int tmp:mp[str]) {
                    if (vec[tmp].fa==pre_id) {
                        cur_id=tmp;
                        break;
                    }
                }
                if (vec[pre_id].child_cata.find(str)!=vec[pre_id].child_cata.end()) {
                    for (int fid:st) {
                        vec[fid].LR_size-=vec[cur_id].LR_size;
                    }
                    vec[pre_id].child_cata.erase(str);
                    vec[cur_id].fa=-1;
                } else if (vec[pre_id].child_file.find(str)!=vec[pre_id].child_file.end()) {
                    for (int fid:st) {
                        vec[fid].LR_size-=vec[cur_id].siz;
                        if (fid==pre_id) {
                            vec[fid].LD_size-=vec[cur_id].siz;
                        }
                    }
                    vec[pre_id].child_file.erase(str);
                    vec[cur_id].fa=-1;
                }
            }
            cout<<"Y\n";
        } else {
            cin>>ld>>lr;
            int pre_id=1;  //上一层目录的id，初始化为根目录
            string str;  //路径中出现的文件名
            int flag=1;  //是否成功
            if (path.length()==1) {
                str="root";
                if ((ld && vec[1].LD_size>ld) || (lr && vec[1].LR_size>lr)) {
                    cout<<"N\n";
                } else {
                    vec[1].LD=ld;
                    vec[1].LR=lr;
                    cout<<"Y\n";
                }
                continue;
            }
            for (int i=1;i<path.length();++i) {
                if (path[i]!='/') {
                    str+=path[i];
                } else {
                    if (vec[pre_id].child_cata.find(str)==vec[pre_id].child_cata.end()) {
                        flag=0;
                        break;
                    }
                    for (int fid:mp[str]) {
                        if (vec[fid].fa==pre_id) {
                            pre_id=fid;
                            str="";
                            break;
                        }
                    }
                }
            }
            if (flag) {
                if (vec[pre_id].child_cata.find(str)==vec[pre_id].child_cata.end()) {
                    flag=0;
                } else {
                    int cur_id;
                    for (int fid:mp[str]) {
                        if (vec[fid].fa==pre_id) {
                            cur_id=fid;
                            str="";
                            break;
                        }
                    }
                    if (ld && vec[cur_id].LD_size>ld) {
                        flag=0;
                    }
                    if (lr && vec[cur_id].LR_size>lr) {
                        flag=0;
                    }
                    if (flag) {
                        vec[cur_id].LD=ld;
                        vec[cur_id].LR=lr;
                    }
                }
            }
            if (flag) {
                cout<<"Y\n";
            } else {
                cout<<"N\n";
            }
        }
    }
    return 0;
}