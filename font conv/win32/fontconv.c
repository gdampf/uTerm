#include "fontconv.h"

// cheap replacement for PathCchRemoveExtension()
void RemoveExtension(char *filename)
{
  char *ext;
  int len;

  len=strlen(filename);

  if(len>2)
  {
    ext=strchr(&filename[len-2],'.');

    if(ext)
      *ext=0;
   }
}

void fprint_bitmap(FILE *outfile,uint32_t n, int width)
{
  int i;

  fprintf(outfile,(width==8)?"  BIN8(":(width==16)?"  BIN16(":"  BIN32(");

  for(i=0;width;)
  {
    fputc((n & (1<<(--width)))?'1':'0',outfile);

    if(width)
      fputc(',',outfile);
  }

  fprintf(outfile,");\n");

}

void processfont(FILE *infile, FILE *outfile1, FILE *outfile2)
{
  char LineBuf[LINE_SIZE+1],FontName[33],*DataType="",*match_loc,*data;
  uint32_t CharBitmap[FONT_YMAX];
  int x, y, rows=8, datasize=8, i, j, k, byte, bitmap;

  while(!feof(infile))
  {
    if(!fgets(LineBuf, sizeof(LineBuf), infile))
      break;

    if((LineBuf[0]==0)||(LineBuf[0]=='\n'))
      fprintf(outfile1,LineBuf);
    else if(!strncmp(LineBuf,C_COMMENT,C_COMMENT_LEN))
    {
      *strchr(LineBuf,'\n')=0;

      if((match_loc=strstr(LineBuf,FONTNAME)))
      {
        strncpy(FontName,&match_loc[PARM_START],sizeof(FontName)-1);
        FontName[sizeof(FontName)-1]=0;

        //fprintf(outfile1,"* fontname: %s\n",FontName);
        fprintf(outfile1,"%s\n",LineBuf);
      }
      else if((match_loc=strstr(LineBuf,FONTSIZE)))
      {
        sscanf(&match_loc[PARM_START],"%d x %d",&x, &y);

        datasize=(x<=8)?8:(x<=16)?16:32;
        rows=(y<=8)?8:FONT_YMAX;

	DataType = (datasize==8)?"uint8_t":(datasize==16)?"uint16_t":"uint32_t";

        //fprintf(outfile1,"* width:%d height %d bits:%d rows:%d\n",x,y,datasize,rows);
        fprintf(outfile1,"%s\n",LineBuf);
      }
      else if(strstr(LineBuf,WARNING))
      { fprintf(outfile1,"// Converted by fontconv V0.0 by K. C. Lee.\n");

        if(!fgets(LineBuf, sizeof(LineBuf), infile))
          break;
      }
      else
        fprintf(outfile1,"%s\n",LineBuf);
    }
    else
    {
      if(strstr(LineBuf,FONTDECL))
      {
        fprintf(outfile1,"const %s %s[] = \n{\n",DataType,FontName);
      }
      else if(strstr(LineBuf,DECL_END))
        fprintf(outfile1,"};\n");
      else
      {
        for(i=0;i<FONT_YMAX;i++)
          CharBitmap[i]=0;

	i= j= 0;

        while(1)
        {
	  bitmap=0;

	  do
          { 
	    do
	    {
              data=strtok(i?NULL:LineBuf,TOKEN);
	      i++;
             } while((rows==16)&&(i==1));

            if(!strcmp(data,C_COMMENT))
              goto exit_readloop;

	    sscanf(data,"0x%x",&byte);

            if((rows==16)&&(i&0x01))
              bitmap |= byte <<8;
            else
              bitmap = byte;

           } while((rows==16)&&!(i&0x01));

           // rotate bitmap
          for(k=0;k<=y;k++)
            CharBitmap[k]|= (bitmap&(1<<k))?(1<<(datasize-1-j)):0;
    
          j++;
	}

exit_readloop:

        data=strtok(NULL,TOKEN_COMMENT);
        fprintf(outfile1,"  // %s\n",data);

#ifdef OUTPUT_BIN

        for(i=0;i<rows;i++)
          fprint_bitmap(outfile1,CharBitmap[i],datasize);
#else
        fprintf(outfile1,"  ");

        for(i=0;i<rows;i++)
          fprintf(outfile1,(datasize==8)?"0x%02x,":(datasize==16)?"0x%04x,":"0x%08x,",CharBitmap[i]);

        fprintf(outfile1,"\n");

#endif

      }
    }

   }

  fprintf(outfile2,"#ifndef _FONT_%s_\n#define _FONT_%s_\n\n",FontName,FontName);
  fprintf(outfile2,"typedef %s FONT_%s_t;\n",DataType,FontName);
  fprintf(outfile2,"\n// Original size\n");
  fprintf(outfile2,"#define FONT_%s_X %d\n#define FONT_%s_Y %d\n",FontName,x,FontName,y);
  fprintf(outfile2,"\n// Padded size\n");
  fprintf(outfile2,"#define FONT_%s_ROW %d\n#define FONT_%s_COL %d\n\n",FontName,rows,FontName,datasize);

#ifdef OUTPUT_BIN
  fprintf(outfile2,"#define BIN8(B7,B6,B5,B4,B3,B2,B1,B0) \\\n");
  fprintf(outfile2,"((B7?0x80:0)|(B6?0x40:0)|(B5?0x20:0)|(B4?0x10:0)|\\\n");
  fprintf(outfile2,"(B3?0x08:0)|(B2?0x04:0)|(B1?0x02:0)|(B0?0x01:0))\n\n");

  fprintf(outfile2,"#define BIN16(B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0) \\\n");
  fprintf(outfile2,"  ((BIN8(B15,B14,B13,B12,B11,B10,B9,B8)<<8)|BIN8(B7,B6,B5,B4,B3,B2,B1,B0))\n\n");

  fprintf(outfile2,"#define BIN32(B31,B30,B29,B28,B27,B26,B25,B24,B23,B22,B21,B20,B19,B18,B17,B16\\\n");
  fprintf(outfile2,"B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0)\\\n");
  fprintf(outfile2,"  ((BIN16(B31,B30,B29,B28,B27,B26,B25,B24,B23,B22,B21,B20,B19,B18,B17,B16)<<16)|\\\n");
  fprintf(outfile2,"    BIN16(B15,B14,B13,B12,B11,B10,B9,B8,B7,B6,B5,B4,B3,B2,B1,B0))\n\n");
#endif

  fprintf(outfile2,"#endif\n\n");

}

int main( int argc, char *argv[])
{
  FILE *infile, *outfile1, *outfile2;

  char outfilename[MAX_PATH+3];
  int ext;

  if((argc!=3))
  { printf("%s <infile> <outfile>\n",argv[0]);
    return(1);
   }

  infile = fopen(argv[1],"r");
  strncpy(outfilename,argv[2],sizeof(outfilename)); 

  RemoveExtension(outfilename);
  ext=strlen(outfilename);

  strncpy(&outfilename[ext],".c",sizeof(outfilename));
  outfile1= fopen(outfilename,"w");
  strncpy(&outfilename[ext],".h",sizeof(outfilename));
  outfile2= fopen(outfilename,"w");

  if(infile && outfile1 && outfile2)
  {
    fprintf(outfile1,"#include <stdint.h>\n#include \"%s\"\n",outfilename);
    processfont(infile,outfile1,outfile2);
  }
  else
  {
    printf("Cannot open file(s) %s %s.c or %s.h\n",argv[2],outfilename,outfilename);
  }

  if(infile)
    fclose(infile);
  if(outfile1)
    fclose(outfile1);
  if(outfile2)
    fclose(outfile2);

  exit(0);
 }
