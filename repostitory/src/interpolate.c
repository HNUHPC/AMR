#include <stdio.h>
#include <stdlib.h>
#define Level 5 



struct datapoint{
	int a,b;
	double val;
};

struct box{
	int x1,y1;
	int x2,y2;
};
double find(struct datapoint *data,int size,int a, int b)
{
	int i;
	for(i=0;i<size;i++)
		if(data[i].a==a&&data[i].b==b)
			return data[i].val;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}
void stat1(struct datapoint **data, int cnt [Level],int li, int hi)
{
	int com_cnt=0;
	int i,j; double delta;
	printf("count= %d %d\n", cnt[li],cnt[hi]);
	char filename[50];
	sprintf(filename,"delta_%d_%d",li,hi);
	FILE *fp=fopen(filename,"w");
	for(j=0;j<cnt[hi];j++)
		for(i=0;i<cnt[li];i++)
		{
			if(data[li][i].a==data[hi][j].a/2&&data[li][i].b==data[hi][j].b/2)
			{
				//	printf("%d %d %lf, %d %d %lf\n", data[li][i].a,data[li][i].b,data[li][i].val,data[hi][j].a,data[hi][j].b,data[hi][j].val);
				int x,y;
				x=data[hi][j].a%2;
				y=data[hi][j].b%2;
				double t1=data[li][i].val;
				double t2=data[li][i].val;
				if(x!=0)
					t2=find(data[li],cnt[li],data[li][i].a+1,data[li][i].b);
				double t3=data[li][i].val;
				if(x!=0&&y!=0)
					t3=find(data[li],cnt[li],data[li][i].a+1,data[li][i].b+1);

				double t4=data[li][i].val;
				if(y!=0)
					t4=find(data[li],cnt[li],data[li][i].a,data[li][i].b+1);
				double temp1=t1+(t4-t1)*y/2;
				double temp2=t2+(t3-t2)*y/2;
				double temp3=temp1+(temp2-temp1)*x/2;

				delta=data[hi][j].val-temp3;
				{
					fwrite(&delta,sizeof(double),1,fp);
					com_cnt++;
				}
				break;
			}
		}

	printf("com_cnt= %d\n", com_cnt);
	fclose(fp);
}

void stat(struct datapoint **data, int cnt [Level],int li, int hi)
{
	int com_cnt=0;
	int i,j; double delta;
	printf("count= %d %d\n", cnt[li],cnt[hi]);
	char filename[50];
	sprintf(filename,"delta_%d_%d",li,hi);
	FILE *fp=fopen(filename,"w");
	for(j=0;j<cnt[hi];j++)
		for(i=0;i<cnt[li];i++)
		{
			if(data[li][i].a==data[hi][j].a/2&&data[li][i].b==data[hi][j].b/2)
			{
				//printf("%d %d %lf, %d %d %lf\n", data[li][i].a,data[li][i].b,data[li][i].val,data[hi][j].a,data[hi][j].b,data[hi][j].val);
				delta=data[hi][j].val-data[li][i].val;
				{
					fwrite(&delta,sizeof(double),1,fp);

					com_cnt++;
				}
				break;
			}
		}

	printf("com_cnt= %d\n", com_cnt);
	fclose(fp);
}
void leveldata(struct datapoint **data, int cnt [Level])
{
	int i,j; 
	for(i=0;i<Level;i++)
	{
		char filename[50];
		sprintf(filename,"Level_%d.dat",i);
		FILE *fp=fopen(filename,"w");
		for(j=0;j<cnt[i];j++)
		{
			fwrite(&data[i][j].val,sizeof(double),1,fp);
		}

		fclose(fp);
	}
}
int main()
{
	int i,j,cnt[Level],box_cnt[Level],read_cnt;
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));



	FILE *fp=fopen("datapoint_0","r");

	for(i=0;i<Level;i++)
	{
	read_cnt=fread(&cnt[i],sizeof(int),1,fp);
		printf("data count= %d\n", cnt[i]);
		 read_cnt=fread(&box_cnt[i],sizeof(int),1,fp);
		printf("box_cnt= %d\n", box_cnt[i]);
		boxes[i]=malloc(box_cnt[i]*sizeof(struct box));
		 read_cnt=fread(boxes[i],sizeof(struct box),box_cnt[i],fp);
		data[i]=malloc(cnt[i]*sizeof(struct datapoint));
		 read_cnt=fread(data[i],sizeof(struct datapoint),cnt[i],fp);
		//for(j=0;j<cnt[i];j++)
		//	printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
	}
	fclose(fp);

	for(i=0;i<Level-1;i++)
		stat(data,cnt,i,i+1);
	leveldata(data,cnt);

	for(i=0;i<Level;i++)	
		free(data[i]);
	for(i=0;i<Level;i++)
		free(boxes[i]);
	free(boxes);
	free(data);


}
