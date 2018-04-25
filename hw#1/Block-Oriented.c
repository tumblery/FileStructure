#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BlockSize 4096
#define RecordSize 32

int main(void){
	unsigned long int id,bl_id;
	char name[20];
	float score;
	int age;
	char input[100];
	char* pointer,*idP;
	unsigned char Block[BlockSize];
	int j,i,N,block_num,record;

	FILE* fp =fopen("in_student.txt","r");
	FILE* out=fopen("out_student.dat","wb");

	fscanf(fp,"%d",&N);
	fgets(input,100,fp);
	block_num = 0;
	record =0;
	memset(Block,0,4096);
	j=4;
	printf("%d %s\n",N,Block);
	for(i=0;i<N;i++){
		printf("%d\n",i);
		fgets(input,100,fp); 
		pointer = strtok(input,",");
		memset(name,0,20);
		strcpy(name,pointer);
		int k;
		strcpy(&Block[j],name);
		for(k=0;k<20-strlen(name);k++){
			Block[j+strlen(name)+k] = 0;
		}
		j+=20;
		pointer = strtok(NULL,",");
		id = strtoul(pointer,&idP,10);
		memcpy(&Block[j],&id,sizeof(unsigned long));
		j +=4;		
		pointer = strtok(NULL,",");
		score = atof(pointer);
		memcpy(&Block[j],&score,sizeof(float));
		j +=4;		
		pointer = strtok(NULL,",");
		age = atoi(pointer);
		memcpy(&Block[j],&age,sizeof(int));
		j +=4;		
		record++;
		if(record%128 == 0){
			memcpy(&Block[0],&block_num,sizeof(int));
			fseek(out,4096*block_num,SEEK_SET);
			printf("block num:%d\n",block_num);
			fwrite(Block,sizeof(char),BlockSize,out);
			memset(Block,0,4096);
			record =0;
			j=4;
			block_num++;
		}
	}
	memcpy(&Block[0],&block_num,sizeof(int));
	fseek(out,4096*block_num,SEEK_SET);
	fwrite(Block,sizeof(char),BlockSize,out);
	
	fclose(fp);
	fclose(out);

	int flag,cnt;
	fp = fopen("out_student.dat","rb");
	
	while(1){
		printf("[+] Enter to ID(quit=0)>>");
		flag = 0;
		scanf("%lu",&id);
		if(id == 0) break;
		fseek(fp,0L,SEEK_SET);
		while(fread(Block,1,4096,fp) >0){
			memcpy(&block_num,&Block,sizeof(int));
			i=4;
			while(i < 4096){
				i +=20;
				bl_id = (unsigned long)Block[i]+(unsigned long)(Block[i+1])*256+(unsigned long)(Block[i+2])*65536+(unsigned long)(Block[i+3])*16777216;
				if( (id == bl_id) && (flag ==0)){
					i -=20;
					flag = 1;
					for(j=0;j<20;j++){
						name[j] = Block[i];
						i++;
					}
					printf("%lu's name is %s\n%s's Block num is %d\n",id,name,name,block_num);
				}
				i+=12;
			}
		}
	}

	fclose(fp);
	return 0;
}
