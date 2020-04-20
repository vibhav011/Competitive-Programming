#include<bits/stdc++.h>
using namespace std;
#define lli long long int
#define mod 998244353

lli power(lli x,lli y,lli m);

lli modInverse(lli a, lli m) 
{ 
     return power(a, m-2, m); 
    
} 
lli power(lli x, lli y, lli m) 
{ 
    if (y == 0) 
        return 1; 
    lli p = power(x, y/2, m) % m; 
    p = (p * p) % m; 
  
    return (y%2 == 0)? p : (x * p) % m; 
} 

int main(){
	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t;
    cin>>t;
    while(t--){
       string s;
       cin>>s;
       lli count=0;
       lli start_index=-1;
       lli stop_index=-1;
       lli current_index=-1;
       lli n=s.length();
       for(lli i=0;i<n;i++){
           if(s[i]=='^'){
           	   if(stop_index==-1){
           	   	stop_index=i;
           	   	current_index=i;
           	   }
           	   else if((i-current_index)<(stop_index-start_index)){
           	   	start_index=current_index;
           	   	stop_index=i;
           	   	current_index=i;
           	   }
           	   else{
                current_index=i;
           	   }
           }
           else if(s[i]=='('||s[i]==')'||s[i]==','){
           	s.erase(s.begin()+i);                             //remove bracket and commas from string
           	n--;i--;
           }
       }
       string b;
       if((n-current_index)<(stop_index-start_index)){                      
       	b=s.substr(current_index+1);                           //pos,till end 
       }
       else if(stop_index==-1&&start_index==-1){               
           b=s;
       }
       else{
       	b=s.substr(start_index+1,stop_index-start_index-1);    //pos,length
       }
       lli orrer=1;lli ander=1; 
       lli k=1;
       lli m=1;
       for(lli i=1;i<b.length();i+=2){
          if(b[i]=='&'){
            ander+=power(2,k,mod);
            ander%=mod;
          }
          else{
          	orrer+=power(2,k,mod);
          	orrer%=mod;
          }
          k++;
       }
       n=int(b.length())/2 +1;
       lli q=modInverse(power(2,2*n,mod),mod);                    //4^n modulo^-1 998244353(denominator)
       cout<<(((ander*ander)%mod)*q)%mod<<" "<<(((orrer*orrer)%mod)*q)%mod<<" "<<(((ander*orrer)%mod)*q)%mod<<" "<<(((ander*orrer)%mod)*q)%mod<<"\n";
    }
    return 0;
}