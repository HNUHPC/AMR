#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Level 5
#define Refine_ratio 2
#define SIZE_MAX1  2147483647
#define Error_ratio 0.001

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
		//	printf("data count= %d\n", cnt[i]);
		read_cnt=fread(&box_cnt[i],sizeof(int),1,fp);
		//	printf("box_cnt= %d\n", box_cnt[i]);
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
	double *data_levelRe=malloc(datasize*sizeof(double));
	double *data_level=malloc(datasize*sizeof(double));
	double *data_baseline=malloc(datasize*sizeof(double));
	int *   recipe_en_levelRe=malloc(datasize*sizeof(int));
	int *   recipe_en_baseline=malloc(datasize*sizeof(int));



	get_zorder_encode_recipe(recipe_en_levelRe,cnt,boxes,box_cnt);
	get_zorder_zmesh_encode_recipe(data, recipe_en_baseline,cnt,boxes,box_cnt);





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
	double  t_compress_levelRe_zfp=0;
	double  t_compress_levelRe_sz=0;
	double  fullsize=datasize*sizeof(double);
	double compressedsize=0;
	double compressedsize_baseline=0;
	double compressedsize_levelRe=0;
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
		double max=-100000000;
		double min=100000000;
		for(i=0;i<Level;i++)
			for(j=0;j<cnt[i];j++)
			{
				data_level[offset]=data[i][j].val;
				if( data_level[offset]>max)
					max= data_level[offset];
				if( data_level[offset]<min)
					min= data_level[offset];
				offset++;

			}
		double Errbound=Error_ratio*(max-min);
		//	double Errbound=Error_ratio*max;
		if(Errbound>10000)
			Errbound=100;

		for(int i1=0;i1<datasize;i1++)
		{
			data_levelRe[i1]=data_level[recipe_en_levelRe[i1]]; 
			data_baseline[i1]=data_level[recipe_en_baseline[i1]]; 
		}  
		//		printf("EB:%lf\n",Errbound);
		char compressed_name[50];
		sprintf(compressed_name,"LevelRe_%d.zfp",list[col]);  

		for(i=4;i<=datasize/4;i=i*2)
		{
			int ny=i;
			int nx=datasize/i;

			compressedsize=zfp2_compress(data_level,nx,ny,Errbound); 
			if(datasize>nx*ny)
				compressedsize+=zfp1_compress(data_level+nx*ny,datasize-nx*ny,Errbound);
			compressedsize_baseline=zfp2_compress(data_baseline,nx,ny,Errbound); 
			if(datasize>nx*ny)
				compressedsize_baseline+=zfp1_compress(data_baseline+nx*ny,datasize-nx*ny,Errbound);
			compressedsize_levelRe=zfp2_compress(data_levelRe,nx,ny,Errbound); 
			if(datasize>nx*ny)
				compressedsize_levelRe+=zfp1_compress(data_levelRe+nx*ny,datasize-nx*ny,Errbound);
		        printf("%lf\n",fullsize/compressedsize);
			printf("%lf\n",fullsize/compressedsize_baseline);
			printf("%lf\n",fullsize/compressedsize_levelRe);
		}


		printf("\n");


		char *confFile = "/home/luo/ZFP/SZ/sz.config";
		size_t outSize;
		int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
		SZ_Init(confFile);
		confparams_cpr->absErrBound =Errbound; 
		unsigned char *compressed;
		double* decompressed;

		for(i=4;i<=datasize/4;i=i*2){
			int ny=i;
			int nx=datasize/i;

			compressed = SZ_compress(SZ_DOUBLE, data_level, &outSize, r5, r4, r3, ny ,nx);
			free(compressed);
			compressedsize=outSize;
			if(datasize>nx*ny){
				compressed = SZ_compress(SZ_DOUBLE, data_level+nx*ny, &outSize, r5, r4, r3, r2 ,datasize-nx*ny);
				free(compressed);
				compressedsize+=outSize;
			}

			compressed = SZ_compress(SZ_DOUBLE, data_baseline, &outSize, r5, r4, r3, ny ,nx);
			free(compressed);
			compressedsize_baseline=outSize;
			if(datasize>nx*ny){
				compressed = SZ_compress(SZ_DOUBLE, data_baseline+nx*ny, &outSize, r5, r4, r3, r2 ,datasize-nx*ny);
				free(compressed);
				compressedsize_baseline+=outSize;
			}

			compressed = SZ_compress(SZ_DOUBLE, data_levelRe, &outSize, r5, r4, r3, ny ,nx);
			free(compressed);
			compressedsize_levelRe=outSize;
			if(datasize>nx*ny){
				compressed = SZ_compress(SZ_DOUBLE, data_levelRe+nx*ny, &outSize, r5, r4, r3, r2 ,datasize-nx*ny);
				free(compressed);
				compressedsize_levelRe+=outSize;
			}
			printf("%lf\n",fullsize/compressedsize);
			printf("%lf\n",fullsize/compressedsize_baseline);
			printf("%lf\n",fullsize/compressedsize_levelRe);
		}

		printf("\n");


		for(i=0;i<Level;i++)	
			free(data[i]);
		for(i=0;i<Level;i++)
			free(boxes[i]);
	}
	//	printf("t_compress_levelRe_zfp: %lf\n",t_compress_levelRe_zfp);
	//	printf("t_compress_levelRe_sz: %lf\n",t_compress_levelRe_sz);
	free(boxes);
	free(data);
	free(recipe_en_levelRe);
	free( recipe_en_baseline);
	free(data_level);
	free(data_levelRe);
	free(data_baseline);
	return 1;
}
