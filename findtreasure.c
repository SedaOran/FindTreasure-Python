#include <stdio.h>
#include <stdlib.h>
void FindKey (int **arr , int keyarray[], int rowofkeymap , int place_of_row ,int place_of_col ){  //func takes as input : 2-D map array ,
                                                                                                    //one dimensional key array , row number of key matrix and two counter
                                                                                                    //for to know place that we go along
    int carpim=0;
    int counter=0;
    int i;
    for(i=0 ; i < rowofkeymap*rowofkeymap ; i++){
        if(counter%rowofkeymap!=0){   // if counter not in last col for multiply mapmatrix index and keymatrix
            carpim+=(arr[place_of_row][place_of_col])*(keyarray[i]);
            place_of_col++;
            counter++;
        }
        else{   // if counter in last col for multiply mapmatrix index and keymatrix
            if(counter==0){
                carpim+=(arr[place_of_row][place_of_col])*(keyarray[i]);
                place_of_col++;
                counter++;
            }
            else{
                place_of_col-=rowofkeymap;
                place_of_row++;
                carpim+=(arr[place_of_row][place_of_col])*(keyarray[i]);
                place_of_col++;
                counter++;
               }
            }
    }
    int w= carpim%5;   // mod of multiplication
    if(w < 0){
        w += 5;
    }
    place_of_row=place_of_row-rowofkeymap+1;
    place_of_col=place_of_col-rowofkeymap;
    if(w==0){   //if 0 , teasure is found
        printf("%d,%d:%d \n",(place_of_row)+(rowofkeymap/2),(place_of_col)+(rowofkeymap/2),carpim);
        return;
    }
    if(w==1){   // if 1 , go up
        printf("%d,%d:%d \n",(place_of_row)+(rowofkeymap/2),(place_of_col)+(rowofkeymap/2),carpim);
        if(arr[place_of_row][place_of_col]==0 && arr[place_of_row][place_of_col+1]==0 && arr[place_of_row][place_of_col+3]==0 ){ // control for bound or not?
            place_of_row+=rowofkeymap;
            FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
        else{
        place_of_row-=rowofkeymap;
        FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
    }
    if(w==2){ // if 2 , go down
        printf("%d,%d:%d \n",(place_of_row)+(rowofkeymap/2),(place_of_col)+(rowofkeymap/2),carpim);
        if(arr[place_of_row+rowofkeymap-1][place_of_col]==0 && arr[place_of_row+rowofkeymap-1][place_of_col+1]==0 && arr[place_of_row+rowofkeymap-1][place_of_col+3]==0 ){ // check for bound or not?
            place_of_row-=rowofkeymap;
            FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
        else{
        place_of_row+=rowofkeymap;
        FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
    }
    if(w==3){  // if 3, go right
        printf("%d,%d:%d \n",(place_of_row)+(rowofkeymap/2),(place_of_col)+(rowofkeymap/2),carpim);
        if(arr[place_of_row][place_of_col+rowofkeymap-1]==0 && arr[place_of_row+1][place_of_col+rowofkeymap-1]==0 && arr[place_of_row+2][place_of_col+rowofkeymap-1]==0 ){ // check for bound or not?
            place_of_col-=rowofkeymap;
            FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }else{
        place_of_col+=rowofkeymap;
        FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
    }
    if(w==4){  // if 4 , go left
        printf("%d,%d:%d \n",(place_of_row)+(rowofkeymap/2),(place_of_col)+(rowofkeymap/2),carpim);
        if(arr[place_of_row][place_of_col]==0 && arr[place_of_row+1][place_of_col]==0 && arr[place_of_row+2][place_of_col]==0 ){  // check for bound or not?
            place_of_col+=rowofkeymap;
            FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
        else{
        place_of_col-=rowofkeymap;
        FindKey(arr,keyarray,rowofkeymap,place_of_row,place_of_col);
        }
    }
}
int main ( int argc, char *argv[] )
{
   int **arr;
    if ( argv[1] == NULL )
    {
        printf( "usage: %s is provided,filename is not provided", argv[0] );
    }
    else
    {

        FILE *file = fopen( argv[3], "r" );  //mapmatrix.txt
        FILE *fileofkey = fopen( argv[4], "r");; //keymatrix.txt
        freopen(argv[5],"w",stdout);  //output.txt  // output.txt
        if ( file == 0 && fileofkey == 0 )
        {
            printf( "Could not open file\n" );
        }
        else{
            char x ,z;
            int row = 1, col = 0, row_key =1;
            int i;
            int d1=0; int d2=0;
            int row_count = 0, column_count = 0;
            sscanf(argv[1], "%dx%d", &row_count, &column_count);   // read row and col count of mapmatrix
            row = row_count;
            col = column_count;
            char *char_ptr;
            int key_size = strtol(argv[2], &char_ptr, 10);   // read row count of keymatrix
            row_key = key_size;

            int keyArr[row_key*row_key];   //array for keymatrix
            rewind(fileofkey);

            int counter =0;
            fscanf(fileofkey,"%d", &d1);
            while(!feof(fileofkey))
            {
                keyArr[counter]=d1;
                fscanf(fileofkey,"%d", &d1);   // reading keymatrix.txt to array
                counter++;
            }
            keyArr[counter]=d1;
            arr  = (int **)malloc(sizeof(int *) * row);
            arr[0] = (int *)malloc(sizeof(int) * col * row);
            for(i = 0; i < row; i++){
                arr[i] = (*arr + col * i);            // 2-D array with malloc for mapmatrix
            }
            rewind(file);

            int a =0;
            int z1 =0;

            int r = 0, c = 0;
            for(r = 0; r < row; r++){
                for(c = 0; c < col; c++){
                    fscanf(file,"%d", &d2);
                    arr[r][c] = d2;
                }
            }
            FindKey(arr,keyArr,row_key,0,0);   // calling void findkey function which find treasure in map matrix

            fclose( file );
            fclose(fileofkey);
            }
        }
         return 0;
}
