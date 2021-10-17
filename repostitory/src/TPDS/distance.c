#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define Refine_ratio 2 
#define Refine_power 1
//Refine_ratio=2^Refine_power




int Level;

struct node_b{
	double val;
	double x_r;
	double y_r;
};
struct node_b * fp_glob;
int ** mapping;

struct parent_box{
	int num;
	int p_list[20];
	int offset[20];
};
struct parent_box **box_mapping;
int Part1By1(int x);
int EncodeMorton2(int x, int y)
{
	return (Part1By1(y) << 1) + Part1By1(x);
}


// "Insert" a 0 bit after each of the 16 low bits of x
int Part1By1(int x)
{
	x &= 0x0000ffff;                  // x = ---- ---- ---- ---- fedc ba98 7654 3210
	x = (x ^ (x <<  8)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
	x = (x ^ (x <<  4)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
	x = (x ^ (x <<  2)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
	x = (x ^ (x <<  1)) & 0x55555555; // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
	return x;
}



// Inverse of Part1By1 - "delete" all odd-indexed bits
int Compact1By1(int x)
{
	x &= 0x55555555;                  // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
	x = (x ^ (x >>  1)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
	x = (x ^ (x >>  2)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
	x = (x ^ (x >>  4)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
	x = (x ^ (x >>  8)) & 0x0000ffff; // x = ---- ---- ---- ---- fedc ba98 7654 3210
	return x;
}




int DecodeMorton2X(int code)
{
	return Compact1By1(code >> 0);
}

int DecodeMorton2Y(int code)
{
	return Compact1By1(code >> 1);
}

void rot(int n, int *x, int *y, int rx, int ry) {
	if (ry == 0) {
		if (rx == 1) {
			*x = n-1 - *x;
			*y = n-1 - *y;
		}

		//Swap x and y
		int t  = *x;
		*x = *y;
		*y = t;
	}
}
int xy2d (int n, int x, int y) {
	int rx, ry, s, d=0;
	for (s=n/2; s>0; s/=2) {
		rx = (x & s) > 0;
		ry = (y & s) > 0;
		d += s * s * ((3 * rx) ^ ry);
		rot(n, &x, &y, rx, ry);
	}
	return d;
}


struct datapoint{
	int a,b;
	double val;
};

struct box{
	int x1,y1;
	int x2,y2;
};

struct node{
	int x,y;
	double val;
	int flag;
	struct node *fchild;
	struct node *next;
	int index;
	double x_r;
	double y_r;
};



void PrintTree(struct node* p,  int flag)
{
	if (p==NULL) 
		return;
	if(flag==1){
		fp_glob[0].val= p->val;
		fp_glob[0].x_r= p->x_r;
		fp_glob[0].y_r= p->y_r;
	}
	fp_glob++;
	p->flag=1;
	//  printf("%d\n",p->flag);
	if (p->fchild!=NULL) 
	{ PrintTree(p->fchild,flag); }
	if (p->next!=NULL)
	{ PrintTree(p->next,flag); } 


}


int find_father(struct datapoint *data, int size,int a, int b)
{

	int i;
	for(i=0;i<size;i++)
		if(data[i].a==a&&data[i].b==b)
			return i;
	printf("do not find (%d,%d)\n",a,b);
	return -1;
}
int compare_box(struct box  b1, struct box  b2)
{
	if(b1.x1/Refine_ratio<b2.x1)
		return 0;

	if(b1.y1/Refine_ratio<b2.y1)
		return 0;

	if(b1.x2/Refine_ratio>b2.x2)
		return 0;

	if(b1.y2/Refine_ratio>b2.y2)
		return 0;

	return 1;

}

int child_cover_parent(struct box  b1, struct box  b2){
	if(b1.x1/Refine_ratio>b2.x1)
		return 0;

	if(b1.y1/Refine_ratio>b2.y1)
		return 0;

	if(b1.x2/Refine_ratio<b2.x2)
		return 0;

	if(b1.y2/Refine_ratio<b2.y2)
		return 0;

	return 1;

}

int find_leftup_box(struct box  b1, struct box  b2){
	if(b1.x1/Refine_ratio<b2.x1)
		return 0;

	if(b1.y1/Refine_ratio<b2.y1)
		return 0;

	if(b1.x2/Refine_ratio<b2.x2&&b1.y2/Refine_ratio<b2.y2)
		return 0;

	if(b1.x1/Refine_ratio>b2.x2)
		return 0;
	if(b1.y1/Refine_ratio>b2.y2)
		return 0;

	return 1;

}


int init_mapping(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	int i,j;
	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{


			int a=(int)data[i][j].a/Refine_ratio;

			int b=(int)data[i][j].b/Refine_ratio;
			mapping[i][j]=find_father(data[i-1],cnt[i-1],a,b);
		}

	return 1;
}

int isoverlap_box(struct box  b1, struct box  b2)
{
	if(b1.x2/Refine_ratio<b2.x1||b1.y2/Refine_ratio<b2.y1)
		return 0;
	if(b1.x1/Refine_ratio>b2.x2||b1.y1/Refine_ratio>b2.y2)
		return 0;

	return 1;


}

struct box* find_overlap(struct box  b1, struct box  b2)
{
	struct box *overlap=malloc(sizeof(struct box));

	if(b1.x1/Refine_ratio>=b2.x1)
		overlap->x1=b1.x1;
	else
		overlap->x1=b2.x1*Refine_ratio;

	if(b1.x2/Refine_ratio<=b2.x2)
		overlap->x2=b1.x2;
	else
		overlap->x2=b2.x2*Refine_ratio+1;

	if(b1.y1/Refine_ratio>=b2.y1)
		overlap->y1=b1.y1;
	else
		overlap->y1=b2.y1*Refine_ratio;

	if(b1.y2/Refine_ratio<=b2.y2)
		overlap->y2=b1.y2;
	else
		overlap->y2=b2.y2*Refine_ratio+1;


	return overlap;
}


void init_box_mapping(struct box **boxes,int box_cnt[Level])
{
	int i,j,k,l;
	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<box_cnt[i];j++)
		{
			int offset=0;
			/*Child box is overlaped with only one parent box*/ 
			for( k=0;k<box_cnt[i-1];k++)
				if(compare_box(boxes[i][j],boxes[i-1][k]))
				{
					box_mapping[i][j].num=1;
					box_mapping[i][j].p_list[0]=k;
					box_mapping[i][j].offset[0]=offset;

					break;

				}
				else

					offset=offset+(boxes[i-1][k].x2-boxes[i-1][k].x1+1)*(boxes[i-1][k].y2-boxes[i-1][k].y1+1);


			/*Child box is overlaped with more than one parent box*/ 
			if(k>=box_cnt[i-1])
			{
				offset=0;
				box_mapping[i][j].num=0;
				for( l=0;l<box_cnt[i-1];l++){

					if(isoverlap_box(boxes[i][j],boxes[i-1][l]))
					{
						box_mapping[i][j].p_list[ box_mapping[i][j].num]=l;

						box_mapping[i][j].offset[ box_mapping[i][j].num]=offset;
						//printf("%d,%d:%d\n",i,j,l);
						box_mapping[i][j].num++;
					}

					offset=offset+(boxes[i-1][l].x2-boxes[i-1][l].x1+1)*(boxes[i-1][l].y2-boxes[i-1][l].y1+1);



				}

			}



		}//j
	}//i


}


void mapping_by_box(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	int i,j,k;
	int offset;
	int off1;

	init_box_mapping(boxes,box_cnt);

	for(i=Level-1;i>0;i--)
	{
		off1=0;
		for(j=0;j<box_cnt[i];j++)
		{

			int width=boxes[i][j].x2-boxes[i][j].x1+1;
			int height=boxes[i][j].y2-boxes[i][j].y1+1;
			int box_size=width*height; 


			if(box_mapping[i][j].num==1) 
			{

				offset=box_mapping[i][j].offset[0];
				int p_index=box_mapping[i][j].p_list[0];
				int width_f=boxes[i-1][p_index].x2-boxes[i-1][p_index].x1+1;

				for (int i1=0;i1<height;i1++)
				{


					int off_y=(boxes[i][j].y1+i1)/Refine_ratio-boxes[i-1][p_index].y1;	

					for (int j1=0;j1<width;j1++)
					{

						int off_x=(boxes[i][j].x1+j1)/Refine_ratio-boxes[i-1][p_index].x1;

						mapping[i][off1+i1*width+j1]=offset+off_x+off_y*width_f;


					}
				}
			}

			else
			{ 

				int p_num=box_mapping[i][j].num;
				for(k =0;k<p_num;k++)
				{
					int  p_index=box_mapping[i][j].p_list[k];
					struct box *overlap=find_overlap(boxes[i][j],boxes[i-1][p_index]); 
					offset=box_mapping[i][j].offset[k];
					// if(!compare_box(*overlap,boxes[i-1][p_index]))
					// printf("Bad news!!!\n");
					int width_f=boxes[i-1][p_index].x2-boxes[i-1][p_index].x1+1;
					for (int i1=overlap->y1;i1<=overlap->y2;i1++)
					{


						int off_y=i1/Refine_ratio-boxes[i-1][p_index].y1;
						for (int j1=overlap->x1;j1<=overlap->x2;j1++)
						{

							int off_x=j1/Refine_ratio-boxes[i-1][p_index].x1;

							mapping[i][off1+(i1-boxes[i][j].y1)*width+j1-boxes[i][j].x1]=offset+off_x+off_y*width_f;


						}
					}


					free(overlap);
				}







			}//Child box are overlaped with more than one parent box.



			off1=off1+box_size;

		}//j for




	}


	/*for(i=Level-1;i>0;i--)
	  for(j=0;j<cnt[i];j++)
	  {
	  if(data[i][j].a/Refine_ratio!=data[i-1][mapping[i][j]].a||data[i][j].b/Refine_ratio!=data[i-1][mapping[i][j]].b) 
	  printf("Error! %d,%d: %d, %d\n",data[i][j].a,data[i-1][mapping[i][j]].a,data[i][j].b,data[i-1][mapping[i][j]].b);
	  }*/

}



void leveldata_box_hilbert(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	char filename[50];
	sprintf(filename,"Level_box_zordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");

	clock_t start_t, end_t; double total_t;
	start_t = clock();
	clock_t start_t1=start_t;
	int i,j,k;

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int offset=0;

	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int side=boxes[i][j].x2-boxes[i][j].x1;
			int n=1;
			while(n<side+1){n=n<<1;}
			int z_size= n*n;
			int *z_index=malloc(z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(side+1)*(side+1);

			for(int m=0;m<=side;m++)
				for(int l=0;l<=side;l++)
				{
					z_index[ xy2d(n,l,m)]=l+m*(side+1);
				}
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}

			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			if(i==Level-1)
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
					trees[i][offset+k].x_r=trees[i][offset+k].x;
					trees[i][offset+k].y_r=trees[i][offset+k].y;

				}
			else
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
					//trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Level-1-i))+(1<<(Level-2-i))-0.5;
					//trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Level-1-i))+(1<<(Level-2-i))-0.5;
trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
                                        trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;

				}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}

	int offset1=0;
	double distance=0;
	for(i=0;i<Level;i++){
		if(i>0)
			distance+=sqrt((trees[i][0].x_r-trees[i-1][cnt[i-1]-1].x_r)*(trees[i][0].x_r-trees[i-1][cnt[i-1]-1].x_r)+(trees[i][0].y_r-trees[i-1][cnt[i-1]-1].y_r)*(trees[i][0].y_r-trees[i-1][cnt[i-1]-1].y_r));

		for(j=1;j<cnt[i];j++)
		{
			distance+=sqrt((trees[i][j].x_r-trees[i][j-1].x_r)*(trees[i][j].x_r-trees[i][j-1].x_r)+(trees[i][j].y_r-trees[i][j-1].y_r)*(trees[i][j].y_r-trees[i][j-1].y_r));	
		}
	}
	printf("%lf\n",distance/(1<<(Level-1)));


	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);


	fclose(fp);
}



