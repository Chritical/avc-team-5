/*Program for tuning line detection ENGR101*/
/* A. Roberts, April 2018*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define CAMERA_WIDTH 320 //Control Resolution from Camera
#define CAMERA_HEIGHT 240 //Control Resolution from Camera
unsigned char pixels_buf[CAMERA_WIDTH*CAMERA_HEIGHT*4];

// returns color component (color==0 -red,color==1-green,color==2-blue
// color == 3 - luminocity
// for pixel located at (row,column)
unsigned char get_pixel( int row,int col, int color)
{
    // calculate address in 1D array of pixels
    int address = CAMERA_WIDTH*row*3 + col*3;
    if ((row < 0 ) || (row > CAMERA_HEIGHT) )
    {
        printf("row is out of range\n");
        return -1;
    }
    if ( (col< 0) || (col > CAMERA_WIDTH))
    {
        printf("column is out of range\n");
        return -1;
    }

    if (color==0)
    {
        return (pixels_buf[address]);
    }
    if (color==1)
    {
        return (pixels_buf[address + 1]);
    }
    if (color==2)
    {
        return (pixels_buf[address + 2]);
    }
    if (color==3)
    {
        unsigned char y = (pixels_buf[address] + pixels_buf[address+1] +pixels_buf[address+2])/3;
        return y;
    }
    printf("Color encoding wrong: 0-red, 1-green,2-blue,3 - luminosity\n");
    return -2; //error
}



int ReadPPM(const char *filename)
{
  //char buff[16];
  FILE *fp=fopen(filename, "rb");
   if (!fp) {
     printf("Unable to open file '%s'\n", filename);
     return -1;
  }
  // read the header
  char ch;
  if ( fscanf(fp,"P%c\n",&ch) != 1 || ch != '6')
  {
	  printf("file is wrong format\n");
	  return -2;
  }
  // skip comments
  ch = getc(fp);
  while(ch == '#')
  {
	  do {
		  ch = getc(fp);
	  } while (ch != '\n');
	  ch = getc(fp);
  }
 
   if (!isdigit(ch))  printf("Wrong header\n");
   ungetc(ch,fp);  
  //read width,height and max color value
  int width, height, maxval;
  int res = fscanf(fp,"%d%d%d\n",&width,&height,&maxval);
  printf("Open file: width=%d height=%d\n",width,height);
  
  //Image *image = (Image *)calloc(1,sizeof(Image));
  //if (!image) {
  //   printf( "Unable to allocate memory\n");
 // }
  int size = width*height*3;
 // image->data = malloc(size);
 // image->width = width;
 // image->height = height;
  
  int num =fread((void*) pixels_buf, 1,size,fp);
  if (num!=size) {
	printf("can not allocate image data memory: file=%s num=%d size=%d\n",
	filename,num,size);
	return -3;
   }
  
  fclose(fp);
  return 0;

} 

int main()
{
	// enter image file name
	char file_name[7];
	printf(" Enter image file name(with extension:\n");
	scanf("%s",file_name);
	printf(" You enter:%s\n",file_name);
	// read image file
	if (ReadPPM(file_name) != 0)
	{
		printf(" Can not open file\n");
		return -1;
	};
	
	
	// save horizontal scan of the image into text file
	FILE *scfile;
	scfile = fopen("scan.txt","w");
	int scan_row = 100;
	for (int i = 0; i <320;i++)
	{
		int pix = get_pixel(scan_row,i,3);
		printf("i=%d col=%d\n",i,pix);
		fprintf(scfile,"%d %d\n",i,pix);
		
	}
	
	
	fclose(scfile);

     
    int max = 0;
    int min =255;
   	for (int i = 0; i <320;i++)
	{
		int pix = get_pixel(scan_row,i,3);
        if ( pix > max) 
        {
			max = pix;
		}
		if (pix < min)
		{
			min =pix;
		}
		
    } 
	int thr = (max+min)/2;
	printf(" min=%d max=%d threshold=%d\n", min, max,thr);
	
	int numWhite = 0;
	int whi[320];  // white pixels
	for (int i = 0; i <320;i++)
	{
		whi[i]= 0 ;
		int pix = get_pixel(scan_row,i,3);
		if ( pix > thr)
		{
			whi[i] = 1;
			numWhite++;
		}
	}
	
	
	for (int i = 0; i <320;i++)
	{
		printf("%d ",whi[i]);
	}
	printf("\n\n");
	
	
	
	
	
	
	int error = 0;

	
		for (int i = 0; i<320; i++)
		{
			error = error+((i-160)/numWhite)*whi[i];
		}
		
		    if (max<150){ // if all black
				error = -10000;
			} else if (min>150){ //if all white
				error = 10000;
			}
		
		printf("\n\n");
		printf("numWhite: %d \n", numWhite);
		printf(" error: %d \n\n", error);
		
		
		for (int i = 0; i <320;i++)
		{
			printf("%d ",whi[i]);
		}
		
	return 0;
}
 

