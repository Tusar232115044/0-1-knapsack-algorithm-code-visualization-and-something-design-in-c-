#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

void clearScreen()
{
    cout << "\033[2J\033[H";
}

void printTable(vector<vector<int> > &dp, vector<int> &weights, vector<int> &values, int W)
{
    clearScreen();

    int n = weights.size();
    cout << "\033[1;31mKnapsack Table Progress:\n\033[0m" << endl;
    cout << "   ";
    for (int w = 0; w <= W; w++)
        cout << "\033[1;34m" << w << "  \033[0m";
    cout << "\n  ";
    for (int w = 0; w <= W; w++)
        cout << "---";
    cout << "\n";

    for (int i = 0; i <= n; i++)
    {
        if (i > 0)
            cout << "\033[1;32m" << weights[i - 1] << " | \033[0m";
        else
            cout << "  | ";

        for (int w = 0; w <= W; w++)
        {
            if (dp[i][w] > 0)
                cout << "\033[1;31m" << dp[i][w] << "  \033[0m";
            else
                cout << dp[i][w] << "  ";
        }
        cout << "\n";
    }
    this_thread::sleep_for(chrono::milliseconds(500));
}

int knapsack(vector<int> &weights, vector<int> &values, int W)
{
    int n = weights.size();
    vector<vector<int> > dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= W; w++)
        {
            if (weights[i - 1] <= w)
                dp[i][w] = max(dp[i - 1][w], values[i - 1] + dp[i - 1][w - weights[i - 1]]);
            else
                dp[i][w] = dp[i - 1][w];

            printTable(dp, weights, values, W);
        }
    }
    return dp[n][W];
}

int main()
{
    while (1)
    {
        cout << endl;
        int n, W;
        cout << "Enter number of items : ";
        cin >> n;
        cout << endl;
        vector<int> weights(n), values(n);

        cout << "Enter weights of items : ";
        for (int i = 0; i < n; i++)
        {
            cin >> weights[i];
        }
        cout << endl;
        cout << "Enter profits of items : ";
        for (int i = 0; i < n; i++)
        {
            cin >> values[i];
        }
        cout << endl;
        cout << "Enter knapsack capacity : ";
        cin >> W;
        cout << endl;
        int maxProfit = knapsack(weights, values, W);

        cout << "\n\033[1;33mMaximum Profit : " << maxProfit << "\033[0m\n";
        cout << endl;
        cout << "\033[1;34mDo you want to run again ?\n\033[0m";
        cout << endl;
        int num1;
        cout << "\033[1;32m1. YES\033[0m" << "\033[1;33m , \033[0m" << "\033[1;31m2. NO \033[0m" << "\033[1;33m: \033[0m";
        cin >> num1;
        if (num1 != 1)
        {
            cout << "\n\033[1;31mBreak.\033[0m";
            break;
        }
    }
    return 0;
}
