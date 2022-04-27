

/**
*Escrito por Roger em 20/04/2022
*Biblioteca que contém algumas funções e classeis úteis para as aulas de estruturas de dados 3.
*Tem função de timestamp, função de geração de números aleatórios, e função para preenxer um vetor com números aleatoriamente.
*Também tem uma classe para depurar o tempo de duração de uma função.
*Bom proveito!
**/

#ifndef ED3_LIB_H
#define ED3_LIB_H

#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include<fstream>
#include<string>
#include<functional>
#include<chrono>
#include<stdint.h>
#include<random>
#include<vector>


//Costume pessoal, isso...
typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;

//Recuperar o tempo em millisegundos desde 01/01/1970...
int64 gettimestamp();
//Retorna um número aleatório entre min_val e max_val...
int32 random_int32(int32 min_val, int32 max_val);
//Preenxe um vector com a quantidade especificada de itens...
void fill_vector(std::vector<int32>& vect, uint32 size, int32 min_val=0, int32 max_val=100);
//Ler uma lista de números de um arquivo e preenxer o vetor...
bool fill_vector_from_file(const std::string& filename, std::vector<int32>& vect);
//Sobrecarga para printar um std::vector...
std::ostream& operator<<(std::ostream& os, const std::vector<int32>& vect);

void print_vector(const std::vector<int32>& vect,int32 n);


/**
*Classe para cronometrar a duração de uma determinada função.
*Basta instanciar passando como parâmetro algum nome que queira para identificar, ou passar a macro __FUNCTION__.
*Ela printa no construtor quando entrou na função, e no destruidor antes da função sair mostrando o tempo que ficou ativa.
**/
class FuncTimer
{
public:
std::string func_name;//Nome da função...
int64 start;//Timestamp, em millisegundos de quando instanciou a classe...
FuncTimer(const std::string& func_name);
~FuncTimer();
};
#endif

#ifndef ED3_LIB_IMPLEMENTATION
#define ED3_LIB_IMPLEMENTATION

//Retorna a quantidade de millisegundos desde 01/01/1970
int64 gettimestamp()
{
std::chrono::system_clock::time_point tp=std::chrono::system_clock::now();
std::chrono::system_clock::duration dtn=tp.time_since_epoch();
return std::chrono::duration_cast<std::chrono::milliseconds>(dtn).count();
}

int32 random_int32(int32 min_val, int32 max_val)
{
  unsigned seed =static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
std::default_random_engine generator (seed);
std::uniform_int_distribution<int32> distribution(min_val, max_val);
return distribution(generator);
}

void fill_vector(std::vector<int32>& vect, uint32 size, int32 min_val, int32 max_val)
{
vect.resize(0);
vect.reserve(size+1);
for(uint32 i=0; i<size; i++)
{
vect.push_back(random_int32(min_val, max_val));
}
}

/**
*Preenxe um vetor lendo os números de um arquivo.
*Os números devem estar um por linha.
**/
bool fill_vector_from_file(const std::string& filename, std::vector<int32>& vect)
{
vect.resize(0);
std::ifstream ifs(filename);
if(!ifs.is_open())
{
std::cout<<"Erro ao ler o arquivo "<<filename<<". O arquivo provavelmente não existe."<<std::endl;
return false;
}
while(!ifs.eof())
{
std::string line="";
std::getline(ifs, line);
if(line.size()==0)
{
continue;
}
vect.push_back(atoi(line.c_str()));
}
ifs.close();
return true;
}

void print_vector(const std::vector<int32>& vect,int32 n)
{
std::cout<<"Mostrando os primeiros "<<n<<" elementos do vector..."<<std::endl;
if(vect.size()==0)
{
std::cout<<"O vetor está vazio!!"<<std::endl;
return;
}
int32 x=0;
for(int32 i=0; i<n; i++)
{
if(i>=vect.size())
{
break;
}
std::cout<<vect[i];
x++;
if(x>=10)
{
x=0;
std::cout<<std::endl;
}
else
{
std::cout<<"\t";
}
}
std::cout<<std::endl;
}

std::ostream& operator<<(std::ostream& os, const std::vector<int32>& vect)
{
std::cout<<"Mostrando vector com "<<vect.size()<<" elementos..."<<std::endl;
for(auto it=vect.begin(); it!=vect.end(); ++it)
{
std::cout<<(*it)<<std::endl;
}
return os;
}

//Classe de cronometração...
FuncTimer::FuncTimer(const std::string& func_name)
{
this->func_name=func_name;
std::cout<<"Entrando na função: "<<func_name<<std::endl;
start=gettimestamp();
}

//"Evitar a fadiga..."
FuncTimer::~FuncTimer()
{
int64 end=gettimestamp();
std::cout<<"A função "<<this->func_name<<" levou "<<(end-start)<<" ms para ser concluída."<<std::endl;
}
#endif
