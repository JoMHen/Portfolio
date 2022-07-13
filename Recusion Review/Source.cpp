// John Hendrick
// CS 372 Data Structures
// Recursion Review
// This program consists of multiple recursive functions to complete different tasks.
// All functions should only consist of doing one task.

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
/* returns number of digits */
int numDig(size_t t)
{
	if (t == 0)
		return 0;
	return numDig(t / 10) + 1;
}
/* prints integer in reverse i.e. 123 to 321*/
void prtRev(int n)
{
	if (n == 0)
		return;
	cout << n % 10;
	prtRev(n / 10);
}
/* reverses the elements in an array */
void revAry(int *a, int f, int l)
{
	if (f == l || f > l)
		return;
	int tmp = a[f];
	a[f] = a[l];
	a[l] = tmp;
	revAry(a, f + 1, l - 1);

}
/* returns position of found element returns 0 if not found */
int locate(int *a, int f, int l, int e)
{
	if (f > l)
		return 0;
	if (a[f] == e)
		return f + 1;
	else
		f = locate(a, f + 1, l, e);
}
/* returns the sum of an array */
int sumAry(int *a, int n)
{
	if (n == 0)
		return a[n];
	int sum = a[n];
	return sum + sumAry(a, n - 1);
}
/* prints the array */
void prtAry(int *a, int m)
{
	for (int i = 0; i < m; i++)
		cout << a[i] << " ";
}
/* returns the greatest common divisor of integers a and b */
int GCD(int a, int b)
{
	if (a < 0)
		a = a * (-1);
	if (b < 0)
		b = b * (-1);
	if (b == 0)
		return a;
	return GCD(b, a % b);
}
/* returns the size (number of passes) for hailstone n to reach 1 */
int hailstones(int n)
{
	if (n == 1)
		return 0;
	if (n % 2 == 0)
		return hailstones(n / 2) + 1;
	if (n % 2 != 0)
		return hailstones(n * 3 + 1) + 1;
}
/* fills array in ascending order */
void fillAscend(int *a, int p, int m)
{
	if (p == m)
		return;
	a[p] = p + 1;
	fillAscend(a, p + 1, m);
}
/* fills array in descending order */
void fillDescend(int *a, int p, int m)
{
	if (p == m)
		return;
	a[p] = m - p;
	fillDescend(a, p + 1, m);
}
/* fills array from mid point odds less than evens greater than*/
void fillMid(int *a, int mod, int mid, int m)
{
	if (mod > m / 2)
		return;
	if (mod == 0)
		a[mid] = 1;
	else
	{
		a[mid - mod] = mod * 2 + 1;
		a[mid + mod] = mod * 2;
	}
	fillMid(a, mod + 1, mid, m);
}
/* prints out line of asterisks */
void astLine(int s, int f)
{
	if (s > f)
		return;
	cout << "*";
	astLine(s + 1, f);
}
/* prints out muliple lines of asterisks*/
void astFull(int s, int n)
{
	if (s > n)
		return;
	astLine(1, s);
	cout << endl;
	astFull(s + 1, n);
}
/* returns integer value from ascii characters in string */
int asciitoint(string a, int l)
{
	if (l == 0)
		return a[l] - '0';
	return 10 * asciitoint(a, l - 1) + (a[l] - '0');
}

int main()
{
	int ary[] = { 2, 3, 4, 5, 6, 7, 8};
	int bry[32], cry[32], dry[13];
	int n = 12345;
	string s = "17968375";
	string t = "745423";
	cout << setw(18) << " Number: " << "12345\n" << setw(18) << "Digits: "<< numDig(n);
	cout << endl << setw(18) << "Reverse Digits: "; prtRev(n);
	cout << "\n\n" << setw(18) << "Array: "; prtAry(ary, 7);
	revAry(ary, 0, 6); cout << "\n";
	cout << setw(18) << "Reversed: "; prtAry(ary, 7); cout << endl;
	cout << setw(18) << "Sum: " << sumAry(ary, 6) << endl;
	cout << setw(18) << "4's Position: " << locate(ary, 0, 6, 4) << " (after reverse)\n\n";
	cout << setw(18) << "GCD(1595, 453): " << GCD(1595, 453) << endl;
	cout << setw(18) << "GCD(7731, 137): " << GCD(7731, 137) << "\n\n";
	cout << setw(30) << "Hailstone Size for 1589: " << hailstones(1589) << endl;
	cout << setw(30) << "Hailstone Size for 116270: " << hailstones(116270) << "\n\n";
	fillAscend(bry, 0, 32);
	cout << setw(30) << "Array SIZE 32 (1-32)" << endl; prtAry(bry, 32);
	fillDescend(cry, 0, 32);
	cout << endl << setw(30) << "Array SIZE 32 (32-1)" << endl; prtAry(cry, 32);
	fillMid(dry, 0, 6, 13);
	cout << endl << setw(35) << "Array SIZE 13 (odds, 1, evens)" << endl; prtAry(dry, 13);
	cout << "\n\n"; astFull(1, 15);
	cout << "\n\n" << setw(30) << "Ascii: 17968375 Integer: " << asciitoint(s, s.length() - 1);
	cout << endl << setw(30) << "Ascii: 745423 Integer: " << asciitoint(t, t.length() - 1);
	cout << endl; system("pause"); return 0;
}