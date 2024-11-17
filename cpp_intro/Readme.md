# Pesquisa sobre C++
aula 1 atividade de casa:

Vantagem da linguagem compilada vs a interpretada:
Na linguagem compilada o código é transformado em um arquivo executável (gera um código intermediário e depois um de máquina nativo ) o que melhora o desempenho. O compilador verifica erros de sintaxe e semântica antes de executar e melhora a otimização.
Tipos de comentários:
// comentário de uma linha//
/* mais de 
uma linha */  (não pode ser usado aninhado)
/** comentario de documentação */ (usado par a descrever funções, classes e parâmetros , gerando uma documentação)

Include: 
O pré-processador é uma ferramenta que processa o código fonte antes da compilação.
Ele interpreta e executa diretivas que começam com #, como #include.

Namespace:
permite agrupar identificadores, como nomes de funções, classes e variáveis, para evitar conflitos de nomes.

Escopo:
escopo em uma linguagem de programação refere-se à área do código onde uma variável, função ou outro identificador é acessível e pode ser utilizado.

Variável Local vs Global:
Local: Declarada dentro de uma função ou bloco de código.Escopo: Acessível apenas dentro da função ou bloco onde foi declarada.
Global: Declarada fora de qualquer função ou bloco, geralmente no início do arquivo.
Escopo: Acessível em qualquer parte do código, incluindo dentro de funções.

Variável alocada na Stack ou na Heap:
Stack: Para variáveis locais, alocação automática, tempo de vida limitado ao escopo, acesso rápido.
Heap: Para objetos ou variáveis alocadas manualmente (malloc em C e new em C++) tempo de vida controlado pelo programador (free em C e delete em C++ para liberar o espaço de memória), acesso mais lento.

Inicialização de variável:
Padrão: int x;
Direta: int x = 5;
Por lista: int x{5} (mais recomendada)
Auto: auto x = 5;
Ponteiro: int* p = new int(10); // p aponta para um inteiro alocado na heap com valor 10

Buffers Padrão:
Buffer de Entrada (stdin): Usado para armazenar dados que são lidos do usuário ou de arquivos.Ex.: std::cin para ler entradas do teclado.

Buffer de Saída (stdout): Usado para armazenar dados que serão exibidos ao usuário ou escritos em arquivos. Ex.: std::cout

Tipos Primitivos:
Inteiros: int, short, long, long long
Ponto Flutuante: float, double, long double
Caracteres: char, wchar_t
Booleano: bool

Modificadores de Tipo: 

signed: Indica que a variável pode armazenar números positivos e negativos (é o padrão para int e char).
unsigned: Indica que a variável pode armazenar apenas números não negativos.
ex: unsigned int x = 10;
short: Reduz a largura de um tipo inteiro, geralmente para 16 bits.
long: Aumenta a largura de um tipo inteiro, geralmente para 32 bits ou mais. O long long é usado para 64 bits.
short int a = 100;
long int b = 1000000;
const: Indica que o valor da variável não pode ser alterado após sua inicialização, promovendo segurança no código.
const int MAX_VALUE = 100;
volatile: O valor pode mudar a qualquer momento. Ex: volatile int flag; 
restrict: ponteiro é a única referência para o objeto apontado, permitindo otimizações.
Ex: void func(int* restrict p);

Auto:
Forma de declarar variáveis, permitindo que o compilador deduza seu tipo automaticamente. 
ex: auto x = 5;  

Conversão entre tipos primitivos:
Conversão implícita: 
int i = 10;
double d = i;
Conversão explícita (cast):
double d = (double)i;
static_cast: Utilizado para conversões seguras entre tipos relacionados.
int i = 42;
double d = static_cast<double>(i);
reinterpret_cast: Usado para conversões que não são seguras e que podem alterar o significado de um valor. 
int* p = new int(10);
void* vp = reinterpret_cast<void*>(p); // Converte um ponteiro para int para um ponteiro genérico.