void leveldata_box_hilbert_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	char filename[50];
	sprintf(filename,"Level_box_zordering_levelreordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");

	clock_t start_t, end_t; double total_t;
	clock_t start_t1;
	start_t = clock();
	start_t1=start_t;
	int i,j,k;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	struct node_b *dataArray=malloc(datasize*sizeof(struct node_b));

	mapping_by_box(data,cnt,boxes,box_cnt);
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}


	int* recipe_de;

	for(i=0;i<Level;i++)
	{ 
		offset=0;

		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
		for(j=0;j<box_cnt[i];j++)
		{
			int side=boxes[i][j].x2-boxes[i][j].x1;
			int n=1;
			while(n<side+1){n=n<<1;}
			int z_size= n*n;
			int *z_index=malloc(z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(side+1)*(side+1);

			for(int m=0;m<=side;m++)
				for(int l=0;l<=side;l++)
				{
					z_index[ xy2d(n,l,m)]=l+m*(side+1);
				}
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}

			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			if(i==Level-1)
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
					trees[i][offset+k].x_r=trees[i][offset+k].x;
					trees[i][offset+k].y_r=trees[i][offset+k].y;
					trees[i][offset+k].index=offset+recipe_en[k];
					trees[i][offset+k].flag=0;
					trees[i][offset+k].fchild=NULL;
					trees[i][offset+k].next=NULL;

				}
			else
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
//					trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Level-1-i))+(1<<(Level-2-i))-0.5;
//					trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Level-1-i))+(1<<(Level-2-i))-0.5;
trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
                                        trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
					trees[i][offset+k].index=offset+recipe_en[k];
					trees[i][offset+k].flag=0;
					trees[i][offset+k].fchild=NULL;
					trees[i][offset+k].next=NULL;
				}
			if(i<Level-1){

				for(int j1=0;j1<box_size;j1++){
					recipe_de[recipe_en[j1]+offset]=j1+offset;
				}
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

		if(i<Level-1)
		{
			for(j=0;j<cnt[i+1];j++){
				mapping[i+1][j]=recipe_de[mapping[i+1][j]];
			}

			free(recipe_de);

		}
	}


	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].x/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].x||trees[i][j].y/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].y)
				printf("error! %d,%d: %d, %d\n",trees[i][j].x,trees[i-1][mapping[i][trees[i][j].index]].x,trees[i][j].y,trees[i-1][mapping[i][trees[i][j].index]].y);
		}


	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][trees[i][j].index];
			struct	node *p=trees[i-1][father_index].fchild;
			if (p==NULL)
				trees[i-1][father_index].fchild=&trees[i][j];
			else
			{
				while(p->next!=NULL)
					p=p->next;
				p->next=&trees[i][j];
			}




		}


	}

	//	double *vp=dataArray;
	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,1);

		}
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}

	double distance=0;
	for(i=1;i<datasize;i++)
		distance+=sqrt((dataArray[i].x_r-dataArray[i-1].x_r)*(dataArray[i].x_r-dataArray[i-1].x_r)+(dataArray[i].y_r-dataArray[i-1].y_r)*(dataArray[i].y_r-dataArray[i-1].y_r));	
	printf("%lf\n",distance/(1<<(Level-1)));
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);


	free(dataArray);



	fclose(fp);

}













