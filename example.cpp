

/**
*Programinha para testar os algoritmos de ordenação da matéria ED3.
*cada teste requer 3 arquivos, um arquivo com ordenação decrescente, crescente, e um arquivo com um conjunto de números totalmente bagunçados.
*Selecione os algoritmos de ordenação que deseja testar digitando os nomes quando solicitado.
*Exemplo: buble selection insertion
*Quando solicitado um nome de arquivo para processar, verifique a pasta modelos e digite um dos nomes, com a devida extenção.
*Cada arquivo como por exemplo, 10k.txt, conterá os caminhos para que o programa encontre os arquivos de conjuntos de dados para os testes.
*Caso queira adicionar mais conjuntos de dados, crie um novo arquivo na pasta de modelos, contendo apontamentos para os novos arquivos de conjuntos.
*ed3_lib.h continua funcional e independente.
**/


#include<map>
#include"ed3_lib.h"
#include"sort_algorithms.h"

using namespace std;

//Definir modelo de função que as funções de sort deverão ter...
typedef function<void(vector<int32>&)> SortFunc;

//Tabela que mantém ponteiros para as funções de sort que podem ser executadas...
//Para que um algoritmo novo funcione, depois de implementado, é necessário adicionar uma entrada manualmente nesta tabela...
map<string, SortFunc> sort_table={
{"buble", buble_sort},
{"selection", selection_sort},
{"insertion", insertion_sort}
};


void run_test(const vector<string>& files, const std::string& algorithm_name);
void parseFunc(const std::string& str, vector<string>& funcs);
void print_algorithms();
bool loadModel(const std::string& filename, vector<string>& files);


int main()
{
setlocale(LC_ALL, "Portuguese");
cout<<"Digite os algoritmos que deseja testar..."<<endl;
print_algorithms();
cout<<"Apenas separe eles por um espaço. Exemplo:"<<endl;
cout<<"buble insertion"<<endl;
string line="";
getline(cin, line);
vector<string> funcs, files;
//Detectar os algoritmos que o usuário informou...
parseFunc(line, funcs);
if(funcs.size()==0)
{
cout<<"Nenhum algoritmo indicado!"<<endl;
return 0;
}
cout<<"Digite o nome do arquivo que contém a lista de arquivos a usar... EX: 10k.txt"<<endl;
string modelname="";
getline(cin, modelname);
if(!loadModel(modelname, files))
{
cout<<"Erro ao ler o arquivo "<<modelname<<endl;
return 0;
}
//E rodar os testes com os algoritmos indicados...
for(auto it=funcs.begin(); it!=funcs.end(); ++it)
{
run_test(files, (*it));
}
cout<<"Testes concluídos!"<<endl;
return 0;
}


void run_test(const vector<string>& files, const string& algorithm_name)
{
FuncTimer ts(__FUNCTION__);
//Verifica se o algoritmo está na tabela lá de cima...
if(sort_table.count(algorithm_name)==0)
{
cout<<"O algoritmo "<<algorithm_name<<" não existe! O teste será ignorado."<<endl;
return;
}
//Recuperar o ponteiro para a função...
SortFunc sortfunc=sort_table.at(algorithm_name);
if(files.size()==0)
{
cout<<"Nenhum arquivo de onde buscar o conjunto de dados foi informado."<<endl;
return;
}
for(auto it=files.begin(); it!=files.end(); ++it)
{
vector<int32> arr;
//Leia o arquivo e tente preenxer o vetor com os números...
if(!fill_vector_from_file((*it), arr))
{
cout<<"Erro ao testar com o arquivo "<<(*it)<<endl;
continue;
}
cout<<"Testando "<<algorithm_name<<" com "<<arr.size()<<" elementos do arquivo "<<(*it)<<endl;
sortfunc(arr);
print_vector(arr, 30);
}
}

void print_algorithms()
{
cout<<"Os algoritmos disponíveis no momento são:"<<endl;
for(auto it=sort_table.begin(); it!=sort_table.end(); ++it)
{
cout<<it->first<<endl;
}
}

void parseFunc(const std::string& str, vector<string>& funcs)
{
if(str.size()==0)
{
return;
}
funcs.clear();
string func_name="";
for(uint32 i=0; i<str.size(); i++)
{
switch(str[i])
{
case ' ':
{
//ignora os espaços...
if(func_name.size()==0)
{
continue;
}
funcs.push_back(func_name);
func_name.clear();
break;
}
default:
{
func_name+=str[i];
break;
}
}
}
if(func_name.size()>0)
{
funcs.push_back(func_name);
}
}

bool loadModel(const std::string& filename, vector<string>& files)
{
files.clear();
string sname="modelos/"+filename;
ifstream ifs(sname);
if(!ifs.is_open())
{
return false;
}
while(!ifs.eof())
{
string ss="";
getline(ifs, ss);
if(ss.size()>0)
{
files.push_back(ss);
}
}
ifs.close();
return files.size()>0;
}
