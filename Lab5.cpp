#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>
#include <iostream>
#include <string>

using namespace std;

class Signal{
private:
	int length;
	int max;
	int min;
	double average;


	vector<int> data;             //vector to store data
	vector<double> newdata;       //new vector to store new data
	void mean();

public:
	//int sizemax(char *);
	void help(char *);
	void writefile(char *, int, double);
	void offset_function(double offset);
	void normalize_function(double scaling);
	void center_f();

	Signal();
	Signal(char*);
	Signal(int);
	~Signal();
};

//----------------function list----------------------
Signal::Signal(){
	length=0;
	max=0;
	min=0;
	average=0;

}


void Signal::mean()
{
	int i;
	for(i=0; i<length; i++)
		{
		average += data[i];
        average /= length;
		}
}

Signal::Signal(int n)
{
	char filename[50];
	sprintf(filename, "Lab4_read_%02d.txt", n);

	FILE *fp1 = fopen(filename, "r");

	fscanf(fp1, "%d %d", &length, &max);
	printf("Number of data: %d\n", length);
	printf("Maximum value: %d\n", max);
	int i=0;
	for(i=0; i<length; i++)
	{
		fscanf(fp1, "%d", &data[i]);
	}
	fclose(fp1);

}

Signal::Signal(char *filename)
{


	FILE *fp1 = fopen(filename, "r");
    if (fp1==NULL)
    {

    }
	fscanf(fp1, "%d %d", &length, &max);
	//	printf("Number of data: %d\n", length);
	//	printf("Maximum value: %d\n", max);
	int i=0;
	for(i=0; i<length; i++)
	{
		fscanf(fp1, "%d", &data[i]);
	}
	fclose(fp1);

}

void Signal::writefile(char *outname, int size, double data)
{
	FILE *fp2 = fopen(outname, "w");
	if(fp2 != NULL)
	{
		fprintf(fp2, "%d  %.4lf\n", size, data);
		int i;
		for(i=0; i<size; i++)
		{
			fprintf(fp2, "  %.4lf\n", newdata[i]);
		}
		fclose(fp2);
		printf("Wrote data to file: %s\n", outname);
	}
}

//double Signal::mean(int *array)
//{
//	double average = 0;
//
//	int i=0;
//	for(i=0; i<length; i++)
//	{
//		average += array[i];
//	}
//	average /= length;
//
//	return average;
//}

//int Signal::maximum()
//{
//	int i;
//	int max=INT_MIN;
//	for(i=0; i<length; i++)
//	{
//		if( data[i] > max )
//		{
//			max = data[i];
//		}
//	}
//	return max;
//}


void Signal::help(char *programName) {
	printf("%s is wrong format",programName);
	puts("The correct format should be like this( the input parameters could be in any order):");
	puts("Get help by input ./My_lab4_program -h    -- help\n");
	puts("./My_lab4_program -n Filenumber -o offset value\n -- a constant value will initialized to input value\n -s scale data -r Newname -- The program will create a copy of the raw file -- multiplying it by the scaling data\n");
	puts("./My_lab4_program -n Filenumber -S Get Statistics \n -C Center Signal \n-N Normalize Signal \n");
}

void Signal::offset_function(double offset)
{
	printf("Offset value %.2lf\n", offset);

	int i=0;
	for(i=0; i<length; i++)
	{
		newdata[i] = offset;
	}

}

void Signal::normalize_function(double scaling)
{
	scaling = (1/(double)maximum);
	int i;
	for(i=0; i<length; i++)
	{
		newdata[i] = ((int)data[i]*scaling);
	}
}

void Signal::center_f(){
	int i;
	for(i=0; i<length; i++)
	{
		newdata[i] = ((int)data[i] - average);
	}


}