void leveldata_box_zordering(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	char filename[50];
	sprintf(filename,"Level_box_zordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");

	clock_t start_t, end_t; double total_t;
	start_t = clock();
	clock_t start_t1=start_t;
	int i,j,k;

	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int offset=0;

	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int side=boxes[i][j].x2-boxes[i][j].x1;
			int z_size= EncodeMorton2(side,side)+1;
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(side+1)*(side+1);

			for(int m=0;m<=side;m++)
				for(int l=0;l<=side;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(side+1);
				}
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			if(i==Level-1)
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
					trees[i][offset+k].x_r=trees[i][offset+k].x;
					trees[i][offset+k].y_r=trees[i][offset+k].y;

				}
			else
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
//					trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Level-1-i))+(1<<(Level-2-i))-0.5;
//					trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Level-1-i))+(1<<(Level-2-i))-0.5;
trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
                                        trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
				}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}

	int offset1=0;
	double distance=0;
	for(i=0;i<Level;i++){
		if(i>0)
			distance+=sqrt((trees[i][0].x_r-trees[i-1][cnt[i-1]-1].x_r)*(trees[i][0].x_r-trees[i-1][cnt[i-1]-1].x_r)+(trees[i][0].y_r-trees[i-1][cnt[i-1]-1].y_r)*(trees[i][0].y_r-trees[i-1][cnt[i-1]-1].y_r));

		for(j=1;j<cnt[i];j++)
		{
			distance+=sqrt((trees[i][j].x_r-trees[i][j-1].x_r)*(trees[i][j].x_r-trees[i][j-1].x_r)+(trees[i][j].y_r-trees[i][j-1].y_r)*(trees[i][j].y_r-trees[i][j-1].y_r));	
		}
	}
	printf("%lf\n",distance/(1<<(Level-1)));


	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);


	fclose(fp);
}



