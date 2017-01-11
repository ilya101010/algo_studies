#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


#define MAX_N 1000

#define vit vector<int>::iterator

class stree // sum
{
private:
	vector<int> T;

	vit begin, end;

	void build(int v, vit l, vit r)
	{
		cout << v << "; " << distance(begin,l) << "; " << distance(begin,r) << endl;
		if(l == r)
		{
			T[v] = *l;
		}
		else
		{
			build(2*v, l, l+distance(l,r)/2);
			build(2*v+1, l+distance(l,r)/2+1, r);
			T[v] = T[v*2]+T[v*2+1];
		}
	}

	int Sum(int v, vit l, vit r, vit vl, vit vr)
	{
		if(l > r)
			return 0;
		cout << v << "; " << distance(begin,l) << "; " << distance(begin,r) << "; " << distance(begin,vl) << "; " << distance(begin,vr) << endl;
		if(l == vl && r == vr)
			{
				cout << "# " << T[v] << endl;
				return T[v];
			}
		// inside our segment
		auto vm = vl+distance(vl,vr)/2;
		return Sum(2*v,l,min(r,vm),vl,vm)+Sum(2*v+1,max(l,vm+1),r,vm+1,vr);
	}
public:
	stree(vit begin, vit end)
	{
		this->begin = begin; this->end = end;
		T.resize(1+4*distance(begin,end));
		cout << "build" << endl;
		build(1, begin, end-1);
	}

	void update()
	{
		for(int i = 0; i<T.size(); i++)
			cout << T[i] << " ";
		cout << endl;
	}

	int sum(int l, int r)
	{
		return Sum(1,begin+l,begin+r,begin,end-1);
	}

	~stree()
	{
	}
	
};

int main()
{
	vector<int> v{1,2,3,4,5,6,7,8};
	stree s(v.begin(),v.end());
	cout << s.sum(1,3);
	cout << endl << endl;
	s.update();
}