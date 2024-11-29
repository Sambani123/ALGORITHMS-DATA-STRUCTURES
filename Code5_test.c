
#include <stdio.h> 
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define MAX 
typedef struct
{
    char label [6];
    int distance;
    int previous;
    int visited;
}
Vertex;


int CreateAdjacencyMatrix(Vertex Vertexarray[MAX],int argc, char *argv[],int Vertexcount,int AdjMatrix [][MAX])
{
    int start = 0, end = 0;
    int i = 0, j = 0;

    char buffer [MAX]= {};
    int l  = 0;

    strcpy(buffer,argv[1]);
    char *token = NULL;
    FILE *FH;

    FH = fopen(buffer,"r+");

    for(i = 0; i <MAX;i++)
        for(j= 0;j<MAX;j++)
            AdjMatrix[i][j]= -1;
    while (fgets(buffer,sizeof(buffer)-1,FH))
    {
       if (buffer[strlen(buffer)-1]== '\n')
            buffer[strlen(buffer)-1]== '\0';
       
        token = strtok(buffer,",");
        strcpy(Vertexarray[l].label,token);
       
       while (token != NULL)
       {
           AdjMatrix[start][end] = atoi(token);
           token = strtok(buffer,",");
           sscanf(buffer,"%d %d",&start,&end);
           end ++;
           AdjMatrix[start][end]= atoi(token);
           token = strtok(NULL,",");
           sscanf(buffer,"%d %d",&start,&end);
           end++;
       }
       start ++;
       end = 0;

       l++;
    }
    fclose(FH);
    return Vertexcount;
}


void  Dijkstra (int VertexCount,int startvertex,int adjacencyMatrix[MAX][MAX],Vertex Vertexarray[MAX])
{
    int CurrentVertex = startvertex;
    Vertexarray[startvertex].distance = 0;
    Vertexarray[startvertex].previous = -1;
    Vertexarray[startvertex].visited= 1;
    int SmallestVertexIndex;
    int dofv , cofuv,dofu;
    int i ,x;

    for ( x = 0; i < VertexCount; x++)
    {
        for ( i = 0; i < VertexCount; i++)
        {
            if (adjacencyMatrix[CurrentVertex][i]!= -1 && !Vertexarray[i].visited )
            {
                dofu = Vertexarray [CurrentVertex].distance;
                cofuv = adjacencyMatrix[CurrentVertex][i];
                dofv = Vertexarray[i].distance;
            
                if (dofu + cofuv < dofv)
                {
                    dofv = dofu + cofuv;
                    Vertexarray[i].distance = dofv;
                    Vertexarray[i].previous = CurrentVertex;
                 }
            
            }
        }
        SmallestVertexIndex = -1;
        int SmallestVertex = INT_MAX;
        for ( i = 0; i < VertexCount; i++)
        {
         if (!Vertexarray[i].visited)
            {
                if (Vertexarray[i].distance < SmallestVertex)
                {
                    SmallestVertex = Vertexarray[i].distance;
                    SmallestVertexIndex = i;
                }
            
            }
        
        }
        CurrentVertex = SmallestVertexIndex;
        Vertexarray[CurrentVertex].visited = 1;
        
    }
    

}

int main (int argc , char *argv[])
{
    int AdjacencyMatrix[MAX][MAX] = {};
    char StartingVertex[MAX]= {};
    char dest [MAX]= {};
    int destindex = -1;
    int VertexCount = 0;
    Vertex Vertexarray[MAX] = {};
    char path [MAX]= {};
    int startindex = 0;
    
    VertexCount = CreateAdjacencyMatrix(Vertexarray,argc,argv,VertexCount,AdjacencyMatrix);
    int i ,j;
    #ifdef PRINTIT
    printf("\n");
    for (i = 0; i < VertexCount; i++)
    {
        for ( j = 0; i < VertexCount; j++)
        {
            printf("%5d\t",AdjacencyMatrix[i][j]);
        printf("\n");
        }
        
    }
    #endif

    printf("What is the starting vertex? ");
    scanf("%s",&StartingVertex);

    #ifdef PRINTIT
    printf("\n\nI\tL\tD\tP\tV\n");
    for ( i = 0; i <VertexCount; i++)
    {
        printf("%d\t%s\t%d\t%d\t%d\n",i,Vertexarray[i].label,Vertexarray[i].distance,Vertexarray[i].previous,Vertexarray[i].visited);
    }
    #endif

    printf("What is the destination? ",Vertexarray[0].label);
    scanf("%s",&dest);
    Dijkstra(VertexCount,startindex,AdjacencyMatrix,Vertexarray);
    destindex = 0;
    while (destindex < VertexCount && dest != Vertexarray[destindex].label)
    {
        destindex++;
    }

    int pathindex = -1;
    destindex = -1;
    int previndex = -1;

    pathindex= Vertexarray[destindex].distance;
    previndex = Vertexarray[destindex].previous;
    path[pathindex]= Vertexarray[destindex].label;

    while (pathindex > 0)
    {
        pathindex --;
        path[pathindex]= Vertexarray[previndex].label;
        previndex = Vertexarray[previndex].previous;
    }
    printf("The path from %c to %c is ",&StartingVertex,&dest);
}
