#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
using namespace std;

const int ROWS = 7;
const int COLS = 6;

// Рекурсивне створення матриці
void Create(int T[][COLS], int i = 0, int j = 0)
{
    if (i >= ROWS)
        return;

    T[i][j] = -42 + rand() % 94;

    if (j < COLS - 1)
        Create(T, i, j + 1);
    else
        Create(T, i + 1, 0);
}

// Рекурсивне виведення матриці
void Print(int T[][COLS], int i = 0, int j = 0)
{
    if (i >= ROWS)
    {
        cout << endl;
        return;
    }

    cout << setw(5) << T[i][j];

    if (j < COLS - 1)
        Print(T, i, j + 1);
    else
    {
        cout << endl;
        Print(T, i + 1, 0);
    }
}

// Рекурсивне копіювання матриці
void Copy(int A[][COLS], int B[][COLS],
    int i = 0, int j = 0)
{
    if (i >= ROWS)
        return;

    B[i][j] = A[i][j];

    if (j < COLS - 1)
        Copy(A, B, i, j + 1);
    else
        Copy(A, B, i + 1, 0);
}

// Рекурсивний підрахунок, обчислення суми та заміна
void Calculate(int T[][COLS], int& count, int& sum,
    int i = 0, int j = 0)
{
    if (i == 0 && j == 0)
    {
        count = 0;
        sum = 0;
    }

    if (i >= ROWS)
        return;

    if (!(T[i][j] > 0 && T[i][j] % 5 == 0))
    {
        count++;
        sum += T[i][j];
        T[i][j] = 0;
    }

    if (j < COLS - 1)
        Calculate(T, count, sum, i, j + 1);
    else
        Calculate(T, count, sum, i + 1, 0);
}

// Перевірка порядку двох рядків
bool NeedSwap(int T[][COLS], int i, int j)
{
    if (T[i][0] > T[j][0])
        return true;

    if (T[i][0] == T[j][0] &&
        T[i][1] < T[j][1])
        return true;

    if (T[i][0] == T[j][0] &&
        T[i][1] == T[j][1] &&
        T[i][2] > T[j][2])
        return true;

    return false;
}

// Рекурсивний обмін рядків
void SwapRows(int T[][COLS], int i, int j, int k = 0)
{
    if (k >= COLS)
        return;

    int temp = T[i][k];
    T[i][k] = T[j][k];
    T[j][k] = temp;

    SwapRows(T, i, j, k + 1);
}

// Рекурсивне сортування рядків
void Sort(int T[][COLS], int i = 0, int j = 1)
{
    if (i >= ROWS - 1)
        return;

    if (j >= ROWS)
    {
        Sort(T, i + 1, i + 2);
        return;
    }

    if (NeedSwap(T, i, j))
        SwapRows(T, i, j);

    Sort(T, i, j + 1);
}

int main()
{
    srand((unsigned)time(0));

    int T[ROWS][COLS];
    int A[ROWS][COLS];
    int B[ROWS][COLS];
    int count, sum;

    Create(T);
    Copy(T, A);
    Copy(T, B);

    cout << "Original matrix:" << endl;
    Print(T);

    Calculate(A, count, sum);

    cout << "Count = " << count << endl;
    cout << "Sum = " << sum << endl;
    cout << "Matrix after replacement:" << endl;
    Print(A);

    Sort(B);

    cout << "Sorted matrix:" << endl;
    Print(B);

    return 0;
}