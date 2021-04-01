#include <iostream>
#include <fstream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include <queue>


#define mp make_pair
#define pb(X) push_back(X)
#define PT pair<int,int>

using namespace std;

typedef struct path_{
	int start_i, start_j;
	int length;
}
path;



//Depth First Search (DFS)
void DepthFirstSearch(int x, int y, vector<string> &labyMap, vector<vector<int> > &visited, vector<string> &v, char &count)
{
	for(int k = x-1;k <= x+1;k++)
	{
	for(int l = y-1;l <= y+1;l++)
	{
		if((k==x-1 && l==y-1) || (k == x-1 && l == y+1) || (k == x+1 && l == y+1) || (k == x+1 && l == y-1))
			continue; 
	    if(k >= 0 && k < labyMap.size() &&  l >=0  && l < labyMap[0].length() &&  labyMap[k][l] == '.' && visited[k][l] == 0) 
	    {
            visited[k][l] = 1;
            v[k].replace(l,1,1,count);
			count++;
            DepthFirstSearch(k,l,labyMap,visited,v,count);
        }
		
		}
	}    	
}


//compare function for std::sort function 
bool cmpr(path a, path b) { return a.length < b.length; }


void laby(string inpt, int count)
{   
    // output file creation
    string outpt = "output" + to_string(count) + ".txt";
    if (std::ifstream(outpt))
    {
        std::cout << "File already exists" << std::endl;
        
    }
    std::ofstream file_out(outpt);
    if (!file_out)
    {
        std::cout << "File could not be created" << std::endl;
        
    }

	ifstream file(inpt + ".txt");	
	string b;
	vector<string> matrix;
	while(std::getline(file, b))
	{
		matrix.pb(b);
	}
	vector<string> final(matrix);
	int id = 1, i,j,k,l, row = matrix.size(), column = matrix[0].length();
	vector<path> paths;
	vector<vector<int> > visited(row,vector<int>(column,0));
	
    //Breadth First Search, hence queue
	queue<PT> open_list;  
	stack<PT> open_stack;
    
	//through BFS
	for(i = 0; i < row ; i++)
	{
	for(j = 0 ; j < column; j++)
		{
		if(matrix[i][j]=='#'||visited[i][j]>0)
			continue;
		open_list.push(mp(i,j));
		int len = 0;
		while(!open_list.empty())
			{
		    PT top = open_list.front();
			open_list.pop();
			visited[top.first][top.second] = id;
			len++;
			for(k=top.first-1;k<=top.first+1;k++)
				{
				for(l=top.second-1;l<=top.second+1;l++)
					{
					if((k==top.first-1&&l==top.second-1)||(k==top.first-1&&l==top.second+1)||(k==top.first+1&&l==top.second+1)||(k==top.first+1&&l==top.second-1))
						continue; 
					if(k<0||l<0||k>row-1||l>column-1)
						continue;
					if(matrix[k][l]=='#'||visited[k][l]>0)
						continue;
					PT next = mp(k,l);
					visited[k][l] = id;
					open_list.push(next);
					}
				}
			}
		path nextpath = {i,j,len};
		paths.pb(nextpath);
		id++;
		}
	}
	std::sort(paths.begin(),paths.end(),cmpr);

	//converting the visited array to zeroes again
	for(i=0;i<row;i++)
		for(j=0;j<column;j++)
			visited[i][j]=0;
	char cnt = '0';

	open_stack.push(mp(paths[paths.size()-1].start_i,paths[paths.size()-1].start_j));
	final[paths[paths.size()-1].start_i].replace(paths[paths.size()-1].start_j,1,1,cnt);	

	//using DFS with only the path with maximum length	
	DepthFirstSearch (paths[paths.size()-1].start_i,paths[paths.size()-1].start_j, matrix, visited, final,cnt);

	//displaying Path Length
    cout << "Path Length: ";
	cout << cnt << endl;

	for(i = 0;i < row; i++)
		{
		for(j = 0; j < column; j++)
			{
			cout << final[i][j];
            if (file_out.is_open())
                file_out << final[i][j];
        	}
			cout << endl;
            file_out << std::endl;
            
		}
	file_out.close();
}



int main()
{
    int count = 0;
    string inpt = "";
    while(inpt != "cancel")
    {
        cout << "Type the txt file name or write 'cancel' to quit : ";
        cin >> inpt; // Get user input from the keyboard
        if (inpt == "cancel")
            break;
        else
            count += 1;
            laby(inpt, count);
    }
    
    
}