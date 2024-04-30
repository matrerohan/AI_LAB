#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cmath>
using namespace std;

//  GLOBAL  FILE  NAME
char file_name[9], file_name_inf[14], file_name_wgt[14], file_name_rst[14];
char file_name_out[14], file_name_dat[14];

// Matrix class to perform matrix operations
class matrix
{
    int row, col;

public:
    float mat[15][15];
    matrix()
    {
        row = 0;
        col = 0;
    }
    // Set the dimensions of the matrix
    void set(int, int);
    // Get the number of rows in the matrix
    int getrows()
    {
        return row;
    }
    // Get the number of columns in the matrix
    int getcols()
    {
        return col;
    }
    void getdata();           // Get matrix data from user input
    FILE *fgetdata(FILE *);   // Get matrix data from file
    void displaydata();       // Display matrix data
    void displaydat();        // Display the number of rows
    FILE *fputdata(FILE *);   // write matrix data to file
    FILE *fputdat(FILE *);    // write the number of rows to file
    matrix operator+(matrix); // Matrix addition
    matrix operator-();       // Matrix transposition
    matrix operator*(matrix); // Matrix multiplication
    matrix operator*(float);  // Scalar multiplication
};

// Set the dimensions of the matrix
void matrix ::set(int i, int j)
{
    row = i;
    col = j;
}

// Get matrix data from file
FILE *matrix::fgetdata(FILE *fmat)
{
    char line;
    int i, j;
    fscanf(fmat, "%d%d", &(row), &(col));
    for (i = 1; i <= row; i++)
        for (j = 1; j <= col; j++)
            fscanf(fmat, "%f", &(mat[i][j]));
    return (fmat);
}

// Get matrix data from user input
void matrix::getdata()
{
    int i, j;
    cout << "Enter the size of the matrix:";
    cin >> row >> col;
    for (i = 1; i <= row; i++)
        for (j = 1; j <= col; j++)
        {
            cout << "element [" << i << "]  [ " << j << " ] ";
            cin >> mat[i][j];
        }
}

// Display matrix data
void matrix::displaydata()
{
    int i, j;
    //  cout<<"The required matrix is :" << endl;
    for (i = 1; i <= row; i++, printf("\n\r"))
        for (j = 1; j <= col; j++, printf("\t"))
            printf("\t\t%10.2f", mat[i][j]);
}

// Display the number of rows
void matrix::displaydat()
{
    int i;
    cout << row;
}

// Write matrix data to file
FILE *matrix::fputdata(FILE *fmat)
{
    int i, j;
    //  fprintf(fmat,"\n");
    fprintf(fmat, "%d\n%d\n", row, col);
    for (i = 1; i <= row; i++)
        for (j = 1; j <= col; j++)
            fprintf(fmat, "%f\n", mat[i][j]);
    return (fmat);
}

// Write the number of rows to file
FILE *matrix::fputdat(FILE *fmat)
{
    int i;
    fprintf(fmat, "%d", row);
    return (fmat);
}

// Matrix addition
matrix matrix ::operator+(matrix m)
{
    matrix temp;
    int i, j;
    if ((row == m.row) && (col == m.col))
        for (i = 1; i <= row; i++)
            for (j = 1; j <= col; j++)
                temp.mat[i][j] = mat[i][j] + m.mat[i][j];
    else
    {
        cout << "The addition of the matrices is not possible";
        exit(1);
    }
    temp.row = row;
    temp.col = col;
    return (temp);
}

// Matrix Transposition
matrix matrix ::operator-()
{
    matrix temp;
    int i, j;
    temp.row = col;
    temp.col = row;
    for (i = 1; i <= col; i++)
        for (j = 1; j <= row; j++)
            temp.mat[i][j] = mat[j][i];
    return (temp);
}

// Matrix multiplication
matrix matrix ::operator*(matrix m)
{
    matrix temp;
    int i, j, k;
    if (col == m.row)
    {
        for (i = 1; i <= row; i++)
            for (j = 1; j <= m.col; j++)
            {
                temp.mat[i][j] = 0;
                for (k = 1; k <= col; k++)
                    temp.mat[i][j] = temp.mat[i][j] + (mat[i][k] * m.mat[k][j]);
            }
    }
    else
    {
        cout << "The multiplication of the matrices is not possible";
        exit(1);
    }
    temp.row = row;
    temp.col = m.col;
    return (temp);
}

