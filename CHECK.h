#pragma once

template <typename T>
void Check(T &ch, T left, T right)
{
	while (!(cin >> ch) || ch < left || ch > right)
	{
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		cout << "Не может быть!!! Ещё раз: ";
	}
	cerr << ch << endl;
}