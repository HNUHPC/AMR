#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define Level 6

#define Refine_ratio 2

#include <gsl/gsl_sort_int.h>


struct node_storage* fp_glob;
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
	int lvl;
	struct node *fchild;
	struct node *next;
	int index;
};


struct node_storage{
	int x,y;
	int lvl;
	double val;
	int flag;
	int flag_block;
};
void PrintTree(struct node* p)
{
	if (p==NULL) 
		return;
	fp_glob->val=p->val;
	fp_glob->x=p->x;
	fp_glob->y=p->y;
	fp_glob->lvl=p->lvl;
	fp_glob->flag=0;
	fp_glob->flag_block=0;       
	//fp=fp+sizeof(struct node_storage);
	fp_glob++;
	//   printf("fp:%ld\n",fp_glob);
	p->flag=1;
	//	p->flag=1; 
	//  printf("%d\n",p->flag);
	if (p->fchild!=NULL) 
	{ PrintTree(p->fchild);}
	if (p->next!=NULL)
	{ PrintTree(p->next); } 


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


}

struct node_storage * leveldata_box_hilbert(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
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
	struct node_storage*dataArray=malloc(datasize*sizeof(struct node_storage));
	int offset=0;

	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
			int n=1;
			while(n<=a||n<=b){n=n<<1;}
			int z_size= n*n;
			int *z_index=malloc(z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[ xy2d(n,l,m)]=l+m*(a+1);
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
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
				trees[i][offset+k].lvl=i;
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}
	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			dataArray[offset1].val=trees[i][j].val;
			dataArray[offset1].x=trees[i][j].x;
			dataArray[offset1].y=trees[i][j].y;
			dataArray[offset1].lvl=i;
			trees[i][j].flag=1;
			offset1++;
		}

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                 
				printf("Not visit %d,%d\n",i,j);

		}


	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	//	free(dataArray);
	return dataArray;
}



struct node_storage* leveldata_box_level_hilbert(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	mapping_by_box(data,cnt,boxes,box_cnt);
	clock_t start_t, end_t; double total_t;
	double total_t1=0;
	clock_t start_t1;
	start_t = clock();
	start_t1=start_t;
	int i,j,k;
	FILE *fp;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	struct node_storage*dataArray=malloc(datasize*sizeof(struct node_storage));

	int offset=0;

	int *recipe_de;
	for(i=0;i<Level;i++)
	{ 
		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
			int n=1;
			while(n<=a||n<=b){n=n<<1;}
			int z_size= n*n;
			int *z_index=malloc(z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[ xy2d(n,l,m)]=l+m*(a+1);
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
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].index=offset+recipe_en[k];
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
				trees[i][offset+k].lvl=i;
			}

			if(i<Level-1){
				size_t *size_t_index_tmp_buffer = (size_t *) malloc (box_size * sizeof (size_t));
				gsl_sort_int_index (size_t_index_tmp_buffer,  recipe_en, 1,box_size );

				for(int j1=0;j1<box_size;j1++){
					recipe_de[j1+offset]=size_t_index_tmp_buffer[j1]+offset;
				}
				free(size_t_index_tmp_buffer);
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


	start_t=clock();

	start_t1=start_t;

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
	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p);

		}

	//printf("vp:%ld,%ld\n",dataArray,fp_glob-dataArray);
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	//free(dataArray);
	return dataArray;

}
struct node_storage * leveldata_box(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
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
	struct node_storage*dataArray=malloc(datasize*sizeof(struct node_storage));
	int offset=0;

	for(i=0;i<Level;i++)
	{ 
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
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
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
				trees[i][offset+k].lvl=i;
			}

			offset+=box_size;
			free(z_index);
			free(recipe_en);
		}

	}
	int offset1=0;
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			dataArray[offset1].val=trees[i][j].val;
			dataArray[offset1].x=trees[i][j].x;
			dataArray[offset1].y=trees[i][j].y;
			dataArray[offset1].lvl=i;
			trees[i][j].flag=1;
			offset1++;
		}

	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                 
				printf("Not visit %d,%d\n",i,j);

		}


	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);
	//	free(dataArray);
	return dataArray;
}



