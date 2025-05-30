#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


int getOverlap(string& first, string &second)
{
    int maxOver = 0; //длина самого длинного перекрытия
    int lenFirst = first.length();
    int lenSec = second.length();

    //перебор длин покрытия
    for(int i=1; i <= min(lenFirst, lenSec); i++)
    {   //сравниваем слово с конца, количество символов, строку с которой сравниваем, с началом, количество символов в second
        if(first.compare(lenFirst - i, i, second, 0, i) == 0) //если суффикс и префикс одинаковые
        {
            maxOver = i; //то обновляем длину перекрытия
        }
    }
    return maxOver;
}

void makeCrossword(vector<string> &words, vector<bool> &used, string curr, int& minLen, string& bestRes, int usedCount, string& lastWord)
{
    //проверка на лучший вариант перестановки
    if (usedCount == words.size()) {
        int len = curr.length();
        if (len < minLen) { 
            minLen = len;
            bestRes = curr;
        }
        return;
    }

    for (size_t i = 0; i < words.size(); ++i) {
        if (!used[i]) {//для каждого неиспользованного слова
            int overlap = getOverlap(lastWord, words[i]); //ищем перекрытие между последним и текущим словом

            used[i] = true; //метка что слово не использовалось повторно
            //добавление неперекрывающейся части слова
            string& nextWord = words[i];
            int oldSize = curr.size();
            for(int j = overlap; j<nextWord.size();j++)
            {
                curr.push_back(nextWord[j]);
            }
            makeCrossword(words, used, curr, minLen, bestRes, usedCount + 1, words[i]); //вызываем рекурсию с добавлеием слова, использованых

            curr.resize(oldSize); //откат чтобы не перемешивать изменённые строки
            used[i] = false;
        }
    }
}

int main()
{
    cout << "Введите количество слов: ";
    int c;


    if(!(cin>>c) || c <=0)
    {
        cout << "Ошибка. Введите положительное число" << endl;
        return 1;
    }

    vector<string> mp(c);
    cout << "Введите " << c << " слов:" << endl;

    for(int i=0; i <c; i++)
    {
        cin >> mp[i];
        if(mp[i].empty())
        {
            cout << "Ошибка: пустое слово невозможно добавить" << endl;
            return 1;
        }
    }
    int minLen = 1e9; //для любой доступной длины суперстроки
    string chain;

    for (size_t i = 0; i < mp.size(); ++i) {
        vector<bool> used(c, false);
        used[i] = true;
        makeCrossword(mp, used, mp[i], minLen, chain, 1, mp[i]);
    }

    cout << "Минимальная длина кроссворда: " << minLen << endl;
    cout << "Цепочка: " << chain << endl;
}