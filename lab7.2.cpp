#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

//генерация перестановок
void GenerPer(vector<int>& nums, int left, vector<string>& res)
{
    if(left == nums.size()) //проверка заполнены ли все позиции числами
    {
        string p = "";
        for(int num : nums)
        {
            p += to_string(num); //каждое число преобразуем в строку и прибавляем к пустой строке
        }
        res.push_back(p);
    return;
    }

    for(int i= left; i<nums.size(); i++)
    {
        swap(nums[left], nums[i]); //меняем местами элемент
        GenerPer(nums, left+1, res); //рекурсивно вызываем функцию для следующей позиции
        swap(nums[left],nums[i]); //возвращаем массив в исходное состояние
    }
}

bool isValInput(int val, int min, int max)
{
    if(val <min) 
        return false;
    if (val > max)
        return false;
    return true;

}

int main()
{
    int n, k;

    cout <<"Введите количество чисел из которых нужно получить перестановки: "; 
    while (!(cin >> n) || !isValInput(n, 1, 9))
    {
        cout <<"Некорректный ввод. Повторите попытку: ";
        cin.clear();
        cin.ignore(10000,'\n'); //пропуск 10к символов новой строки
    }

    int fact = 1;
    for(int i=2; i <= n; i++)
    {
        fact *=i; //вычисление факториала
    }

    cout << "Введите порядковый номер перестановки: ";
    while(!(cin>>k) || !isValInput(k,1,fact)){
        cout << "Неккорентный ввод. Повторите попытку: ";
        cin.clear();
        cin.ignore(10000,'\n');
    }
    //инициализируем и заполняем массив
    vector<int> nums;
    for(int i=1; i<=n; i++)
    {
        nums.push_back(i);
    }

    vector<string> res;

    GenerPer(nums, 0, res); 
    sort(res.begin(), res.end());//сортируем престановки по ascii порядку

    cout << "Результат: " << res[k-1] << endl;
}