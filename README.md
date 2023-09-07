# AlgorithmCYK

Голуб Алла Б05-123

### Инструкция по запуску: 
```cd FormalLanguagesAlgorithmCYK ```  
```mkdir build```  
```cmake --DCMAKE_BUILD_TYPE=Coverage .. ```  
```make all```   
```make testing ```
```make coverage```


Для удобства в одну строчку:  
```cd FormalLanguagesAlgorithmCYK && mkdir build && cd build && cmake --DCMAKE_BUILD_TYPE=Coverage .. && make all && make testing && make coverage```

### Инструкция  по использованию:

1. Ввести количество правил задающих грамматику и количество слов, которые будут проверятся на принадлежность грамматике.

2. Ввести правила, задающие грамматику. Стартовым терминалом является S.

Правила КС-грамматики вводятся в формате: 

S→aB

A→aBBB

B→e(пустое слово — e)

3. Ввести слова, которые будут проверятся на принадлежность грамматике.
