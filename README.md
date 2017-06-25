# projetoTP1_2
Projeto final disciplina Técnicas de Programação 1 

O reconhecimento facial é uma das técnicas mais utilizadas na biometria tanto para a segurança da informação como para segurança de nossa sociedade. 

Este trabalho implementa um software que reconhece uma imagem retirada através de um webcam ou câmera para reconhecer suas características e compará-las com as de um banco de dados. 

Foi utilizada a biblioteca OpenCV, biblioteca para a utilização de processamento de imagens de grande eficácia e por obter excelentes resultados no reconhecimento de características utilizando os HaarCascade. O software foi
desenvolvido em c++.

> Versões utilizadas: ...


## Diagrama Casos de uso

Esse diagrama foi feito pensando nos principais atores presentes no laboratório.
É também uma ideia inicial de modelagem do banco de dados.

![Diagrama casos de uso](diagrama_casos_de_uso.png)

Fonte:

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

Descreve o parte do sistema de reconhecimento de faces para permitir a entrada ou cadastrar uma pessoa no linf.

![Diagrama atividade](diagrama_atividade.png)

Fonte:

https://yuml.me/diagram/nofunky/activity/samples

```
(start)->(Reconhecer_Face)-><a>[Ok]->(Permite_Acesso_Linf),
<a>[Nao_identificado]->(Digita_login_senha)->(Atualiza_Cadastro)->(Permite_Acesso_Linf)->(end)
```

##  Diagram de Sequência

Primeiro diagrama de sequência 

![Diagrama de sequencia](diagrama_sequencia.png)

Fonte:

https://www.websequencediagrams.com/

```
title Sistema Trabalho 2
User->SGBD: informar número de matrícula
alt Matrícula encontrada
    SGBD->SYSTEM: retorna fotos do User
    User->SYSTEM: captura uma foto
    SYSTEM->User: reconhece foto
    alt foto Não reconhecida
        User->SYSTEM: captura foto
        SYSTEM->SGBD: armazena nova foto
    end
else Matrícula não encontrada
    SGBD->User: cadastrar_User()
    User->SGBD: informa dados()
    User->SYSTEM: captura fotos()
    SYSTEM->SGBD: armazena fotos()
end
SYSTEM->User: Validar User
```