// Scalar multiplication
matrix matrix ::operator*(float svalue)
{
    matrix temp;
    int i, j;
    for (i = 1; i <= row; i++)
        for (j = 1; j <= col; j++)
            temp.mat[i][j] = mat[i][j] * svalue;
    temp.row = row;
    temp.col = col;
    return (temp);
}

// Training class for neural network training
class training
{
    FILE *fin, *fout, *fwt;
    matrix Input[5], Output[5], // array of vectors
        Weights[5], dWeights[5], d, e, T;
    float alpha, /* Momentum factor			*/
        eta,     /* Learning rate			*/
        err,     /* Error Constant			*/
        theta,   /* Threshold value			*/
        lamda,   /* Scaling parameter			*/
        edata,
        error;
    int TotalLayers,  // total # of layers
        HiddenLayers, // total number of hidden layers
        l[5],         // NO of neurons in each layer
        ntest,
        iterates;
    long filepos;

public:
    training();           // Constructor
    void readinputs();    // Read input parameters
    void printing();      // Print parameters
    void initweights();   // Initialize weights randomly
    void initdweights();  // Initialize weight differences
    void train();         // Train the neural network
    void io_values();     // Calculate input/output values of neurons
    void backpropagate(); // Backpropagation algorithm
    void errors();        // Calculate errors
    void chgweights();    // Change weights
    void newweights();    // Update weights
    ~training();          // Destructor
};

// Constructor
training::training()
{
    if ((fin = fopen(file_name_dat, "r")) == NULL)
        exit(1);
    if ((fout = fopen(file_name_out, "w")) == NULL)
        exit(1);
    if ((fwt = fopen(file_name_wgt, "w")) == NULL)
        exit(1);
    /*if  ( (fin = fopen("SOIL30.DAT","r")) == NULL) exit(1);
    if ( (fout=fopen("SOIL30.OUT","w")) == NULL) exit(1);
    if ( (fwt=fopen("SOIL30.WGT","w") ) == NULL) exit(1);*/
    readinputs();
    printing();
    initweights();
    initdweights();
    train();
}

// Read input parameters
void training ::readinputs()
{
    int i;
    error = 0;
    char line;
    fscanf(fin, "%d", &HiddenLayers); /*  get no. of hidden layers   */
    TotalLayers = HiddenLayers + 1;   /*  total number of layers     */
    for (i = 0; i <= TotalLayers; i++)
        fscanf(fin, "%d", &l[i]);
    fscanf(fin, "%f%f%f%f%f", &alpha, &err, &eta, &theta, &lamda);
    fscanf(fin, "%d%d", &ntest, &iterates);
    filepos = ftell(fin);
}

// Print parameters
void training ::printing()
{
    for (int i = 0; i <= TotalLayers; i++)
        fprintf(fout, "\nNumber of Neurons in layer[%d]=%d", i + 1, l[i]);
    fprintf(fout, "\nAlpha value(Momentum factor): %f", alpha);
    fprintf(fout, "\nError constant : %f", err);
    fprintf(fout, "\nLearning rate : %f", eta);
    fprintf(fout, "\nThreshold value : %f", theta);
    fprintf(fout, "\nScaling Parameter: %f", lamda);
    fprintf(fout, "\nNo of Training data : %d", ntest);
    fprintf(fout, "\nMaximum Iteration : %d", iterates);
    system("clear");
    printf("\n\n\n");
    for (int i = 0; i <= TotalLayers; i++)
        printf("\n\t\tNumber of Neurons in layer[%d]=%d", i + 1, l[i]);
    printf("\n\n\t\tAlpha value(Momentum factor): %f", alpha);
    printf("\n\t\tError constant              : %f", err);
    printf("\n\t\tLearning rate               : %f", eta);
    printf("\n\t\tThreshold value             : %f", theta);
    printf("\n\t\tScaling Parameter           : %f", lamda);
    printf("\n\t\tNo of Training data         : %d", ntest);
    printf("\n\t\tMaximum Iteration           : %d", iterates);
    cin.get();
}

void training ::initweights()
{
    /*  Initialize initial weights randomly   */
    srand(2000);
    srand(time(0));
    for (int k = 0; k < TotalLayers; k++)
    {
        Weights[k].set(l[k], l[k + 1]);
        for (int i = 1; i <= l[k]; i++)
            for (int j = 1; j <= l[k + 1]; j++)
                Weights[k].mat[i][j] = ((float)rand() / 32767) - 0.5;
        fprintf(fout, "\nWeights[%d]:", k);
        Weights[k].fputdata(fout);
    }
}

