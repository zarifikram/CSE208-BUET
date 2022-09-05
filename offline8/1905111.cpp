#include <iostream>
#include <vector>
#include <string>
#include "HashTable.h"
#include <chrono>
using namespace std;
int p[205];
double searchBefore[4][6];
double searchAfter[4][6];
string techniques[] = {"Seperate chaining", "Linear Probing   ", "Quadratic Probing", "Double Hashing   "};
double probesBefore[4][6], probesAfter[4][6];

vector<string> getRandomStrings(int nStrings)
{
    vector<string> strings(nStrings, "");
    for (int i = 0; i < nStrings; i++)
    {
        for (int k = 0; k < 7; k++)
            strings[i] += ('a' + rand() % 26);
    }
    return strings;
}

int main()
{
    int N, nStringsInserted, nStringsDeleted;
    vector<string> stringPool = getRandomStrings(1000000);
    double loadFactor;
    cin >> N;

    loadFactor = 0.4;
    cout << "Load Factor    AVG SEARCH TIME    AVG SEARCH TIME" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << loadFactor << "\t\t\t";
        HashLinked hl(N);
        vector<string> chosenStrings, deletedStrings;
        nStringsInserted = (int)(N * loadFactor);
        for (int k = 0; k < nStringsInserted; k++)
        {
            string chosenString = stringPool[rand() % 1000];
            chosenStrings.push_back(chosenString);
            hl.insert(chosenString, k + 1);
        }
        int p = (int)(nStringsInserted / 10);

        auto start = chrono::steady_clock::now();
        for (int k = 0; k < p; k++)
        {

            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            hl.search(chosenString);
        }
        auto end = chrono::steady_clock::now();
        searchBefore[0][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchBefore[0][i]
             << " ns"
             << "\t\t\t";
        nStringsDeleted = p;
        for (int k = 0; k < nStringsDeleted; k++)
            auto end = chrono::steady_clock::now();
        {
            string deletedString = chosenStrings[rand() % chosenStrings.size()];
            deletedStrings.push_back(deletedString);
            hl.deleteElement(deletedString);
        }
        start = chrono::steady_clock::now();
        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = deletedStrings[rand() % deletedStrings.size()];
            hl.search(chosenString);
        }

        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            hl.search(chosenString);
        }
        end = chrono::steady_clock::now();
        searchAfter[0][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchAfter[0][i]
             << " ns" << endl;
        loadFactor += 0.1;
    }
    // return 0;

    loadFactor = 0.4;
    cout << "Load Factor    AVG NUMBER OF PROBES    AVG SEARCH TIME   AVG NUMBER OF PROBES     AVG SEARCH TIME" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << loadFactor << "\t\t\t";
        HashLinear hlin(N);
        vector<string> chosenStrings, deletedStrings;
        nStringsInserted = (int)(N * loadFactor);
        for (int k = 0; k < nStringsInserted; k++)
        {
            string chosenString = stringPool[rand() % 1000];
            chosenStrings.push_back(chosenString);
            hlin.insert(chosenString, k + 1);
        }
        int p = (int)(nStringsInserted / 10);
        auto start = chrono::steady_clock::now();
        for (int k = 0; k < p; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            probesBefore[1][i] += hlin.search(chosenString);
        }
        cout << probesBefore[1][i] / p << "\t\t\t";
        auto end = chrono::steady_clock::now();
        searchBefore[1][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchBefore[1][i]
             << " ns"
             << "\t\t\t";
        nStringsDeleted = p;
        for (int k = 0; k < nStringsDeleted; k++)
        {
            string deletedString = chosenStrings[rand() % chosenStrings.size()];
            deletedStrings.push_back(deletedString);
            hlin.deleteElement(deletedString);
        }
        start = chrono::steady_clock::now();
        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = deletedStrings[rand() % deletedStrings.size()];
            probesAfter[1][i] += hlin.search(chosenString);
        }
        cout << probesAfter[1][i] / p << "\t\t\t";

        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            probesAfter[1][i] += hlin.search(chosenString);
        }
        end = chrono::steady_clock::now();
        searchAfter[1][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchAfter[1][i]
             << " ns" << endl;
        probesBefore[1][i] /= p;
        probesAfter[1][i] /= p;
        loadFactor += 0.1;
    }

    loadFactor = 0.4;
    cout << "Load Factor   AVG NUMBER OF PROBES    AVG SEARCH TIME    AVG NUMBER OF PROBES    AVG SEARCH TIME" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << loadFactor << "\t\t\t";
        HashQuadratic hquad(N);
        vector<string> chosenStrings, deletedStrings;
        nStringsInserted = (int)(N * loadFactor);
        for (int k = 0; k < nStringsInserted; k++)
        {
            string chosenString = stringPool[rand() % 1000];
            chosenStrings.push_back(chosenString);
            hquad.insert(chosenString, k + 1);
        }
        int p = (int)(nStringsInserted / 10);
        auto start = chrono::steady_clock::now();
        for (int k = 0; k < p; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            probesBefore[2][i] += hquad.search(chosenString);
        }
        cout << probesBefore[2][i] / p << "\t\t\t";
        auto end = chrono::steady_clock::now();
        searchBefore[2][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchBefore[2][i]
             << " ns"
             << "\t\t\t";
        nStringsDeleted = p;
        for (int k = 0; k < nStringsDeleted; k++)
        {
            string deletedString = chosenStrings[rand() % chosenStrings.size()];
            deletedStrings.push_back(deletedString);
            hquad.deleteElement(deletedString);
        }
        start = chrono::steady_clock::now();
        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = deletedStrings[rand() % deletedStrings.size()];
            probesAfter[2][i] += hquad.search(chosenString);
        }

        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            probesAfter[2][i] += hquad.search(chosenString);
        }
        cout << probesAfter[2][i] / p << "\t\t\t";
        end = chrono::steady_clock::now();
        searchAfter[2][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchAfter[2][i]
             << " ns" << endl;
        loadFactor += 0.1;
        probesBefore[2][i] /= p;
        probesAfter[2][i] /= p;
    }

    loadFactor = 0.4;
    cout << "Load Factor    AVG NUMBER OF PROBES    AVG SEARCH TIME    AVG NUMBER OF PROBES    AVG SEARCH TIME" << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << loadFactor << "\t\t\t";
        DoubleHash dh(N);
        vector<string> chosenStrings, deletedStrings;
        nStringsInserted = (int)(N * loadFactor);
        for (int k = 0; k < nStringsInserted; k++)
        {
            string chosenString = stringPool[rand() % 1000];
            chosenStrings.push_back(chosenString);
            dh.insert(chosenString, k + 1);
        }
        int p = (int)(nStringsInserted / 10);
        auto start = chrono::steady_clock::now();
        for (int k = 0; k < p; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            probesBefore[3][i] += dh.search(chosenString);
        }
        cout << probesBefore[3][i] / p << "\t\t\t";
        auto end = chrono::steady_clock::now();
        searchBefore[3][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchBefore[3][i]
             << " ns"
             << "\t\t\t";
        nStringsDeleted = p;
        for (int k = 0; k < nStringsDeleted; k++)
        {
            string deletedString = chosenStrings[rand() % chosenStrings.size()];
            deletedStrings.push_back(deletedString);
            dh.deleteElement(deletedString);
        }
        start = chrono::steady_clock::now();
        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = deletedStrings[rand() % deletedStrings.size()];
            probesAfter[3][i] += dh.search(chosenString);
        }

        for (int k = 0; k < p / 2; k++)
        {
            string chosenString = chosenStrings[rand() % chosenStrings.size()];
            probesAfter[3][i] += dh.search(chosenString);
        }
        cout << probesAfter[3][i] / p << "\t\t\t";
        end = chrono::steady_clock::now();
        searchAfter[3][i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count() / p;
        cout << ""
             << searchAfter[3][i]
             << " ns" << endl;
        probesBefore[3][i] /= p;
        probesAfter[3][i] /= p;
        loadFactor += 0.1;
    }

    for (int i = 0; i < 4; i++)
    {
        double sums[] = {0, 0, 0, 0};
        for (int k = 0; k < 6; k++)
        {
            sums[0] += searchBefore[i][k];
            sums[1] += probesBefore[i][k];
            sums[2] += searchAfter[i][k];
            sums[3] += probesAfter[i][k];
        }
        if (!i)
            cout << techniques[i] << "\t" << sums[0] / 6 << "ns\t" << "N/A" << "\t" << sums[2] / 6 << "ns\t" << "N/A" << "\t" << endl;
        else
            cout << techniques[i] << "\t" << sums[0] / 6 << "ns\t" << sums[1] / 6 << "\t" << sums[2] / 6 << "ns\t" << sums[3] / 6 << "\t" << endl;
    }
}