void leveldata_box_zordering_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level],int col)
{
	char filename[50];
	sprintf(filename,"Level_box_zordering_levelreordering_%d.dat",col);
	FILE *fp=fopen(filename,"w");

	clock_t start_t, end_t; double total_t;
	clock_t start_t1;
	start_t = clock();
	start_t1=start_t;
	int i,j,k;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	struct node_b *dataArray=malloc(datasize*sizeof(struct node_b));

	mapping_by_box(data,cnt,boxes,box_cnt);
	int offset=0;

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{

			trees[i][j].flag=0;

		}


	int* recipe_de;

	for(i=0;i<Level;i++)
	{ 
		offset=0;

		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
		for(j=0;j<box_cnt[i];j++)
		{
			int side=boxes[i][j].x2-boxes[i][j].x1;
			int z_size= EncodeMorton2(side,side)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(side+1)*(side+1);

			for(int m=0;m<=side;m++)
				for(int l=0;l<=side;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(side+1);
				}
			int *recipe_en=malloc(box_size*sizeof(int));
			int tr=0;
			for(k=0;k<z_size;k++){
				if(z_index[k]!=-1)
					recipe_en[tr++]=z_index[k];
			}
			if(tr!=box_size){
				printf("tr!=box_size, %d, %d\n",tr,box_size);
				for (k=0;k<box_size;k++)
					printf("%d ",recipe_en[k]);
			}
			if(i==Level-1)
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
					trees[i][offset+k].x_r=trees[i][offset+k].x;
					trees[i][offset+k].y_r=trees[i][offset+k].y;
					trees[i][offset+k].index=offset+recipe_en[k];
					trees[i][offset+k].flag=0;
					trees[i][offset+k].fchild=NULL;
					trees[i][offset+k].next=NULL;

				}
			else
				for(k=0;k<box_size;k++)
				{
					trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
					trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
					trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
//					trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Level-1-i))+(1<<(Level-2-i))-0.5;
//					trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Level-1-i))+(1<<(Level-2-i))-0.5;
trees[i][offset+k].x_r=(trees[i][offset+k].x<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
                                        trees[i][offset+k].y_r=(trees[i][offset+k].y<<(Refine_power*(Level-1-i)))+(1<<(Refine_power*(Level-1-i)))/2-0.5;
					trees[i][offset+k].index=offset+recipe_en[k];
					trees[i][offset+k].flag=0;
					trees[i][offset+k].fchild=NULL;
					trees[i][offset+k].next=NULL;
				}
			if(i<Level-1){

				for(int j1=0;j1<box_size;j1++){
					recipe_de[recipe_en[j1]+offset]=j1+offset;
				}
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

		if(i<Level-1)
		{
			for(j=0;j<cnt[i+1];j++){
				mapping[i+1][j]=recipe_de[mapping[i+1][j]];
			}

			free(recipe_de);

		}
	}


	for(i=Level-1;i>0;i--)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].x/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].x||trees[i][j].y/Refine_ratio!=trees[i-1][mapping[i][trees[i][j].index]].y)
				printf("error! %d,%d: %d, %d\n",trees[i][j].x,trees[i-1][mapping[i][trees[i][j].index]].x,trees[i][j].y,trees[i-1][mapping[i][trees[i][j].index]].y);
		}


	start_t=clock();


	for(i=Level-1;i>0;i--)
	{
		for(j=0;j<cnt[i];j++)
		{       
			int father_index=mapping[i][trees[i][j].index];
			struct	node *p=trees[i-1][father_index].fchild;
			if (p==NULL)
				trees[i-1][father_index].fchild=&trees[i][j];
			else
			{
				while(p->next!=NULL)
					p=p->next;
				p->next=&trees[i][j];
			}




		}


	}

	//	double *vp=dataArray;
	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p,1);

		}
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}

	double distance=0;
	for(i=1;i<datasize;i++)
		distance+=sqrt((dataArray[i].x_r-dataArray[i-1].x_r)*(dataArray[i].x_r-dataArray[i-1].x_r)+(dataArray[i].y_r-dataArray[i-1].y_r)*(dataArray[i].y_r-dataArray[i-1].y_r));	
	printf("%lf\n",distance/(1<<(Level-1)));
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);


	free(dataArray);



	fclose(fp);

}




