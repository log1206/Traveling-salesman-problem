#include <bits/stdc++.h> // all library (੭ु´･ω･`)੭ु⁾⁾


using namespace std;

// input size n 5-15
//cost range 1-99


int** graph; //graph for city relationship
int n;  //n city
 
// assumption: every time start at zero

int final_cost = INT_MAX;
int *final_path_f_BB;
/* we know that brute force is to try every possible path
so we can calculate every path's cost  and find which is the smallest*/

void TSP_brute(){   

    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();

    
    vector<int> path; //path for this round 
    for(int i=1; i <n ;i++){    //initialization: load every node to path except first node 0
            path.push_back(i);
    }
    int cost =INT_MAX; //initial biggest number to minimum cost
    vector<int> final_path;
    do{
                
        int node =0; //head = 0 in array
        int cur_cost = 0; // current path cost
        for(int i=0;i < path.size();i++){
            cur_cost += graph[node][path[i]];
            node = path[i];
        }
        cur_cost += graph[node][0]; // add the cost of last node to head
        if(cost > cur_cost){
            final_path = path;  //maybe has problem
            cost =cur_cost;
        }
    }
    while(next_permutation(path.begin(),path.end()));

    // calculate time
    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    diff /= 1000000;

    // save to file
    fstream file;
    file.open("BF.txt",ios::out);
    file << "Cost     : "<< cost << endl;
    file << "Solution : 0 - ";
    for(int i=0;i<final_path.size();i++){
        file << final_path[i] <<" - ";
    }
    file << "0" << endl;
    file << "Time     : " << setprecision(6)<<diff<< endl;
    file.close();
}


void TSP_BB_lev(int cur_bound, int cur_weight, int level, int cur_path[], bool visited[]){

    if (level==n) //if is final point
	{ 
		if (graph[cur_path[level-1]][cur_path[0]] != -1) //last node to head
		{ 
			// cur_res has the total weight of the 
			// solution we got 
			int cur_cost = cur_weight + graph[cur_path[level-1]][cur_path[0]]; 

			// Update final result and final path if 
			// current result is better. 
			if (cur_cost < final_cost) 
			{ 
				for (int i=0; i<n; i++) //put path to final path
		            final_path_f_BB[i] = cur_path[i]; 
	            final_path_f_BB[n] = cur_path[0]; 
				final_cost = cur_cost; 
			} 
		} 
		return; 
	}

    for (int i=0; i<n; i++) 
	{ 
		if (graph[cur_path[level-1]][i] != 0 && visited[i] == false) //see next node not visited and not itself 
		{ 
			int temp = cur_bound; 
			cur_weight += graph[cur_path[level-1]][i]; 

			
		//	if (level==1)  //if this computatuon is level 2
		//	cur_bound -= ((firstMin(curr_path[level-1]) + 
		//					firstMin(i))/2); 
		//	else
		//	cur_bound -= ((secondMin(adj, curr_path[level-1]) + 
		//					firstMin(adj, i))/2); 

			// curr_bound + curr_weight is the actual lower bound 
			// for the node that we have arrived on 
			// If current lower bound < final_res, we need to explore 
			// the node further 
			if (cur_bound + cur_weight < final_cost) 
			{ 
				cur_path[level] = i; 
				visited[i] = true; 

				// call TSPRec for the next level 
		//		TSPRec(adj, cur_bound, cur_weight, level+1,cur_path); 
			} 

			// Else we have to prune the node by resetting 
			// all changes to curr_weight and curr_bound 
			cur_weight -= graph[cur_path[level-1]][i]; 
			cur_bound = temp; 

		} 
	}




}
void TSP_BB(){



    int cur_path[n+1]; //for record the path to current 
    bool visited[n]; //for record the node which is visited
	int cur_bound = 0; //lower bound
    int graph_f_BB[n][n];
    final_path_f_BB = new int(n+1);
	memset(cur_path, -1, sizeof(cur_path)); 
	memset(visited, 0, sizeof(cur_path)); 
    std::chrono::steady_clock::time_point t1 = std::chrono::steady_clock::now();
	
    for(int i=0;i<n;i++)    //copy global graph to local graph for after substract
        for(int j=0;j<n;j++)
            graph_f_BB[i][j] = graph[i][j]; 
    
    // Compute initial bound 
	for (int i=0; i<n; i++) 
	//	cur_bound += firstMin(i); 
	
	visited[0] = true; // first node visited 
	cur_path[0] = 0; //current path only first node

	
	TSP_BB_lev(cur_bound, 0, 1, cur_path, visited); 

    std::chrono::steady_clock::time_point t2 = std::chrono::steady_clock::now();
    double diff = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    diff /= 1000000;

    cout.setf(ios::fixed);
    // write the answer to BF.txt
    cout << setprecision(6)<<diff<< endl;
    fstream file;

    file.open("BB.txt",ios::out);
    file << "Cost     : "<< final_cost << endl;
    file << "Solution : 0 - ";
    for(int i=0;i<n;i++){
        file << final_path_f_BB[i] <<" - ";
    }
    file << "0" << endl;
    file << "Time     : " << setprecision(6)<<diff<< endl;
    file.close();
}


    

void readFile(){
 
    fstream file; 
    file.open("input.txt",ios::in);
    file >> n;  //n for city number
    graph = new int*[n];
    for(int i = 0; i < n; ++i)  //initial each line
        graph[i] = new int[n];

    for(int i=0; i<n;i++)      //input each line
        for(int j=0;j<n;j++)
            file >> graph[i][j];
    file.close();
}



int main(void){

    readFile();

    /*
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++){
            cout << graph[i][j] <<" ";
        }
        cout << endl;
    }
    cout << n<< endl;
    */
    


    TSP_brute();



    system("pause");

    return 0;
}

