# 🏦 UAIBANK - Sistema Bancário em C

Este é um projeto prático de engenharia de software desenvolvido em **C** como parte da disciplina de *Laboratório de Introdução à Ciência de Computação I* (SSC0502) no **ICMC-USP**.

O objetivo principal deste repositório é demonstrar bases sólidas em lógica de programação, desenvolvimento estruturado e gerenciamento dinâmico de memória na linguagem C.

---

## 📐 Planejamento e Arquitetura

Diferente de muitos projetos introdutórios, este sistema foi totalmente planejado antes de qualquer linha de código ser escrita. Foram desenhados fluxogramas lógicos e esboçados pseudocódigos detalhados para cada módulo principal (Inserção, Busca, Transferência, Remoção e Persistência de Arquivos).

📄 **Relatório de Arquitetura:** Você pode encontrar a documentação completa do planejamento e os fluxogramas detalhados no arquivo [UAIBANK_Architecture_Report.pdf](./UAIBANK_Architecture_Report.pdf)

---

## ⚙️ Funcionalidades Principais

O sistema roda diretamente no terminal e oferece as seguintes operações:
* **Cadastro de Usuários:** Criação de contas únicas ou múltiplas com validação de idade (maior de 18 anos) e saldo inicial.
* **Busca por ID:** Localização rápida de registros de clientes usando um ID sequencial gerado automaticamente.
* **Transferências Seguras:** Execução e validação de transferências de dinheiro entre contas diferentes, com verificação de saldo e impedimento de auto-transferência.
* **Remoção de Contas:** Exclusão segura de registros de usuários mantendo a integridade da estrutura e evitando vazamentos de memória.
* **Persistência Básica:** Salvamento e exportação automática de todos os dados das contas para um arquivo de texto (`Usuarios.txt`) ao encerrar o programa.

---

## 💻 Tecnologias e Conceitos Aplicados
* **Linguagem:** C
* **Conceitos Principais:**
  * Estruturas (`struct`).
  * Ponteiros duplos e passagem por referência.
  * Alocação Dinâmica de Memória (`realloc`, `free`)
  * Manipulação de Strings (`strcspn`)
  * Manipulação de Entrada/Escrita de Arquivos (`FILE`)

---

## 👤 Autor
* **Pedro Artur Barberá Sarni**

---

## 🚀 Como Executar

Para compilar e rodar este projeto localmente, certifique-se de ter um compilador C (como o GCC) instalado.

1. Clone o repositório:
```bash
git clone [https://github.com/PedroSarni/uaibank.git](https://github.com/PedroSarni/uaibank.git)
```

2. Compile o código:
```bash
gcc UAIBANK.c -o uaibank
```

3. Execute o executável:
```bash
./uaibank
```
