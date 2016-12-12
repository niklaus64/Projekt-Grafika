#include <iostream>
#include <string>
#include <vector>

using std::vector;
using std::cout;
using std::endl;
using std::string;


struct pixel
{
	unsigned char r;
	unsigned char g;
	unsigned char b;

	bool operator==(pixel &p) const
	{
		if ((r == p.r) && (g == p.g) && (b == p.b)) return true;
		else return false;
	}
	bool operator!=(pixel &p) const
	{
		return !operator==(p);
	}
};

void fillPixel(pixel &a, int position);
void writePixel(pixel &a, string b, int c);
void compress();

vector<unsigned char> bitmap;
vector<char> bitmap2;
vector<char> temp;

int main()
{

	bitmap.push_back('0');// 0
	bitmap.push_back('0');
	bitmap.push_back('0');
	
	bitmap.push_back('1');// 3
	bitmap.push_back('1');
	bitmap.push_back('1');
	
	bitmap.push_back('2');//12
	bitmap.push_back('2');
	bitmap.push_back('2');

	bitmap.push_back('3');//21
	bitmap.push_back('2');
	bitmap.push_back('1');
	
	bitmap.push_back('3');//24
	bitmap.push_back('2');
	bitmap.push_back('1');
	
	bitmap.push_back('3');//27
	bitmap.push_back('2');
	bitmap.push_back('1');
	
	bitmap.push_back('3');//30
	bitmap.push_back('2');
	bitmap.push_back('1');

	bitmap.push_back('1');//30
	bitmap.push_back('1');
	bitmap.push_back('1');

	bitmap.push_back('2');//30
	bitmap.push_back('2');
	bitmap.push_back('2');

	bitmap.push_back('3');//30
	bitmap.push_back('3');
	bitmap.push_back('3');

	compress();
	
	for (int i = 0; i < bitmap2.size(); i++)
	{
		cout << bitmap2[i] << endl;
	}
	
	/*for (int i = 0; i < temp.size(); i++)
	{
		cout << temp[i] << endl;
	}*/
	
	system("PAUSE>nul");
	return 0;
}

void fillPixel(pixel &a, int position)
{

	a.r = bitmap.at(position);
	a.g = bitmap.at(position + 1);
	a.b = bitmap.at(position + 2);
}

void writePixel(pixel &a, string b, int c)
{
	cout << endl << b;
	cout << "\nr: " << a.r;
	cout << "\nb: " << a.g;
	cout << "\ng: " << a.b;
	cout << "\ncur pos: " << c << endl;
}

void compress()
{
	size_t buffSize = bitmap.size() - 1;
	pixel currentPixel;
	pixel comparePixel;
	int currentPosition = 0;
	bool isRepeated = true;
	
	while (currentPosition <= buffSize)
	{
		fillPixel(currentPixel, currentPosition);
		int reapeat = 1;
		int noRepeat = 1;
		
		while (isRepeated == true)
		{
			if (currentPosition + reapeat * 3 > buffSize)
			{
				bitmap2.push_back(char(-reapeat + 1));
				bitmap2.push_back(currentPixel.r);
				bitmap2.push_back(currentPixel.g);
				bitmap2.push_back(currentPixel.b);
				break;
			}
			fillPixel(comparePixel, currentPosition + reapeat * 3);
			
			if (currentPixel == comparePixel)
			{
				isRepeated = true;
				++reapeat;
			}
			else
			{
				if (reapeat != 1)
				{
					bitmap2.push_back(char(-reapeat + 1));
					bitmap2.push_back(currentPixel.r);
					bitmap2.push_back(currentPixel.g);
					bitmap2.push_back(currentPixel.b);
				}
				isRepeated = false;
				break;
			}
		}
		
		while (isRepeated == false)
		{
			fillPixel(currentPixel, currentPosition);

			if (currentPosition + 3 > buffSize) break;
		
			fillPixel(comparePixel, currentPosition + 3);

			if (currentPixel != comparePixel)
			{
				temp.push_back(currentPixel.r);
				temp.push_back(currentPixel.g);
				temp.push_back(currentPixel.b);
				isRepeated = false;
				++noRepeat;
				currentPosition += 3;
				continue;
			}
			else
			{
				/*temp.push_back(comparePixel.r);
				temp.push_back(comparePixel.g);
				temp.push_back(comparePixel.b);*/
				bitmap2.insert(bitmap2.end(), temp.begin(), temp.end());
				temp.clear();
				isRepeated = true;
				break;
			}
		}
		currentPosition += reapeat * 3;
	}
}
