# 🏦 UAIBANK - Sistema Bancário em C

Este é o meu primeiro projeto prático desenvolvido em **C**. O objetivo deste repositório não é ser um sistema complexo e definitivo, mas sim aplicar na prática os conceitos fundamentais da faculdade, como estruturas de controle, manipulação de variáveis, ponteiros e alocação dinâmica de memória.

## ⚙️ Funcionalidades

O sistema roda diretamente no terminal e permite as seguintes operações:
* **Cadastro de Usuários:** Criação de contas únicas ou múltiplas com validação de idade (maior de 18 anos) e saldo inicial.
* **Busca:** Localização de clientes utilizando um sistema de ID gerado automaticamente.
* **Transferências:** Operações seguras entre contas, com validação de remetente, destinatário e saldo disponível.
* **Remoção de Contas:** Exclusão de usuários com realocação automática da memória.
* **Persistência Básica:** Salvamento dos dados em um arquivo de texto (`Usuarios.txt`) ao encerrar o programa.

## 💻 Tecnologias e Conceitos Aplicados
* **Linguagem:** C
* **Conceitos:** 
  * Estruturas (`struct`)
  * Ponteiros duplos e passagem por referência
  * Alocação Dinâmica de Memória (`realloc`, `free`)
  * Manipulação de Strings (`strcspn`)
  * Leitura e Escrita de Arquivos (`FILE`)

## 🚀 Como executar

Para rodar este projeto na sua máquina, você precisa ter um compilador C (como o GCC) instalado.

1. Clone o repositório:
```bash
git clone [https://github.com/PedroSarni/uaibank.git](https://github.com/PedroSarni/uaibank.git)
```

2. Compile o código:
```bash
gcc UAIBANK.c -o uaibank
```

3. Execute o programa:
```bash
./uaibank
```
