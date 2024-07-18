#include "mycommon.h"
using namespace std;

struct Person
{
  int age;
  int height;
  string name;
};
using PersonField = std::variant<int Person::*, string Person::*>;
unordered_map<string_view, PersonField> person_fields = {
    {"age", &Person::age},
    {"height", &Person::height},
    {"name", &Person::name},
};

struct n
{
  int mat[2][2];
};
n mat_mul(n n1, n n2)
{
  n n3;
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      n3.mat[i][j] = 0;
      for (int k = 0; k < 2; k++)
      {
        n3.mat[i][j] += n1.mat[i][k] * n2.mat[k][j];
      }
    }
  }
  return n3;
}
int main()
{
  Person p1 = {20, 180, "Tom"};
  for (auto &&[name, value] : person_fields)
  {
    visit([&](auto &&field) { cout << name << ": " << p1.*field << endl; }, value);
  }

  n n1 = {{{1, 0}, {0, 0}}};
  // 使用矩阵乘法来计算feibinaqie数列
  n n2 = {{{1, 1}, {1, 0}}};
  // 第6项：
  for (int i = 1; i <= 5; i++) n1 = mat_mul(n1, n2);
  cout << n1.mat[0][0] << endl;
}