void training ::initdweights()
{
    for (int k = 0; k < TotalLayers; k++)
    {
        /* Initial differnce in weights is zero  */
        dWeights[k].set(l[k], l[k + 1]);
        for (int i = 1; i <= l[k]; i++)
            for (int j = 1; j <= l[k + 1]; j++)
                dWeights[k].mat[i][j] = 0.0;
    }
}

// Train the neural network
void training ::train()
{
    int k;
    float error1;
    for (int jtr = 1; jtr <= iterates; jtr++) // iterates
    {
        /*    ITERATION LOOP    */
        error = 0.0;
        fseek(fin, filepos, SEEK_SET);
        cout << "\nIteration Number: " << jtr << endl;
        for (int itr = 1; itr <= ntest; itr++)
        {
            /* NTEST LOOP	       */
            Input[0].fgetdata(fin); /* Read Training Data  */
            T.fgetdata(fin);        /* Read Desired Output */
            cout << "\rTraining Data Number: " << itr;
            io_values();
            backpropagate();
            errors();
            chgweights();
            newweights();
        }
        // ntest loop
        fprintf(fout, " %10.3E\n", error / ntest);
    }
    cin.get();
    /* iterates loop */
    for (k = 0; k < TotalLayers; k++)
        fwt = Weights[k].fputdata(fwt);
}
//////////////////////////TRAIN//////////////////////////////
// Calculate input/output values of neurons
void training ::io_values()
{
    /*  CALCULATION OF Input/OUT VALUES OF NEURONS  */

    Output[0] = Input[0];
    for (int m = 0; m <= TotalLayers - 1; m++)
    {
        Input[m + 1] = -Weights[m] * Output[m];
        Output[m + 1].set(l[m + 1], 1);
        for (int i = 1; i <= l[m + 1]; i++)
            Output[m + 1].mat[i][1] = 1.0 / (1.0 + exp(-lamda * (Input[m + 1].mat[i][1] + theta)));
    }
}
void training ::backpropagate()
{
    /*	BACK PROPAGATION       */
    d.set(l[TotalLayers], 1);
    for (int i = 1; i <= l[TotalLayers]; i++)
        d.mat[i][1] = Output[TotalLayers].mat[i][1] * (1 - Output[TotalLayers].mat[i][1]) * (T.mat[i][1] - Output[TotalLayers].mat[i][1]);
    dWeights[TotalLayers - 1] = (dWeights[TotalLayers - 1] * alpha) + ((Output[TotalLayers - 1] * -d) * eta);
}
void training ::chgweights()
{
    /*   CALCULATION OF CHANGE IN WEIGHTS	*/
    int k;
    for (int i = 0; i <= TotalLayers - 2; i++)
    {
        k = TotalLayers - i - 1;
        e = Weights[k] * d;
        d.set(l[k], 1);
        for (int j = 1; j <= l[k]; j++)
        {
            d.mat[j][1] = Output[k].mat[j][1] * (1 - Output[k].mat[j][1]) * e.mat[j][1];
        }
        //	dWeights[k-1]=(Output[k-1]*-d);
        dWeights[k - 1] = (dWeights[k - 1] * alpha) + ((Output[k - 1] * -d) * eta);
    }
}

void training ::newweights()
{
    for (int k = 0; k < TotalLayers; k++)
        Weights[k] = Weights[k] + dWeights[k];
}

void training ::errors()
{
    /*  ERROR CALCULATION	*/
    float sum = 0.0, x, y1, y2;
    for (int j = 1; j <= l[TotalLayers]; j++)
    {
        y1 = T.mat[j][1];
        y2 = Output[TotalLayers].mat[j][1];
        x = fabs(y1 - y2);
        x = x * x;
        sum = sum + x;
    }
    sum = sqrt(sum / l[TotalLayers]);
    error = error + sum;
    // printf(" Error=%10.3f",error);
    cout << "\t\t Error =" << error;
}

training ::~training()
{
    fclose(fin);
    fclose(fout);
    fclose(fwt);
}
/////////      INFERENCE         /////////////

class inference
{
    FILE *fin, *fout, *fwt;
    matrix Input[5], Output[5], // array of vectors
        Weights[5], T, CalculatedErr, NoOfTest;
    float alpha, /* Momentum factor			*/
        eta,     /* Learning rate			*/
        err,     /* Error Constant			*/
        theta,   /* Threshold value			*/
        x1, x2,
        lamda, /*  Scaling Parameter                   */
        Calerror;
    int TotalLayers, // total Number of layers
        ntest,       // Number of test data
        l[10];       // Number of neurons in each layer
public:
    inference();
    void readinput();
    void print();
    void infer();
};

