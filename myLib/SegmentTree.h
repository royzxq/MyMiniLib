class SegmentTree
{
public:
	SegmentTree(int arr[], n){
		int x = int(ceil(log2(n)));
		int max_size = 2*(int)pow(2,x) - 1;
		st = new int [max_size];
		construct(arr,0,n-1,st,0);
	}
	~SegmentTree(){
		delete [] st;
		st = 0;
	}
	void update(int *arr, int *st, int n, int i , int new_val){
		if(i<0 || i>n-1){
			return;
		}
		int diff = new_val - arr[i];
		arr[i] = new_val;
		updateUtil(st,0,n-1,i,diff,0); 
	}
	int getSum(int* arr, int *st, int n, int qs, int qe){
		return getSumUtil(st,0, n-1, qs, qe, 0);
	}
private:
	int * st;
	int getMid(int start, int end){
		return (end-start)/2 + start;
	}

	int getSumUtil(int * st, int ss, int se, int qs, int qe, int index){
		if(qs<=ss && qe>=se)
			return st[index];
		if(se < qs || ss>qe){
			return 0;
		}
		int mid = getMid(ss,se);
		return getSumUtil(st,ss,mid,qs,qe,2*index +1) + getSumUtil(st,mid+1,se,qs,qe,2*index + 2);
	}
	void updateUtil(int * st, int ss, int se, int i , int diff, int index){
		if(i<ss || i>se){
			return;
		}
		st[index] += diff;
		if(se != ss){
			int mid = getMid(ss,se);
			updateUtil(st,ss,mid,i,diff,2*index + 1);
			updateUtil(st,mid+1,se,i,diff,2*index + 2);
		}
	}
	void construct(int arr[], int ss, int se, int *st, int si){
		if(se == ss){
			st[si] = arr[ss];
			return ;
		}
		int mid = getMid(ss,se);
		st[si] = construct(arr,ss,mid,st,2*si + 1) + construct(arr,mid+1,se,st,2*si+2);
		return ;
	}


	/* data */
};