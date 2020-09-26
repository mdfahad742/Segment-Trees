#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

const ll INF=1e18+5;

struct node{
	ll seg,pref,suff,sum;
};


void build1(vector<ll> &b,vector<node> &t1,ll st,ll en,ll tn){
	if(st==en){
		t1[tn].seg=b[st];
		t1[tn].pref=b[st];
		t1[tn].suff=b[st];
		t1[tn].sum=b[st];
		return;
	}
	ll mid=(st+en)/2;
	build1(b,t1,st,mid,tn*2);
	build1(b,t1,mid+1,en,tn*2+1);
	
	t1[tn].seg=max({t1[2*tn].seg,t1[2*tn+1].seg,t1[2*tn].suff+t1[2*tn+1].pref});
	t1[tn].pref=max(t1[2*tn].pref,t1[2*tn].sum+t1[2*tn+1].pref);
	t1[tn].suff=max(t1[2*tn+1].suff,t1[2*tn].suff+t1[2*tn+1].sum);
	t1[tn].sum=t1[2*tn].sum+t1[2*tn+1].sum;
	
}

void update1(vector<ll> &b,vector<node> &t1,ll st,ll en,ll ind,ll val,ll tn){
	if(ind>en || ind<st)return;
	if(st==en){
		b[st]=val;
		t1[tn].seg=b[st];
		t1[tn].pref=b[st];
		t1[tn].suff=b[st];
		t1[tn].sum=b[st];
		return;
	}
	ll mid=(st+en)/2;
	if(ind<=mid)
		update1(b,t1,st,mid,ind,val,tn*2);
	else
		update1(b,t1,mid+1,en,ind,val,tn*2+1);
	
	
	t1[tn].seg=max({t1[2*tn].seg,t1[2*tn+1].seg,t1[2*tn].suff+t1[2*tn+1].pref});
	t1[tn].pref=max(t1[2*tn].pref,t1[2*tn].sum+t1[2*tn+1].pref);
	t1[tn].suff=max(t1[2*tn+1].suff,t1[2*tn].suff+t1[2*tn+1].sum);
	t1[tn].sum=t1[2*tn].sum+t1[2*tn+1].sum;
}

node query1(vector<node> &t1,ll st,ll en,ll tn,ll l,ll r){
	if(st>=l && en<=r){
		return t1[tn];
	}
	if(st>r || en<l)return (node){-INF,-INF,-INF,-INF};
	ll mid=(st+en)/2;
	node ans1=query1(t1,st,mid,tn*2,l,r);
	node ans2=query1(t1,mid+1,en,tn*2+1,l,r);
	
	t1[tn].seg=max({ans1.seg,ans2.seg,ans1.suff+ans2.pref});
	t1[tn].pref=max(ans1.pref,ans1.sum+ans2.pref);
	t1[tn].suff=max(ans2.suff,ans1.suff+ans2.sum);
	t1[tn].sum=ans1.sum+ans2.sum;
	
	return t1[tn];
	
}

int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;cin>>n>>m;
	
	vector<ll> b(n);
	vector<node> t1(4*n+1);
	for(int i=0;i<n;i++){
		int x;cin>>x;
		b[i]=x;
	}
	
	build1(b,t1,0,n-1,1);
	
	
	//for(int x:b)cout<<x<<" ";
	//cout<<endl;
	
	//for(int x:t1)cout<<x<<" ";
	//cout<<endl;
	node tmp=query1(t1,0,n-1,1,0,n-1);
	if(tmp.seg<0)cout<<0<<endl;
	else cout<<tmp.seg<<endl;
	while(m--){
		int i,v;cin>>i>>v;
		
		update1(b,t1,0,n-1,i,v,1);
		
		tmp=query1(t1,0,n-1,1,0,n-1);
		if(tmp.seg<0)cout<<0<<endl;
		else cout<<tmp.seg<<endl;
	}
		
	
	return 0;
}
