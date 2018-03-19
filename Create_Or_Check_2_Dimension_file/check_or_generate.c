#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>

struct position {
	int X;
	int Y;
};


bool checkifvalueinarray(int val1, int val2, struct position *arr, int size) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr[i].X == val1 && arr[i].Y == val2)
			return true;
	}
	return false;
}


int main(int argc, char *argv[]) {
	FILE *fp;
	int max_x, max_y, num_pt;
	int *x_coordinate, *y_coordinate;
	int inputfile = 0, outputfile = 0;
	int i;
	int a[1];
	int size=1000;
	int k;
	struct position coord[size];

	if (argc > 5){
		printf("TOO Many Arguments\n");
		printf("->Correct Input Format %s [-i inputfile [-o outputfile]]\n", argv[0]);
	}

	

	if (argc == 1) {
		/* to generate random instances, accepting parameters from stdin */
		int MAX_X , MAX_Y;
		int numberOffile;
		int numberOfpoint;
		int numP;
		int numF;
		char filename[32];
		FILE *fo;
		int size2=1000;
		int j;
		struct position coord2[size2];
		int r1,r2;
		printf("Generating random instances ...\n");
		printf("Enter the circuit board size MAX_X MAX_Y: ");
		scanf("%d %d",&MAX_X ,&MAX_Y);
		if ((MAX_X<0 || MAX_X>1000)&&(MAX_Y<0 || MAX_Y>1000)){
			printf("Input for both Max_x and Max_y is out of range.\n");
			return -44;
		}
		if (MAX_X<0 || MAX_X>1000){
			printf("Input for Max_x is out of range to generate coordinate points.\n");
			return -45;
		}
		if (MAX_Y<0 || MAX_Y>1000){
			printf("Input for Max_y is out of range to generate coordinate points.\n");
			return -46;
		}
		printf("Enter the number of points: ");
		scanf("%d",&numberOfpoint);
		if (numberOfpoint<1 || numberOfpoint>10000) {
			printf("Incorrect input for number of points.\n");
			return -47;
		}
		if (numberOfpoint>((MAX_X+1)*(MAX_Y+1)) ){
			printf("The Max_x and Max_y you provided can not generate that many points.\n");
			return -50;
		}
		printf("Enter the number of random instances to be generated: ");
		scanf("%d",&numberOffile);
		size2 = numberOfpoint;
		
		for (numF=1;numF<=numberOffile;numF++) {
			snprintf(filename,sizeof(char)*32,"instance%d_%d.txt",numberOfpoint,numF);
			fo = fopen(filename,"w");
			fprintf(fo,"%d\t%d\n",MAX_X,MAX_Y);
			fprintf(fo,"%d\n",numberOfpoint);
               		for (j=0;j<size2;j++) {
                        	coord2[j].X = -1;
                        	coord2[j].Y = -1;
			}
			for (numP=0;numP<numberOfpoint;numP++){
				 r1 = rand()%(MAX_X+1);
				 r2 = rand()%(MAX_Y+1);
				while (1) {
					if (checkifvalueinarray(r1,r2,coord2,size2)){
						 r1 = rand()%(MAX_X+1);
						 r2 = rand()%(MAX_Y+1);
					} else {
						coord2[numP].X = r1;
						coord2[numP].Y = r2;
						break; 
					}
				}
				fprintf(fo,"%d\t%d\n",r1,r2);	
			}
                        fclose(fo);
                        printf("%s\n",filename);
		}
											
		return 1;
	}

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0)
			inputfile = i + 1;
		else if (strcmp(argv[i], "-o") == 0)
			outputfile = i + 1;
	}
	if (inputfile == 0) {
		/* invalid command line options */
		printf("Invalid command line options\n");
		printf("Correct Input Format-> %s [-i inputfile [-o outputfile]]\n", argv[0]);
		return -1;
	}
	if ((fp = fopen(argv[inputfile], "r")) == NULL) {
		/* open file error */
		printf("Input File does not exist.\n");
		return -2;
	}
	if (strlen(argv[inputfile]) > 30) {
		printf("The input file name is too long.\n");
		return -22;
	}
	if (outputfile != 0) {
		if (strlen(argv[outputfile]) > 30) {
			printf("The output file name is too long.\n");
			return -23;
		}
	}	
	char str[60];
	bool pre=false;
	int Line=0;
	while (1) {
		int num=-1;
		bool lineskip=false;
        	memset(str,0,sizeof(str));
		fgets(str,60,fp);
		if (feof(fp)){
			break;
		}
		int size = sizeof(str)/sizeof(str[0]);
		for (int index=0;index<size;index++){
			if (str[index] == '#'){
				
				lineskip=true;
				break;
			}

			if (str[0] == '\n'){
				lineskip=true;
				break;
			}
		
		       if (isalpha(str[index])){
                                printf("File Structure Error(a line contains non-integer character)\n");
                               // printf("%c\n",str[index]);
                                fclose(fp);
                                return -50;
                        }

			if (str[index]<='9'&&str[index]>='0'){
				if (pre){
				//	k[num]=k[num]*10+str[index]-'0';
				}
				else pre=true,++num;
			}
			else pre=false;
		}
		
		
		if (num+1 != 0 && !lineskip) {
			Line+=1;
		}
             
		if (Line==1&&!lineskip){
			if (num+1 < 2){
				printf("File Structure Error(Max_x Max_y line has only one int.)\n");
				fclose(fp);
				return -51;
			}
			if (num+1 > 2){
				printf("File Structure Error(Max_x Max_y line has more than two int.)\n");				  fclose(fp);
				return -53;
			}
		}
		if (Line==2&&!lineskip){
			if (num+1 < 1 || num+1 >1){
				printf("File Structure Error(Number of point line is missing.)\n");	
			 	fclose(fp);
				return -52;
			}
		}
		if (Line>2 && !lineskip){
			if (num+1 <2){
				printf("File Structure Error(One of the Coordinate Point is missing x/y.)\n");
				fclose(fp);
				return -66;
			}
			if (num+1 >2){
				printf("File Structure Error(Too many integers in a coordinate line.)\n");
				fclose(fp);
				return -67;
			}
		}	
	}
	fclose(fp);
	fp = fopen(argv[inputfile],"r");

	while (fscanf(fp, "%d", &max_x) != 1) {
		if (ferror(fp)) {
			/* read error */
			printf("Read error for max_x.\n");
			fclose(fp);
			return -3;
		}
		if (feof(fp)) {
			/* no integer to read */
			printf("No integer to read for max_x.\n");
			fclose(fp);
			return -4;
		}
		fscanf(fp, "%*[^\n]"); /* skip the rest of line */
	}
	if (max_x>1000 || max_x<0) {
		printf("Max_x is out of range. The range for Max_x should be [0,1000].\n");
		fclose(fp);
		return -34;
	}
	if (fscanf(fp, "%d", &max_y) != 1) {
		/* max_y not following max_x */
		printf("max_y is not following max_x.\n");
		fclose(fp);
		return -5;
	}
	if (max_y>1000 || max_y<0) {
		printf("Max_y is out of range. The range for Max_y should be [0,1000].\n");
		fclose(fp);
		return -35;
}
	while (fscanf(fp, "%d", &num_pt) != 1) {
		if (ferror(fp)) {
			/* read error */
			printf("Read error for num_pt\n");
			fclose(fp);
			return -6;
		}
		if (feof(fp)) {
			/* no integer to read */
			printf("No integer to read for num_pt.\n");
			fclose(fp);
			return -7;
		}
		fscanf(fp, "%*[^\n]"); /* skip the rest of line */
	}
    if (num_pt>((max_x+1)*(max_y+1))){
        printf("Number of point is larger than the all possible points that can be generated by max_x and max_y.\n");
        fclose(fp);
        return -70;
    }
    
	if (num_pt >10000 || num_pt <1) {
		printf("The number of points is out of range. It should be in the range of [1-10000].\n");
		fclose(fp);
		return -36;
}
	x_coordinate = (int *)malloc(num_pt * sizeof(int));
	y_coordinate = (int *)malloc(num_pt * sizeof(int));
	size = num_pt;
	for (k=0;k<size;k++){
		coord[k].X = -1;
		coord[k].Y = -1;
}
	for (i = 0; i < num_pt; i++) {
		while (fscanf(fp, "%d", &x_coordinate[i]) != 1) {
			if (ferror(fp)) {
				/* read error */
				printf("Read error for x_coordinate.\n");
				fclose(fp);
				return -8;
			}
			if (feof(fp)) {
				/* no integer to read */
				printf("No integer to read for x_coordinate.\n");
				fclose(fp);
				return -9;
			}
			fscanf(fp, "%*[^\n]"); /* skip the rest of line */
		}
		if (x_coordinate[i]>max_x || x_coordinate[i]<0){
			printf("File Structure Error(one of the coordinate x is out of range.)\n");
			fclose(fp);
			return 60;
		} 
		if (fscanf(fp, "%d", &y_coordinate[i]) != 1) {
			/* y_coordinate not following x_coordinate */
			printf("y_coordinate is not following x_coordinate.\n");
			fclose(fp);
			return -10;
		}
	
		if (y_coordinate[i]>max_y || y_coordinate[i]<0){
			printf("File Structure Error(one of the coordiante y is out of range.)\n");
			fclose(fp);
			return -61;
		} 
		if (checkifvalueinarray(x_coordinate[i], y_coordinate[i], coord, size)) {
			printf("Duplicate coordinate point found.\n");
			fclose(fp);
			return -33;
		}
		else {
			coord[i].X = x_coordinate[i];
			coord[i].Y = y_coordinate[i];
		}
	}
	if (fscanf(fp, "%d", &a[1]) == 1) {
		printf("Number of coordinate points does not match the number of points should be in the file.\n");
		fclose(fp);
		return -33;
	}

	fclose(fp);
	if (outputfile > 0) {
		if ((fp = fopen(argv[outputfile], "w")) == NULL) {
			/* open file error */
			printf("Opening outputfile error.\n");
			return -2;
		}
		
		fprintf(fp, "%d\t%d\n", max_x, max_y);
		fprintf(fp, "%d\n", num_pt);
		for (i = 0; i < num_pt; i++) {
			fprintf(fp, "%d\t%d\n", x_coordinate[i], y_coordinate[i]);
		}
		
		fclose(fp);
	}
	else {
		printf("%d\t%d\n", max_x, max_y);
		printf("%d\n", num_pt);
		for (i = 0; i < num_pt; i++) {
			printf("%d\t%d\n", x_coordinate[i], y_coordinate[i]);
		}
		
	}
	free(x_coordinate);
	free(y_coordinate);
	return 0;
}




