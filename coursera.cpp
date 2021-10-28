#include <iostream>
#include <fstream>
#include<string>
#include<vector>
#include<algorithm>
#include <sstream>
using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::endl;
using std::fstream;
using std::getline;
using std::size_t;
using std::stringstream;

int main()
{
	vector<string> vec;
	vector<vector<string>> vec2;
	string path = "product.list.txt";
	string space = " ";
	fstream file;
	size_t pos;
	file.open(path);
	if (!file.is_open())
		cout << "It seems like file doesn't exist.";
	else
	{
		while (!file.eof())
		{
			string str;
			getline(file, str);
			int i = 0;
			while ((pos = str.find(space)) != string::npos)
			{
				vec.push_back(str.substr(0, pos));
				str.erase(0, pos + space.length());
				++i;
				if (i == 3)
				{
					vec.push_back(str);
					break;
				}

			}
			vec2.push_back(vec);
			vec.clear();
		}
		vec2.pop_back();
	}
	file.close();
	string start;
	stringstream ss;
	string purchase;
	string product;
	string quant;
	int quantity;
	int stquant;
	string stleft;
	int left;
	getline(cin, start);
	getline(cin, purchase);
	while (purchase != "purchase transaction ended")
	{
		pos = purchase.find(space);
		product = purchase.substr(0, pos);
		quant = purchase.substr(pos + 1);
		int flag = 0;
		for (int i = 0; i < vec2.size()-1; ++i)
		{
			if (vec2[i][0] == product)
			{
				flag = 1;
				ss << vec2[i][1];
				ss >> stquant;
				ss.clear();
				ss << quant;
				ss >> quantity;
				ss.clear();
				left =  stquant - quantity;
				if (left < 0)
					cout << "Sorry, you can't buy "<< quantity << " of this product. Buy less."<< endl;
				else
				{
					ss << left;
					ss >> stleft;
					ss.clear();
					vec2[i][1] = stleft;
				}
				cout << vec2[i][3]<<"\n";
			}
			if (flag == 1)
				break;
		}
		if (flag == 0)
			cout << "Sorry, this product can't be found in the story";

		getline(cin, purchase);

	}

	file.open(path);
	if (!file.is_open())
		cout << "It seems like file doesn't exist.";
	else
	{
		for (int i = 0; i < vec2.size(); ++i)
		{
			for (int j =0; j<4; ++j)
			file << vec2[i][j]<<" ";
			file << "\n";
		}
	}
	file.close();
}
