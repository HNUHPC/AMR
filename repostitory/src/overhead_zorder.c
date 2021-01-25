#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define Level 5
#define Refine_ratio 2
#define SIZE_MAX1  2147483647
#define Error_ratio 0.0001


#define Num_run 10

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
//		printf("data count= %d\n", cnt[i]);
		read_cnt=fread(&box_cnt[i],sizeof(int),1,fp);
//		printf("box_cnt= %d\n", box_cnt[i]);
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




	//	int* recipe=	get_baseline_encode_recipe_hilbert(data,cnt,boxes,box_cnt);
	//	free(recipe);
	int datasize=0;
	for(i=0;i<Level;i++)
		datasize=datasize+cnt[i];
	double *data_level=malloc(datasize*sizeof(double));
	double *data_baseline=malloc(datasize*sizeof(double));
	double *data_baseline_de=malloc(datasize*sizeof(double));
	double *data_levelRe=malloc(datasize*sizeof(double));
	double *data_levelRe_de=malloc(datasize*sizeof(double));
	int *   recipe_en_baseline=malloc(datasize*sizeof(int));
	int *   recipe_de_baseline=malloc(datasize*sizeof(int));
	int *   recipe_en_levelRe=malloc(datasize*sizeof(int));
	int *   recipe_de_levelRe=malloc(datasize*sizeof(int));

	clock_t start_t, end_t; double t_recipe_en_baseline,t_recipe_de_baseline,t_recipe_en_levelRe,t_recipe_de_levelRe;

	start_t=clock(); 
	for(i=0;i<Num_run;i++){
		get_zorder_encode_recipe(recipe_en_baseline,cnt,boxes,box_cnt);
	}
	end_t=clock();
	t_recipe_en_baseline = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("get_baseline_encode_recipe: %lf\n", t_recipe_en_baseline  );

	start_t=clock();
	for(i=0;i<Num_run;i++){
		//	get_baseline_decode_recipe(recipe_de_baseline,cnt,boxes,box_cnt);
		for(j=0;j<datasize;j++)
			recipe_de_baseline[recipe_en_baseline[j]]=j;
	}
	end_t=clock();
	t_recipe_de_baseline = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("get_baseline_decode_recipe: %lf\n", t_recipe_en_baseline+t_recipe_de_baseline  );


	start_t=clock();
	for(i=0;i<Num_run;i++){
		get_zorder_zmesh_encode_recipe(data,recipe_en_levelRe,cnt,boxes,box_cnt);
	}
	end_t=clock();
	t_recipe_en_levelRe = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("get_levelRe_encode_recipe: %lf\n", t_recipe_en_levelRe  );

	start_t=clock();
	for(i=0;i<Num_run;i++){
		//	get_levelRe_decode_recipe(data,recipe_de_levelRe,cnt,boxes,box_cnt);
		for(j=0;j<datasize;j++)
			recipe_de_levelRe[recipe_en_levelRe[j]]=j;
	}
	end_t=clock();
	t_recipe_de_levelRe = (double)(end_t - start_t) / CLOCKS_PER_SEC;
	printf("get_levelRe_decode_recipe: %lf\n", t_recipe_en_levelRe+t_recipe_de_levelRe  );




	double  t_compress_baseline_zfp=0,t_decompress_baseline_zfp=0,t_compress_levelRe_zfp=0,t_decompress_levelRe_zfp=0;
	double  t_compress_baseline_sz=0,t_decompress_baseline_sz=0,t_compress_levelRe_sz=0,t_decompress_levelRe_sz=0;
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
	if(Errbound>10000)
		Errbound=100;

	//		printf("EB:%lf\n",Errbound);
	char compressed_name[50];
	sprintf(compressed_name,"Baseline_%d.zfp",list[0]);  
	start_t=clock();
	for( i=0;i<Num_run;i++){
		for(int i1=0;i1<datasize;i1++)
		{
			data_baseline[i1]=data_level[recipe_en_baseline[i1]]; 
		}  
		zfp1_compress_write(data_baseline,datasize,Errbound,compressed_name); 




	}
	end_t=clock();
	t_compress_baseline_zfp+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;

	start_t=clock();
	for( i=0;i<Num_run;i++){
		zfp1_decompress(data_baseline,datasize,Errbound,compressed_name); 
		for(int i1=0;i1<datasize;i1++)
		{
			data_baseline_de[i1]=data_baseline[recipe_de_baseline[i1]]; 
			//	if(data_baseline_de[i1]-data_level[i1]>Errbound)
			//		printf("Error\n");
		}  




	}
	end_t=clock();
	t_decompress_baseline_zfp+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;


	sprintf(compressed_name,"LevelRe_%d.zfp",list[0]);  
	start_t=clock();
	for( i=0;i<Num_run;i++){
		for(int i1=0;i1<datasize;i1++)
		{
			data_levelRe[i1]=data_level[recipe_en_levelRe[i1]]; 
		}  
		zfp1_compress_write(data_levelRe,datasize,Errbound,compressed_name); 




	}
	end_t=clock();
	t_compress_levelRe_zfp+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;

	start_t=clock();
	for( i=0;i<Num_run;i++){
		zfp1_decompress(data_levelRe,datasize,Errbound,compressed_name); 
		for(int i1=0;i1<datasize;i1++)
		{
			data_levelRe_de[i1]=data_levelRe[recipe_de_levelRe[i1]]; 
			//	if(data_levelRe_de[i1]-data_level[i1]>Errbound)
			//		printf("Error\n");
		}  




	}
	end_t=clock();
	t_decompress_levelRe_zfp+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;

	char *confFile = "/home/luo/ZFP/SZ/sz.config";
	size_t outSize;
	int r4 = 0, r3 = 0, r2 = 0, r5 = 0;
	SZ_Init(confFile);
	confparams_cpr->absErrBound =Errbound; 
	unsigned char *compressed;
	double* decompressed;
	sprintf(compressed_name,"Baseline_%d.sz",list[0]);  
	start_t=clock();
	for( i=0;i<Num_run;i++){
		for(int i1=0;i1<datasize;i1++)
		{
			data_baseline[i1]=data_level[recipe_en_baseline[i1]]; 
		}  


		compressed = SZ_compress(SZ_DOUBLE, data_baseline, &outSize, r5, r4, r3, r2 ,datasize);

		fp=fopen(compressed_name,"w");
		fwrite(compressed, 1, outSize, fp);
		fclose(fp);
		free(compressed); 

	}

	end_t=clock();
	t_compress_baseline_sz+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;

	start_t=clock();
	for( i=0;i<Num_run;i++){
		outSize=SIZE_MAX1;
		compressed=malloc(datasize*sizeof(double));
		fp=fopen(compressed_name,"r");
		outSize=fread(compressed, 1, outSize, fp);
		fclose(fp);



		decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed, outSize,r5, r4, r3, r2, datasize);
		for(int i1=0;i1<datasize;i1++)
		{
			data_baseline_de[i1]=decompressed[recipe_de_baseline[i1]]; 
			//	if(data_baseline_de[i1]-data_level[i1]>Errbound)
			//		printf("Error\n");
		}  

		free(compressed);
		free(decompressed);

	}
	end_t=clock();
	t_decompress_baseline_sz+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;



	sprintf(compressed_name,"LevelRe_%d.sz",list[0]);  
	start_t=clock();
	for( i=0;i<Num_run;i++){
		for(int i1=0;i1<datasize;i1++)
		{
			data_levelRe[i1]=data_level[recipe_en_levelRe[i1]]; 
		}  


		compressed = SZ_compress(SZ_DOUBLE, data_levelRe, &outSize, r5, r4, r3, r2 ,datasize);

		fp=fopen(compressed_name,"w");
		fwrite(compressed, 1, outSize, fp);
		fclose(fp);
		free(compressed); 


	}

	end_t=clock();
	t_compress_levelRe_sz+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;

	start_t=clock();
	for( i=0;i<Num_run;i++){
		outSize=SIZE_MAX1;
		compressed=malloc(datasize*sizeof(double));
		fp=fopen(compressed_name,"r");
		outSize=fread(compressed, 1, outSize, fp);
		fclose(fp);



		decompressed = (double *)SZ_decompress(SZ_DOUBLE, compressed, outSize,r5, r4, r3, r2, datasize);
		for(int i1=0;i1<datasize;i1++)
		{
			data_levelRe_de[i1]=decompressed[recipe_de_levelRe[i1]]; 
			//	if(data_levelRe_de[i1]-data_level[i1]>Errbound)
			//		printf("Error\n");
		}  

		free(compressed);
		free(decompressed);
	}
	end_t=clock();
	t_decompress_levelRe_sz+=  (double)(end_t - start_t) / CLOCKS_PER_SEC;






	printf("t_compress_baseline_zfp: %lf\n",t_compress_baseline_zfp );
	printf("t_decompress_baseline_zfp: %lf\n",t_decompress_baseline_zfp);
	printf("t_compress_levelRe_zfp: %lf\n",t_compress_levelRe_zfp);
	printf("t_decompress_levelRe_zfp: %lf\n",t_decompress_levelRe_zfp);
	printf("t_compress_baseline_sz: %lf\n",t_compress_baseline_sz);
	printf("t_decompress_baseline_sz: %lf\n",t_decompress_baseline_sz);
	printf("t_compress_levelRe_sz: %lf\n",t_compress_levelRe_sz);
	printf("t_decompress_levelRe_sz: %lf\n",t_decompress_levelRe_sz);

	for(i=0;i<Level;i++)
		free(mapping[i]);
	free(mapping);
	for(i=0;i<Level;i++)
		free(box_mapping[i]);

	for(i=0;i<Level;i++)	
		free(data[i]);
	for(i=0;i<Level;i++)
		free(boxes[i]);
	free(box_mapping);
	free(boxes);
	free(data);
	free(recipe_en_baseline);
	free(recipe_de_baseline);
	free(recipe_en_levelRe);
	free(recipe_de_levelRe);
	free(data_level);
	free(data_baseline);
	free(data_baseline_de);
	free(data_levelRe);
	free(data_levelRe_de);
	return 1;
}
