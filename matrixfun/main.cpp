#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath> 
#include <sstream>
#include <string>

using namespace std;

void printMatrix(vector< vector< double > >* vectorsource) // Often-used function that prints a matrix that is sent into it to console
{
     for (int x = 0; x < (*vectorsource).size(); x++)
        for (int y = 0; y < (*vectorsource)[0].size(); y++)
        {
            cout<< (*vectorsource)[x][y];
                        
            if (y< (*vectorsource)[0].size()-1)
            cout<<", ";
            else 
            cout<< endl;
        }
    cout<<endl;
}

vector<vector<double> > getV(vector<double>* xpoint1, int highestorder) // accepts list of x coordinates from points, and highest order, returns 2D V matrix 
{
    vector< vector< double > > newV( (*xpoint1).size(), vector< double >(highestorder+1) ); // creates matrix with size (*xpoint1).size() x (highestorder+1)
    
    for (int x = 0; x < newV.size(); x++) //iteration through each spot in the matrix to assign values
        for (int y = 0; y < newV[0].size(); y++)
        {
            // the first number in a row of the matrix is the one raised to the highest power
            // order the x coordinate is raised to is calculated from the equation highestorder-y
            // I.E. the first spot of a 8x4 matrix is the first x-value raised to the 3-0, or 3rd power
            newV[x][y] = pow( (*xpoint1)[x], highestorder-y ); 
        }
    return newV; //returns V matrix                
}

vector<vector<double> > getTranspose(vector< vector< double > >* original) // accepts original matrix to be transposed
{
    vector< vector< double > > transposeMatrix( (*original)[0].size(), vector< double >( (*original).size() ) ); // creates matrix with row and column sizes switched
    
    for (int x = 0; x < transposeMatrix.size(); x++) //iteration through each spot in the matrix to assign values
        for (int y = 0; y < transposeMatrix[0].size(); y++)
        {
            transposeMatrix[x][y] = (*original)[y][x]; // assigns number at a row,column spot to the Transpose matrix at the column,row spot
        }
    return transposeMatrix; //returns transposed matrix                
}

vector<vector<double> > multiplyMatrix(vector< vector< double > >* vector1, vector< vector< double > >* vector2) // accepts two matrixes to be multiplied
{
    vector< vector< double > > multiplyResult( (*vector1).size(), vector< double >( (*vector2)[0].size() ) ); // creates matrix of size a x d from first matrix of size a x b and second matrix of size c x d
    
    for (int x = 0; x < multiplyResult.size(); x++) //iteration through each spot in the matrix to assign values
        for (int y = 0; y < multiplyResult[0].size(); y++)
        {
            // since the value at each spot in a multiplied matrix is the sum of multiplied elements, this keeps track
            // For example the point at row 1 col 1 would be the 1,1(first matrix) * 1,1(second matrix) + 1,2(first matrix) * 2,1(second matrix) + 1,3(first matrix) * 3,1(second matrix) and so on
            double dotProduct=0; 
            
            for(int counter = 0; counter < (*vector1)[0].size(); counter++)
            {
                dotProduct += (*vector1)[x][counter] * (*vector2)[counter][y]; //Calculates the term to add to the dot product result
            }
            multiplyResult[x][y]= dotProduct; // assigns number at a row,column spot to the Transpose matrix at the column,row spot
        }
    return multiplyResult; //returns multiplied matrix                
}

vector<vector<double> > getMinorMatrix(vector< vector< double > >* vectortoshrink, int row, int col) //This gets the minor matrix of a specified element in an matrix
{
    vector< vector< double > > minorMatrix( (*vectortoshrink).size()-1, vector< double >( (*vectortoshrink)[0].size()-1 ) ); 
    
    int xshiftcounter = 0; // the row number equivalent after shifting
    for (int x = 0; x < minorMatrix.size(); x++) //iteration through each spot in the matrix to assign values
    { 
        if (x == row) // shifts the row number counter to skip the row
           xshiftcounter++;
        
        int yshiftcounter = 0; // the column number equivalent after shifting
        for (int y = 0; y < minorMatrix[0].size(); y++)
        {    
             if (y == col) // shifts the column number counter to skip the column
                yshiftcounter++; 
             minorMatrix[x][y]= (*vectortoshrink)[xshiftcounter][yshiftcounter]; // assigns number at a row,column spot to the Transpose matrix at the column,row spot
             
             yshiftcounter++; //column advances after each loop
        }
        xshiftcounter++; //row advances after each loop
    }
    return minorMatrix; //returns multiplied matrix                
}

