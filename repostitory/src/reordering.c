#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define Level 5
#define Refine_ratio 2
#define SIZE_MAX1  2147483647
#define Error_ratio 0.0001





#include "util.h"
#include "compress.h"




int main(int argc, char **argv)
{
	int i,j,cnt[Level],box_cnt[Level],read_cnt;
	struct datapoint** data;
	data=malloc(Level*sizeof(* data)); 
	struct box** boxes;
	boxes=malloc(Level*sizeof(* boxes));

	int list[6]={0,1,2,4,11,12}; 
	char filename[50];
	sprintf(filename,"datapoint_%d",list[0]);


	FILE *fp=fopen(filename,"r");
	if (fp==NULL)
	{
		printf("Can not open file\n");
		return 0;

	}




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

	mapping=malloc(Level*sizeof(* mapping));
	for(i=0;i<Level;i++)
		mapping[i]=malloc(cnt[i]*sizeof(int));

	box_mapping=malloc(Level*sizeof(* box_mapping));
	for(i=0;i<Level;i++)
		box_mapping[i]=malloc(box_cnt[i]*sizeof(struct parent_box));



	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *data_all=malloc(datasize*sizeof(double));
	double *data_zorder=malloc(datasize*sizeof(double));
	double *data_zorder_zmesh=malloc(datasize*sizeof(double));
	double *data_hilbert=malloc(datasize*sizeof(double));
	double *data_hilbert_zmesh=malloc(datasize*sizeof(double));
	int *   recipe_zorder=malloc(datasize*sizeof(int));
	int *   recipe_zorder_zmesh=malloc(datasize*sizeof(int));
	int *   recipe_hilbert=malloc(datasize*sizeof(int));
	int *   recipe_hilbert_zmesh=malloc(datasize*sizeof(int));

	get_zorder_encode_recipe(recipe_zorder,cnt,boxes,box_cnt);
	get_zorder_zmesh_encode_recipe(data,recipe_zorder_zmesh,cnt,boxes,box_cnt);
	get_hilbert_encode_recipe(recipe_hilbert,cnt,boxes,box_cnt);
	get_hilbert_zmesh_encode_recipe(data,recipe_hilbert_zmesh,cnt,boxes,box_cnt);




	for(i=0;i<Level;i++)	
		free(data[i]);
	for(i=0;i<Level;i++)
		free(boxes[i]);
	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);
	for(i=0;i<Level;i++)
		free(box_mapping[i]);
	free(box_mapping);

	//total number of quantities is 18: for(int col=0;col<6;col++){
	for(int col=0;col<1;col++){
		sprintf(filename,"datapoint_%d",list[col]);

		fp=fopen(filename,"r");
		if (fp==NULL)
		{
			printf("Can not open file\n");
			return 0;

		}




		for(i=0;i<Level;i++)
		{
			read_cnt=fread(&cnt[i],sizeof(int),1,fp);
			read_cnt=fread(&box_cnt[i],sizeof(int),1,fp);
			boxes[i]=malloc(box_cnt[i]*sizeof(struct box));
			read_cnt=fread(boxes[i],sizeof(struct box),box_cnt[i],fp);
			data[i]=malloc(cnt[i]*sizeof(struct datapoint));
			read_cnt=fread(data[i],sizeof(struct datapoint),cnt[i],fp);
			//for(j=0;j<cnt[i];j++)
			//	printf("%d %d %lf\n", data[i][j].a,data[i][j].b,data[i][j].val);
		}
		fclose(fp);

		int offset=0;
		for(i=0;i<Level;i++)
			for(j=0;j<cnt[i];j++)
			{
				data_all[offset]=data[i][j].val;
				offset++;

			}
		for(int i1=0;i1<datasize;i1++)
		{
			data_zorder[i1]=data_all[recipe_zorder[i1]]; 
			data_zorder_zmesh[i1]=data_all[recipe_zorder_zmesh[i1]]; 
			data_hilbert[i1]=data_all[recipe_hilbert[i1]]; 
			data_hilbert_zmesh[i1]=data_all[recipe_hilbert_zmesh[i1]]; 
		}  

        sprintf(filename,"Level_box_zorder_%d.dat",col);
        fp=fopen(filename,"w");

	fwrite(data_zorder,sizeof(double),datasize,fp);
	fclose(fp);

        sprintf(filename,"Level_box_zorder_zmesh%d.dat",col);
        fp=fopen(filename,"w");

	fwrite(data_zorder_zmesh,sizeof(double),datasize,fp);
	fclose(fp);


        sprintf(filename,"Level_box_hilbert_%d.dat",col);
        fp=fopen(filename,"w");

	fwrite(data_hilbert,sizeof(double),datasize,fp);
	fclose(fp);


        sprintf(filename,"Level_box_hilbert_zmesh_%d.dat",col);
        fp=fopen(filename,"w");

	fwrite(data_hilbert_zmesh,sizeof(double),datasize,fp);
	fclose(fp);

		free(boxes);
		free(data);
		free(recipe_zorder);
		free(recipe_zorder_zmesh);
		free(recipe_hilbert);
		free(recipe_hilbert_zmesh);
		free(data_all);
		free(data_zorder);
		free(data_zorder_zmesh);
		free(data_hilbert);
		free(data_hilbert_zmesh);
		return 1;
	}
}