int main()
{
	for(Level=1;Level<13;Level++){
		//printf("Level:%d\n",Level);
		int i,j,cnt[Level],box_cnt[Level],read_cnt;
		struct datapoint** data;
		data=malloc(Level*sizeof(* data));
		struct box** boxes;
		boxes=malloc(Level*sizeof(* boxes));
		mapping=malloc(Level*sizeof(* mapping));
		box_mapping=malloc(Level*sizeof(* box_mapping));
		int col=0;
		for(i=0;i<Level;i++)
		{
			box_cnt[i]=1;
			//printf("box_cnt= %d\n", box_cnt[i]);
			boxes[i]=malloc(sizeof(struct box));
			int width=Refine_ratio<<i;;
			//printf("width: %d\n",width);
			boxes[i][0].x1=0;
			boxes[i][0].y1=0;
			boxes[i][0].x2=width-1;
			boxes[i][0].y2=width-1;
			cnt[i]=width*width;
			data[i]=malloc(cnt[i]*sizeof(struct datapoint));
			for(j=0;j<cnt[i];j++)
			{

				data[i][j].a=j%width;
				data[i][j].b=j/width;
				data[i][j].val=j;

			}
			//      printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
		}

		for(i=0;i<Level;i++)
			mapping[i]=malloc(cnt[i]*sizeof(int));

		for(i=0;i<Level;i++)
			box_mapping[i]=malloc(box_cnt[i]*sizeof(struct parent_box));

		leveldata_box_zordering(data,cnt,boxes,box_cnt,col);
		leveldata_box_zordering_level(data,cnt,boxes,box_cnt,col);
		leveldata_box_hilbert(data,cnt,boxes,box_cnt,col);
		leveldata_box_hilbert_level(data,cnt,boxes,box_cnt,col);
		for(i=0;i<Level;i++)	
			free(data[i]);
		for(i=0;i<Level;i++)
			free(boxes[i]);
		for(i=0;i<Level;i++)
			free(mapping[i]);
		for(i=0;i<Level;i++)
			free(box_mapping[i]);
		free(boxes);
		free(data);
		free(mapping);
		free(box_mapping);
	}
	return 1;
}