int main(int argc, char **argv) {
	char optional, filename[32], outname[32];
	int size;

	// FILE fp2;
	double offset, scaling;
	// Command line args
	int filenumber = 0, Statistic=0, normalize=0, center=0;
	int offsetFlag = 0,scalingFlag = 0,renameFlag = 0;
	char *rename = NULL;//initialize

	Signal signal;

	if(argc < 2)      //To test there is more than 2 arguments
	{
		signal.help(argv[0]);//show help information
		return 0;
	}

	// Divide all options before performing anything
	int i=0;
	for(i=0; i<argc; i++)
	{
		if(argv[i][0] == '-')
		{

			if(argv[i][1] == 'h' || argv[i][1] == 'H')
			{
				signal.help(argv[0]);
				return 0;
			}

			switch(argv[i][1])
			{
			case 'n': {
				if(i+1 < argc)
				{
					filenumber = atoi(argv[i+1]);
					sprintf(filename, "Raw_data_%02d.txt", filenumber);
				}
				break;
			}

			case 'o': {
				if(i+1 < argc)
				{
					offset =strtod(argv[i+1], NULL);
					offsetFlag=1;
				}
				break;
			}
			case 's': {
				if(i+1 < argc)
				{
					scaling = atof(argv[i+1]);
					scalingFlag=1;
				}
				break;
			}
			case 'S': { Statistic = 1;
			break; }
			case 'C': { center = 1;
			break; }
			case 'N': { normalize = 1;
			break; }
			case 'r': {
				if(i+1 < argc)
				{
					rename = argv[i+1];
					renameFlag=1;
				}
				break;
			}
			}
		}
	}

	if(filenumber <= 0)
	{
		printf("Need more arguments\n");
		signal.help(argv[0]);
		return 0;
	}

	if(rename != NULL)
	{
		sprintf(outname, "%s.txt", rename);
	}

	signal(filenumber);

	//// Open file and populatint i;
	for(i=0; i<size; i++)
	{
		newdata[i] = ((int)data[i] - average);
	}
	if(rename == NULL)
	{
		sprintf(outname, "Centered_data_%02d.txt", filenumber);
	}
	else
	{
		sprintf(outname, "%s_Centered_%02d.txt", rename,filenumber);
	}
	writefilee global array
	sprintf(filename, "Raw_data_%02d.txt", filenumber);
	printf("Input file is: %s\n", filename);

	size = signal(filename);           //determine the size of number in the file
	if(size<0 ) { return 0; }
	int *cfPtr = (int*)malloc(1000*sizeof(int));      //store file data from data pointer to data
	*cfPtr=data[0];


	// Offset
	if(offsetFlag == 1)
	{
		signal.offset_function(offset);
	}




	// Scaling
	if(scalingFlag == 1)
	{
		printf("Scaling value: %lf\n", scaling);
		int i=0;
		for(i=0; i<size; i++)
		{
			newdata[i] = data[i]*scaling;
		}
		if(rename == NULL)
		{
			sprintf(outname, "Scaled_data_%02d.txt", filenumber);
		}
		else
		{
			sprintf(outname, "%s_Scaled_%02d.txt", rename,filenumber);
		}
		writefile(outname, size, scaling);
	}

	double average = mean(cfPtr, size);
	int maximum = max(cfPtr, size);// Find mean and max


	// Center the data
	if(center)
	{
		signal.center_f();
	}

	// normalize the data
	if(normalize)
	{
		signal.normalize_function(scaling);
	}

	if(Statistic)
	{
		if(rename == NULL)
		{
			sprintf(outname, "Statistics_data_%02d.txt", filenumber);
		}
		else
		{
			sprintf(outname, "%s_Statistics_%02d.txt", rename,filenumber);
		}
		printf("Writing file %s\n", outname);


		// Find mean and max and write them to a file
		//		int *cfPtr = data;
		//		double average = mean(cfPtr, size);
		//		int maximum = max(cfPtr, size);
		//		FILE *fp2 = fopen(outname, "w");

		if(fp2 != NULL)
		{
			fprintf(fp2, "%.4lf, %02d", average, maximum);
		}
		fclose(fp2);
	}

	// Check if -r option is passed by itself.
	// In that case copy the original file
	if(renameFlag==1)
	{
		FILE *fp1, *fp2;
		char buf[1000];

		sprintf(outname, "%s.txt", rename);
		printf("Copying file %s to %s\n", filename, outname);
		fp1=fopen(filename, "r");
		fp2=fopen(outname, "w");
		if(fp2 != NULL && fp1 != NULL)
		{
			while(fgets(buf, 1000, fp1))
			{
				fprintf(fp2, "%s", buf);
			}
		}
		fclose(fp2);
		fclose(fp1);
	}
	return 0;
}

