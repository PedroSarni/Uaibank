# 🏦 UAIBANK — Sistema Bancário em C

UAIBANK é um projeto pessoal de evolução em C. Seu ponto de partida foi um exercício proposto na disciplina de Laboratório de Introdução à Ciência de Computação I (SSC0502), no ICMC-USP, cuja versão inicial era propositalmente simples e continha apenas um arquivo de código (`UAIBANK.c`) e um arquivo de usuários (`Usuarios.txt`).

A partir dessa base, desenvolvi esta versão de forma independente para praticar e ampliar meus conhecimentos. O projeto passou a ter uma estrutura organizada, persistência em CSV, novas operações bancárias, documentação e recuperação de senha por e-mail. A proposta acadêmica foi o início; esta implementação representa a continuidade do meu desenvolvimento pessoal.

## Funcionalidades

- Cadastro individual ou múltiplo de usuários.
- Busca de usuário por ID e validação de senha.
- Transferências entre contas, com validação de saldo e bloqueio de auto-transferência.
- Remoção de contas.
- Salvamento de usuários e transferências em arquivos CSV.
- Recuperação de senha por código de verificação enviado por e-mail.

## Estrutura

- `src/`: código-fonte em C.
- `scripts/`: automações em Python, incluindo o envio de e-mail.
- `data/`: arquivos CSV gerados pelo programa.
- `docs/`: documentação e relatório de arquitetura.
- `build/`: executável compilado; é recriado automaticamente e não é versionado.
- `main.ipynb`: notebook do projeto.

## Tecnologias e conceitos

- C e GCC.
- Estruturas (`struct`), ponteiros e alocação dinâmica com `realloc`.
- Manipulação de strings e arquivos (`FILE`).
- Python e SMTP para o envio do código de recuperação.

## Como executar

Pré-requisitos: GCC, `make` e Python 3.

Para usar a recuperação de senha por e-mail, configure uma conta remetente e uma senha de aplicativo do Gmail no terminal. Não inclua essa senha em arquivos enviados ao GitHub.

```bash
export UAIBANK_EMAIL_REMETENTE="seuemail@gmail.com"
export UAIBANK_SENHA_APP="sua-senha-de-aplicativo"
```

```bash
git clone https://github.com/PedroSarni/Uaibank.git
cd Uaibank
make run
```

Para apenas compilar:

```bash
make build
```

## Documentação

O relatório e os fluxogramas da primeira versão do projeto estão em [docs/UAIBANK_Architecture_Report.pdf](docs/UAIBANK_Architecture_Report.pdf).

## Autor

Pedro Artur Barberá Sarni
