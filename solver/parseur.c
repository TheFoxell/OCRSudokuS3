#include <stdio.h>
#include <err.h>
#include <string.h>


void parser(int grid[9][9],const char * filename)
{
	FILE* reader;
	reader =fopen(filename,"r");
	if(reader ==NULL)
		err(1,"parser: le fichier n'existe pas");
	else
	{
		int x;
		int i=0;
		x=fgetc(reader);
		while(!feof(reader))
		{
			if(x==' ' && (i%9==3 || i%9==6))
			{
				x=fgetc(reader);
			}
			else if(x=='\n' && i%9==0)
			{
				x=fgetc(reader);
				if(!feof(reader)&&(x=='\n' && (i/9==3||i/9==6)))
				{
					x=fgetc(reader);
				}
				if(feof(reader) && i==81)
					return;
			}
			if (feof(reader) || x==' ' || x=='\n')
				err(4,"parser: ls fichier pas au bon format");
			
			if(x=='.')
			{
				grid[i/9][i%9]=0;
				i++;
			}
			else if(x>'0' ||x<='9')
			{
				grid[i/9][i%9]=x-(int)'0';
				i++;
			}
			else
				err(4,"parser: le fichier pas au bon format");
			x=fgetc(reader);

		}
		if(i!=81)
			err(4,"parser: le fichier pas au bon format");
	}
	fclose(reader);
}

void recorder(int grid[9][9],const char * filename)
{
	FILE *writer;
	writer = fopen(filename, "w+");
	for(int i=0; i<9;i++)
        {
                for(int j=0; j<9; j++)
		{
                        fprintf(writer,"%i",grid[i][j]);
			if (j==2||j==5)
				fprintf(writer," ");
		}
		fprintf(writer,"\n");
		if (i==2||i==5)
                        fprintf(writer,"\n");
        }
	fclose(writer);
}

/* testeur pour le parser et le recorder
int main(int argc, char *argv[]) 
{
	if (argc!=2)
		err(1,"too many argument");
	int grid[9][9]; 
	parser(grid,argv[1]);
	recorder(grid, strcat(argv[1],".resultat"));
	return 0;
}
*/
