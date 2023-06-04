#include <iostream>
using namespace std;

class Hungarian_Method
{
    bool if_found = false;
    bool **last_assignment;
public:
    void Give_pairs(float **intial_matrix, int r, int c);
    void Print_pairs(float **temp, int r, int c);
    void part_1(float **temporary_matrix, int r, int c);
    void part_2(float **temporaray_matrix, int r, int c);
};
void Hungarian_Method::Print_pairs(float **temp, int r, int c)
{
    cout << endl;
    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            cout << temp[i][j] << " ";
        }
        cout << endl;
    }
}
void Hungarian_Method::Give_pairs(float **first_matrix, int r, int c)
{
    int n = r >= c ? r : c;

    float **tem_matx = new float *[n];
    for (int i = 0; i < n; i++)
    {
        tem_matx[i] = new float[n];
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            tem_matx[i][j] = first_matrix[i][j];
        }
    }

    if (r > c)
    {
        for (int i = 0; i < r; i++)
            for (int j = 0; j < r - c; j++)
                tem_matx[i][n - j - 1] = 0;
    }

    if (r < c)
    {
        for (int i = 0; i < c - r; i++)
            for (int j = 0; j < c; j++)
                tem_matx[n - i - 1][j] = 0;
    }

    last_assignment = new bool *[n];
    for (int i = 0; i < n; i++)
        last_assignment[i] = new bool[n];

    part_1(tem_matx, n, n);

    while (!if_found)
        part_2(tem_matx, n, n);

    cout << "\nThe Optimal assignment is " << endl;
    float tot = 0;
    for (int i = 0; i < n; i++)
    {
        if (r < i + 1)
            break;
        cout << i + 1 << " assigned to column - ";

        for (int j = 0; j < n; j++)
        {
            if (last_assignment[i][j])
            {
                cout << j << " normalized match = ";

                if (c < (j + 1))
                {
                    cout << "0" << endl;
                    break;
                }
                else
                {
                    cout << first_matrix[i][j] << endl;
                    tot += first_matrix[i][j];
                    break;
                }
            }
        }
    }
    cout << "Minimum total is: " << tot << endl;
}

void Hungarian_Method::part_1(float **temp, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        float row_minimum = temp[i][0];
        for (int j = 0; j < c; j++)
        {
            if (row_minimum > temp[i][j])
                row_minimum = temp[i][j];
        }
        for (int j = 0; j < c; j++)
        {
            temp[i][j] -= row_minimum;
        }
    }

    for (int i = 0; i < c; i++)
    {
        float col_min = temp[0][i];
        for (int j = 0; j < r; j++)
        {
            if (col_min > temp[j][i])
                col_min = temp[j][i];
        }
        for (int j = 0; j < r; j++)
        {
            temp[j][i] -= col_min;
        }
    }
}

void Hungarian_Method::part_2(float **temmp, int p, int z)
{
    bool *can_check_row = new bool[p];
    bool *can_check_column = new bool[z];
    bool **h_light = new bool *[p];
    for (int i = 0; i < p; i++)
        h_light[i] = new bool[z];

    for (int i = 0; i < p; i++)
        for (int j = 0; j < z; j++)
            h_light[i][j] = false;

    for (int i = 0; i < p; i++)
        can_check_row[i] = false;

    for (int i = 0; i < z; i++)
        can_check_column[i] = false;

    bool if_all_zero_covered = false;

    while (!if_all_zero_covered)
    {
        for (int i = 0; i < p; i++)
        {
            int zeros_n = 0;
            if (can_check_row[i])
                continue;
            for (int j = 0; j < z; j++)
            {
                if (!can_check_column[j] && temmp[i][j] == 0)
                    zeros_n++;
            }
            if (zeros_n == 1)
            {
                int index_column = 0;
                for (int j = 0; j < z; j++)
                {
                    if (!can_check_column[j] && temmp[i][j] == 0)
                    {
                        index_column = j;
                        break;
                    }
                }
                h_light[i][index_column] = true;
                can_check_column[index_column] = true;
            }
        }
        for (int i = 0; i < z; i++)
        {
            int number_of_zeros = 0;
            if (can_check_column[i])
                continue;
            for (int j = 0; j < p; j++)
            {
                if (!can_check_row[j] && temmp[j][i] == 0)
                    number_of_zeros++;
            }
            if (number_of_zeros == 1)
            {
                int row_index = 0;
                for (int j = 0; j < p; j++)
                {
                    if (!can_check_row[j] && temmp[j][i] == 0)
                    {
                        row_index = j;
                        break;
                    }
                }
                h_light[row_index][i] = true;
                can_check_row[row_index] = true;
            }
        }
        if_all_zero_covered = true;
        for (int i = 0; i < p; i++)
            for (int j = 0; j < p; j++)
                if (!can_check_row[i] && !can_check_column[j] && temmp[i][j] == 0)
                {
                    if_all_zero_covered = false;
                    h_light[i][j] = true;
                    can_check_row[i] = true;
                    can_check_column[j] = true;
                }
    }
    int Number_of_marked = 0;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < p; j++)
        {
            if (h_light[i][j])
                Number_of_marked++;
        }
    }
    if (Number_of_marked == p)
    {
        this->if_found = true;
        for (int i = 0; i < p; i++)
            for (int j = 0; j < p; j++)
                last_assignment[i][j] = h_light[i][j];
        return;
    }
    float Min_of_h_lighted;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < z; j++)
        {
            if (!can_check_row[i] && !can_check_column[j])
            {
                Min_of_h_lighted = temmp[i][j];
                break;
            }
        }
    }
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < z; j++)
        {
            if (!can_check_row[i] && !can_check_column[j] && temmp[i][j] < Min_of_h_lighted)
                Min_of_h_lighted = temmp[i][j];
        }
    }
    for (int i = 0; i < p; i++)
        for (int j = 0; j < z; j++)
        {
            if (!can_check_row[i] && !can_check_column[j])
                temmp[i][j] -= Min_of_h_lighted;
            if (can_check_row[i] && can_check_column[j])
                temmp[i][j] += Min_of_h_lighted;
        }
}

int main()
{
    Hungarian_Method H;

    int rows, columns;


    cout << "Please Enter (row and column) number: " << endl;
    cin >> rows >> columns;

    cout << "Enter values in row in sequence: " << endl;

    float **arr;

    arr = new float *[rows];

    for (int i = 0; i < rows; i++)
    {
        arr[i] = new float[columns];
    }

    for (int i = 0; i < rows; i++)
    {
        cout << i + 1 << " - ";
        for (int j = 0; j < columns; j++)
            cin >> arr[i][j];
    }

    H.Give_pairs(arr, rows, columns);

    return 0;
}
