#include <iostream>
#include <iomanip>
using namespace std;

#define MaxNumber 20

static int n;
static int m;
static int Available[MaxNumber];//��������Դ
static int Max[MaxNumber][MaxNumber];//����������
static int Allocation[MaxNumber][MaxNumber];//�ѷ������
static int Need[MaxNumber][MaxNumber];//���������
static int Request[MaxNumber];//���������Դ����
static int SafeOrder[MaxNumber];//��ȫ����
static bool Finish[MaxNumber];//�Ƿ����㹻��Դ���������

static bool isDisplayAvaliable = true;
static char sourceName[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K' };	  //��Դ����


void display()
{
	char processName[] = { '0', '1', '2', '3', '4', '5' };

	cout << "----------------------------------------------------------------------" << endl;
	cout << "��ǰ���̸���Ϊ n = " << n << endl;
	cout << "��ǰ��Դ����Ϊ m = " << m << endl;
	cout << "ϵͳ��������Դ��������£�" << endl;
	for (int i = 0; i < m; i++)
	{
		cout << setw(5) << sourceName[i] << " ";
	}
	cout << endl;
	cout << setw(5) << Available[0] << " ";
	cout << setw(5) << Available[1] << " ";
	cout << setw(5) << Available[2] << " " << endl;

	cout << "------------------------------------------------------------------------" << endl;

	cout << "������";
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
	int work[MaxNumber];//��������
	for (int i = 0; i < m; i++)  
	{
		work[i] = Available[i];
	}
	for (int i = 0; i < n; i++)  
	{
		Finish[i] = false;
		SafeOrder[i] = -1;  //��ʼ����ȫ����
	}

	int FinishNumebr = 0;
	int isSafe;//������¼ÿ����Դ�Ƿ�ȫ
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

		if (isSafe == m)  //���ҽ������̶�Ӧ��������Դ�������������ʱ��ų���
		{
			Finish[i] = true;
			SafeOrder[FinishNumebr] = i;
			FinishNumebr++;
			for (j = 0; j < m; j++)
			{
				work[j] += Allocation[i][j];
			}
			i = 0;  //�ҵ����������Ľ��̺󣬴�ͷ��ʼ�ٽ���Ѱ��
		}
		else
			i++;

		if (FinishNumebr == n)
		{
			cout << "********************************* ��ȫ! *****************************" << endl;
			cout << "��Ӧ�İ�ȫ����Ϊ��" << endl;
			cout << "P" << SafeOrder[0];
			for (int i = 1; i < n; i++)
			{
				cout << "-->" << "P" << SafeOrder[i];
			}
			cout << endl;
			return true;
		}
	}

	cout << "***************************** ����ȫ! *****************************" << endl;
	return false;
}
 
void input()
{
	cout << "�������ܽ�������";
	cin >> n;
	cout << "��������Դ����������";
	cin >> m;
	cout << "������" << m << "��ϵͳ��������Դ��";
	for (int i = 0; i < m; i++)
	{
		cin >> Available[i];
	}
	cout << "�������ѷ������" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			cin >> Allocation[i][j];
		}
	}
	cout << "�����뻹�������" << endl;
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
	cout << "*****************************����ʼ*******************************" << endl;
	display();
	if (!isSystemSafe())
	{
		cout << "**************************��ǰ���н��*****************************" << endl;
		cout << "��ǰ��������Դ�Ѿ����������κν��̵����󣬹�ϵͳ���벻��ȫ״̬��ϵͳ��������Դ��" << endl;
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
		//�б�ȴ����ǲ��ٷ���
		bool isRequestNeedOK = true;
		bool isRequestAvailableOK = true;

		cout << "������Ҫ������Դ�Ľ��̺�" << endl << "chooseProcess=";
		cin >> chooseProcess;
		cout << "���������������ĸ�����Դ��������(A B C)" << endl;
		for (int i = 0; i < m; i++)
		{
			cin >> Request[i];
		}
		//��������ж�
		for (int i = 0; i < m; i++)
		{
			if (Request[i] > Need[chooseProcess][i])
			{
				cout << "**************************��ǰ���н��*****************************" << endl;
				cout << "������������������Ӧ����Դ����������������������������룡" << endl;
				isRequestNeedOK = false;
				continue;
			}
			if (Request[i] > Available[i])
			{
				cout << "**************************��ǰ���н��*****************************" << endl;
				cout << "�������������̵���Դ��������ϵͳ�������������Դ����p"<<chooseProcess<<"����ȴ������������룡" << endl;
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
			for (int j = 0; j < m; j++)//�ָ�
			{
				Available[j] += Request[j];
				Allocation[chooseProcess][j] -= Request[j];
				Need[chooseProcess][j] += Request[j];
			}
			//Request�����Need��Available���Ѳ����ٷ�����Դ
			if (isRequestAvailableOK&&isRequestNeedOK)
			{
				cout << "**************************��ǰ���н��*****************************" << endl;
				cout << "��ǰ��������Դ�Ѿ����������κν��̵����󣬹�ϵͳ���벻��ȫ״̬��ϵͳ��������Դ��" << endl;
				cout << "****************************************************************" << endl;
			}

		}

		cout << "���Ը���p"<<chooseProcess<<"�������������������Դ�����" << endl;
		display();

		cout << "----------------------------------------------------------------------" << endl;
		cout << "�Ƿ���������������request���в��ԣ��ǣ�Y��,��N��" << endl;
		cout << "isContinue = ";
		cin >> isContinue;
		if (isContinue == 'Y' || isContinue == 'y')
		{
			continue;
		}
		else if (isContinue == 'N' || isContinue == 'n')
		{
			cout << "******************************�������*****************************" << endl;
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