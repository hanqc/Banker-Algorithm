#include <iostream>
#include <iomanip>
using namespace std;

#define MaxNumber 20

static int n;
static int m;
static int Available[MaxNumber];//可利用资源
static int Max[MaxNumber][MaxNumber];//最大需求矩阵
static int Allocation[MaxNumber][MaxNumber];//已分配矩阵
static int Need[MaxNumber][MaxNumber];//还需求矩阵
static int Request[MaxNumber];//申请各类资源数量
static int SafeOrder[MaxNumber];//安全序列
static bool Finish[MaxNumber];//是否有足够资源分配给进程

static bool isDisplayAvaliable = true;
static char sourceName[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K' };	  //资源名称


void display()
{
	char processName[] = { '0', '1', '2', '3', '4', '5' };

	cout << "----------------------------------------------------------------------" << endl;
	cout << "当前进程个数为 n = " << n << endl;
	cout << "当前资源个数为 m = " << m << endl;
	cout << "系统可利用资源数情况如下：" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << setw(5) << sourceName[i] << " ";
	}
	cout << endl;
	cout << setw(5) << Available[0] << " ";
	cout << setw(5) << Available[1] << " ";
	cout << setw(5) << Available[2] << " " << endl;

	cout << "------------------------------------------------------------------------" << endl;

	cout << "进程名";
	cout << setw(10) << "Max[][]" << " ";
	cout << setw(15) << "Allocation[][]" << " ";
	cout << setw(10) << "Need[][]" << " ";
	if (isDisplayAvaliable)
	{
		cout << setw(15) << "Available[][]";
	}
	cout << endl;
	cout << setw(15);
	for (int i = 0; i < m; i++)
	{
		cout << sourceName[i] << setw(3);
	}

	cout << setw(5);
	for (int i = 0; i < m; i++)
	{
		cout << sourceName[i] << setw(3);
	}

	cout << setw(10);
	for (int i = 0; i < m; i++)
	{
		cout << sourceName[i] << setw(3);
	}

	if (isDisplayAvaliable)
	{
		cout << setw(5);
		for (int i = 0; i < m; i++)
		{
			cout << sourceName[i] << setw(3);
		}
	}
	cout << endl;

	bool OnlyOneLineAvaliable = true; 
	for (int i = 0; i < n; i++)
	{
		cout << setw(5) << "P" << processName[i];
		cout << setw(10);
		for (int j = 0; j < m; j++)
		{
			cout << Max[i][j] << setw(3);
		}

		cout << setw(5);
		for (int j = 0; j < m; j++)
		{
			cout << Allocation[i][j] << setw(3);
		}

		cout << setw(10);
		for (int j = 0; j < m; j++)
		{
			cout << Need[i][j] << setw(3);
		}

		if (isDisplayAvaliable&&OnlyOneLineAvaliable)
		{
			cout << setw(5);
			for (int i = 0; i < m; i++)
			{
				cout << Available[i] << setw(3);
			}
			OnlyOneLineAvaliable = false;
		}
		
		cout << endl;
	}

}
bool isSystemSafe()
{
	int work[MaxNumber];//工作向量
	for (int i = 0; i < m; i++)  
	{
		work[i] = Available[i];
	}
	for (int i = 0; i < n; i++)  
	{
		Finish[i] = false;
		SafeOrder[i] = -1;  //初始化安全序列
	}

	int FinishNumebr = 0;
	int isSafe;//用来记录每个资源是否安全
	int i = 0, j;
	while (i < n)
	{
		isSafe = 0;
		for (j = 0; j < m; j++)
		{
			if (Finish[i] == false && Need[i][j] <= work[j])
			{
				isSafe++;
			}
			else
				break;
		}

		if (isSafe == m)  //当且仅当进程对应的所有资源的数量都满足的时候才成立
		{
			Finish[i] = true;
			SafeOrder[FinishNumebr] = i;
			FinishNumebr++;
			for (j = 0; j < m; j++)
			{
				work[j] += Allocation[i][j];
			}
			i = 0;  //找到满足条件的进程后，从头开始再进行寻找
		}
		else
			i++;

		if (FinishNumebr == n)
		{
			cout << "********************************* 安全! *****************************" << endl;
			cout << "对应的安全序列为：" << endl;
			cout << "P" << SafeOrder[0];
			for (int i = 1; i < n; i++)
			{
				cout << "-->" << "P" << SafeOrder[i];
			}
			cout << endl;
			return true;
		}
	}

	cout << "***************************** 不安全! *****************************" << endl;
	return false;
}
 
