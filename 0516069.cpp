/*
	Name: HW1-big number calculation
	Author: weng-ying-chieh
	Date: 11/03/17 10:28
	Description:calculations of 20000-digit number 
*/
#include<iostream>
#include<stdlib.h>
#include<fstream>
using namespace std;

#define er 48

char *b_plus(char *x,char *y);
char *b_minus(char *x,char *y);
char *b_time(char *x,char *y);
char *b_divide(char *x,char *y);
char *b_minus_divide(char*x,char *y);
int compare(char *x,char *y);

char *b_plus(char *x,char *y){
	char *ans=(char*)calloc(40000,sizeof(char));
	//count the length of both x,y
	int contx,conty,b,c,d;
	for(b=0;x[b]!=NULL;b++){contx=b;}
	for(b=0;y[b]!=NULL;b++){conty=b;}
	//main calculation
	for(b=0,c=contx,d=conty;c>=0&&d>=0;b++,d--,c--){
		if(ans[b]==NULL){
			ans[b]=((x[c]-er)+(y[d]-er))%10+er;
			ans[b+1]=((x[c]-er)+(y[d]-er))/10+er;
		}
		else{
			ans[b+1]=(ans[b]-er+(x[c]-er)+(y[d]-er))/10+er;
			ans[b]=(ans[b]-er+(x[c]-er)+(y[d]-er))%10+er;
		}
		//cout<<x[c]<<"+"<<y[d]<<"="<<ans[b+1]<<ans[b]<<endl;
	}
	while(d>=0){
		if(ans[b]==NULL){
			ans[b]=y[d];
		}
		else{
			ans[b+1]=(ans[b]-er+y[d]-er)/10+er;
			ans[b]=(ans[b]-er+y[d]-er)%10+er;
		}
		b++;
		d--;
	}
	while(c>=0){
		if(ans[b]==NULL){
			ans[b]=x[c];
		}
		else{
			ans[b+1]=(ans[b]-er+x[c]-er)/10+er;
			ans[b]=(ans[b]-er+x[c]-er)%10+er;
		}
		b++;
		c--;
	}
	return ans;
}

char *b_minus(char *x,char *y){
		//cout<<"minus_divide  ";
	char *temp;
	char *ans=(char*)calloc(40000,sizeof(char));
	char *ans2=(char*)calloc(40000,sizeof(char));
	//make sure x is larger than y
	int check=0;
	if(compare(x,y)==0){
		temp=x;
		x=y;
		y=temp;
		check=1;
	}
	
	//count the length of both x,y
	int contx,conty,b,c,d;
	for(b=0;x[b]!=NULL;b++){contx=b;}
	for(b=0;y[b]!=NULL;b++){conty=b;}
	//main calculation
	for(b=0,c=contx,d=conty;c>=0&&d>=0;b++,d--,c--){
		if(x[c]>=y[d]){
			ans[b]=((x[c]-er)-(y[d]-er))+er;
		}
		else{
			ans[b]=(10+x[c]-y[d])+er;
			int g;
			for(g=c;g>=0&&x[g-1]=='0'&&x[g-2]=='0';g--){x[g-1]=9+er;}
			x[g-1]-=1;
		}
	}
	while(c>=0){
		ans[b]=x[c];
		b++;
		c--;
	}
	if(check==1){
		ans[b]='-';
	}
	
	return ans;
}

char *b_time(char *x,char *y){
	char *ans=(char*)calloc(40002,sizeof(char));
	//count the length of both x,y
	int contx,conty,b,c,d,e;
	for(b=0;x[b]!=NULL;b++){contx=b;}
	for(b=0;y[b]!=NULL;b++){conty=b;}
	//main calculation
	for(e=0,d=conty;d>=0;d--,e++){
		for(b=e,c=contx;c>=0;c--,b++){
			if(ans[b]==NULL){
				ans[b]=((x[c]-er)*(y[d]-er))%10+er;
				ans[b+1]=((x[c]-er)*(y[d]-er)/10)+er;
				//cout<<"route 1"<<endl;
			}
			else{
				if(ans[b+1]==NULL){
					ans[b+1]=(ans[b]-er+(x[c]-er)*(y[d]-er))/10+er;
					//cout<<"route 2"<<endl;
				}
				else{
					ans[b+1]+=(ans[b]-er+(x[c]-er)*(y[d]-er))/10;
					//cout<<"route 3"<<endl;
				}
				ans[b]=(ans[b]-er+(x[c]-er)*(y[d]-er))%10+er;
			}
			//cout<<x[c]<<"*"<<y[d]<<"="<<ans[b+1]<<ans[b]<<endl;
		}
	}
	ans[b+1]=(ans[b]-er)/10+er;
	ans[b]=(ans[b]-er)%10+er;
	
	return ans;
}

