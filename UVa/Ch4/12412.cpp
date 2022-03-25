#include <cstdio>
#include <cstring>
#include <algorithm>
#define EPS 1e-5
using namespace std; 

class student
{
public:
	char sid[20] = { 0 };
	int cid = 0;
	char name[20];
	int c = 0, m = 0, e = 0, p = 0;
	int sum()
	{
		return c + m + e + p;
	}
}stu[1000];
int res[1000] = { -1 }, cnt = 0;
void show()
{
	printf("Welcome to Student Performance Management System (SPMS).\n\n");
	printf("1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
}
void add()
{
	while (true)
	{
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		scanf("%s", &stu[cnt].sid);
		if (!strcmp(stu[cnt].sid, "0"))
			break;
		int flag = 0;
		for (int i = 0; i < cnt; i++)
			if (!strcmp(stu[i].sid, stu[cnt].sid))
			{
				printf("Duplicated SID.\n");
				flag = 1;
				break;
			}
		scanf("%d%s%d%d%d%d", &stu[cnt].cid, &stu[cnt].name, &stu[cnt].c, &stu[cnt].m, &stu[cnt].e, &stu[cnt].p);
		if (flag)
			continue;
		cnt++;
	}
}
int showRank(int x)
{
	int r = 1, s = stu[x].sum();
	for (int i = 0; i < cnt; i++)
		if (stu[i].name[0] != '?' && stu[i].sum() > s)
			r++;
	return r;
}
int query()
{
	memset(res, -1, sizeof(res));
	char s[20];
	int num = 0;
	scanf("%s", &s);
	if (s[0] >= '0'&&s[0] <= '9')
	{
		if (!strcmp(s, "0"))
			return -1;

		for (int i = 0; i < cnt; i++)
			if (!strcmp(stu[i].sid, s))
				res[num++] = i;
	}
	else
	{
		for (int i = 0; i < cnt; i++)
			if (!strcmp(stu[i].name, s))
				res[num++] = i;
	}
	return num;
}
void rem()
{
	while (true)
	{
		printf("Please enter SID or name. Enter 0 to finish.\n");
		int num = query();
		if (num == -1)
			break;
		for (int i = 0; i < num; i++)
		{
			stu[res[i]].c = 0;
			stu[res[i]].m = 0;
			stu[res[i]].e = 0;
			stu[res[i]].p = 0;
			stu[res[i]].sid[0] = '?';
			stu[res[i]].name[0] = '?';
		}
		printf("%d student(s) removed.\n", num);
	}
}
void que()
{
	while (true)
	{
		printf("Please enter SID or name. Enter 0 to finish.\n");
		int num = query();
		if (num == -1)
			break;
		for (int i = 0; i < num; i++)
		{
			int rank = showRank(res[i]);
			printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank, stu[res[i]].sid, stu[res[i]].cid, stu[res[i]].name, stu[res[i]].c, stu[res[i]].m, stu[res[i]].e, stu[res[i]].p, stu[res[i]].sum(), stu[res[i]].sum() / 4.0 + EPS);
		}
	}
}
void showSta()
{
	printf("Please enter class ID, 0 for the whole statistics.\n");
	int cmd;
	double avg[5] = { 0 };
	scanf("%d", &cmd);
	int peo = 0, cs = 0, cp = 0, ms = 0, mp = 0, es = 0, ep = 0, ps = 0, pp = 0;
	int pass[5] = { 0 };

	for (int i = 0; i < cnt; i++)
		if (stu[i].name[0] != '?' && (stu[i].cid == cmd || cmd == 0))
		{
			int num = 0;
			peo++;
			cs += stu[i].c;
			ms += stu[i].m;
			es += stu[i].e;
			ps += stu[i].p;
			if (stu[i].c >= 60)
			{
				num++;
				cp++;
			}
			if (stu[i].m >= 60)
			{
				num++;
				mp++;
			}
			if (stu[i].e >= 60)
			{
				num++;
				ep++;
			}
			if (stu[i].p >= 60)
			{
				num++;
				pp++;
			}
			pass[num]++;
		}
	if (peo)
	{
		avg[0] = double(cs) / peo + EPS;
		avg[1] = double(ms) / peo + EPS;
		avg[2] = double(es) / peo + EPS;
		avg[3] = double(ps) / peo + EPS;
	}
	printf("Chinese\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", avg[0], cp, peo - cp);
	printf("Mathematics\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", avg[1], mp, peo - mp);
	printf("English\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", avg[2], ep, peo - ep);
	printf("Programming\nAverage Score: %.2f\nNumber of passed students: %d\nNumber of failed students: %d\n\n", avg[3], pp, peo - pp);
	printf("Overall:\nNumber of students who passed all subjects: %d\nNumber of students who passed 3 or more subjects: %d\nNumber of students who passed 2 or more subjects: %d\n", pass[4], pass[3] + pass[4], pass[2] + pass[3] + pass[4]);
	printf("Number of students who passed 1 or more subjects: %d\nNumber of students who failed all subjects: %d\n\n", pass[1] + pass[2] + pass[3] + pass[4], pass[0]);
}
int main()
{
	//freopen("in2.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int cmd;
	while (show(), scanf("%d", &cmd) && cmd != 0)
	{
		switch (cmd)
		{
		case 1:
			add();
			break;
		case 2:
			rem();
			break;
		case 3:
			que();
			break;
		case 4:
			printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");
			//printf("Showing the ranklist hurts students’ self-esteem. Don’t do that.\n");
			break;
		case 5:
			showSta();
			break;
		}
	}
	return 0;
}