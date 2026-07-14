# Jogo da Vida em DOS (C)

Trata-se de uma implementação do "Jogo da Vida de Conway" para o MS-DOS, desenvolvida em C, que utiliza programação gráfica com VGA (Modo 13h - 320x200, 256 cores).

Este repositório serve como registo da minha evolução técnica e dos experimentos realizados nesta área.


# Objetivos

- Aperfeiçoar os conhecimentos de programação de baixo nível;
- Compreender melhor o funcionamento da comunicação direta com o hardware.
- Praticar a manipulação de memória e estruturas de dados em C.
- Desenvolver uma implementação própria do "Jogo da Vida", sem recorrer a bibliotecas gráficas modernas.
- Documentar a minha evolução e os meus experimentos com o desenvolvimento para o DOS.

---

Tecnologias:

- Linguagem: C
- Plataforma: MS-DOS
- Modo gráfico: VGA Mode 13h (320x200, 256 cores)
- Compilador: Open Watcom V2
- Emulador: DOSBox

---

Funcionalidades:

- Implementação do algoritmo do Jogo da Vida de Conway;
- Renderização com acesso direto ao modo gráfico VGA;
- Atualização do tabuleiro em tempo real;

---

Sobre a implementação:

Este projeto foi desenvolvido com o objetivo de compreender os conceitos envolvidos na programação para DOS, em vez de otimizar o desempenho.

Embora existam técnicas mais eficientes para a renderização e a atualização da tela, como a utilização de back buffers na RAM e algoritmos mais otimizados para o desenho de pixels, optei por implementar grande parte da lógica manualmente, a fim de compreender melhor o funcionamento interno do hardware gráfico e da linguagem C.

Por conseguinte, algumas partes do código poderão ser aprimoradas no futuro, mas foram mantidas. 


<img width="637" height="422" alt="image" src="https://github.com/user-attachments/assets/7a2e2e29-bcee-4c51-8d53-bae4f3905d08" />
