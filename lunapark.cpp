#include<iostream>
#include<vector>
#include<utility>
#include<cstring>
using namespace std;

const int Max_N=200010,Max_Q=1000010;

int n,q;

vector<int> result;

int witim [Max_N];

void initialize_witim(){
    for(int counter=0;counter<n;counter++){
        witim [counter]=counter;
    }
return;
}

bool graf [Max_N];
pair<int,int> pyrwoto;
int pyrwoto_length;

vector< pair<int,int> > graph [Max_N];

vector<int> loop;
int max_in_interwal [Max_N][20];

pair<int,int> parents [Max_N];

void find_circle_dfs(int current){
graf[current]=true;
for(int counter=0;counter<graph [current].size();counter++){
    if(!graf[graph[current][counter].first]){
        parents[graph[current][counter].first].first=current;
        parents[graph[current][counter].first].second=graph[current][counter].second;
        find_circle_dfs(graph[current][counter].first);
    }
}
return;
}

void find_circle(int a,int b){
memset(graf,0,sizeof(graf));
parents [a].first=-1;
graf [a]=true;
for(int counter=0;counter<graph[a].size();counter++){
    if(graph [a][counter].first!=b){
    parents[graph[a][counter].first].first=a;
    parents[graph[a][counter].first].second=graph[a][counter].second;
    graf[graph[a][counter].first]=true;
    find_circle_dfs(graph[a][counter].first);
    }
}
int current=b;
while(parents[current].first!=-1){
   loop.push_back(current);
   current=parents[current].first;
}
loop.push_back(current);
//for(int counter=0;counter<loop.size();counter++){
//    cout<<counter<<" "<<loop [counter]<<endl;
//}
return;
}

int find_max(int a,int b){
if(a>b){
    return a;
}
return b;
}

void find_max_in_interval(){
int c;
for(c=0;c+1<loop.size();c++){
    max_in_interwal [c][0] = parents[loop [c]].second;
}
max_in_interwal[c][0]=pyrwoto_length;
int level=0;
while(true){
    level++;
    for(int counter=0;counter<loop.size();counter++){
            //cout<<"Check "<<(counter + (1<<level))<<" "<<loop.size()<<" "<<counter<<" "<<level<<endl;
        if((counter + (1<<level))>loop.size()){
            max_in_interwal [counter][level]=-1;
        }else{
        max_in_interwal [counter][level] = find_max(max_in_interwal[counter][level-1],max_in_interwal [counter + 1<<(level-1)][level-1]);
        }
    }
    if(max_in_interwal[0][level]==-1){
        goto a;
    }
}
a:;
for(int counter=0;counter<level;counter++){
    for(int coun=0;coun<loop.size();coun++){
        cout<<max_in_interwal [coun][counter]<<" ";
    }
    cout<<endl;
}
return;
}

int longest_to_circle [Max_N];

void longest_to_circle_dfs(int current){
graf [current]=true;
for(int counter=0;counter<graph [current].size();counter++){
    if(!graf[graph[current][counter].first]){
        longest_to_circle [graph[current][counter].first] = find_max(longest_to_circle[current],graph[current][counter].second);
        longest_to_circle_dfs(graph[current][counter].first);
    }
}
return;
}

void long_to_circle(){
memset(graf,0,sizeof(graf));
for(int counter=0;counter<loop.size();counter++){
    graf[loop[counter]]=true;
    if(counter==0){
        for(int c=0;c<graph[loop[counter]].size();c++){
            if(graph[loop[counter]][c].first!=loop[loop.size()-1] and graph[loop[counter]][c].first!=loop[counter+1]){
                longest_to_circle [graph[loop[counter]][c].first]=graph[loop[counter]][c].second;
                longest_to_circle_dfs(graph[loop[counter]][c].first);
            }
        }
    }else if(counter==loop.size()-1){
        for(int c=0;c<graph[loop[counter]].size();c++){
            if(graph[loop[counter]][c].first!=loop[counter-1] and graph[loop[counter]][c].first!=loop[0]){
                longest_to_circle [graph[loop[counter]][c].first]=graph[loop[counter]][c].second;
                longest_to_circle_dfs(graph[loop[counter]][c].first);
            }
        }
    }else{
        for(int c=0;c<graph[loop[counter]].size();c++){
            if(graph[loop[counter]][c].first!=loop[counter-1] and graph[loop[counter]][c].first!=loop[counter+1]){
                longest_to_circle [graph[loop[counter]][c].first]=graph[loop[counter]][c].second;
                longest_to_circle_dfs(graph[loop[counter]][c].first);
            }
        }
    }
}
//for(int counter=0;counter<n;counter++){
//    cout<<"longest to circle: "<<counter<<" "<<longest_to_circle[counter]<<endl;
//}
}

int find_max_in_random_interval(int a,int b){
int result=0,l=b-a+1,k;
while(l>0){
    k=0;
    while((1<<k)<=l){
        k++;
    }
    k--;
    result=find_max(result,max_in_interwal[b-l+1][k]);
    l-=(1<<k);
}
return result;
}

int calculate_needed(int a,int b){

}

int main(){
ios_base::sync_with_stdio(false);
cin>>n;
int a,b,c;
for(int counter=0;counter<n;counter++){
    cin>>a>>b>>c;
    a--;
    b--;
    graph [a].push_back({b,c});
    graph [b].push_back({a,c});
    if(graf[a] and graf[b]){
        pyrwoto.first=a;
        pyrwoto.second=b;
        pyrwoto_length=c;
    }else{
    graf[a]=true;
    graf[b]=true;
    }
}
//cout<<"first "<<pyrwoto.first<<pyrwoto.second<<endl;
find_circle(pyrwoto.first,pyrwoto.second);
find_max_in_interval();
long_to_circle();
initialize_witim();
cin>>q;
int d;
for(int c=0;c<q;c++){
    cin>>a>>b>>c;
    b--;
    c--;
    if(a==1){
        result.push_back(calculate_needed(witim[b],witim[c]));
    }else{
        d=witim[c];
        witim[c]=witim[b];
        witim[b]=d;
    }
}





return 0;
}
