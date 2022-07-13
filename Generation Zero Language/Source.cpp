// John Hendrick
// CS 414 Programming Language
// Generation Zero Language 
// This programming assignment handles different commands based on signs and digits that
// call their corresponding functions to work with two operands and a destination.
// These commands will be read in through strings and using substrings to place in each
// structure element.

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct line
{
	int loc;
	char s;
	int f;
	int op1;
	int op2;
	int dest;
};

/* moves value from one destination to another */
void move(line now, long long *dat)
{ dat[now.dest] = dat[now.op1]; }

/* adds two values and stores in destination */
void addit(line now, long long *dat)
{ dat[now.dest] = dat[now.op1] + dat[now.op2]; }

/* subtracts two values and stores in destination */
void subit(line now, long long *dat)
{ dat[now.dest] = dat[now.op1] - dat[now.op2]; }

/* multiplies two given values */
void multi(line now, long long *dat)
{ dat[now.dest] = dat[now.op1] * dat[now.op2]; }

/* divides two given values */
void divide(line now, long long *dat)
{ dat[now.dest] = dat[now.op1] / dat[now.op2]; }

/* squares specified value */
void square(line now, long long *dat)
{ dat[now.dest] = dat[now.op1] * dat[now.op1]; }

/* places square root of value in specified location */
void sqRoot(line now, long long *dat)
{ dat[now.dest] = sqrt(dat[now.op1]); }

/* conditional statement tests for equal */
int equal(line now, long long *dat)
{
	if (dat[now.op1] == dat[now.op2])
		return now.dest;
	return now.loc + 1;
}

/* conditional statement tests for not equal */
int notEqual(line now, long long *dat)
{
	if (dat[now.op1] != dat[now.op2])
		return now.dest;
	return now.loc + 1;
}

/* conditional greater than or equal to statement */
int GTE(line now, long long *dat)
{
	if (dat[now.op1] >= dat[now.op2])
		return now.dest;
	return now.loc + 1;
}

/* conditional less than statement */
int LT(line now, long long *dat)
{
	if (dat[now.op1] < dat[now.op2])
		return now.dest;
	return now.loc + 1;
}

/* places array element in specified location */
void takeFrom(line now, long long *dat)
{
	int index = dat[now.op1] + now.op2;
	dat[now.dest] = dat[index];
}

/* moves value into array */
void moveInto(line now, long long *dat)
{
	int index = now.dest + dat[now.op2];
	dat[index] = dat[now.op1];
}

/* increments array and checks if at final element */
int inc(line now, long long *dat)
{
	dat[now.op1]++;
	if (dat[now.op1] < dat[now.op2])
		return now.dest;
	return now.loc + 1;
}

/* decrements array and checks if at starting element */
int dec(line now, long long *dat)
{
	now.op1--;
	if (dat[now.op1] > 0)
		return now.dest;
	return now.loc + 1;
}

/* reads next input data into specified location */
void read(ifstream &f, line now, long long *dat)
{
	string temp;
	f >> temp;
	dat[now.dest] = stoi(temp.substr(1, 10));
}

/* prints out the data in specified location */
void print(line now, long long *dat)
{ cout << dat[now.op1] << endl; }

/* stops the program */
int stop(line now, long long *dat)
{ return now.dest; }

/* modulus checks divisibility */
void modulus(line now, long long *dat)
{ dat[now.dest] = dat[now.op1] % dat[now.op2]; }

/* switch case calls appropriate plus function passing struct*/
int switchPlus(ifstream &in, line now, long long *dat)
{
	switch (now.f)
	{
	case 0:
		move(now, dat);
		break;
	case 1:
		addit(now, dat);
		break;
	case 2:
		multi(now, dat);
		break;
	case 3:
		square(now, dat);
		break;
	case 4:
		return equal(now, dat);
		break;
	case 5:
		return GTE(now, dat);
		break;
	case 6:
		takeFrom(now, dat);
		break;
	case 7:
		return inc(now, dat);
		break;
	case 8:
		read(in, now, dat);
		break;
	case 9:
		return stop(now, dat);
		break;
	}
	now.loc++;
	return now.loc;
}

/* switch case calls appropriate minus function passing struct */
int switchMinus(line now, long long *dat)
{
	switch (now.f)
	{
	case 1:
		subit(now, dat);
		break;
	case 2:
		divide(now, dat);
		break;
	case 3:
		sqRoot(now, dat);
		break;
	case 4:
		return notEqual(now, dat);
		break;
	case 5:
		return LT(now, dat);
		break;
	case 6:
		moveInto(now, dat);
		break;
	case 7:
		return dec(now, dat);
		break;
	case 8:
		print(now, dat);
		break;
	case 9:
		modulus(now, dat);
		break;
	}
	now.loc++;
	return now.loc;
}
/* checks for sign */
int signCheck(ifstream &in, line now, long long *dat)
{
	int ip = now.loc;
	if (now.s == '-')
		ip = switchMinus(now, dat);
	if (now.s == '+')
		ip = switchPlus(in, now, dat);
	return ip;
}

int main()
{
	string temp = "  ";
	long long data[1000];
	line instr[1000];
	int i = 0;
	ifstream f;
	f.open("Instructions.txt");
	/* initial data setup */
	f >> temp;
	while (temp[1] != '9')
	{
		data[i] = 0;
		i++;
		f >> temp;
	}
	/* reading instructions */
	temp = "";
	i = 0;
	while (temp != "+9999999999")
	{
		f >> temp;
		instr[i].loc = i;
		instr[i].s = temp[0];
		instr[i].f = temp[1] - '0';
		instr[i].op1 = stoi(temp.substr(2, 3));
		instr[i].op2 = stoi(temp.substr(5, 3));
		instr[i].dest = stoi(temp.substr(8, 3));
		i++;
	}
	f.close();
	/* running program */
	f.open("InputData.txt");
	i = 0;
	while (instr[i].s != '+' || instr[i].f != 9)
		i = signCheck(f, instr[i], data);
	f.close();
	/* Any key to exit program */
	system("pause");
	return 0;
}
