# Sistema de Caching usando Heap

PS: Heap é a estrutura de dados utilizada para implementar uma **Fila de Prioridade**.

## Ideia geral

Um sistema de cache baseado em tempo e uma capacidade.
Para facilitar a visualização, criei uma classe User, que servirá de exemplo.

Com isso posso determinar (por construtor) a capacidade e o intervalo de tempo em que os objetos (User) expiram.
Se o cache estiver cheio e o objeto mais velho (timestamp) não estiver expirado, apenas retiro ele do Heap. Caso contrário faço o mesmo teste com o próximo mais velho.

## Motivação

Esse projeto bem pequeno é para mostrar que o conhecimento básico de estrutura de dados (e das ferramentas da linguagem) podem evitar a implementação não ótima, mesmo que ela seja muito fácil de codificar.

*Evita que façamos um sistema de cache com uma tabela hashing usando uma lista duplamente encadeada como estrutura de busca.*
