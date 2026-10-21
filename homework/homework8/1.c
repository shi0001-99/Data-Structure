#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    char s[100];
    char t[100];
    char r[200];
    scanf("%s",s);
    scanf("%s",t);
    scanf("%s",r);
    int dp[101][101]={0};//s的前i个，t的前j个，能不能拼成r的前i+j个
    int slen=strlen(s);
    int tlen=strlen(t);
    int rlen=strlen(r);
    if(slen+tlen!=rlen){
        printf("False");
        return 0;
    }
    for(int i=0;i<slen;i++){
        if(s[i]==r[i]){
            dp[i+1][0]=1;
        }
        else{
            break;
        }
    }
    for(int i=0;i<tlen;i++){
        if(t[i]==r[i]){
            dp[0][i+1]=1;
        }
        else{
            break;
        }
    }
    for(int i=1;i<=slen;i++){
        for(int j=1;j<=tlen;j++){
            dp[i][j]=((dp[i][j-1]&&t[j-1]==r[i+j-1])||(dp[i-1][j]&&s[i-1]==r[i+j-1]));
        }
    }
    if(dp[slen][tlen]){
        printf("True");
    }
    else{
        printf("False");
    }
    return 0;
}