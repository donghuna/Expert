#define rint register int

int countingN[65555];
int T[1000005];

void countingSort(int arraySize, int *arr) {
	// const int makePlus = 32768; // == 1 << 15 , 값을 0 ~ 65535 으로 만들어주자.
	rint i;
	// 카운팅
	for (i = 0; i < arraySize; ++i)
	{
		arr[i] += (1 << 15);
		countingN[arr[i]]++;
	}

	// 누적
	for (i = 1; i < 65555; ++i)
	{
		countingN[i] += countingN[i - 1];
	}

	for (i = arraySize - 1; i >= 0 ; --i)
	{
		/*
		int idx = countingN[arr[i] + makePlus] - 1;
		countingN[arr[i] + makePlus]--;
		T[idx] = arr[i];
		*/
		T[--countingN[arr[i]]] = arr[i];
	}
}

int query(int idx) {
	return T[idx] - (1 << 15);
}
