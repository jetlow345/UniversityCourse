#include <string.h>
#include <time.h>
#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;
#define BITSIZE 201
// we supposed a > b
void Sub(char a[], char b[], char res[], int base)
{
	int na = strlen(a);
	int nb = strlen(b);

	int i = 0;
	char carry = 0;
	int n = max(na, nb);
	while (i < na || i < nb || carry > 0)
	{
		char d = carry;
		if (i < na)
			d += a[na - i - 1] - '0';
		if (i < nb)
			d -= b[nb - i - 1] - '0';
		if (d < 0)
		{
			carry = -1; d += base;
		}
		else
			carry = 0;
		res[n - 1 - i] = (char)(d + '0');
		i++;
	}
	// shift leading zeros
	int ind = 0;
	while (res[ind] == 0) ind++;
	i = 0;
	while (ind < n)
	{
		res[i++] = res[ind];
		ind++;
	}
	while (i < n) res[i++] = 0;
}

void Sum(char a[], char b[], char res[], int base)
{
	int na = strlen(a);
	int nb = strlen(b);

	int i = 0;
	char carry = 0;
	int n = max(na, nb) + 1;
	while (i < na || i < nb || carry > 0)
	{
		char d = carry;
		if (i < na)
			d += a[na - i - 1] - '0';
		if (i < nb)
			d += b[nb - i - 1] - '0';
		if (d >= base)
		{
			carry = 1; d -= base;
		}
		else
			carry = 0;
		res[n - 1 - i] = (char)(d + '0');
		i++;
	}
	// shift leading zeros
	int ind = 0;
	while (res[ind] == 0) ind++;
	i = 0;
	while (ind < n)
	{
		res[i++] = res[ind];
		ind++;
	}
	while (i < n) res[i++] = 0;
}


void Mul(char a[], char b[], char res[], int base)
{
	int na = strlen(a);
	int nb = strlen(b);
	int n = max(na, nb);
	if (n % 2 == 1)
		n++;
	if (na == 1)
	{
		char carry = 0;
		for (int i = 0; i < nb; i++)
		{
			char d = (a[0] - '0') * (b[nb - 1 - i] - '0') + carry;
			if (d >= base)
			{
				carry = d / base;
				d = d % base;
			}
			else
				carry = 0;
			res[nb - i] = d + '0';
		}
		if (carry > 0)
			res[0] = carry + '0';
	}
	else if (nb == 1)
	{
		char carry = 0;
		for (int i = 0; i < na; i++)
		{
			char d = (b[0] - '0') * (a[na - 1 - i] - '0') + carry;
			if (d >= base)
			{
				carry = d / base;
				d = d % base;
			}
			else
				carry = 0;
			res[na - i] = d + '0';
		}
		if (carry > 0)
			res[0] = carry + '0';
	}
	else
	{
		char al[BITSIZE] = { 0 };
		char bl[BITSIZE] = { 0 };
		char ar[BITSIZE] = { 0 };
		char br[BITSIZE] = { 0 };

		char resll[BITSIZE] = { 0 };
		char resrr[BITSIZE] = { 0 };

		for (int i = 0; i < n; i++)
		{
			if (i < n / 2)
			{
				if (i < n - na)
				{
					al[i] = '0';
				}
				else
				{
					al[i] = a[i - n + na];
				}
			}
			else
			{
				if (i < n - na)
					ar[i - n / 2] = '0';
				else
					ar[i - n / 2] = a[i - n + na];
			}
		}
		al[n / 2] = 0; ar[n / 2] = 0;
		for (int i = 0; i < n; i++)
		{
			if (i < n / 2)
			{
				if (i < n - nb)
				{
					bl[i] = '0';
				}
				else
				{
					bl[i] = b[i - n + nb];
				}
			}
			else
			{
				if (i < n - nb)
					br[i - n / 2] = '0';
				else
					br[i - n / 2] = b[i - n + nb];
			}
		}
		bl[n / 2] = 0; br[n / 2] = 0;
		//XlYl + 2n/2 * [(Xl + Xr)(Yl + Yr) - XlYl - XrYr] + XrYr
		Mul(al, bl, resll, base);
		Mul(ar, br, resrr, base);

		char resm1[BITSIZE] = { 0 };
		char resm2[BITSIZE] = { 0 };

		Sum(al, ar, resm1, base);
		Sum(bl, br, resm2, base);

		char resmm[BITSIZE] = { 0 };

		Mul(resm1, resm2, resmm, base);

		char ressub1[BITSIZE] = { 0 };
		char ressub2[BITSIZE] = { 0 };

		Sub(resmm, resll, ressub1, base);
		Sub(ressub1, resrr, ressub2, base);

		char resshifted1[BITSIZE] = { 0 };

		int len = strlen(resll);
		for (int i = 0; i < len; i++)
			resshifted1[i] = resll[i];
		for (int i = 0; i < n; i++)
		{
			resshifted1[len + i] = '0';
		}

		char resshifted2[BITSIZE] = { 0 };

		len = strlen(ressub2);
		for (int i = 0; i < len; i++)
			resshifted2[i] = ressub2[i];
		for (int i = 0; i < n / 2; i++)
		{
			resshifted2[len + i] = '0';
		}
		char fres1[BITSIZE] = { 0 };

		Sum(resshifted1, resshifted2, fres1, base);
		Sum(fres1, resrr, res, base);

	}

	// shift leading zeros
	int ind = 0;
	while (res[ind] == 0) ind++;
	int i = 0;
	while (ind < 2 * n && res[ind] != 0)
		res[i++] = res[ind++];
	while (i < 2 * n)
		res[i++] = 0;
}
void Mult1(char a[], char b[], char res[], int base)
{
	Mul(a, b, res, base);
	int n = strlen(res);
	int ind = 0;

	while (ind < n && (res[ind] == 0 || res[ind] == '0')) ind++;
	int i = 0;
	while (ind < n && res[ind] != 0)
		res[i++] = res[ind++];
	while (i < n)
		res[i++] = 0;
	if (strlen(res) == 0)
		res[0] = '0';
}
int main()
{
	char I1[101], I2[101];
	char res[201];

	int B;
	cin >> I1 >> I2 >> B;
	memset(res, 0, 201);
	Sum(I1, I2, res, B);
	cout << res;
	cout << " ";

	memset(res, 0, 201);

	Mult1(I1, I2, res, B);

	cout << res << "\n";

}