inference ::inference()
{
    puts("Inference Session");
    if ((fin = fopen(file_name_inf, "r")) == NULL)
        exit(1);
    if ((fout = fopen(file_name_rst, "w")) == NULL)
        exit(1);
    if ((fwt = fopen(file_name_wgt, "r")) == NULL)
        exit(1);
    readinput();
    print();
    infer();
}

void inference ::readinput()
{
    fscanf(fin, "%d", &TotalLayers); /*  get no. of hidden layers   */
    TotalLayers = TotalLayers + 1;   /*  total number of layers     */
    for (int i = 0; i <= TotalLayers; i++)
        fscanf(fin, "%d", &l[i]);
    fscanf(fin, "%f%f%f%f%f", &alpha, &err, &eta, &theta, &lamda);
    fscanf(fin, "%d", &ntest);
}
void inference ::print()
{
    system("clear");
    printf("\n");
    for (int i = 0; i <= TotalLayers; i++)
        printf("\n\t\tNumber of Neurons in layer[%d]=%d", i + 1, l[i]);
    printf("\n\n\t\tAlpha value(Momentum factor): %f", alpha);
    printf("\n\t\tError constant              : %f", err);
    printf("\n\t\tLearning rate               : %f", eta);
    printf("\n\t\tThreshold value             : %f", theta);
    printf("\n\t\tScaling Parameter           : %f", lamda);
    printf("\n\t\tNo of Training data         : %d", ntest);
    cin.get();
}
void inference ::infer()
{
    float Calerror = 0.0;

    for (int no = 1; no <= ntest; no++)
    {
        Input[0].fgetdata(fin);
        // Input[0].fputdata(fout);
        T.fgetdata(fin);
        for (int i = 0; i < TotalLayers; i++)
            Weights[i].fgetdata(fwt);
        Output[0] = Input[0];
        for (int m = 0; m <= TotalLayers - 1; m++)
        {
            Input[m + 1] = -Weights[m] * Output[m];
            Output[m + 1].set(l[m + 1], 1);
            for (int i = 1; i <= l[m + 1]; i++)
                Output[m + 1].mat[i][1] = 1.0 / (1.0 + exp(-lamda * (Input[m + 1].mat[i][1] + theta)));
        }
        for (int j = 1; j <= l[TotalLayers]; j++)
        {
            x1 = T.mat[j][1];
            x2 = Output[TotalLayers].mat[j][1];
            Calerror = fabs(x1 - x2);
            CalculatedErr.set(j, 1);
            CalculatedErr.mat[j][1] = Calerror;
        }
        printf("\n");
        fprintf(fout, "\n\tINFERENCE TEST DATA NO :");
        NoOfTest.set(no, 1);
        NoOfTest.fputdat(fout);
        fprintf(stdout, "\n\t\tINFERENCE TEST DATA NO:");
        NoOfTest.displaydat();
        fprintf(fout, "\nCalculated Value:\n");
        Output[TotalLayers].fputdata(fout);
        fprintf(stdout, "\n\t\tCALCULATED VALUE:\n");
        Output[TotalLayers].displaydata();
        fprintf(fout, "\nActual Value:\n");
        T.fputdata(fout);
        fprintf(stdout, "\n\t\tACTUAL VALUE:\n");
        T.displaydata();
        fprintf(fout, "\nCALCULATED ERROR:\n");
        CalculatedErr.fputdata(fout);
        fprintf(stdout, "\n\t\tCalculated Error:\n");
        CalculatedErr.displaydata();
        printf("\t\tPress any Key to Continue ");
        cin.get();
    }
}
///////////        MAIN  PROGRAM    ///////////
int main(void)
{

    int ch;
    system("clear");
    cout << endl
         << "Enter  the  file  name  :  ";
    cin >> file_name;
    strcat(strcpy(file_name_dat, file_name), ".dat");
    strcat(strcpy(file_name_inf, file_name), ".inf");
    strcat(strcpy(file_name_wgt, file_name), ".wgt");
    strcat(strcpy(file_name_rst, file_name), ".rst");
    strcat(strcpy(file_name_out, file_name), ".out");

    do
    {
        system("clear");
        cout << "\n\t\t\t1.Training";
        cout << "\n\t\t\t2.Inference";
        cout << "\n\t\t\t3.Exit";
        cout << "\nEnter your choice : ";
        cin >> ch;
        if (ch == 1)
        {
            training t;
        }
        else
        {
            if (ch == 2)
            {
                inference i;
            }
            else
                exit(0);
        }
    } while (ch != 3);
}
