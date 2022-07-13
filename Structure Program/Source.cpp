// John Hendrick
// CS 318 Computer Science II
// Structure Inventory Program
// This program will organize and sort a list of inventory items by item number
// and warehouse.  The data from each file is to be read in, but is not organized
// so this program will check for matches while reading in.

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

struct WREC // setting up structure
{
	int itemnum;
	string itemname;
	string WHname;
	int quant;
	float wsale;
	float markup;
};

WREC comp[100]; // sets up array of structures

bool readit(ifstream &f, string &s) // returns value for conditional while reading string
{
	if (f >> s)
		return 1;
	return 0;
}

bool readint(ifstream &f, int &i) // reads in an integer
{
	if (f >> i)
		return 1;
	return 0;
}

bool readflt(ifstream &f, float &flt) // reads in a float
{
	if (f >> flt)
		return 1;
	return 0;
}

void sort(WREC wh[], int c) // sorts warehouse name alphabetically and numerically
{
	string previous;
	WREC temp;
	int pre;

	for (int j = 0; j < c; j++) // each run through the sort
	{
		previous = wh[0].WHname;
		for (int i = 1; i < c; i++) // sort for each number
		{
			if (wh[i].WHname == previous) // checks if the name is the same
			{
				if (wh[i].itemnum < wh[i - 1].itemnum) // switch records if item# < previous item#
				{
					temp = wh[i];
					wh[i] = wh[i - 1];
					wh[i - 1] = temp;
				}
			}
			if (wh[i].WHname < previous) // switch records if name < previous alphabetically
			{
				temp = wh[i];
				wh[i] = wh[i - 1];
				wh[i - 1] = temp;
			}
			previous = wh[i].WHname; // sets up previous name for next test
		}
	}
}

void printHead(string wh) // format for each warehouse header printed
{
	cout << "\n\n" << setw(25) << "Warehouse Location: " << wh << "\n\n";
	cout << setw(10) << "  Item #  " << setw(16) << " Item Name ";
	cout << setw(14) << " Quantity " << setw(19) << " Wholesale Price ";
	cout << setw(17) << " Mark-Up Value " << setw(17) << " Retail Value \n\n";
}

void printRec(WREC wh, float calc) // format for each record printed 
{
	cout << setw(8) << wh.itemnum << "  "<< setw(17) << wh.itemname;
	cout << setw(9) << wh.quant << setw(11) << "$";
	cout << setw(7) << setprecision(2) << fixed << wh.wsale;
	cout << setw(11) << "%" << setw(4) << setprecision(0) << fixed << wh.markup;
	cout << setw(11) << "$" << setw(8) << setprecision(2) << fixed << calc << endl;
}

float RV(WREC wh) // formula to calculate retail value
{
	float calc;
	calc = wh.quant * wh.wsale * (1 + (wh.markup / 100.0));
	return calc;
}

void printReport(WREC wh[], int c) // function prints out entire report through loops
{
	float sum = 0;
	float calc;
	string previous = wh[1].WHname;
	printHead(wh[1].WHname); // print first header 

	for (int i = 1; i < c; i++) // loops for each record
	{
		if (wh[i].WHname != previous) // displays previous WH total, sets up new header
		{
			cout << endl << setw(60) << "Total: $ " << sum;
			printHead(wh[i].WHname);
			sum = 0;
		}
		printRec(wh[i], RV(wh[i])); // calls to print record
		sum = sum + RV(wh[i]);
		previous = wh[i].WHname;
	}
	cout << endl << setw(60) << "Total: $ " << sum; // one more calculation
}

int main()
{
	int test = 0;
	int count = 1;
	int i = 0;
	string testst;
	ifstream inf;
	inf.open("WLL1.dat"); // open first data file

	while (readint(inf, comp[i].itemnum)) // checks if reading
	{
		readit(inf, comp[i].itemname);
		i++; count++;
	} 
	inf.close(); // closing the file 

	inf.open("WLL2.dat"); // opening second data file
	while (inf >> test)
		for (i = 0; i < count; i++)
			if (test == comp[i].itemnum)	
				getline(inf, comp[i].WHname); // using getline to get full name	
	inf.close();

	inf.open("WLL3.dat"); // opening third data file
	while (inf >> testst)
		for (i = 0; i < count; i++)
			if (testst == comp[i].itemname)
				readint(inf, comp[i].quant);
	inf.close();

	inf.open("WLL4.dat"); // opening final data file
	while (inf >> testst)
		for (i = 0; i < count; i++)
			if (testst == comp[i].itemname + to_string(comp[i].itemnum)) // adds for testing
			{  
				readflt(inf, comp[i].wsale); // wholesale read in first
				readflt(inf, comp[i].markup); // markup next				
			}
	inf.close(); // last file close

	sort(comp, count); // calls to sort record contents
	printReport(comp, count); // prints out final report results

	cin.get();
	return 0;
}
