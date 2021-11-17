#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

long L;
int S;
int A;
int B;
int where;

/**
 * @brief Computes distance between left and right location.
 * Uses distance of two points since we have constant X coordinates.
 * Therefore its basically |[0, i][S, j]|
 * 
 * @param i left location
 * @param j right location 
 * @return int Distance between i and j
 */
double d(int i, int j)
{
    return sqrt((pow(S, 2) + pow((i - j), 2)));
}

/**
 * @brief Determine minimum value from the supplied
 * 
 * @param a 
 * @param b 
 * @param c 
 * @return int min
 */
int min(double a, double b, double c)
{
    if (a < b)
    {
        if (a < c)
        {
            where = 1;
            return a;
        }
    }
    else
    {
        if (b < c)
        {
            where = 2;
            return b;
        }
    }
    where = 3;
    return c;
}

int main()
{
    //Initialize inputs
    cin >> L;               //length of canal
    cin >> S;               //width of canal
    cin >> A;               //number of left locations
    cin >> B;               //number of right locations
    int aa[A + 1];          //distances of left locations from start
    int bb[B + 1];          //distances of left locations from start
    double T[A + 1][B + 1]; //total ferry distances
    int V[A + 1][B + 1];    //"ferry modes" basically from where to where described in an int
    //V == 1 => T[i - 1, j]
    //V == 2 => T[i, j - 1]
    //V == 2 => T[i - 1, j - 1]
    //No other options, paths cannot cross otherwise we lenghten the path

    for (int i = 1; i <= A; i++)
    {
        cin >> aa[i];
    }
    for (int i = 1; i <= B; i++)
    {
        cin >> bb[i];
    }

    T[1][1] = d(aa[1], bb[1]); //initialize first position;
    for (int j = 2; j <= B; j++)
    {
        //iterate first row
        T[1][j] = T[1][j - 1] + d(aa[1], bb[j]);
        V[1][j] = 2;
    }

    for (int i = 2; i <= A; i++)
    {
        //Iterate the entire T
        //We have to initialize first position as there isn't previous to compare to
        T[i][1] = T[i - 1][1] + d(i, 1);
        V[i][1] = 1;
        //other positions...
        for (int j = 2; j <= B; j++)
        {
            T[i][j] = min(T[i - 1][j], T[i][j - 1], T[i - 1][j - 1]) + d(aa[i], bb[j]);
            V[i][j] = where;
        }
    }

    int i = A;
    int j = B;
    cout << i << " " << j << endl;
    while (i > 1 || j > 1)
    {
        switch (V[i][j])
        {
        case 1:
            i -= 1;
            break;
        case 2:
            j -= 1;
            break;
        case 3:
            i -= 1;
            j -= 1;
            break;
        }
        cout << i << " " << j << endl;
    }
    return 0;
}