struct node_storage* leveldata_box_level(struct datapoint **data, int cnt [Level],struct box **boxes,int box_cnt[Level])
{
	mapping_by_box(data,cnt,boxes,box_cnt);
	clock_t start_t, end_t; double total_t;
	double total_t1=0;
	clock_t start_t1;
	start_t = clock();
	start_t1=start_t;
	int i,j,k;
	FILE *fp;
	struct node** trees;
	trees=malloc(Level*sizeof(* trees));
	for(i=0;i<Level;i++)
		trees[i]=malloc(cnt[i]*sizeof(struct node));
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	struct node_storage*dataArray=malloc(datasize*sizeof(struct node_storage));

	int offset=0;

	int *recipe_de;
	for(i=0;i<Level;i++)
	{ 
		if(i<Level-1)
			recipe_de=malloc(cnt[i]*sizeof(int));
		offset=0;
		for(j=0;j<box_cnt[i];j++)
		{
			int a=boxes[i][j].y2-boxes[i][j].y1;
			int b=boxes[i][j].x2-boxes[i][j].x1;
			int z_size= EncodeMorton2(a,b)+1;
			//printf("%d,%d,%d\n",a,b,z_size);
			int *z_index=malloc(z_size*sizeof(int));
			//memset (z_index,-1,z_size*sizeof(int));
			for(k=0;k<z_size;k++){
				z_index[k]=-1;
			}

			int box_size=(a+1)*(b+1);

			for(int m=0;m<=b;m++)
				for(int l=0;l<=a;l++)
				{
					z_index[EncodeMorton2(l,m)]=l+m*(a+1);
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
			for(k=0;k<box_size;k++)
			{
				trees[i][offset+k].x=data[i][offset+recipe_en[k]].a;
				trees[i][offset+k].y=data[i][offset+recipe_en[k]].b;
				trees[i][offset+k].val=data[i][offset+recipe_en[k]].val;
				trees[i][offset+k].index=offset+recipe_en[k];
				trees[i][offset+k].flag=0;
				trees[i][offset+k].fchild=NULL;
				trees[i][offset+k].next=NULL;
				trees[i][offset+k].lvl=i;
			}

			if(i<Level-1){
				size_t *size_t_index_tmp_buffer = (size_t *) malloc (box_size * sizeof (size_t));
				gsl_sort_int_index (size_t_index_tmp_buffer,  recipe_en, 1,box_size );

				for(int j1=0;j1<box_size;j1++){
					recipe_de[j1+offset]=size_t_index_tmp_buffer[j1]+offset;
				}
				free(size_t_index_tmp_buffer);
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


	start_t=clock();

	start_t1=start_t;

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
	fp_glob=dataArray;
	for(i=0;i<1;i++)
		for(j=0;j<cnt[i];j++)
		{
			struct  node *p=&trees[i][j];
			PrintTree(p);

		}

	//printf("vp:%ld,%ld\n",dataArray,fp_glob-dataArray);
	for(i=0;i<Level;i++)
		for(j=0;j<cnt[i];j++)
		{
			if(trees[i][j].flag==0)                      
				printf("Not visit %d,%d\n",i,j);

		}
	for(i=0;i<Level;i++)
		free(trees[i]);
	free(trees);

	//free(dataArray);
	return dataArray;

}

int checkinclude(struct node_storage point, struct box *inq){
	int x=point.x>>point.lvl;
	int y=point.y>>point.lvl;
	//int x=point.x;
	//int y=point.y;
	//printf("%d,%d\n",x,y);
	if(x<inq->x1)
		return 0;
	if(x>inq->x2)
		return 0;
	if(y<inq->y1)
		return 0;
	if(y>inq->y2)
		return 0;
	return 1;

}

void pattern_box(struct node_storage *data, int cnt [Level],struct box *inq){
	//	printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int cnt1=0;
	for(i=0;i<datasize;i++)
	{

		if (checkinclude(data[i],inq))
		{
			data[i].flag=1;
			cnt1++;
		}
	}
}




int flag_block_c(struct node_storage *data, int cnt [Level]){
	//      printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	int cnt1=0;
	for(i=0;i<datasize;i++)
	{

		if (data[i].flag==1)
		{
			for(j=i+1;j<i+2;j++)
			{
				if(j<datasize&&data[j].flag==0)
					data[j].flag_block=1;

			}
		}
	}
	data[datasize-1].flag_block=1;
	for(i=0;i<datasize;i++)
	{

		if (data[i].flag_block==1)
			cnt1++;
	}
	//	printf("%d ",cnt1);
	return cnt1;
}

void flag_block_init(struct node_storage *data, int cnt [Level]){
	//      printf("%d,%d,%d,%d\n",inq->x1,inq->x2,inq->y1,inq->y2);
	int i,j;
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	for(i=0;i<datasize;i++)
	{
		data[i].flag=0;
		data[i].flag_block=0;
	}


}


int main()
{
	int i,j,cnt[Level],box_cnt[Level];
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));




	FILE *fp=fopen("datapoint_0","r");
	//		FILE *fp=fopen("datapoint_noghost.info","r");
	for(i=0;i<Level;i++)
	{
		fread(&cnt[i],sizeof(int),1,fp);
		printf("data count= %d\n", cnt[i]);
		fread(&box_cnt[i],sizeof(int),1,fp);
		printf("box_cnt= %d\n", box_cnt[i]);
		boxes[i]=malloc(box_cnt[i]*sizeof(struct box));
		fread(boxes[i],sizeof(struct box),box_cnt[i],fp);
		data[i]=malloc(cnt[i]*sizeof(struct datapoint));
		fread(data[i],sizeof(struct datapoint),cnt[i],fp);
		//for(j=0;j<cnt[i];j++)
		//	printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
	}
	fclose(fp);


	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));
	box_mapping=malloc(Level*sizeof(* box_mapping));
	for(i=0;i<Level;i++)
		box_mapping[i]=malloc(box_cnt[i]*sizeof(struct parent_box));

