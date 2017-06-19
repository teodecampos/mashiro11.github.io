# projetoTP1_2
Projeto final disciplina Técnicas de Programação 1 

## Diagrama Casos de uso

Esse diagrama foi feito pensando nos principais atores presentes no laboratório.
É tambm uma ideia inicial de modelagem do banco de dados.

![Diagrama casos de uso](diagrama_casos_de_uso.png)

Código fonte:

https://yuml.me/diagram/scruffy/usecase/samples

```
[Professor]-(Reservar laboratório)
[Professor]-(Acessar laboratório)
[Professor]-(Criar cadastro de acesso)
[Aluno]-(Criar cadastro de acesso)
[Aluno]-(Acessar laboratório)
[Funcionário]-(Criar cadastro de acesso)
[Funcionário]-(Acessar laboratório)
[Funcionário]-(Modificar cadastro de acesso)
[Funcionário]-(Excluir cadastro de acesso)
```

## Diagrama de Atividades

Descreve o sistema de reconhecimento de faces para permitir a entrada ou cadastrar uma pessoa no linf.

![Diagrama atividade](diagrama_atividade.png)

Código fonte:

https://yuml.me/diagram/nofunky/activity/samples

```
(start)->(Reconhecer_Face)-><a>[Ok]->(Permite_Acesso_Linf),
<a>[Nao_identificado]->(Digita_login_senha)->(Atualiza_Cadastro)->(Permite_Acesso_Linf)->(end)
```
