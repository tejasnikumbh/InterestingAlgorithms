/*
 * File : dynamicKnapsack.cpp
 *-------------------------------------------------------------------------
 * This program is a c++ implementation for the binary knapsack problem.
 * The problem statement is as follows : You are given a series of objects,
 * x0 to xN with weights w0 to wN and values v0 to vN. Given a limit of
 * W, you have to decide which objects can you select such that the total
 * weight of these objects does not exceed W and their value is maximum.
 * The solution to the problem is evaluating the maximum value.
 */

/* Including standard libraries */
#include <vector>
#include <iostream>
#include <string>
using namespace std;

/* Constants and type definitions*/
  //Limit of the knapsack problem
  const int W = 15;
  //Total no of objects.
  const int N = 5;

/* Function prototypes */
  int optimizeAndProduce(const vector<int>& weights,const vector<int>& values);
  void presentSolution(const int& maxValue);
  int max(const int& n1,const int& n2);

/* Main program */
  int main(){

    // #Tutorial Aspect. Displaying the current status of the program.[Introduction]
    cout<<"=====================================Welcome!==================================="<<endl;
    cout<<"...Introduction..."<<endl;
    cout<<"Welcome! This is a demonstration cum implementation of the dynamic algorithm for the knapsack problem"<<endl<<endl;

    // #Tutorial Aspect. Displaying the current status of the program.[Variable Initialization]
    cout<<"...Variable Initialization..."<<endl<<"Here, we initialize the input variables for the test case"<<endl<<"...Done..."<<endl<<endl;

    //Initialize the input variables.

    //Initializing the weights array.
    vector<int> weights(5);
    weights[0]=1;weights[1]=1;weights[2]=2;weights[3]=4;weights[4]=12;

    //Initializing the values array.
    vector<int> values(5);
    values[0]=1;values[1]=2;values[2]=2;values[3]=10;values[4]=4;

    // #Tutorial Aspect. Displaying the current status of the program.[Displaying variable values]
    cout<<"...Variable Status..."<<endl<<"Here, we display the varriable values that have been initialized..."<<endl;
    //Weight and value pairs
    cout<<"No of weight value pairs : "<<N<<endl;
    cout<<"...Weight and Value pairs..."<<endl;
    cout<<"{Weight : "<<weights[0]<<",Value : "<<values[0]<<"}"<<" , "<<endl;
    cout<<"{Weight : "<<weights[1]<<",Value : "<<values[1]<<"}"<<" , "<<endl;
    cout<<"{Weight : "<<weights[2]<<",Value : "<<values[2]<<"}"<<" , "<<endl;
    cout<<"{Weight : "<<weights[3]<<",Value : "<<values[3]<<"}"<<" , "<<endl;
    cout<<"{Weight : "<<weights[4]<<",Value : "<<values[4]<<"}"<<endl;

    //Limit of the knapsack problem
    cout<<"Weight limit : "<<W<<endl<<endl;

    // #Tutorial Aspect. Displaying the current status of the program.[Displaying variable values]
    cout<<"...Dynamic Optimization started..."<<endl;

    //Run the dynamic algorithm to produce the optimum value in the knapsack.
    int maxValue = optimizeAndProduce(weights,values);

    // #Tutorial Aspect. Displaying the current status of the program.[Final Solution]
    cout<<"...Final Solution..."<<endl;

    //Presenting the user with the final solution
    presentSolution(maxValue);
    cout<<endl<<"=======================Hope you enjoyed the project!============================"<<endl;
    return 0;
  }

/*
 * Function : optimizeAndProduce(weights,vals)
 * ---------------------------------------------------------------------------------
 * This function performs the dynamic optimization procedure on the given test case
 */

  int optimizeAndProduce(const vector<int>& weights,const vector<int>& values){
    // #Tutorial Aspect. Displaying the current status of the program.[Process Description]
    cout<<"...Process Description..."<<endl;
    cout<<"We begin by creating a table of dimension (N+1) X (W+1). Here it means 6X16 An entry m[i,j]";
    cout<<"in this table indicates the maximum value that can be stored in the knapsack when limit is j";
    cout<<"and the items that can be used are the first i items[which are sorted according to weights in";
    cout<<"the weights array]"<<endl<<endl;

    //Declaration of the table of maxVals
    vector<vector<int> > maxVals(weights.size()+1);

    // #Tutorial Aspect. Displaying the current status of the program.[Initialization]
    cout<<"...Initializing the first row of the table to be 0..."<<endl;
    cout<<"We need to initialize the first row of this table[i=0] to be 0, since if no object can be taken";
    cout<<"maximum value in the rucksack is always 0"<<endl<<endl;

    //Initializing the first row of the table to be 0
    for(int i=0;i<=W;i++){
        maxVals[0].push_back(0);
    }

    //Initializing the rest of the table to be 0 for default values.
    for(int j=1;j<=N;j++){
      for(int i=0;i<=W;i++){
        maxVals[j].push_back(0);
      }
    }

    //#Tutorial Aspect Explaining the algorithm to the user.
    cout<<"...Algorithm Explanation..."<<endl;
    cout<<"Realize that we need to find m[N,W], which is the bottom right entry in the table.";
    cout<<"Our approach is to find m[N,W] recursively.Here the notations m[i,j],w[i],v[i] mean ";
    cout<<"maximum value attained by taking objects until ith index in the list of weights ";
    cout<<"sorted by weight, keeping the limit to be j.w[i] and v[i]] mean weight and value ";
    cout<<"of the ith object respectively"<<endl;
    cout<<"The recursive relation used in the algorithm is : "<<endl;
    cout<<"m[i,j] = m[i-1,j] if j<i and "<<endl;
    cout<<"m[i,j] = max(m[i-1,j],m[i-1,j-w[i]]+v[i]) otherwise"<<endl;
    cout<<"Applying the above algorithm , we recursively calculate m[N,W]"<<endl<<endl;


    // #Tutorial Aspect. Displaying the current status of the program.[Starting the dynamic prodecure]
    cout<<"...Starting the dynamic optimization procedure..."<<endl;

    //Starting the dynamic optimization procedure.
    for(int i=1;i<=N;i++){
      for(int j=0;j<=W;j++){

        // -1 factor in weights[i] different from pseudo code since weights and values are indexed from 0.
        if(j>=weights[i-1])
          maxVals[i][j] = max(maxVals[i-1][j],maxVals[i-1][j-weights[i-1]]+values[i-1]);
        else
          maxVals[i][j] = maxVals[i-1][j];
      }
    }

    cout<<"The table of maxVals produced according to the above algorithm is..."<<endl;
    for(int i=0;i<=N;i++){
      for(int j=0;j<=W;j++){
        int temp = maxVals[i][j];
        if(temp/10==0)
          cout<<"0"<<temp<<" ";
        else
          cout<<temp<<" ";
      }
      cout<<endl;
    }
    cout<<"...Done..."<<endl<<endl;
    return maxVals[N][W];

  }


/*
 * Function : presentSolution(val)
 * ----------------------------------------------------------------------------------------
 * Outputs the solution to the current knapsack problem. The solution is the maximum value
 * that can be carried inside the knapsack given the limit W.
 */

  void presentSolution(const int& maxValue){
    cout<<"The maximum value that can be carried in the knapsack, given the limit "<<W<<" is "<<maxValue<<endl;
  }

  int max(const int& n1,const int& n2){
    if(n1>n2) return n1; else return n2;
  }