double findDeterminant(vector< vector< double > >* vectorsource) //This is a recursive function that finds the determinant of any square matrix
{
    //In a 2x2 square matrix of 
    // [ a   b ]
    // [ c   d ]   
    //The determinant is a * d - b * c
    
    //Base case
    
    if ((*vectorsource).size() ==1 && (*vectorsource)[0].size() ==1) // If single number is sent, return number
       return (*vectorsource)[0][0];
        
    else if ((*vectorsource).size() ==2 && (*vectorsource)[0].size() ==2) // If the matrix is 2x2, the determinant can be found without further recursion
       return (*vectorsource)[0][0]*(*vectorsource)[1][1] - (*vectorsource)[0][1]*(*vectorsource)[1][0];
    
    //Not base case, so recurses
    else // If the matrix sent in is larger than 2x2, recursively finds the minors of the first row of elements, and summates them imposed on an alternating + - grid
    {
        double determinant = 0;
        for (int column = 0; column< (*vectorsource)[0].size(); column++)//loops through first row of matrix
        {
            vector<vector<double> > minorMatrix = getMinorMatrix((vectorsource), 0,column);
            
            //Finds determinant of minor matrix for each of the elements, and uses the formula  (-1)^(row + column) to add them 
            determinant += (findDeterminant(&minorMatrix))* pow((-1.0),(double)((column+1)+1)) * (*vectorsource)[0][column];          
        }        
        return determinant;  
    }             
}

vector<vector<double> > getAdjointMatrix(vector< vector< double > >* vectorsource) //This gets the minor matrix of a specified element in an matrix
{
    vector< vector< double > > adjointMatrix( (*vectorsource).size(), vector< double >( (*vectorsource)[0].size() ) ); 
    
    for (int x = 0; x < adjointMatrix.size(); x++) //iteration through each spot in the matrix to assign values
        for (int y = 0; y < adjointMatrix[0].size(); y++)
        {    
             vector< vector< double > >tempMinorMatrix = getMinorMatrix((vectorsource), x,y);
             adjointMatrix[x][y]= pow((-1.0),(double)((x+1)+(y+1))) * findDeterminant(&tempMinorMatrix); 
            
        }
    //We now have the cofactor matrix.
    
    //Thd Adjoint matrix is the tranpose of the cofactor.
    adjointMatrix = getTranspose(&adjointMatrix);
    
    return adjointMatrix; //returns Adjoint matrix                
}

int getInt() // manages user input of integer, handles issues with inputs that cannot be parsed into int
{
    string input1;
    int numberReturn;    
    while (true) 
        {   
            //cin.clear();
            //cin.ignore(INT_MAX);         
            
            getline(cin, input1);
            
            stringstream myStream(input1);
            
            if (myStream >> numberReturn)
                   break;
            cout << "Invalid number, please try again" << endl;
            }
    return numberReturn;
}

double getDouble() // manages user input of integer, handles issues with inputs that cannot be parsed into int
{
    string input1;
    double numberReturn;    
    while (true) 
        {   
            //cin.clear();
            //cin.ignore(INT_MAX);         
            
            getline(cin, input1);
            stringstream myStream(input1);
            if (myStream >> numberReturn)
                   break;
            cout << "Invalid number, please try again" << endl;
            }
    return numberReturn;
}

