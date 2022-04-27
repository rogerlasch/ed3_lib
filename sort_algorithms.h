

/**
*Escrito por Roger em 2022.
*Contém todos os algoritmos de ordenação estudados na aula de ED3.
*Para futuros algoritmos, de preferência manter as assinaturas de funções como a baixo, ou pode quebrar com a reflexão do aplicativo....
**/

#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

void buble_sort(std::vector<int32>& arr);
void selection_sort(std::vector<int32>& arr);
void insertion_sort(std::vector<int32>& arr);

#endif

#ifndef SORT_ALGORITHMS_CPP
#define SORT_ALGORITHMS_CPP
void buble_sort(std::vector<int32>& arr)
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
for(int32 i=0; i<arr.size(); i++)
{
for(int32 i1=0; i1<arr.size(); i1++)
{
if(arr[i]<arr[i1])
{
//Troca os 2 valores... Função disponível em algorithm...
std::swap(arr[i], arr[i1]);
}
}
}
}

void selection_sort(std::vector<int32>& arr)
{
FuncTimer ts(__FUNCTION__);
if(arr.size()<2)
{
return;
}
for(int32 i=0; i<arr.size(); i++)
{
int32 x=i;
for(int32 i1=(i+1); i1<arr.size(); i1++)
{
if(arr[i1]<arr[x])
{
x=i1;
}
}
std::swap(arr[i], arr[x]);
}
}

void insertion_sort(std::vector<int32>& arr)
{
FuncTimer ts(__FUNCTION__);
if(arr.size()<2)
{
return;
}
for(int32 i=1; i<arr.size(); i++)
{
int32 key=arr[i];
int32 j=i;
while(j>0&&arr[j-1]>key)
{
arr[j]=arr[j-1];
j--;
}
arr[j]=key;
}
}

#endif
