#include <iostream>
using namespace std;

int val[10005][10005];
bool rowTaken[10005], colTaken[10005];

int n;
int fixed(int col, int row)
{

    int maxBand = 0;
    int band;
    int lastCnt = 0;
    for (int i = 0; i < col; i++)
    {
        band = 0;
        lastCnt = 0;
        for (int j = 0; j < n; j++)
        {
            if (val[j][i])
            {
                if (j < row)
                    band = max(band, (abs(j - i) + 1));
                else
                {
                    lastCnt++;
                    band = max(band, abs(i - (lastCnt + row - 1)) + 1);
                }
            }
        }

        maxBand = max(maxBand, band);

    }
    for (int i = 0; i < row; i++)
    {
        band = 0;
        lastCnt = 0;
        for (int j = 0; j < n; j++)
        {
            if (val[i][j])
            {
                if (j < col)
                    band = max(band, (abs(j - i) + 1));
                else
                {
                    lastCnt++;
                    band = max(band, abs(i - (lastCnt + col - 1)) + 1);
                }
            }
        }

        maxBand = max(maxBand, band);

    }
    return maxBand;
}

int unfixed(int col, int row)
{
    int maxband = 0, band;
    for (int i = row; i < n; i++)
    {
        band = 0;
        for (int j = col; j < n; j++)
        {
            if (val[i][j])
                band++;
        }

        maxband = max(maxband, band);
    }
    for (int i = col; i < n; i++)
    {
        band = 0;
        for (int j = row; j < n; j++)
        {
            if (val[j][i])
                band++;
        }

        maxband = max(maxband, band);
    }

    return (maxband + 1) / 2;
}

int getMaxBand(int col, int row)
{
    return max(fixed(col, row), unfixed(col, row));
}

void swaprows(int r1, int r2)
{
    for (int i = 0; i < n; i++)
    {
        swap(val[r1][i], val[r2][i]);
    }
}
void swapcols(int c1, int c2)
{
    for (int i = 0; i < n; i++)
    {
        swap(val[i][c1], val[i][c2]);
    }
}

void print()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << (val[i][j] ? 'X' : '0') << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    freopen("input.in", "r", stdin);

    cin >> n;
    char c;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> c;
            val[i][j] = (c == 'X');
        }
    }

    int maxband = 1e9, row, col;
    for (int i = 0; i < n - 1; i++)
    {
        maxband = 1e9;
        for (int j = 0; j < n; j++)
        {
            if (!colTaken[j])
            {
                swapcols(i, j);
                if (getMaxBand(i + 1, i) <= maxband)
                {
                    maxband = getMaxBand(i + 1, i);
                    col = j;
                }
                swapcols(i, j);
            }
        }

        colTaken[col] = 1;
        swapcols(i, col);

        maxband = 1e9;
        for (int j = 0; j < n; j++)
        {
            if (!rowTaken[j])
            {
                swaprows(i, j);
                if (getMaxBand(i + 1, i + 1) <= maxband)
                {
                    maxband = getMaxBand(i + 1, i);
                    row = j;
                }
                swaprows(i, j);
            }
        }
        rowTaken[row] = 1;
        swaprows(i, row);

    }

    cout << getMaxBand(n, n) << endl;
    print();
}
