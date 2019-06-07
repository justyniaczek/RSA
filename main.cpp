#include<iostream>
#include<cstdlib>
#include<vector>
#include<math.h>

using namespace std;

void sito(bool *tab, unsigned int n)
{
	for (int i = 2; i*i <= n; i++)
	{                         
								
		if (!tab[i])            
			for (int j = i * i; j <= n; j += i) /
				tab[j] = 1;     
	}
}


int euklidesAlgorithm(int a, int b, int& x, int& y, bool start = true)
{
	static int staticX[2] = {};
	static int staticY[2] = {};

	int r = a % b;
	int q = (a - r) / b;

	std::cout << a << " = " << q << " * " << b << " + " << r << "\n";

	if (r != 0) {
		// Wyczyść wartości x i y, jeśli jest to pierwsze wywołanie funkcji
		if (start) {
			staticX[0] = 0;
			staticX[1] = 1;
			staticY[0] = 1;
			staticY[1] = -q;
		}
		else {
			int tempX = staticX[1];
			staticX[1] = staticX[0] - staticX[1] * q;
			staticX[0] = tempX;

			int tempY = staticY[1];
			staticY[1] = staticY[0] - staticY[1] * q;
			staticY[0] = tempY;
		}

		std::cout << "x = " << staticX[1] << " y = " << staticY[1] << "\n\n";

		return euklidesAlgorithm(b, r, x, y, false);
	}

	x = staticX[1];
	y = staticY[1];

	return b;
}

int decToBinSize(int dec)
{
	for (int i = 0; ; i++) {
		if (pow(2, i) > dec) {
			return i;
		}
	}
}

std::vector<bool> decToBin(int dec)
{
	int size = decToBinSize(dec);
	std::vector<bool> bin;

	for (int i = size - 1; i >= 0; i--) {
		if (pow(2, i) <= dec) {
			dec -= pow(2, i);
			bin.push_back(1);
		}
		else {
			bin.push_back(0);
		}
	}

	return bin;
}

unsigned long long int modulo(unsigned long long int a, const unsigned long long int b, unsigned long long int c)
{
	std::vector<bool> binB = decToBin(b);
	int binSize = decToBinSize(b);

	unsigned long long int currentNumber = a; // pow(a, 1)
	currentNumber %= c;

	unsigned long long int result = 1;

	if (binB[binSize - 1] == 1) {  // binb to potega zapisana w formie binarnej
		result *= currentNumber;
		result %= c;
	}

	for (unsigned long long int i = 1; i < binSize; i++) {
		currentNumber = pow(currentNumber, 2);
		currentNumber %= c;

		if (binB[binSize - 1 - i] == 1) {
			result *= currentNumber;
			result %= c;
		}
	}

	return result;
}


void rsa()
{
	int finalNumber;
	bool *tab;

	//cout << "Podaj zakres górny przedziału: ";
	finalNumber = 2800000;

	tab = new bool[finalNumber + 1];
	for (int i = 2; i <= finalNumber; i++) //zerowanie tablicy
		tab[i] = 0;

	sito(tab, finalNumber); //przesianie liczb

	//cout << "Kolejne liczby pierwsze z przedziału [2.." << finalNumber << "]: ";
	int primecounter = 0;

	int p = 0;
	int q = 0;
	cout << "Wpisz liczbe 1: ";
	int n1;
	cin >> n1;
	cout << "Wpisz liczbe 2: ";
	int n2;
	cin >> n2;
	unsigned long long int liczba;
	for (int i = 2; i <= finalNumber; i++)
		if (!tab[i] && (p == 0 || q == 0)) {
			//  cout<<i<<" ";
			liczba = i;
			primecounter++;
			if (primecounter == n1)
				p = liczba;
			if (primecounter == n2)
				q = liczba;
		}

	int n = p * q;
	cout << "n=" << n << endl;

	int m = (p - 1)*(q - 1);
	cout << "m=" << m << endl;

	int e, x, y;
	do
	{
		cout << "Podaj losowa liczbe z przedzialu <1;" << m << ">:";
		cin >> e;
	} while (e < 1 || e > m || euklidesAlgorithm(e, m, x, y) != 1);

	cout << "x=" << x << endl;

	int d, s, t;

	cout << "Podaj t: ";
	cin >> t;

	if (x > 0)
	{
		d = x;
		cout << "d = " << d << endl;
	}

	cout << endl << "Klucz publiczny: {" << n << ", " << e << "}" << endl;
	cout << "Klucz prywatny: {" << n << ", " << d << "}" << endl << endl;

	s = modulo(t, e, n);
	cout << "s = " << s << endl;

	t = modulo(s, d, n);
	cout << "t = " << t << endl;

	delete[]tab;
}


int main()
{

// 1.
	{
		std::cout << "Zadanie 1." << endl << endl;
		int n;
		bool *tab;

		cout << "Podaj zakres gorny przedzialu: ";
		n = 2800000;

		tab = new bool[n + 1];
		for (int i = 2; i <= n; i++) //zerowanie tablicy
			tab[i] = 0;

		sito(tab, n); //przesianie liczb

		cout << "Kolejne liczby pierwsze z przedzialu [2.." << n << "]: ";
		int primecounter = 0;

		cout << "Wpisz liczbe n: ";
		int d;
		cin >> d;
		unsigned long long int liczba;
		for (int i = 2; i <= n; i++)
			if (!tab[i] && primecounter < d) {
				//  cout<<i<<" ";
				liczba = i;
				primecounter++;
			}

		cout << endl;
		cout << "N-ta liczba pierwsza:  " << liczba;

		delete[] tab;
	}

	// 2.
	{
		std::cout << endl << endl << "Zadanie 2" << endl;
		int a, b, x, y;
		cout << "Wpisz liczbe a: ";
		cin >> a;
		cout << "Wpisz liczbe b: ";
		cin >> b;

		int d = euklidesAlgorithm(a, b, x, y);

		cout << "NWD ( " << a << ", " << b << " )" << " = " << d << endl;

	}

	// 3.
	{
		std::cout << endl << endl << "Zadanie 3" << endl << endl;
		rsa();
	}


	cin.get();

	system("pause");
	return 0;
}