	struct node_storage* s_data;
	struct node_storage* s_data1;
	struct node_storage* s_data_h;
	struct node_storage* s_data_h1;
	s_data=leveldata_box(data,cnt,boxes,box_cnt);
	s_data1=leveldata_box_level(data,cnt,boxes,box_cnt);

	s_data_h=leveldata_box_hilbert(data,cnt,boxes,box_cnt);
	s_data_h1=leveldata_box_level_hilbert(data,cnt,boxes,box_cnt);

	struct box inq;

	double num_run1=0;
	double num_run2=0;
	double num_run_h1=0;
	double num_run_h2=0;
	//for(i=0;i<Level;i++)
	for(i=0;i<1;i++)
		for(j=0;j<box_cnt[i];j++){
			inq=boxes[i][j];
			inq.x1=inq.x1>>i;
			inq.y1=inq.y1>>i;
			inq.x2=inq.x2>>i;
			inq.y2=inq.y2>>i;

			flag_block_init(s_data,cnt);       
			pattern_box(s_data,cnt,&inq);
			num_run1+=	flag_block_c(s_data,cnt);

			flag_block_init(s_data1,cnt);
			pattern_box(s_data1,cnt,&inq);
			num_run2+= flag_block_c(s_data1,cnt);

			flag_block_init(s_data_h,cnt);       
			pattern_box(s_data_h,cnt,&inq);
			num_run_h1+=	flag_block_c(s_data_h,cnt);

			flag_block_init(s_data_h1,cnt);
			pattern_box(s_data_h1,cnt,&inq);
			num_run_h2+= flag_block_c(s_data_h1,cnt);
		}
	printf("Number of run, Z: %lf, %lf, %f\n",num_run1/box_cnt[0],num_run2/box_cnt[0], (double)(num_run1-num_run2)/(double)num_run1);

	printf("Number of run, H: %lf, %lf, %f\n",num_run_h1/box_cnt[0],num_run_h2/box_cnt[0], (double)(num_run_h1-num_run_h2)/(double)num_run_h1);
	free(s_data);
	free(s_data1);

	free(s_data_h);
	free(s_data_h1);

	for(i=0;i<Level;i++)	
		free(data[i]);
	for(i=0;i<Level;i++)
		free(boxes[i]);
	free(boxes);
	free(data);
	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);
	for(i=0;i<Level;i++)
		free(box_mapping[i]);
	free(box_mapping);

	return 1;
}
