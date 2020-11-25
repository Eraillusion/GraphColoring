#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#define random(number) rand()%number+1
#define Max 10001

int Twotier(int N)
{
    int i;
    int randomseed=90;
    if(random(randomseed)<=40){
        return random(N/10);
    }
    else return random(N);
}

int Skewed(int N)
{
    int i;
    int count=0;
    int *a;
    int *flag;
    int p=0;
    a = (int*)malloc((N*N+N)*sizeof(int));
    flag = (int*)malloc(N*sizeof(int));
    flag[0]=2*N-1;
    for(i=1;i<N;i++)
        flag[i]=0;
    for(i=1;i<N;i++){
        flag[i]=flag[i-1]+2*N-2*i;
        //printf("%d,",flag[i]);
    }
    for(i=0;i<N*N+N;i++){
        a[i]=count;
        if(i>=flag[p])
        {
            count++;
            p++;
        }
    }
    return a[random(N*N+N)]+1;
}

int Mydistribution(int N)
{
    int i;
    int randomseed=100;
    if(random(randomseed)<=80){
        return random(N/2);
    }
    else return random(N);
}

/*int main()
{
        FILE *fpWrite=NULL;
    int i,j,temp;
    int a[101]={0};
    fpWrite=fopen("I:\\data.txt","w");
    for(i=0;i<10000;i++){
        temp = Mydistribution(100);
        for(j=1;j<=100;j++)
            if(temp ==j)
                a[j]++;
        //printf("%d,", temp);
    }
    for(j=1;j<=100;j++)
       fprintf(fpWrite,"%d\n",a[j]);
    fclose(fpWrite);

}
*/

int main()
{
    struct timeval start;
    struct timeval end;
    unsigned long timer;

    srand(time(0));
    int sessioncount=0;
    int sessioncountk=0;
    int repeatflag = 0;
    int temp;
    int i=0,j=0,m=0;
    int countm=0;
    int N;
    int S;
    int K;
    int ** Sarray;
    int ** Earray;
    int Karray[100000] = {0};/*100,000*/
    char DIST[10];
    int M;
    int T;
    int E[100000]={0};
    int P[100000]={0};
    int pflag=0;
    int phavevalue=0;
    printf("Type N Number of session (MAX = 10,000) :");
    scanf("%d",&N);
    Sarray =(int**)malloc(Max*sizeof(int*));
    for(i=0;i<Max;i++){
        Sarray[i]=(int*)malloc(Max*sizeof(int));
    }
    for(i=0;i<Max;i++){
        for(j=0;j<Max;j++){
            Sarray[i][j]=0;
        }
    }
    i=0,j=0;
    Earray =(int**)malloc(Max*sizeof(int*));
    for(i=0;i<Max;i++){
        Earray[i]=(int*)malloc(Max*sizeof(int));
    }
    for(i=0;i<Max;i++){
        for(j=0;j<Max;j++){
            Earray[i][j]=0;
        }
    }
    i=0,j=0;
    printf("Type S Number of attendees (MAX = 100,000) :");
    scanf("%d",&S);
    printf("Type K Number of session per attendee(MAX = N for uniform and two-tiered distributions,\
MAX = 0.1N for skewed and self-defined distributions;) :");
    scanf("%d",&K);
    if(K>N){
        printf("K is too large.");
        return 0;
    }
    printf("Type DIST :");
    scanf("%s",&DIST);

    gettimeofday(&start, NULL);

    while(sessioncount < S){
    while(i < K){
        if(strcmp(DIST,"UNIFORM")==0||strcmp(DIST,"1")==0)
            temp = random(N);//produce different distribution base on DIST.
        else if(strcmp(DIST,"TIERED")==0||strcmp(DIST,"2")==0)
            temp = Twotier(N);
        else if(strcmp(DIST,"SKEWED")==0||strcmp(DIST,"3")==0)
            temp = Skewed(N);
        else if(strcmp(DIST,"YOURS")==0||strcmp(DIST,"4")==0)
            temp = Mydistribution(N);
        else{
            printf("Distribution is invalid!");
            return 0;
        }
        for(j=0;j<i;j++){
            if(Karray[j] == temp){
                repeatflag = 1;
            }
        }
        if(repeatflag == 0){
            Karray[i++] = temp;
        }
        else
        {
            repeatflag = 0;
            continue;
        }
    }
    i=0;
    for(sessioncountk=0;sessioncountk<K;sessioncountk++)
        Sarray[sessioncount][sessioncountk] = Karray[sessioncountk];
    sessioncount++;
    }


/*Output"*/
    printf("\n--------------Belows are Outputs--------------\n");
    printf("N = %d\n",N);
    printf("T = %d\n",S * K * (K-1) / 2);
    printf("S = %d\n",S);
    printf("K = %d\n",K);
    printf("DIST = %s",DIST);

    for(j=0;j<S;j++)
        for(i=0;i<K-1;i++){
            for(m=i+1;m<K;m++){
                Earray[Sarray[j][i]][Sarray[j][m]]=1;
                Earray[Sarray[j][m]][Sarray[j][i]]=1;
            }
        }
    printf("\n");
    for(j=1;j<=N;j++)
        for(i=1;i<=N;i++){
            printf("%d ",Earray[j][i]);
            if(Earray[j][i]==1){
                E[countm]=i;
                countm++;
                phavevalue=1;
            }
            if(i==N){
                printf("\n");
                if(phavevalue==1){
                    P[++pflag]=countm;
                    phavevalue=0;
                }
            }
        }
    printf("M = %d\n",countm/2);
    for(i=0;i<countm;i++){
        if(i!= countm-1)
            printf("E[%d] = %d ,",i,E[i]);
        if(i== countm-1)
            printf("E[%d] = %d\n",i,E[i]);
    }
    for(i=0;i<pflag;i++){
        if(i!= pflag-1)
            printf("P[%d] = %d ,",i,P[i]);
        if(i== pflag-1)
            printf("P[%d] = %d\n",i,P[i]);
    }

    gettimeofday(&end, NULL);

    timer = 1000000 * (end.tv_sec - start.tv_sec) + end.tv_usec - start.tv_usec;

    printf("timer = %ld us\n", timer);

    free(Sarray);
    free(Earray);

    return 0;
}