Pré e Pós-incremento
++variável: Incrementa e retorna o novo valor.
int a = 5;
int b = ++a; // a agora é 6, b é 6
variável++: Retorna o valor atual e, em seguida, incrementa.
int a = 5;
int b = a++; // a agora é 6, b é 5

Operador Ternário:
ferramenta útil para simplificar expressões condicionais simples. Fórmula:
condição ? expressão_se_verdadeira : expressão_se_falsa;
Exemplo: 
int a = 5, b = 10;
int maior = (a > b) ? a : b; // maior será 10

Elementos de Primeira Classe
Um elemento de primeira classe é uma entidade que pode ser: atribuída em uma variável toda a função, passada como argumento e retornada de outra função.
embora C++ não trate funções exatamente como elementos de primeira classe 
,ele oferece recursos que permitem manipular funções de maneira similar através de ponteiros, lambdas e std::function. 

Lambda (função anônima)
Formula abaixo:
lambda argumentos: expressão
Exemplo:
soma = lambda x, y: x + y
resultado = soma(2, 3)
print(resultado)  # Saída: 5
Return sem valor
funções que não retornam valores são úteis para executar ações, modificar estados, organizar código e gerenciar fluxos de controle.
Return vs If Else
Depende da complexidade do código; se for simples use return.
Função inline
As funções inline são uma maneira de otimizar funções pequenas e frequentemente chamadas, eliminando a sobrecarga de chamadas de função. Exemplo:
#include <iostream>

inline int soma(int a, int b) {
    return a + b;
}

int main() {
    int resultado = soma(5, 3);  // Chamada de função inline
    std::cout << "Resultado: " << resultado << std::endl;  // Saída: 8
    return 0;
}
Sobrecarga de Função:
#include <iostream>

// Função que soma dois inteiros
int soma(int a, int b) {
    return a + b;
}

// Função que soma três inteiros
int soma(int a, int b, int c) {
    return a + b + c;
}

// Função que soma dois números de ponto flutuante
double soma(double a, double b) {
    return a + b;
}

int main() {
    std::cout << "Soma de 2 e 3: " << soma(2, 3) << std::endl;               // Chama a primeira função
    std::cout << "Soma de 1, 2 e 3: " << soma(1, 2, 3) << std::endl;       // Chama a segunda função
    std::cout << "Soma de 2.5 e 3.5: " << soma(2.5, 3.5) << std::endl;     // Chama a terceira função
    return 0;
}
Requisitos de Sobrecarga:
1. Número de Parâmetros: As funções podem ter um número diferente de parâmetros.
2. Tipos de Parâmetros: As funções podem ter tipos de parâmetros diferentes.
3. Ordem dos Tipos de Parâmetros: A ordem dos tipos de parâmetros pode ser diferente.
Parametro passado por cópia vs por Referência Constante
Por cópia: o compilador cria uma cópia do valor original e a função trabalha com essa cópia. Modificações feitas na cópia não afetam o valor original.
Int x = 10; 
Int x = 5;
Por referência constante (usando const): a função recebe uma referência ao valor original, mas não pode modificá-lo. Usado quando você deseja garantir que o valor não será modificado dentro da função, mas ainda deseja evitar a sobrecarga de cópia.
Definição e Declaração de Função:
Declaração: Diz ao compilador que a função existe (sem detalhes).
int soma(int a, int b);  // Declaração
Definição: Implementa a função (com o código que executa).
int soma(int a, int b) {  // Definição
    return a + b;        // O que a função faz
}
Tabela de Símbolos Compilador
permite a verificação e gerenciamento eficaz de identificadores ao longo do código. Ela garante que variáveis e funções sejam usadas corretamente
Uso padrão de Hello World
Tipo padrão: const char[] (string literal).a string é armazenada como um array de caracteres (char), terminando com um caractere nulo (‘\0’).
const char* mensagem = "Hello World";
Uso recomendado: Para mais flexibilidade e funcionalidade, use std::string.
td::string mensagem = "Hello World";

## Correção

int a = 5;
int b = a;
a += 1;  
b -= 1;
a += 1;
int c = a + b;  
std::cout << a << " " << b << " " << c << '\n';