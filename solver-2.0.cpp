#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstring>
#include <stdlib.h>
using namespace std;

int candidates[9][9][10]={0};
int problem[9][9];
void display();
void displaytf();
bool check(int r,int c,int num);
bool solve();

int main(){
	int i,j,k,x,y;
	time_t start,finish;
	char data[81];
	gets(data);
		
		cout<<data<<endl;
		for(i=0,x=0,y=0;i<81;i++,y++)
			{
				if(y==9){x++;y=0;}
				
				if(data[i]=='.') {problem[x][y]=0;candidates[x][y][0]=1;}
				else {problem[x][y] = data[i]-48;candidates[x][y][0]=0;}				
			}
		display();
		start= clock();

		for(i=0;i<9;i++)
			for(j=0;j<9;j++)
			{
				if(problem[i][j]==0)
				{
						for(k=0;k<9;k++)
						{
							if(problem[i][k]!=0) {candidates[i][j][0]++;candidates[i][j][problem[i][k]]=1;} //removeCandidate(i,j,problem[i][k]);
							if(problem[k][j]!=0) {candidates[i][j][0]++;candidates[i][j][problem[k][j]]=1;} //removeCandidate(i,j,problem[k][j]);
						}
						for(x=(i/3)*3;x<(i/3)*3+3;x++)
							for(y=(j/3)*3;y<(j/3)*3+3;y++)
								if(problem[x][y]!=0) {candidates[i][j][0]++;candidates[i][j][problem[x][y]]=1;}
				}
			}

		cout<<"\n\n";

		if(solve())
			{
				finish = clock();
				display();
			}
		else
			cout<<"CANNOT SOLVE!!!";
	
				
		cout<<endl<<"time : "<<(long double)(finish-start)/CLOCKS_PER_SEC;	
	return 0; 
}

void display(){
	int i,j;

	cout<<"\n\n";
	
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			cout<<problem[i][j]<<" ";
			if(((j+1)%3==0)&&j<8)
				cout<<"| ";
		}
		cout<<endl;
		if(((i+1)%3==0)&&i<8)
			cout<<"- - - + - - - + - - -\n";
	}
	
	cout<<"\n\n";
}
bool solve(){
	int max=0,r=0,c=0,i,j;

	for(i=0;i<9;i++)
		for(j=0;j<9;j++)
			if(candidates[i][j][0]>max)
				{
					max=candidates[i][j][0];
					r=i;c=j;
				}
	if(max==0) return true;

	candidates[r][c][0]-=1000;

		for(int num=1;num<=9;num++)
		{
			if(candidates[r][c][num]==1)continue;
			if(check(r,c,num))
			{
 				problem[r][c]=num;
				if(solve())
					return true;
				problem[r][c]=0;		// This triggers BackTracking
			}
		}
		candidates[r][c][0]+=1000;
		return false;	// Reverting Back in case of Failure 
	}
bool check(int row,int col,int num)
	{
		int r,c,chk,x,y;
		for(chk=0;chk<9;chk++)
			if(problem[row][chk]==num || problem[chk][col]==num)
				return false;
		

		for(x=(row/3)*3;x<(row/3)*3+3;x++)
			for(y=(col/3)*3;y<(col/3)*3+3;y++)
					if(problem[x][y]==num) 
						return false;
		return true;
	}
void displaytf(){
	int i,j;

	cout<<"\n\n";
	
	for(i=0;i<9;i++)
	{
		for(j=0;j<9;j++)
		{
			cout<<candidates[i][j][0]<<" ";
			if(((j+1)%3==0)&&j<8)
				cout<<"| ";
		}
		cout<<endl;
		if(((i+1)%3==0)&&i<8)
			cout<<"- - - + - - - + - - -\n";
	}
	
	cout<<"\n\n";
}
/*void removeCandidate(int i,int j, int val){
	vector<int>::iterator it=candidates[i][j].begin();
	 it=find(candidates[i][j].begin(),candidates[i][j].end(),val);
	
	//int pos = it - candidates[i][j].begin();
 	int pos = distance (candidates[i][j].begin (), it);
	candidates[i][j].erase(candidates[i][j].begin()+pos);
}*/
	/*int problem[9][9]=	   {{0,0,0,7,0,0,0,0,0},
						{1,0,0,0,0,0,0,0,0},
						{0,0,0,4,3,0,2,0,0},
						{0,0,0,0,0,0,0,0,6},
						{0,0,0,5,0,9,0,0,0},
						{0,0,0,0,0,0,4,1,8},
						{0,0,0,0,8,1,0,0,0},
						{0,0,2,0,0,0,0,5,0},
						{0,4,0,0,0,0,3,0,0}};*/
/*int problem[9][9]=  {
	{4,0,0,0,0,0,8,0,5},
	{0,3,0,0,0,0,0,0,0},
	{0,0,0,7,0,0,0,0,0},
	{0,2,0,0,0,0,0,6,0},
	{0,0,0,0,8,0,4,0,0},
	{0,0,0,0,1,0,0,0,0},
	{0,0,0,6,0,3,0,7,0},
	{5,0,0,2,0,0,0,0,0},
	{1,0,4,0,0,0,0,0,0},};*/
/*int problem[9][9]=  {
	{0,6,0,1,0,4,0,0,5},
	{0,0,8,3,0,5,6,0,0},
	{2,0,0,0,0,0,0,0,1},
	{8,0,0,4,0,7,0,0,6},
	{0,0,6,0,0,0,3,0,0},
	{7,0,0,9,0,1,0,0,4},
	{5,0,0,0,0,0,0,0,2},
	{0,0,7,2,0,6,9,0,0},
	{0,4,0,5,0,8,0,7,0},
};*/
