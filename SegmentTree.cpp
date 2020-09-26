#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define endl '\n'

const ll INF=1e18+5;


void build1(vector<ll> &b,vector<ll> &t1,ll st,ll en,ll tn){
	if(st==en){
		t1[tn]=b[st];
		return;
	}
	
	ll mid=(st+en)/2;
	build1(b,t1,st,mid,tn*2);
	build1(b,t1,mid+1,en,tn*2+1);
	
	t1[tn]=(t1[2*tn]+t1[2*tn+1]);
}

void update1(vector<ll> &b,vector<ll> &t1,ll st,ll en,ll ind,ll val,ll tn){
	if(ind>en || ind<st)return;
	if(st==en){
		b[st]=val;
		t1[tn]=val;
		return;
	}
	
	ll mid=(st+en)/2;
	if(ind<=mid)
		update1(b,t1,st,mid,ind,val,tn*2);
	else
		update1(b,t1,mid+1,en,ind,val,tn*2+1);
	t1[tn]=t1[2*tn]+t1[2*tn+1];
}

ll query1(vector<ll> &t1,ll st,ll en,ll tn,ll l,ll r){
	
	if(st>=l && en<=r){
		return t1[tn];
	}
	
	if(st>r || en<l)return 0;
	
	ll mid=(st+en)/2;
	
	ll ans1=query1(t1,st,mid,tn*2,l,r);
	ll ans2=query1(t1,mid+1,en,tn*2+1,l,r);
	return (ans1+ans2);
}

int main(){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int n,m;cin>>n>>m;
	
	vector<ll> b(n),t1(4*n+1);
	for(int i=0;i<n;i++){
		int x;cin>>x;
		b[i]=x;
	}
	
	build1(b,t1,0,n-1,1);
	
	
	//for(int x:b)cout<<x<<" ";
	//cout<<endl;
	
	//for(int x:t1)cout<<x<<" ";
	//cout<<endl;
	
	while(m--){
		int op;cin>>op;
		if(op==1){
			int i,v;
			cin>>i>>v;
			update1(b,t1,0,n-1,i,v,1);
		}
		else{
			int l,r;cin>>l>>r;
			cout<<query1(t1,0,n-1,1,l,r-1)<<endl;
			
		}
	}
		
	
	return 0;
}