char *b_divide(char *x,char *y){
	char *ans=(char*)calloc(40000,sizeof(char));
	//count the length of both x,y
	int contx,conty,b,c,d;
	for(b=0;x[b]!=NULL;b++){contx=b;}
	for(b=0;y[b]!=NULL;b++){conty=b;}
	//x<y
	//cout<<contx<<","<<conty<<endl;
	if(compare(x,y)==0){
		ans[0]='0';
		return ans;
	}
	//main calculation
	for(b=contx-conty;b>=0;b--){
		//cout<<x;
		//y2=y1*10^(contx-conty)
		char *y2=(char*)malloc(sizeof(char)*20000);
		for(c=0;x[c]!=NULL;c++){contx=c;}
		for(c=0;c<=conty;c++){
			y2[c]=y[c];
		}
		for(c=conty+1;c<b+conty+1;c++){
			y2[c]=er;
		}
		y2[c]=NULL;
		//find divide with minus
		int count=0;
		//cout<<compare(x,y2)<<endl;
		while(compare(x,y2)!=0){
			//cout<<"Fuck!"<<endl;
			x=b_minus_divide(x,y2);
			count++;
		}
		ans[b]=count+er;
		//cout<<"/"<<y2<<"="<<ans[b]<<"("<<b<<")"<<endl;
	}
	
	return ans;
}

char *b_minus_divide(char *x,char *y){
	//cout<<"minus_divide  ";
	char *ans=(char*)calloc(40000,sizeof(char));
	char *ans2=(char*)calloc(40000,sizeof(char));
	//count the length of both x,y
	int contx,conty,b,c,d;
	for(b=0;x[b]!=NULL;b++){contx=b;}
	for(b=0;y[b]!=NULL;b++){conty=b;}
	//main calculation
	for(b=0,c=contx,d=conty;c>=0&&d>=0;b++,d--,c--){
		if(x[c]>=y[d]){
			ans[b]=((x[c]-er)-(y[d]-er))+er;
		}
		else{
			ans[b]=(10+x[c]-y[d])+er;
			int g;
			for(g=c;g>=0&&x[g-1]=='0'&&x[g-2]=='0';g--){x[g-1]=9+er;}
			x[g-1]-=1;
		}
	}
	while(c>=0){
		ans[b]=x[c];
		b++;
		c--;
	}
	int e;
	for(e=b-1;ans[e]=='0'&&e>=0;e--){}
	for(int f=0;e>=0;e--,f++){
		ans2[f]=ans[e];
	}
	//cout<<x<<"-"<<y<<"="<<ans2<<"("<<ans<<")"<<endl;
	free(ans);
	return ans2;
}

int compare(char *x,char *y){
	//cout<<"com:";
	int contx,conty,i;
	for(i=0;x[i]!=NULL;i++){contx=i;}
	for(i=0;y[i]!=NULL;i++){conty=i;}
	//cout<<"("<<x<<","<<y<<")"<<endl;
	if(contx<conty){return 0;}
	else if(contx>conty){return 1;}
	else{
		for(i=0;x[i]==y[i]&&i<=contx;i++){
			
		}
		if(x[i]<y[i]){return 0;}
		return 1;
	}
}

int main(int argc,char **argv){
	fstream fin(argv[1],ios::in);
	int t_num;//number of test
	fin>>t_num;
	//calculation
	for(int a=0;a<t_num;a++){
		char *num1=(char*)malloc(sizeof(char)*20001);//first number
		char *num2=(char*)malloc(sizeof(char)*20001);//second number
		char op;//operator
		fin.get();
		fin.get(num1,20001,' ');
		fin.get();//eats the space
		fin.get(op);
		fin.get();//eats the space
		fin.get(num2,20001,' ');
				
		char *ans;
		switch(op){
			case '+':
				ans=b_plus(num1,num2);
				break;
			case '-':
				ans=b_minus(num1,num2);
				break;
			case '*':
				ans=b_time(num1,num2);
				break;
			case '/':
				ans=b_divide(num1,num2);
				break;
			default:
				cout<<"Error : Not proper operator!"<<endl;
		}
		//cout<<num1<<op<<num2<<"="<<ans<<endl;
		
		//check negative
		for(int b=0;ans[b]!=NULL;b++){
			if(ans[b]=='-'){cout<<"-";}
		}
		//out-put answer
		int front,rear;
		fin>>front>>rear;
		for(int b=rear;b>=front;b--){
			cout<<ans[b]-er;
		}
		cout<<endl;
		free(num1);
		free(num2);
		free(ans);
	}
	
	return 0;
} 