int main(int argc, char *argv[])
{
    int coordcount;
    int highestorder;
    
    cout<<"Use coordinate points from the question or enter others? Enter: "<<endl;
    cout<<"1. Points from Assignment 0 question"<<endl;
    cout<<"2. New points that you will need to enter"<<endl;
    cout<<"Your choice: ";
    int choice1 = cin.get();

    if (choice1 ==1)
    coordcount = 8; // How many coordinate points there are
    else 
    {
        cout<<"How many coordinate pairs? ";
        coordcount = getInt();
    }
    vector<double> xpoint (coordcount); // list of the x coordinates of the points
    vector<double> ypoint (coordcount); // list of the y coordinates of the points
    
    if (choice1 ==1)
    {                
        highestorder = 3; // the order polynomial wanted
        
        //Preset Points
        xpoint[0]= 1.01;
        xpoint[1]= 2.2;
        xpoint[2]= 2.9;
        xpoint[3]= 4.03;
        xpoint[4]= 5.32;
        xpoint[5]= 6.22;
        xpoint[6]= 8.56;
        xpoint[7]= 9.09;
        
        ypoint[0]= 18.5;
        ypoint[1]= 76.2;
        ypoint[2]= 150.5;
        ypoint[3]= 365;
        ypoint[4]= 780;
        ypoint[5]= 1265;
        ypoint[6]= 3250;
        ypoint[7]= 7099;
    }
    if (choice1 == 2)
    {
        cout<<endl;
        cout<<"What order polynomial? ";
        
        highestorder = cin.get();           
       
        for (int i = 0; i< coordcount; i++)
        {
            cout<<"Enter x coordinate: ";
            xpoint[i]= cin.get();
            
            cout<<"Enter y coordinate: ";
            ypoint[i]= cin.get(); 
        }
    }
    
    cout<<endl;
    
    //Outputs x-y points for reference
    cout<<"Your points (x,y): "<<endl;      
    for (int i = 0; i< xpoint.size(); i++)
    {
        cout<<xpoint[i]<<", "<<ypoint[i]<<endl;
    }   
    cout<<endl;
    
    cout<<"--------";     
    system("PAUSE");
    cout<<endl;
    
    //Gets the V matrix from function by sending in the x coordinates and the order polynomial wanted  
    vector<vector<double> > V = getV(&xpoint, highestorder);
    cout<<"Your V matrix: "<<endl;    
    printMatrix(&V); //Displays the V matrix
    
    cout<<"--------";     
    system("PAUSE");
    cout<<endl;
    
    //Gets the V^T matrix from function by sending in the V matrix
    vector<vector<double> > VTranspose = getTranspose(&V);
    cout<<"Your V^T matrix: "<<endl;    
    printMatrix(&VTranspose); //Displays V-tranpose

    cout<<"--------";     
    system("PAUSE");
    cout<<endl;
    
    //Gets the V^T * V matrix from function by sending in the V-T and V matrix
    vector<vector<double> > VTV = multiplyMatrix(&VTranspose, &V);
    cout<<"Your V^T * V matrix: "<<endl;    
    printMatrix(&VTV); //Displays V^T * V matrix 
    
    cout<<"--------";     
    system("PAUSE");
    cout<<endl;
    
    //Gets the V * V^T matrix from function by sending in the V-T and V matrix
    vector<vector<double> > VVT = multiplyMatrix(&V, &VTranspose);
    cout<<"Your V * V^T matrix: "<<endl;
    printMatrix(&VVT); //Displays V * V^T matrix     
    
    //Ask user whether to stop or solve rest of matrix for equation
    cout<<endl;
    cout<<"********************************"<<endl;
    cout<<"This program will now solve the matrix below."<<endl<<"Press 0 to cancel, or any other key to continue: ";
    
    char choice2;
    choice2 = cin.get(); //The user's choice is recorded into the choice variable
   
    if (choice2 != '0') // Conditional statement entered only if user decides not to quit
    {
        cout<<endl;
        cout<<"The process will start with V * C = Y ."<<endl<<endl;
        cout<<"V is the original matrix, C is the vector containing the coefficients, and Y is the vector containing y coordinates from our points"<<endl<<endl;
        cout<<"Multiply both sides by V^T to get: "<<endl;
        cout<<"V^T * V * C = V^T * Y "<<endl<<endl;
        cout<<"Multiply both sides by (V^T * V)^-1 to get: "<<endl;
        cout<<"(V^T * V)^-1 * (V^T * V) * C = (V^T * V)^-1 * V^T * Y "<<endl<<endl;
        cout<<"(V^T * V)^-1 * (V^T * V) = the Identity matrix I, but "<<endl;
        cout<<"I * C = C , so the equation becomes "<<endl;
        cout<<"C = (V^T * V)^-1 * V^T * Y "<<endl<<endl;
        
        cout<<"--------";     
        system("PAUSE");
        cout<<endl;
        
        cout<<"The individual matrixes are displayed below: "<<endl<<endl;
                
        //Redisplays V^T * V matrix
        cout<<"Your V^T * V matrix: "<<endl;  
        printMatrix(&VTV); 
        
        //Gets the Y Vector
        cout<<"Your Y vector: "<<endl; 
        vector< vector< double > > YVector( (ypoint).size(), vector< double >(1) );
        for (int x = 0; x < YVector.size(); x++)// Transfers Y coordinates to a vector
            for (int y = 0; y < YVector[0].size(); y++)            
                YVector[x][0] = ypoint[x]; 
        printMatrix(&YVector); // Display Y Vector                     
        
        cout<<"--------";     
        system("PAUSE");
        cout<<endl;
        
        //Explanation
        cout<<"If the inverse of (V^T * V) exists, the Determinant of V^T * V must not be 0."<<endl;        
        cout<<"This determinant is calculated to be: " <<  findDeterminant(&VTV)<<endl;
        
        if (findDeterminant(&VTV) !=0)
        {
        
            cout<<"Therefore we can calculate the inverse of V^T * V by using the formula: "<<endl;
            cout<<"A^-1 = (1/det(A)) * (Adjoint Matrix of A)"<<endl<<endl;
            
            cout<<"The adjoint matrix is the transpose of the cofactor matrix of A."<<endl;
            cout<<"The cofactor matrix is where each element in a matrix is replaced by the "<<endl;
            cout<<"the determinant of the minor of each of the element itself, and "<<endl;
            cout<<"each element is multiplied by (-1)^(row+column)"<<endl<<endl;
            
            cout<<"In our problem, the formula is:"<<endl;
            cout<<"(V^T * V)^-1 = (1/det(V^T * V) * (Cofactor Matrix of (V^T * V))^T"<<endl<<endl;
            
            
            //Gets the adjoint Matrix to be used as part of (V^T * V) inverse calculation
            cout<<"The transpose of the Cofactor Matrix of (V^T * V), or adjoint matrix is: "<<endl;
            vector<vector<double> > VTVadjoint = getAdjointMatrix(&VTV);
            printMatrix(&VTVadjoint);   //Display (V^T * V) 's adjoint matrix    
            
            cout<<"--------";     
            system("PAUSE");
            cout<<endl;
                   
            //Calculates the inverse of (V^T * V) matrix using reciprocal of determinant multiplied by adjoint matrix
            cout<<"Your (V^T * V)^-1 matrix is calculated to be: "<<endl;  
            vector<vector<double> > VTVinv = VTVadjoint;
            
            for (int x = 0; x < VTVinv.size(); x++) // Accesses each of the elements of the matrix
                for (int y = 0; y < VTVinv[0].size(); y++)            
                    VTVinv[x][y]*= (1/(findDeterminant(&VTV))); //multiplies each element by reciprocal of determinant
            printMatrix(&VTVinv); //Display (V^T * V)^-1          
          
            //Explanation        
            cout<<"The solution vector C is again: "<<endl;
            cout<<"C = (V^T * V)^-1 * V^T * Y "<<endl<<endl;
            cout<<"Now that we have (V^T * V)^-1, V^T, and Y,"<<endl;
            cout<<"We find the solution vector to be: "<<endl;
            
            // Creates a final solution Vector of the appropriate dimensions: (highest order # + 1) rows by 1 column
            vector< vector< double > > solutionVector( highestorder+1, vector< double >(1) );       
            // Solution vector is (V^T * V)^-1 * V^T * Y
            solutionVector=multiplyMatrix(&VTVinv, &VTranspose); // First matrix multiplication: (V^T * V) * V^T
            solutionVector=multiplyMatrix(&solutionVector, &YVector); //Result of above step * Y vector
            
            printMatrix(&solutionVector); //Display Solution vector    
           
            cout<<"The least-square's computed equation is: "<<endl;
            // Associate solution vector results with coefficients of polynomial powers
            for (int x = 0; x < solutionVector.size(); x++)
            {    
                 cout<<"("<<solutionVector[x][0]<<")";
                 if (x < solutionVector.size()-1)
                    cout<<"x";
                 if (x < solutionVector.size()-2)
                    cout<<"^"<<highestorder-x; 
                 if (x < solutionVector.size()-1)
                    cout<<" + ";                                         
            }
            cout<<endl;               
        }
        else // If determinant is zero, no inverse can be calculated
        cout<<endl<<"The determinant was 0. Therefore no inverse can be found, which means there is more than one solution."<<endl;      
    }
    cout<<"--------";     
    system("PAUSE");
    cout<<endl;
    return EXIT_SUCCESS;    
}