void input()
{
	cout << "请输入总进程数：";
	cin >> n;
	cout << "请输入资源的种类数：";
	cin >> m;
	cout << "请输入" << m << "个系统可利用资源：";
	for (int i = 0; i < m; i++)
	{
		cin >> Available[i];
	}
	cout << "请输入已分配矩阵：" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> Allocation[i][j];
		}
	}
	cout << "请输入还需求矩阵：" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> Need[i][j];
		}
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			Max[i][j] = Need[i][j] + Allocation[i][j];
		}
	}
	cout << "*****************************程序开始*******************************" << endl;
	display();
	if (!isSystemSafe())
	{
		cout << "**************************当前运行结果*****************************" << endl;
		cout << "当前可利用资源已经不能满足任何进程的需求，故系统进入不安全状态，系统不分配资源！" << endl;
		cout << "****************************************************************" << endl;
		exit(EXIT_FAILURE);
	}

}



void bankerAlgorithm()
{
	int chooseProcess;
	char isContinue;

	while (1)
	{
		//判别等待还是不再分配
		bool isRequestNeedOK = true;
		bool isRequestAvailableOK = true;

		cout << "请输入要申请资源的进程号" << endl << "chooseProcess=";
		cin >> chooseProcess;
		cout << "请输入进程所请求的各类资源的数量：(A B C)" << endl;
		for (int i = 0; i < m; i++)
		{
			cin >> Request[i];
		}
		//输入错误判断
		for (int i = 0; i < m; i++)
		{
			if (Request[i] > Need[chooseProcess][i])
			{
				cout << "**************************当前运行结果*****************************" << endl;
				cout << "您输入的请求进程所对应的资源数量超过最大需求量，请重新输入！" << endl;
				isRequestNeedOK = false;
				continue;
			}
			if (Request[i] > Available[i])
			{
				cout << "**************************当前运行结果*****************************" << endl;
				cout << "您输入的请求进程的资源数量超过系统所供给的最大资源数量p"<<chooseProcess<<"必须等待，请重新输入！" << endl;
				isRequestAvailableOK = false;
				continue;
			}
		}

		for (int j = 0; j < m; j++)
		{
			Available[j] -= Request[j];
			Allocation[chooseProcess][j] += Request[j];
			Need[chooseProcess][j] -= Request[j];
		}
	

		cout << "----------------------------------------------------------------------" << endl;


		if (!isSystemSafe())   
		{
			for (int j = 0; j < m; j++)//恢复
			{
				Available[j] += Request[j];
				Allocation[chooseProcess][j] -= Request[j];
				Need[chooseProcess][j] += Request[j];
			}
			//Request满足和Need、Available，已不能再分配资源
			if (isRequestAvailableOK&&isRequestNeedOK)
			{
				cout << "**************************当前运行结果*****************************" << endl;
				cout << "当前可利用资源已经不能满足任何进程的需求，故系统进入不安全状态，系统不分配资源！" << endl;
				cout << "****************************************************************" << endl;
			}

		}

		cout << "尝试根据p"<<chooseProcess<<"发出的请求向量后的资源情况：" << endl;
		display();

		cout << "----------------------------------------------------------------------" << endl;
		cout << "是否继续输入请求变量request进行测试，是（Y）,否（N）" << endl;
		cout << "isContinue = ";
		cin >> isContinue;
		if (isContinue == 'Y' || isContinue == 'y')
		{
			continue;
		}
		else if (isContinue == 'N' || isContinue == 'n')
		{
			cout << "******************************程序结束*****************************" << endl;
			break;
		}

	}
}


int main()
{
	input();
	bankerAlgorithm();
	return 0;
}