#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


class LCS {
public:
	int LongestCommonSubsequence(string text1, string text2) {
		int i, j, longest_length;
		int len1 = text1.size();
		int len2 = text2.size();
		int dp[100][100];
		memset(dp, 0, sizeof(dp));
		for (i = 1; i <= len1; i++) { 
			for (j = 1; j <= len2; j++) { 
				if (text1[i - 1] == text2[j - 1])                
					dp[i][j] = dp[i - 1][j - 1] + 1;            
				else if (dp[i - 1][j] > dp[i][j - 1])                
					dp[i][j] = dp[i - 1][j];            
				else                
					dp[i][j] = dp[i][j - 1]; 
			} 
		}
		
		longest_length = dp[len1][len2];
		return longest_length;
	}
};

struct Node {
		int starttime = 0;
		int endtime = 0;
		int profit = 0;
};

bool cmp(Node a, Node b) {
		if (a.starttime == b.starttime) return a.endtime < b.endtime;
		return a.starttime < b.starttime;
}

class WIS {
public:
	int WeightedIntervalScheduling(vector<int> &startTime, vector<int> &endTime, vector<int> &Profit) {
		int dp[1000];
		Node node[1000];
        int maximum_profit = 0;
		int len = startTime.size();

		for (int i = 0; i < len; i++)
		{
			node[i].starttime = startTime[i];
			node[i].endtime = endTime[i];
			node[i].profit = Profit[i];
		}

		sort(node, node + len, cmp);

		for (int i = 0; i < len; i++)
		{
			dp[i] = node[i].profit;
			for (int j = 0; j <= i; j++)
			{
				if (node[j].endtime <= node[i].starttime)
					dp[i] = max(dp[i], dp[j] + node[i].profit);
			}
		}
		
		for (int i = 0; i < len; i++)
			maximum_profit = max(maximum_profit, dp[i]);
		return maximum_profit;
	}
};

class KP {
public:
	int KnapsackProblem(vector<int> &weight, vector<int> &value, int W) {
		int dp[100][1000];
		int len = weight.size();
		int maximum_value = 0;

		for (int i = 0; i <= len; i++)  dp[i][0] = 0;
		for (int j = 0; j <= W; j++)    dp[0][j] = 0;
		
		for (int i = 1; i <= len; i++) {
			for (int j = 1; j <= W; j++)
				if (j < weight[i - 1])
					dp[i][j] = dp[i - 1][j];
				else
					dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i - 1]] + value[i - 1]);  
		}

		maximum_value = dp[len][W];

		return maximum_value;
	}
};


// For testing
int main(int argc, const char * argv[]) {

	//*********** Test Longest Common Subsequence ***********//
	string text1 = "springtime";
	string text2 = "printing";
	LCS lcs = LCS();
	cout << "Test Longest Common Subsequence..." << endl;
	cout << lcs.LongestCommonSubsequence(text1, text2) << endl;
	cout << "The expected output: 6" << endl;
	cout << endl;

	//********** Test Weighted Interval Scheduling **********//
	vector<int> startTime = { 1,2,3,4,6 };
	vector<int> endTime = { 3,5,9,6,9 };
	vector<int> Profit = { 20,20,100,70,60 };
	WIS wis = WIS();
	cout << "Test Weighted Interval Scheduling..." << endl;
	cout << wis.WeightedIntervalScheduling(startTime, endTime, Profit) << endl;
	cout << "The expected output: 150" << endl;
	cout << endl;

	//*************** Test Knapsack Problem ****************//
	vector<int> weight = { 1, 2, 5, 6, 7 };
	vector<int> value = { 1, 6, 18, 22, 28 };
	int W = 11;
	KP kp = KP();
	cout << "Test Knapsack Problem..." << endl;
	cout << kp.KnapsackProblem(weight, value, W) << endl;
	cout << "The expected output: 40" << endl;
	cout << endl;
	
                system("pause");
	return 0;
}
