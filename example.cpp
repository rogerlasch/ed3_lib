

/**
*Exemplos de uso das funções ed3_lib...
*Também implementei os 3 algoritmos buble sort passados na aula de 20/04/2022.
**/

#include"ed3_lib.h"

using namespace std;

void bublesort_1(vector<int>& arr);
void bublesort_2(vector<int>& arr);
void bublesort_3(vector<int>& arr);

int main()
{
setlocale(LC_ALL, "Portuguese");
FuncTimer ts(__FUNCTION__);
int32 qtd;
cout<<"Digite a quantidade de números que deverão ser gerados..."<<endl;
cin>>qtd;
vector<int32> arr;
fill_vector(arr, qtd);
bublesort_1(arr);
fill_vector(arr, qtd);
bublesort_2(arr);
fill_vector(arr, qtd);
bublesort_3(arr);
if(arr.size()>20)
{
arr.resize(20);
}
cout<<"Mostrando os primeiros "<<arr.size()<<" elementos..."<<endl;
cout<<arr<<endl;
return 0;
}

void bublesort_1(vector<int>& arr)
{
//Inicializa um objeto FuncTimer com o nome da função...
//__FUNCTION__ é suportado pela maioria dos compiladores,mas, qualquer coisa, basta passar um nome qualquer entre aspas duplas...
//Exemplo: FuncTimer ts("bublesort_1");
//Quando a função terminar, o destruidor da classe é invocado, e ele calculará o tempo que a função levou para finalizar...
FuncTimer sf(__FUNCTION__);
if(arr.size()<2)
{
return;
}
for(int i=0; i<arr.size(); i++)
{
for(int i1=0; i1<arr.size(); i1++)
{
if(arr[i]<arr[i1])
{
//Troca os 2 valores... Função disponível em algorithm...
swap(arr[i], arr[i1]);
}
}
}
}

void bublesort_2(vector<int>& arr)
{
FuncTimer sf(__FUNCTION__);
bool ordenando=false;
do
{
ordenando=false;
for(int i=0; i<arr.size(); i++)
{
if(arr[i]>arr[(i+1)])
{
swap(arr[i], arr[i+1]);
ordenando=true;
}
}
} while(ordenando==true);
}

void bublesort_3(vector<int>& arr)
{
FuncTimer sf(__FUNCTION__);
bool ordenando=true;
while(ordenando==true)
{
ordenando=false;
for(int i=0; i<arr.size(); i++)
{
if(arr[i]>arr[(i+1)])
{
swap(arr[i], arr[i+1]);
ordenando=true;
}
}
}
}
